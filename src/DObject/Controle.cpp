///*
//
//	-----------------------------------------------------------------------
//
//	 Fichier		: 	Controle.cpp
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe de test
//
//	-----------------------------------------------------------------------
//	 Révisions		:	16/7/2014 : 
//	-----------------------------------------------------------------------
//*/

// Inclusions
#include "Stdafx.h"
#include "DObject\Controle.h"

// Inclusions
#include <SQLite/SQLiteSource.h>
#include <Poco/NumberFormatter.h>
#include <RcReader/RcReader.h>


namespace GDSObject
{
	//! Constructeur
	CControle::CControle(unsigned long ulId) : CDObjBase(ulId)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Destructeur
	CControle::~CControle(void)
	{
		//
		RemoveEnfants();

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Constructeur par copie.
	CControle::CControle(const CControle &source)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CControle & CControle::operator=(const CControle &source)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);

		return *this;
	}

	//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
	void CControle::ClonnerDonnees(const CControle &source)
	{
		CDObjBase::ClonnerDonnees(source);

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Copie des variables membres de l'objet. */
		m_sLibelle = source.m_sLibelle;
		m_sType = source.m_sType;
		m_ulResdent = source.m_ulResdent;
	}

	//! Initialisation des données membres de la classe
	void CControle::InitialiserDonnees()
	{
		m_sLibelle = std::string();
		m_sType = std::string();
		m_ulResdent = DefULong;
		m_bExclu = false;
	}

	//! Initialisation de l'objet
	bool CControle::Initialiser()
	{
		if (DoitEtreInitialiser() == false) return true;

		// Initialisation depuis la base
		if (!EstAcquis() && m_ulId!=DefULong)
		{
			std::ostringstream osQuery;
			osQuery << "select CTR_RES_IDENT, CTR_LIBELLE, CTR_TYPE, CTR_EXCLU from CONTROLE where RES_IDENT = " << ToQuery(m_ulId);
			
			SQLite::Statement query(*CSQLiteSource::database(), osQuery.str());
			if (query.executeStep())
			{
				m_ulResdent		= query.getColumn(0).getInt();
				m_sLibelle		= query.getColumn(1).getText();
				m_sType			= query.getColumn(2).getText();
				m_bExclu		= query.getColumn(3).getInt();

				// L'objet est acquis
				SetAcquis();
			}
		}

		// L'objet est initialisé
		SetInitaliser();

		return true;
	}

	bool CControle::Verifier(std::string* sMsg)
	{
		// Les objets qui dépendent de cette objet ne doivent
		// pas être vérifiés lors de la création.
		if (!EstNouveau())
		{
		}

		if (!Initialiser())				{ if (sMsg) sMsg->assign("Erreur lors de l'initialisation."); return false; }
		if (m_sLibelle.empty())			{ if (sMsg) sMsg->assign("Erreur : m_sLibelle est vide."); return false; }
		if (m_sType.empty())			{ if (sMsg) sMsg->assign("Erreur : m_sType est vide."); return false; }
		if (m_ulResdent==DefULong)		{ if (sMsg) sMsg->assign("Erreur : m_ulResdent est vide."); return false; }

		return true;
	}

	bool CControle::Sauver()
	{
		if (!(DoitEtreSauver() || DoitEtreSupprimer())) return true;
		if (!(PeutEtreSauver() || PeutEtreSupprimer())) return false;

		// Mémorisation de l'etat de l'objet avant sauvegarde
		DObject::CDObjState state(this);

		// Gestion automatique des transactions
		__TRANSACTION_AUTO_DEBUT__;

		// Sauvegarde de l'objet
		if (EstModifier())
		{
			if (!Verifier())
			{
				// Restauration de l'état précédent
				state.Restore();
				// Fin de la transaction automatique
				__TRANSACTION_AUTO_ANNULE__;
				return false;
			}

			try
			{
				if (EstNouveau())
				{
					std::ostringstream osQuery;
					osQuery << "insert into CONTROLE (CTR_IDENT, CTR_RES_IDENT, CTR_LIBELLE, CTR_TYPE, CTR_EXCLU)";
					osQuery << " values (";
					osQuery << "	" << ToQuery(DefULong) << ",";
					osQuery << "	" << ToQuery(m_ulResdent) << ",";
					osQuery << "	" << ToQuery(m_sLibelle) << ",";
					osQuery << "	" << ToQuery(m_sType) << ",";
					osQuery << "	" << ToQuery(m_bExclu) << "";
					osQuery << ");";

					CSQLiteSource::database()->exec(osQuery.str());

					m_ulId = static_cast<unsigned long>(CSQLiteSource::database()->getLastInsertRowid());
				}

				else if (EstModifier())
				{
					std::ostringstream osQuery;
					osQuery << "update CONTROLE set";
					osQuery << "	CTR_RES_IDENT = "	<< ToQuery(m_ulResdent) << ",";
					osQuery << "	CTR_LIBELLE = "		<< ToQuery(m_sLibelle) << ",";
					osQuery << "	CTR_TYPE = "		<< ToQuery(m_sType) << ",";
					osQuery << "	CTR_EXCLU = "		<< ToQuery(m_bExclu) << " ";
					osQuery << "where";
					osQuery << "	CTR_IDENT = "		<< ToQuery(m_ulId) << ";";

					CSQLiteSource::database()->exec(osQuery.str());
				}

				// L'objet est acquis
				SetAcquis();
			}
			catch (SQLite::Exception& e)
			{
				Poco::Logger::get("SQLiteException").debug(e.what());
				// Restauration de l'état précédent
				state.Restore();
				// Fin de la transaction automatique
				__TRANSACTION_AUTO_ANNULE__;
				return false;
			}
		}

		//
		if (!SontEnfantsModifier())
		{
			// Fin de la transaction automatique
			__TRANSACTION_AUTO_VALIDE__;
			return true;
		}

		// Fin de la transaction automatique
		__TRANSACTION_AUTO_VALIDE__;

		return true;
	}

	bool CControle::Supprimer()
	{
		if (DoitEtreSupprimer() == false) { SetSupprimer(true);  return true; }
		if (PeutEtreSupprimer() == false) { SetSupprimer(false); return false; }

		// Mémorisation de l'etat de l'objet avant sauvegarde
		DObject::CDObjState state(this);

		// Gestion automatique des transactions
		__TRANSACTION_AUTO_DEBUT__;

		try
		{
			std::ostringstream osQuery;
			osQuery << "delete from CONTROLE where CTR_IDENT = " << ToQuery(m_ulId);

			SQLite::Statement query(*CSQLiteSource::database(), osQuery.str());
			query.exec();
		}
		catch (SQLite::Exception& e)
		{
			Poco::Logger::get("SQLiteException").debug(e.what());
			// Restauration de l'état précédent
			state.Restore();
			// Fin de la transaction automatique
			__TRANSACTION_AUTO_ANNULE__;
			return false;
		}

		// Fin de la transaction automatique
		__TRANSACTION_AUTO_VALIDE__;

		// L'objet est supprimé
		SetSupprimer();

		return true;
	}

	std::string CControle::GetLibelle()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return std::string();

		return m_sLibelle;
	}

	bool CControle::SetLibelle(std::string sName)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_sLibelle != sName)
		{
			// Affectation de la nouvelle valeur.
			m_sLibelle = sName;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	std::string CControle::GetType()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return std::string();

		return m_sType;
	}

	bool CControle::SetType(std::string sType)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_sType != sType)
		{
			// Affectation de la nouvelle valeur.
			m_sType = sType;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	unsigned long CControle::GetResIdent()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return DefULong;

		return m_ulResdent;
	}

	bool CControle::SetResIdent(unsigned long ulResIdent)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_ulResdent != ulResIdent)
		{
			// Affectation de la nouvelle valeur.
			m_ulResdent = ulResIdent;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	bool CControle::GetExclu()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		return m_bExclu;
	}

	bool CControle::SetExclu(bool bExclu)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_bExclu != bExclu)
		{
			// Affectation de la nouvelle valeur.
			m_bExclu = bExclu;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	GDSObject::ControleType CControle::GetControleType()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return ControleType::Inconnu;

		//
		if(m_controlType != ControleType::Inconnu)
			return m_controlType;

		// Détermine le type de controle
		RcReader::RcControlType rcControleType = RcReader::CRcControle::ToRcControlType(m_sType);
		switch(rcControleType)
		{
			// Generic Control (recensés à ce jour 08/01/2015)
			case RcReader::RcControlType::Button :				m_controlType = ControleType::Boutton;					break;
			case RcReader::RcControlType::MfcButton :			m_controlType = ControleType::MfcButton;				break;
			case RcReader::RcControlType::MfcColorButton :		m_controlType = ControleType::MfcColorButton;			break;
			case RcReader::RcControlType::MfcEditBrowse :		m_controlType = ControleType::MfcEditBrowse;			break;
			case RcReader::RcControlType::MfcFontComboBox :		m_controlType = ControleType::MfcFontComboBox;			break;
			case RcReader::RcControlType::MfcLink :				m_controlType = ControleType::MfcLink;					break;
			case RcReader::RcControlType::MfcMaskedEdit :		m_controlType = ControleType::MfcMaskedEdit;			break;
			case RcReader::RcControlType::MfcMenuButton :		m_controlType = ControleType::MfcMenuButton;			break;
			case RcReader::RcControlType::MfcPropertyGrid :		m_controlType = ControleType::MfcPropertyGrid;			break;
			case RcReader::RcControlType::MfcShellList :		m_controlType = ControleType::MfcShellList;				break;
			case RcReader::RcControlType::MfcVSListBox :		m_controlType = ControleType::MfcVsListBox;				break;
			case RcReader::RcControlType::msctls_netaddress :	m_controlType = ControleType::NetworkAdress;			break;
			case RcReader::RcControlType::msctls_progress32 :	m_controlType = ControleType::Progress;					break;
			case RcReader::RcControlType::msctls_trackbar32 :	m_controlType = ControleType::Slider;					break;
			case RcReader::RcControlType::RichEdit20W :			m_controlType = ControleType::RichEdit;					break;
			case RcReader::RcControlType::Static :				m_controlType = ControleType::StaticText;				break;
			case RcReader::RcControlType::SysAnimate32 :		m_controlType = ControleType::Animation;				break;
			case RcReader::RcControlType::SysDateTimePick32 :	m_controlType = ControleType::DateTimePicker;			break;
			case RcReader::RcControlType::SysIPAddress32 :		m_controlType = ControleType::IpAdress;					break;
			case RcReader::RcControlType::SysLink :				m_controlType = ControleType::Syslink;					break;
			case RcReader::RcControlType::SysListView32 :		m_controlType = ControleType::List;						break;
			case RcReader::RcControlType::SysMonthCal32 :		m_controlType = ControleType::MontCalendar;				break;
			case RcReader::RcControlType::SysTabControl32 :		m_controlType = ControleType::Tab;						break;
			case RcReader::RcControlType::SysTreeView32 :		m_controlType = ControleType::Tree;						break;

			// Static Control
 			case RcReader::RcControlType::LTEXT:				m_controlType = ControleType::StaticText;				break;
 			case RcReader::RcControlType::RTEXT :				m_controlType = ControleType::StaticText;				break;
 			case RcReader::RcControlType::CTEXT :				m_controlType = ControleType::StaticText;				break;

			// Button Control
 			case RcReader::RcControlType::AUTO3STATE :			m_controlType = ControleType::CheckBox;					break;
 			case RcReader::RcControlType::AUTOCHECKBOX :		m_controlType = ControleType::CheckBox;					break;
 			case RcReader::RcControlType::AUTORADIOBUTTON :		m_controlType = ControleType::RadioButton;				break;
 			case RcReader::RcControlType::CHECKBOX :			m_controlType = ControleType::CheckBox;					break;
 			case RcReader::RcControlType::PUSHBOX :				m_controlType = ControleType::Boutton;					break;
 			case RcReader::RcControlType::PUSHBUTTON :			m_controlType = ControleType::Boutton;					break;
 			case RcReader::RcControlType::DEFPUSHBUTTON :		m_controlType = ControleType::Boutton;					break;
 			case RcReader::RcControlType::RADIOBUTTON :			m_controlType = ControleType::RadioButton;				break;
 			case RcReader::RcControlType::STATE3 :				m_controlType = ControleType::CheckBox;					break;
 			case RcReader::RcControlType::USERBUTTON :			m_controlType = ControleType::Boutton;					break;
 			case RcReader::RcControlType::SPLITBUTTON :			m_controlType = ControleType::SplitButton;				break;
 			case RcReader::RcControlType::COMMANDLINK :			m_controlType = ControleType::CommandButton;			break;

			// Edit Control
 			case RcReader::RcControlType::EDITTEXT:				m_controlType = ControleType::Edit;						break;
 			case RcReader::RcControlType::BEDIT :				m_controlType = ControleType::Edit;						break;
 			case RcReader::RcControlType::HEDIT :				m_controlType = ControleType::Edit;						break;
 			case RcReader::RcControlType::IEDIT :				m_controlType = ControleType::Edit;						break;

			// Combo Control
 			case RcReader::RcControlType::COMBOBOX:				m_controlType = ControleType::ComboBox;					break;

			// GroupBox Control
 			case RcReader::RcControlType::GROUPBOX:				m_controlType = ControleType::GroupBox;					break;

			// ListBox Control
 			case RcReader::RcControlType::LISTBOX:				m_controlType = ControleType::ListBox;					break;

			// Icon Control
 			case RcReader::RcControlType::ICON:					m_controlType = ControleType::Image;					break;


			// Icon Control
 			case RcReader::RcControlType::SCROLLBAR:			m_controlType = ControleType::ScrollBarHorizontal;		break;

			default:											m_controlType = ControleType::Inconnu;					break;
		}

		return m_controlType;
	}











	//! Constructeur
	CControleListe::CControleListe()
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Destructeur
	CControleListe::~CControleListe(void)
	{
		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Constructeur par copie.
	CControleListe::CControleListe(const CControleListe &source)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CControleListe & CControleListe::operator=(const CControleListe &source)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);

		return *this;
	}

	//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
	void CControleListe::ClonnerDonnees(const CControleListe &source)
	{
		/* Copie des éléments de la liste */
		__super::ClonnerDonnees(source);

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Copie des variables membres de l'objet. */
		m_ulResIdent = source.m_ulResIdent;

		/* Copie des pointeurs membres de l'objet. */
	}

	//! Initialisation des données membres de la classe
	void CControleListe::InitialiserDonnees()
	{
		m_ulResIdent = DefULong;
	}

	//! Initialisation de la liste d'objet
	bool CControleListe::Initialiser()
	{
		if (DoitEtreInitialiser() == false) return true;
		if (PeutEtreInitialiser() == false) return false;

		// Initialisation depuis la base
		if (!EstAcquis())
		{
			std::ostringstream osQuery;
			osQuery << "select CTR_IDENT, CTR_RES_IDENT, CTR_LIBELLE, CTR_TYPE, CTR_EXCLU from CONTROLE";

			SQLite::Statement query(*CSQLiteSource::database(), osQuery.str());
			while (query.executeStep())
			{
				CControle* pControle		= new CControle(query.getColumn(0).getInt());
				pControle->m_ulResdent		= query.getColumn(1).getInt();
				pControle->m_sLibelle		= query.getColumn(2).getText();
				pControle->m_sType			= query.getColumn(3).getText();
				pControle->m_bExclu			= query.getColumn(4).getInt();

				// L'objet est acquis
				pControle->SetAcquis();

				Add(pControle);
			}

			// L'objet est acquis
			if (GetSize()) SetAcquis();
		}

		// L'objet est initialisé
		SetInitaliser();

		return true;
	}

	//! Verification
	bool CControleListe::Verifier(std::string* sMsg)
	{
		// Vérifications de base
		return CDObjListe::Verifier(sMsg);
	}

	//! Sauvegarde
	bool CControleListe::Sauver()
	{
		if (!(DoitEtreSauver() || DoitEtreSupprimer())) return true;
		if (!(PeutEtreSauver() || PeutEtreSupprimer())) return false;

		// Gestion automatique des transactions
		__TRANSACTION_AUTO_DEBUT__;

		// Sauvegarde des objets
		if (!CDObjListe::Sauver())
		{
			// Fin de la transaction automatique
			__TRANSACTION_AUTO_ANNULE__;
			return false;
		}

		// Fin de la transaction automatique
		__TRANSACTION_AUTO_VALIDE__;

		// Les objets sont acquis
		SetAcquis();

		return true;
	}

	//! Suppression
	bool CControleListe::Supprimer()
	{
		if (DoitEtreSupprimer() == false) return true;
		if (PeutEtreSupprimer() == false) return false;

		// Gestion automatique des transactions
		__TRANSACTION_AUTO_DEBUT__;

		// Suppression des objets
		if (!CDObjListe::Supprimer())
		{
			// Fin de la transaction automatique
			__TRANSACTION_AUTO_ANNULE__;
			return false;
		}

		// Fin de la transaction automatique
		__TRANSACTION_AUTO_VALIDE__;


		// Les objets sont supprimés
		SetSupprimer();

		return true;
	}

	bool CControleListe::InitialiserAPartirDeResIdent(unsigned long ulResIdent)
	{
		if (DoitEtreInitialiser() == false) return true;
		if (PeutEtreInitialiser() == false) return false;

		//! Initialisation des données membres de la classe
		InitialiserDonnees();
		
		m_ulResIdent = ulResIdent;

		// Initialisation depuis la base
		if (!EstAcquis())
		{
			std::ostringstream osQuery;
			osQuery << "select CTR_IDENT, CTR_RES_IDENT, CTR_LIBELLE, CTR_TYPE, CTR_EXCLU from CONTROLE where CTR_RES_IDENT = " << ToQuery(ulResIdent) << " order by CTR_IDENT";

			SQLite::Statement query(*CSQLiteSource::database(), osQuery.str());
			while (query.executeStep())
			{
				CControle* pControle		= new CControle(query.getColumn(0).getInt());
				pControle->m_ulResdent		= query.getColumn(1).getInt();
				pControle->m_sLibelle		= query.getColumn(2).getText();
				pControle->m_sType			= query.getColumn(3).getText();
				pControle->m_bExclu			= query.getColumn(4).getInt();

				// L'objet est acquis
				pControle->SetAcquis();

				Add(pControle);
			}

			// L'objet est acquis
			if (GetSize()) SetAcquis();
		}

		// L'objet est initialisé
		SetInitaliser();

		return true;
	}

	unsigned long CControleListe::GetResIdent()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return DefULong;

		return m_ulResIdent;
	}

	bool CControleListe::SetResIdent(unsigned long ulResIdent)
	{
		if (!Initialiser()) return false;

		// Mise à jour de la variable
		if (m_ulResIdent != ulResIdent)
		{
			m_ulResIdent = ulResIdent;
			SetModifier();
		}

		// Mise à jour de la liste
		for (int i = 0; i < GetSize(); i++)
			if (GetAt(i)->SetResIdent(ulResIdent) == false)
				return false;

		return true;
	}

}
