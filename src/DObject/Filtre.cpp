///*
//
//	-----------------------------------------------------------------------
//
//	 Fichier		: 	Filtre.cpp
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
#include "StdAfx.h"
#include "Filtre.h"

// Inclusions
#include <SQLite/SQLiteSource.h>
#include <Poco/NumberFormatter.h>


namespace GDSObject
{
	//! Constructeur
	CFiltre::CFiltre(unsigned long ulId) : CDObjBase(ulId)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Destructeur
	CFiltre::~CFiltre(void)
	{
		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Constructeur par copie.
	CFiltre::CFiltre(const CFiltre &source)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CFiltre & CFiltre::operator=(const CFiltre &source)
	{
		/* Clonage des données. */
		ClonnerDonnees(source);

		return *this;
	}

	//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
	void CFiltre::ClonnerDonnees(const CFiltre &source)
	{
		CDObjBase::ClonnerDonnees(source);

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Copie des variables membres de l'objet. */
		m_sLibelle = source.m_sLibelle;
		m_ulPrjIdent = source.m_ulPrjIdent;
		m_ulFtrIdent = source.m_ulFtrIdent;
		m_ptHFolder = source.m_ptHFolder;
		m_ptCppFolder = source.m_ptCppFolder;

		/* Copie des pointeurs membres de l'objet. */
	}

	//! Initialisation des données membres de la classe
	void CFiltre::InitialiserDonnees()
	{
		m_sLibelle = std::string();
		m_ulPrjIdent = DefULong;
		m_ulFtrIdent = DefULong;
		m_ptHFolder.clear();
		m_ptCppFolder.clear();
	}

	//! Initialisation de l'objet
	bool CFiltre::Initialiser()
	{
		if (DoitEtreInitialiser() == false) return true;

		// Initialisation depuis la base
		if (!EstAcquis() && m_ulId!=DefULong)
		{
			std::ostringstream osQuery;
			osQuery << "select FTR_LIBELLE, FTR_TYPE, FTR_PRJ_IDENT, FTR_FTR_IDENT, FTR_H_FOLDER, FTR_CPP_FOLDER from FILTRE where FTR_IDENT = " << ToQuery(m_ulId);
			
			SQLite::Statement query(*CSQLiteSource::database(), osQuery.str());
			if (query.executeStep())
			{
				m_sLibelle		= query.getColumn(0).getText();
				m_iType			= (FiltreType)query.getColumn(1).getInt();
				m_ulPrjIdent	= query.getColumn(1).isNull() ? DefULong : query.getColumn(1).getInt();
				m_ulFtrIdent	= query.getColumn(2).isNull() ? DefULong : query.getColumn(2).getInt();
				m_ptHFolder		= query.getColumn(3).isNull() ? Poco::Path() : query.getColumn(3).getText();
				m_ptCppFolder	= query.getColumn(5).isNull() ? Poco::Path() : query.getColumn(4).getText();

				// L'objet est acquis
				SetAcquis();
			}
		}

		// L'objet est initialisé
		SetInitaliser();

		return true;
	}

	bool CFiltre::Verifier(std::string* sMsg)
	{
		// Les objets qui dépendent de cette objet ne doivent
		// pas être vérifiés lors de la création.
		if (!EstNouveau())
		{
		}

		if (!Initialiser())				{ if (sMsg) sMsg->assign("Erreur lors de l'initialisation."); return false; }
		if (m_sLibelle.empty())			{ if (sMsg) sMsg->assign("Erreur : m_sName est vide."); return false; }
		if (m_ulPrjIdent == DefULong && m_ulFtrIdent==DefULong)	{ if (sMsg) sMsg->assign("Erreur : m_ulPrjIdent ou m_ulFtrIdent est vide."); return false; }

		return true;
	}

	bool CFiltre::Sauver()
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
					osQuery << "insert into FILTRE (FTR_IDENT, FTR_LIBELLE, FTR_TYPE, FTR_PRJ_IDENT, FTR_FTR_IDENT, FTR_H_FOLDER, FTR_CPP_FOLDER)";
					osQuery << " values (";
					osQuery << "	" << ToQuery(DefULong) << ",";
					osQuery << "	" << ToQuery((int)m_iType) << ",";
					osQuery << "	" << ToQuery(m_sLibelle) << ",";
					osQuery << "	" << ToQuery(m_ulPrjIdent) << ",";
					osQuery << "	" << ToQuery(m_ulFtrIdent) << ",";
					osQuery << "	" << ToQuery(m_ptHFolder.toString()) << ",";
					osQuery << "	" << ToQuery(m_ptCppFolder.toString()) << "";
					osQuery << ");";

					CSQLiteSource::database()->exec(osQuery.str());

					m_ulId = static_cast<unsigned long>(CSQLiteSource::database()->getLastInsertRowid());
				}

