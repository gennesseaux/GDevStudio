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
#include "GyResGen/DObject/Controle.h"
#include "GyResGen/DObject/SQLiteHelper.h"

// Inclusion des namespaces
using namespace SQLite;

namespace GyResGen
{
	//! Constructeur
	CControle::CControle(unsigned long ulId /*= DefULong*/, CDObject* pOwner /*= nullptr*/) : CDObjBase(ulId,pOwner)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Destructeur
	CControle::~CControle(void)
	{
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
		m_sClasseNom = source.m_sClasseNom;
		m_sVariableNom = source.m_sVariableNom;
	}

	//! Initialisation des données membres de la classe
	void CControle::InitialiserDonnees()
	{
		m_sClasseNom = std::string();
		m_sVariableNom = std::string();
	}

	//! Initialisation de l'objet
	bool CControle::Initialiser()
	{
		if (DoitEtreInitialiser() == false) return true;

		// Initialisation depuis la base
		if (!EstAcquis() && m_ulId!=DefULong)
		{
			std::ostringstream osQuery;
			osQuery << "select CTR_CLASSE_NOM, CTR_VARIABLE_NOM from GRG_CONTROLE where CTR_IDENT = " << ToQuery(m_ulId);
			
			SQLite::Statement query(*CSQLiteHelper::Database(), osQuery.str());
			if (query.executeStep())
			{
				m_sClasseNom		= query.getColumn(0).isNull() ? std::string() : query.getColumn(0).getText();
				m_sVariableNom		= query.getColumn(1).isNull() ? std::string() : query.getColumn(1).getText();

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

		return true;
	}

	bool CControle::Sauver()
	{
		// L'objet n'est pas modifié
		if ( !(DoitEtreSauver() || DoitEtreSupprimer()) ) return true;
		// L'objet est supprimé
		if ( !(PeutEtreSauver() || PeutEtreSupprimer()) ) return false;
		// L'objet est à supprimer
		if ( DoitEtreSupprimer() ) return Supprimer();

		// SaveGuard
		DObject::DObjSaveGuard::Start(this);

		// Gestion automatique des transactions
		__TRANSACTION_AUTO_DEBUT__(CSQLiteHelper::Transaction());

		// Sauvegarde de l'objet
		if (EstModifier())
		{
			if (!Verifier())
			{
				// Fin de la transaction automatique
				__TRANSACTION_AUTO_ANNULE__;
				return DObject::DObjSaveGuard::Error(this);
			}

			try
			{
				if (EstNouveau())
				{
					std::ostringstream osQuery;
					osQuery << "insert into GRG_CONTROLE (CTR_IDENT, CTR_CLASSE_NOM, CTR_VARIABLE_NOM)";
					osQuery << " values (";
					osQuery << "	" << ToQuery(m_ulId) << ",";
					osQuery << "	" << ToQuery(m_sClasseNom) << ",";
					osQuery << "	" << ToQuery(m_sVariableNom) << " ";
					osQuery << ");";

					CSQLiteHelper::Database()->exec(osQuery.str());
				}

				else if (EstModifier())
				{
					std::ostringstream osQuery;
					osQuery << "update GRG_CONTROLE set";
					osQuery << "	CTR_CLASSE_NOM = "			<< ToQuery(m_sClasseNom) << ",";
					osQuery << "	CTR_VARIABLE_NOM = "		<< ToQuery(m_sVariableNom) << " ";
					osQuery << "where";
					osQuery << "	CTR_IDENT = "				<< ToQuery(m_ulId) << ";";

					CSQLiteHelper::Database()->exec(osQuery.str());
				}

				// L'objet est acquis
				SetAcquis();
			}
			catch (SQLite::Exception& e)
			{
				Poco::Logger::get("SQLiteException").debug(e.what());

				// Fin de la transaction automatique
				__TRANSACTION_AUTO_ANNULE__;
				return DObject::DObjSaveGuard::Error(this);
			}
		}

		//
		if (!SontEnfantsModifier())
		{
			// Fin de la transaction automatique
			__TRANSACTION_AUTO_VALIDE__;
			return DObject::DObjSaveGuard::Sucess(this);
		}

		// Fin de la transaction automatique
		__TRANSACTION_AUTO_VALIDE__;

		return DObject::DObjSaveGuard::Sucess(this);
	}

	bool CControle::Supprimer()
	{
		if (DoitEtreSupprimer() == false) return true;
		if (PeutEtreSupprimer() == false) return false;

		// SaveGuard
		DObject::DObjSaveGuard::Start(this);

		// Gestion automatique des transactions
		__TRANSACTION_AUTO_DEBUT__(CSQLiteHelper::Transaction());

		try
		{
			std::ostringstream osQuery;
			osQuery << "delete from GRG_CONTROLE where CTR_IDENT = " << ToQuery(m_ulId);

			SQLite::Statement query(*CSQLiteHelper::Database(), osQuery.str());
			query.exec();
		}
		catch (SQLite::Exception& e)
		{
			Poco::Logger::get("SQLiteException").debug(e.what());

			// Fin de la transaction automatique
			__TRANSACTION_AUTO_ANNULE__;
			return DObject::DObjSaveGuard::Error(this);
		}

		// Fin de la transaction automatique
		__TRANSACTION_AUTO_VALIDE__;

		// L'objet est supprimé
		SetSupprimer();

		return DObject::DObjSaveGuard::Sucess(this);
	}
	
	void CControle::OnSupprimer(CDObject* pDObject,CDObject* sender)
	{
	}

	std::string CControle::GetDefClasseNom()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return std::string();

		//
		GDSAPI::CControle* pControle = (GDSAPI::CControle*)GetOwner();
		assert(pControle);

		//
		switch(pControle->GetControleType())
		{
			// Generic Control (recensés à ce jour 08/01/2015)
			case GDSAPI::ControleType::MfcButton:				return "CMFCButton";
			case GDSAPI::ControleType::MfcColorButton:			return "CMFCButton";
			case GDSAPI::ControleType::MfcEditBrowse:			return "CMFCEditBrowseCtrl";
			case GDSAPI::ControleType::MfcFontComboBox:			return "CMFCFontComboBox";
			case GDSAPI::ControleType::MfcLink:					return "CMFCLinkCtrl";
			case GDSAPI::ControleType::MfcMaskedEdit:			return "CMFCMaskedEdit";
			case GDSAPI::ControleType::MfcMenuButton:			return "CMFCMenuButton";
			case GDSAPI::ControleType::MfcPropertyGrid:			return "CMFCPropertyGridCtrl";
			case GDSAPI::ControleType::MfcShellList:			return "CMFCShellListCtrl";
			case GDSAPI::ControleType::MfcVsListBox:			return "CMFCListCtrl";
			case GDSAPI::ControleType::NetworkAdress:			return "CNetAddressCtrl";
			case GDSAPI::ControleType::Progress:				return "CProgressCtrl";
			case GDSAPI::ControleType::Slider:					return "CSliderCtrl";
			case GDSAPI::ControleType::RichEdit:				return "CRichEditCtrl";
			case GDSAPI::ControleType::Animation:				return "CAnimateCtrl";
			case GDSAPI::ControleType::DateTimePicker:			return "CDateTimeCtrl";
			case GDSAPI::ControleType::IpAdress:				return "CIPAddressCtrl";
			case GDSAPI::ControleType::Syslink:					return "CLinkCtrl";
			case GDSAPI::ControleType::List:					return "CListCtrl";
			case GDSAPI::ControleType::MontCalendar:			return "CMonthCalCtrl";
			case GDSAPI::ControleType::Tab:						return "CTabCtrl";
			case GDSAPI::ControleType::Tree:					return "CTreeCtrl";

			// Static Control
 			case GDSAPI::ControleType::StaticText:				return "CStatic";

			// Button Control
 			case GDSAPI::ControleType::Boutton:					return "CButton";
			case GDSAPI::ControleType::CheckBox:				return "CButton";
 			case GDSAPI::ControleType::RadioButton:				return "CButton";
 			case GDSAPI::ControleType::SplitButton:				return "CSplitButton";
 			case GDSAPI::ControleType::CommandButton:			return "CButton";

			// Edit Control
 			case GDSAPI::ControleType::Edit:					return "CEdit";

			// Combo Control
 			case GDSAPI::ControleType::ComboBox:				return "CComboBox";

			// GroupBox Control
 			case GDSAPI::ControleType::GroupBox:				return "CStatic";

			// ListBox Control
 			case GDSAPI::ControleType::ListBox:					return "CComboBox";

			// Icon Control
 			case GDSAPI::ControleType::Image:					return "CStatic";


			// Icon Control
 			case GDSAPI::ControleType::ScrollBarHorizontal:		return "CScrollBar";
 			case GDSAPI::ControleType::ScrollBarVertical:		return "CScrollBar";

			default:									return "CStatic";
		}

		return "";
	}

	std::string CControle::GetDefVariableNom()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return std::string();

		//
		std::string sName = "m_";

		//
		GDSAPI::CControle* pControle = (GDSAPI::CControle*)GetOwner();
		assert(pControle);

		//
		switch(pControle->GetControleType())
		{
			// Generic Control (recensés à ce jour 08/01/2015)
			case GDSAPI::ControleType::MfcButton:				sName += "btn";		break;
			case GDSAPI::ControleType::MfcColorButton:			sName += "btn";		break;
			case GDSAPI::ControleType::MfcEditBrowse:			sName += "edt";		break;
			case GDSAPI::ControleType::MfcFontComboBox:			sName += "cbx";		break;
			case GDSAPI::ControleType::MfcLink:					sName += "lnk";		break;
			case GDSAPI::ControleType::MfcMaskedEdit:			sName += "edt";		break;
			case GDSAPI::ControleType::MfcMenuButton:			sName += "btn";		break;
			case GDSAPI::ControleType::MfcPropertyGrid:			sName += "pgd";		break;
			case GDSAPI::ControleType::MfcShellList:			sName += "slt";		break;
			case GDSAPI::ControleType::MfcVsListBox:			sName += "lbx";		break;
			case GDSAPI::ControleType::NetworkAdress:			sName += "nad";		break;
			case GDSAPI::ControleType::Progress:				sName += "pgs";		break;
			case GDSAPI::ControleType::Slider:					sName += "sld";		break;
			case GDSAPI::ControleType::RichEdit:				sName += "ret";		break;
			case GDSAPI::ControleType::Animation:				sName += "ani";		break;
			case GDSAPI::ControleType::DateTimePicker:			sName += "dtc";		break;
			case GDSAPI::ControleType::IpAdress:				sName += "adr";		break;
			case GDSAPI::ControleType::Syslink:					sName += "lnk";		break;
			case GDSAPI::ControleType::List:					sName += "lst";		break;
			case GDSAPI::ControleType::MontCalendar:			sName += "mcd";		break;
			case GDSAPI::ControleType::Tab:						sName += "tab";		break;
			case GDSAPI::ControleType::Tree:					sName += "tre";		break;

			// Static Control
 			case GDSAPI::ControleType::StaticText:				sName += "stx";		break;

			// Button Control
 			case GDSAPI::ControleType::Boutton:					sName += "btn";		break;
			case GDSAPI::ControleType::CheckBox:				sName += "btn";		break;
 			case GDSAPI::ControleType::RadioButton:				sName += "btn";		break;
 			case GDSAPI::ControleType::SplitButton:				sName += "btn";		break;
 			case GDSAPI::ControleType::CommandButton:			sName += "btn";		break;

			// Edit Control
 			case GDSAPI::ControleType::Edit:					sName += "edt";		break;

			// Combo Control
 			case GDSAPI::ControleType::ComboBox:				sName += "cbx";		break;

			// GroupBox Control
 			case GDSAPI::ControleType::GroupBox:				sName += "gbx";		break;

			// ListBox Control
 			case GDSAPI::ControleType::ListBox:					sName += "lbx";		break;

			// Icon Control
 			case GDSAPI::ControleType::Image:					sName += "img";		break;


			// Icon Control
 			case GDSAPI::ControleType::ScrollBarHorizontal:		sName += "sbh";		break;
 			case GDSAPI::ControleType::ScrollBarVertical:		sName += "sbv";		break;

			default:									sName += "";		break;
		}

		//
		sName += IdToString();

		return sName;
	}