				else if (EstModifier())
				{
					std::ostringstream osQuery;
					osQuery << "update FILTRE set";
					osQuery << "	FTR_LIBELLE = "		<< ToQuery(m_sLibelle) << ",";
					osQuery << "	FTR_TYPE = "		<< ToQuery((int)m_iType) << ",";
					osQuery << "	FTR_PRJ_IDENT = "	<< ToQuery(m_ulPrjIdent) << ",";
					osQuery << "	FTR_FTR_IDENT = "	<< ToQuery(m_ulFtrIdent) << ",";
					osQuery << "	FTR_H_FOLDER = "	<< ToQuery(m_ptHFolder.toString()) << ",";
					osQuery << "	FTR_CPP_FOLDER = "	<< ToQuery(m_ptCppFolder.toString()) << " ";
					osQuery << "where";
					osQuery << "	FTR_IDENT = "		<< ToQuery(m_ulId) << ";";

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

		// Fin de la transaction automatique
		__TRANSACTION_AUTO_VALIDE__;

		return true;
	}

	bool CFiltre::Supprimer()
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
			osQuery << "delete from FILTRE where FTR_IDENT = " << ToQuery(m_ulId);

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

	std::string CFiltre::GetLibelle()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return std::string();

		return m_sLibelle;
	}

	bool CFiltre::SetLibelle(std::string sName)
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

	GDSObject::FiltreType CFiltre::GetType()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return FiltreType::Filtre;

		return m_iType;
	}

	bool CFiltre::SetType(GDSObject::FiltreType iType)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_iType != iType)
		{
			// Affectation de la nouvelle valeur.
			m_iType = iType;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	unsigned long CFiltre::GetPrjIdent()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return DefULong;

		return m_ulPrjIdent;
	}

	bool CFiltre::SetPrjIdent(unsigned long ulPrjIdent)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_ulPrjIdent != ulPrjIdent)
		{
			// Affectation de la nouvelle valeur.
			m_ulPrjIdent = ulPrjIdent;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	unsigned long CFiltre::GetFtrIdent()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return DefULong;

		return m_ulFtrIdent;
	}

	bool CFiltre::SetFtrIdent(unsigned long ulFtrIdent)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_ulFtrIdent != ulFtrIdent)
		{
			// Affectation de la nouvelle valeur.
			m_ulFtrIdent = ulFtrIdent;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}


	Poco::Path CFiltre::GetHFolder()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return Poco::Path();

		return m_ptHFolder;
	}

	bool CFiltre::SetHFolder(Poco::Path ptHFolder)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_ptHFolder.toString() != ptHFolder.toString())
		{
			// Affectation de la nouvelle valeur.
			m_ptHFolder = ptHFolder;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	Poco::Path CFiltre::GetCppFolder()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return Poco::Path();

		return m_ptCppFolder;
	}

	bool CFiltre::SetCppFolder(Poco::Path ptCppFolder)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_ptCppFolder.toString() != ptCppFolder.toString())
		{
			// Affectation de la nouvelle valeur.
			m_ptCppFolder = ptCppFolder;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}










	//! Constructeur
	CFiltreListe::CFiltreListe()
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Destructeur
	CFiltreListe::~CFiltreListe(void)
	{
		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Constructeur par copie.
	CFiltreListe::CFiltreListe(const CFiltreListe &source)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CFiltreListe & CFiltreListe::operator=(const CFiltreListe &source)
	{
		/* Clonage des données. */
		ClonnerDonnees(source);

		return *this;
	}

	//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
	void CFiltreListe::ClonnerDonnees(const CFiltreListe &source)
	{
		/* Initialisation des données. */
		InitialiserDonnees();

		/* Copie des variables membres de l'objet. */
		m_ulPrjIdent = source.m_ulPrjIdent;
		m_ulFtrIdent = source.m_ulFtrIdent;

		/* Copie des pointeurs membres de l'objet. */
	}

	//! Initialisation des données membres de la classe
	void CFiltreListe::InitialiserDonnees()
	{
		m_ulPrjIdent = DefULong;
		m_ulFtrIdent = DefULong;
	}

	//! Initialisation de la liste d'objet
	bool CFiltreListe::Initialiser()
	{
		if (DoitEtreInitialiser() == false) return true;
		if (PeutEtreInitialiser() == false) return false;

		// Initialisation depuis la base
		if (!EstAcquis())
		{
			std::ostringstream osQuery;
			osQuery << "select FTR_IDENT, FTR_LIBELLE, FTR_TYPE, FTR_PRJ_IDENT, FTR_FTR_IDENT, FTR_H_FOLDER, FTR_CPP_FOLDER from FILTRE";

			SQLite::Statement query(*CSQLiteSource::database(), osQuery.str());
			while (query.executeStep())
			{
				CFiltre* pFiltre		= new CFiltre(query.getColumn(0).getInt());
				pFiltre->m_sLibelle		= query.getColumn(1).getText();
				pFiltre->m_iType		= (FiltreType)query.getColumn(1).getInt();
				pFiltre->m_ulPrjIdent	= query.getColumn(2).isNull() ? DefULong : query.getColumn(2).getInt();
				pFiltre->m_ulFtrIdent	= query.getColumn(3).isNull() ? DefULong : query.getColumn(3).getInt();
				pFiltre->m_ptHFolder	= query.getColumn(4).isNull() ? Poco::Path() : query.getColumn(4).getText();
				pFiltre->m_ptCppFolder	= query.getColumn(5).isNull() ? Poco::Path() : query.getColumn(5).getText();

				// L'objet est acquis
				pFiltre->SetAcquis();

				Add(pFiltre);
			}

			// L'objet est acquis
			if (GetSize()) SetAcquis();
		}

		// L'objet est initialisé
		SetInitaliser();

		return true;
	}

	//! Verification
	bool CFiltreListe::Verifier(std::string* sMsg)
	{
		// Vérifications de base
		return CDObjListe::Verifier(sMsg);
	}

	//! Sauvegarde
	bool CFiltreListe::Sauver()
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
	bool CFiltreListe::Supprimer()
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

	bool CFiltreListe::InitialiserAPartirDePrjIdent(unsigned long PrjIdent)
	{
		if (DoitEtreInitialiser() == false) return true;
		if (PeutEtreInitialiser() == false) return false;

		// Initialisation depuis la base
		if (!EstAcquis())
		{
			std::ostringstream osQuery;
			osQuery << "select FTR_IDENT, FTR_LIBELLE, FTR_TYPE, FTR_PRJ_IDENT, FTR_FTR_IDENT, FTR_H_FOLDER, FTR_CPP_FOLDER from FILTRE where FTR_PRJ_IDENT = " << ToQuery(PrjIdent);

			SQLite::Statement query(*CSQLiteSource::database(), osQuery.str());
			while (query.executeStep())
			{
				CFiltre* pFiltre		= new CFiltre(query.getColumn(0).getInt());
				pFiltre->m_sLibelle		= query.getColumn(1).getText();
				pFiltre->m_iType		= (FiltreType)query.getColumn(2).getInt();
				pFiltre->m_ulPrjIdent	= query.getColumn(2).isNull() ? DefULong : query.getColumn(2).getInt();
				pFiltre->m_ulFtrIdent	= query.getColumn(3).isNull() ? DefULong : query.getColumn(3).getInt();
				pFiltre->m_ptHFolder	= query.getColumn(4).isNull() ? Poco::Path() : query.getColumn(4).getText();
				pFiltre->m_ptCppFolder	= query.getColumn(5).isNull() ? Poco::Path() : query.getColumn(5).getText();

				// L'objet est acquis
				pFiltre->SetAcquis();

				Add(pFiltre);
			}

			// L'objet est acquis
			if (GetSize()) SetAcquis();
		}

		// L'objet est initialisé
		SetInitaliser();

		return true;
	}

	bool CFiltreListe::InitialiserAPartirDeFtrIdent(unsigned long FtrIdent)
	{
		if (DoitEtreInitialiser() == false) return true;
		if (PeutEtreInitialiser() == false) return false;

		// Initialisation depuis la base
		if (!EstAcquis())
		{
			std::ostringstream osQuery;
			osQuery << "select FTR_IDENT, FTR_LIBELLE, FTR_TYPE, FTR_PRJ_IDENT, FTR_FTR_IDENT, FTR_H_FOLDER, FTR_CPP_FOLDER from FILTRE where FTR_FTR_IDENT = " << ToQuery(FtrIdent);

			SQLite::Statement query(*CSQLiteSource::database(), osQuery.str());
			while (query.executeStep())
			{
				CFiltre* pFiltre		= new CFiltre(query.getColumn(0).getInt());
				pFiltre->m_sLibelle		= query.getColumn(1).getText();
				pFiltre->m_iType		= (FiltreType)query.getColumn(2).getInt();
				pFiltre->m_ulPrjIdent	= query.getColumn(2).isNull() ? DefULong : query.getColumn(2).getInt();
				pFiltre->m_ulFtrIdent	= query.getColumn(3).isNull() ? DefULong : query.getColumn(3).getInt();
				pFiltre->m_ptHFolder	= query.getColumn(4).isNull() ? Poco::Path() : query.getColumn(4).getText();
				pFiltre->m_ptCppFolder	= query.getColumn(5).isNull() ? Poco::Path() : query.getColumn(5).getText();

				// L'objet est acquis
				pFiltre->SetAcquis();

				Add(pFiltre);
			}

			// L'objet est acquis
			if (GetSize()) SetAcquis();
		}

		// L'objet est initialisé
		SetInitaliser();

		return true;
	}

	//
	unsigned long CFiltreListe::GetPrjIdent()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return DefULong;

		return m_ulPrjIdent;
	}

	//
	bool CFiltreListe::SetPrjIdent(unsigned long ulPrjIdent)
	{
		if (!Initialiser()) return false;

		// Mise à jour de la variable
		if (m_ulPrjIdent != ulPrjIdent)
		{
			m_ulPrjIdent = ulPrjIdent;
			SetModifier();
		}

		// Mise à jour de la liste
		for (int i = 0; i < GetSize(); i++)
			if (GetAt(i)->SetPrjIdent(ulPrjIdent) == false)
				return false;

		return true;
	}

	unsigned long CFiltreListe::GetFtrIdent()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return DefULong;

		return m_ulFtrIdent;
	}

	bool CFiltreListe::SetFtrIdent(unsigned long ulFtrIdent)
	{
		if (!Initialiser()) return false;

		// Mise à jour de la variable
		if (m_ulFtrIdent != ulFtrIdent)
		{
			m_ulFtrIdent = ulFtrIdent;
			SetModifier();
		}

		// Mise à jour de la liste
		for (int i = 0; i < GetSize(); i++)
			if (GetAt(i)->SetFtrIdent(ulFtrIdent) == false)
				return false;

		return true;
	}


}