	std::string CControle::IdToString()
	{
		//
		GDSAPI::CControle* pControle = (GDSAPI::CControle*)GetOwner();
		assert(pControle);

		//
		bool bUpper = true;
		std::string sIdString = "";
		std::string sLibelle = pControle->GetLibelle();

		if(StringTools::starts_with(sLibelle,"IDC_"))		sLibelle = StringTools::remove_from_start(sLibelle,"IDC_");
		else if(StringTools::starts_with(sLibelle,"ID"))	sLibelle = StringTools::remove_from_start(sLibelle,"ID");

		for(int i = 0; i < sLibelle.length(); i++)
		{
			if(bUpper)
			{
				char sChar = sLibelle.at(i);
				std::string szChar = std::string() + sChar;
				sIdString += StringTools::toUpper(szChar);
				bUpper = false;
			}
			else
			{
				if(sLibelle.at(i) == '_' || sLibelle.at(i) == '-' || sLibelle.at(i) == ' ')
				{
					bUpper = true;
					continue;
				}
				char sChar = sLibelle.at(i);
				std::string szChar = std::string() + sChar;
				sIdString += StringTools::toLower(szChar);
			}
		}

		return sIdString;
	}

	std::string CControle::GetClasseNom()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return std::string();

		if(m_sClasseNom.empty()) return GetDefClasseNom();

		return m_sClasseNom;
	}

	bool CControle::SetClasseNom(std::string sClasseNom)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Nom par défaut
		if(sClasseNom.empty()) sClasseNom = GetDefClasseNom();

		// Le champ est modifié uniquement si sa valeur change.
		if (m_sClasseNom != sClasseNom)
		{
			// Affectation de la nouvelle valeur.
			m_sClasseNom = sClasseNom;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	std::string CControle::GetVariableNom()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return std::string();

		if(m_sVariableNom.empty()) return GetDefVariableNom();

		return m_sVariableNom;
	}

	bool CControle::SetVariableNom(std::string sVariableNom)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;
		
		// Variable par défaut
		if(sVariableNom.empty()) sVariableNom = GetDefVariableNom();

		// Le champ est modifié uniquement si sa valeur change.
		if (m_sVariableNom != sVariableNom)
		{
			// Affectation de la nouvelle valeur.
			m_sVariableNom = sVariableNom;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

}
