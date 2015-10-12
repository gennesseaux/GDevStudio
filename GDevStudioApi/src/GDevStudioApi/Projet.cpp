///*
//
//	-----------------------------------------------------------------------
//
//	 Fichier		: 	Projet.cpp
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
#include "GDevStudioApi\Projet.h"
#include "GDevStudioApi\Filtre.h"

// Inclusions des namespaces
using namespace SQLite;


namespace GDSAPI
{
	//! Constructeur
	CProjet::CProjet(unsigned long ulId /*= DefULong*/, CDObject* pOwner /*= nullptr*/) : CDObjBase(ulId,pOwner)
	{
		/* Initialisation des pointeurs. */
		m_pFiltreListe = nullptr;

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Destructeur
	CProjet::~CProjet(void)
	{
		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Constructeur par copie.
	CProjet::CProjet(const CProjet &source)
	{
		/* Initialisation des pointeurs. */
		m_pFiltreListe = nullptr;

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CProjet & CProjet::operator=(const CProjet &source)
	{
		/* Initialisation des pointeurs. */
		m_pFiltreListe = nullptr;

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);

		return *this;
	}

	//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
	void CProjet::ClonnerDonnees(const CProjet &source)
	{
		CDObjBase::ClonnerDonnees(source);

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Copie des variables membres de l'objet. */
		m_sLibelle = source.m_sLibelle;
		m_sDescription = source.m_sDescription;
		m_ptHFolder = source.m_ptHFolder;
		m_ptCppFolder = source.m_ptCppFolder;
		m_uuidResGen = source.m_uuidResGen;
		m_uuidClsGen = source.m_uuidClsGen;

		/* Copie des pointeurs membres de l'objet. */
		if (source.m_pFiltreListe)
			m_pFiltreListe = new CFiltreListe(*source.m_pFiltreListe);
	}

	//! Initialisation des données membres de la classe
	void CProjet::InitialiserDonnees()
	{
		m_sLibelle = std::string();
		m_sDescription = std::string();
		m_ptHFolder.clear();
		m_ptCppFolder.clear();
		m_uuidResGen = Poco::UUID();
		m_uuidClsGen = Poco::UUID();

		delete m_pFiltreListe; m_pFiltreListe = nullptr;
	}

	//! Initialisation de l'objet
	bool CProjet::Initialiser()
	{
		if (DoitEtreInitialiser() == false) return true;

		// Initialisation depuis la base
		if (!EstAcquis() && m_ulId!=DefULong)
		{
			std::ostringstream osQuery;
			osQuery << "select PRJ_LIBELLE, PRJ_DESCRIPTION, PRJ_H_FOLDER, PRJ_CPP_FOLDER, PRJ_UUID_RES_GEN, PRJ_UUID_CLS_GEN from PROJET where PRJ_IDENT = " << ToQuery(m_ulId);
			
			SQLite::Statement query(*CSQLiteSource::Database(), osQuery.str());
			if (query.executeStep())
			{
				m_sLibelle = query.getColumn(0);
				m_sDescription = query.getColumn(1);
				m_ptHFolder = query.getColumn(2).getText();
				m_ptCppFolder = query.getColumn(3).getText();
				m_uuidResGen = Poco::UUID(query.getColumn(4).getText());
				m_uuidClsGen = Poco::UUID(query.getColumn(5).getText());

				// L'objet est acquis
				SetAcquis();
			}
		}

		// L'objet est initialisé
		SetInitaliser();

		return true;
	}

	bool CProjet::Verifier(std::string* sMsg)
	{
		// Les objets qui dépendent de cette objet ne doivent
		// pas être vérifiés lors de la création.
		if (!EstNouveau())
		{
			if (m_pFiltreListe && (!m_pFiltreListe->Verifier(sMsg))) return false;
		}

		if (!Initialiser())				{ if (sMsg) sMsg->assign("Erreur lors de l'initialisation."); return false; }
		if (m_sLibelle.empty())			{ if (sMsg) sMsg->assign("Erreur : m_sName est vide."); return false; }

		return true;
	}

	bool CProjet::Sauver()
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
		__TRANSACTION_AUTO_DEBUT__(CSQLiteSource::Transaction());

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
					osQuery << "insert into PROJET (PRJ_IDENT, PRJ_LIBELLE, PRJ_DESCRIPTION, PRJ_H_FOLDER, PRJ_CPP_FOLDER, PRJ_UUID_RES_GEN, PRJ_UUID_CLS_GEN)";
					osQuery << " values (";
					osQuery << "	" << ToQuery(DefULong) << ",";
					osQuery << "	" << ToQuery(m_sLibelle) << ",";
					osQuery << "	" << ToQuery(m_sDescription) << ",";
					osQuery << "	" << ToQuery(m_ptHFolder.toString()) << ",";
					osQuery << "	" << ToQuery(m_ptCppFolder.toString()) << ",";
					osQuery << "	" << ToQuery(m_uuidResGen.toString()) << ",";
					osQuery << "	" << ToQuery(m_uuidClsGen.toString()) << "";
					osQuery << ");";

					CSQLiteSource::Database()->exec(osQuery.str());

					m_ulId = static_cast<unsigned long>(CSQLiteSource::Database()->getLastInsertRowid());
				}

				else if (EstModifier())
				{
					std::ostringstream osQuery;
					osQuery << "update PROJET set";
					osQuery << "	PRJ_LIBELLE = "			<< ToQuery(m_sLibelle) << ",";
					osQuery << "	PRJ_DESCRIPTION = "		<< ToQuery(m_sDescription) << ",";
					osQuery << "	PRJ_H_FOLDER = "		<< ToQuery(m_ptHFolder.toString()) << ",";
					osQuery << "	PRJ_CPP_FOLDER = "		<< ToQuery(m_ptCppFolder.toString()) << ",";
					osQuery << "	PRJ_UUID_RES_GEN = "	<< ToQuery(m_uuidResGen.toString()) << ",";
					osQuery << "	PRJ_UUID_CLS_GEN = "	<< ToQuery(m_uuidClsGen.toString()) << " ";
					osQuery << "where";
					osQuery << "	PRJ_IDENT = "		<< ToQuery(m_ulId) << ";";

					CSQLiteSource::Database()->exec(osQuery.str());
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

		//
		if (m_pFiltreListe && (!((m_pFiltreListe->SetPrjIdent(m_ulId)) && (m_pFiltreListe->Sauver()))))
		{
			// Fin de la transaction automatique
			__TRANSACTION_AUTO_ANNULE__;
			return DObject::DObjSaveGuard::Error(this);
		}

		// Fin de la transaction automatique
		__TRANSACTION_AUTO_VALIDE__;

		return DObject::DObjSaveGuard::Sucess(this);
	}

	bool CProjet::Supprimer()
	{
		if (DoitEtreSupprimer() == false) return true;
		if (PeutEtreSupprimer() == false) return false;

		// SaveGuard
		DObject::DObjSaveGuard::Start(this);

		// Gestion automatique des transactions
		__TRANSACTION_AUTO_DEBUT__(CSQLiteSource::Transaction());

		try
		{
			std::ostringstream osQuery;
			osQuery << "delete from PROJET where PRJ_IDENT = " << ToQuery(m_ulId);

			SQLite::Statement query(*CSQLiteSource::Database(), osQuery.str());
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
	
	void CProjet::OnSupprimer(CDObject* pDObject,CDObject* sender)
	{
		if(m_pFiltreListe && m_pFiltreListe==pDObject)	m_pFiltreListe = nullptr;
	}

	std::string CProjet::GetLibelle()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return std::string();

		return m_sLibelle;
	}

	bool CProjet::SetLibelle(std::string sName)
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

	std::string CProjet::GetDescription()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return std::string();

		return m_sDescription;
	}

	bool CProjet::SetDescription(std::string sDescription)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_sDescription != sDescription)
		{
			// Affectation de la nouvelle valeur.
			m_sDescription = sDescription;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	Poco::Path CProjet::GetHFolder()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return Poco::Path();

		return m_ptHFolder;
	}

	bool CProjet::SetHFolder(Poco::Path ptHFolder)
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

	Poco::Path CProjet::GetCppFolder()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return Poco::Path();

		return m_ptCppFolder;
	}

	bool CProjet::SetCppFolder(Poco::Path ptCppFolder)
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
	
	Poco::UUID CProjet::GetUuidResGen()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return Poco::UUID();

		return m_uuidResGen;
	}

	bool CProjet::SetUuidResGen(Poco::UUID uuid)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_uuidResGen != uuid)
		{
			// Affectation de la nouvelle valeur.
			m_uuidResGen = uuid;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	bool CProjet::SetUuidResGen(std::string uuid)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_uuidResGen.toString() != uuid)
		{
			// Affectation de la nouvelle valeur.
			m_uuidResGen = Poco::UUID(uuid);

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	Poco::UUID CProjet::GetUuidClsGen()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return Poco::UUID();

		return m_uuidClsGen;
	}

	bool CProjet::SetUuidClsGen(Poco::UUID uuid)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_uuidClsGen != uuid)
		{
			// Affectation de la nouvelle valeur.
			m_uuidClsGen = uuid;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	bool CProjet::SetUuidClsGen(std::string uuid)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_uuidClsGen.toString() != uuid)
		{
			// Affectation de la nouvelle valeur.
			m_uuidClsGen = Poco::UUID(uuid);

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	CFiltreListe* CProjet::GetFiltreListe(bool bInit)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return nullptr;

		// Si la liste n'existe pas, alosr on la crée. 
		if (m_pFiltreListe == nullptr)
		{
			m_pFiltreListe = new CFiltreListe(this);
			if (bInit) m_pFiltreListe->InitialiserAPartirDePrjIdent(m_ulId);
		}
		// 
		else if (m_pFiltreListe && m_pFiltreListe->GetPrjIdent() != m_ulId)
		{
			delete m_pFiltreListe; m_pFiltreListe = nullptr;
			return GetFiltreListe(bInit);
		}

		return m_pFiltreListe;
	}











	//! Constructeur
	CProjetListe::CProjetListe(CDObject* pOwner /*= nullptr*/) : CDObjListe(pOwner)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Destructeur
	CProjetListe::~CProjetListe(void)
	{
		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Constructeur par copie.
	CProjetListe::CProjetListe(const CProjetListe &source)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CProjetListe & CProjetListe::operator=(const CProjetListe &source)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);

		return *this;
	}

	//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
	void CProjetListe::ClonnerDonnees(const CProjetListe &source)
	{
		/* Copie des éléments de la liste */
		__super::ClonnerDonnees(source);

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Copie des variables membres de l'objet. */

		/* Copie des pointeurs membres de l'objet. */
	}

	//! Initialisation des données membres de la classe
	void CProjetListe::InitialiserDonnees()
	{
	}

	//! Initialisation de la liste d'objet
	bool CProjetListe::Initialiser()
	{
		if (DoitEtreInitialiser() == false) return true;
		if (PeutEtreInitialiser() == false) return false;

		// Initialisation depuis la base
		if (!EstAcquis())
		{
			std::ostringstream osQuery;
			osQuery << "select PRJ_IDENT, PRJ_LIBELLE, PRJ_DESCRIPTION, PRJ_H_FOLDER, PRJ_CPP_FOLDER, PRJ_UUID_RES_GEN, PRJ_UUID_CLS_GEN from PROJET";

			SQLite::Statement query(*CSQLiteSource::Database(), osQuery.str());
			while (query.executeStep())
			{
				CProjet* pProjet = new CProjet(query.getColumn(0).getInt(),GetOwner());
				pProjet->m_sLibelle = query.getColumn(0);
				pProjet->m_sDescription = query.getColumn(1);
				pProjet->m_ptHFolder = query.getColumn(2).getText();
				pProjet->m_ptCppFolder = query.getColumn(3).getText();
				pProjet->m_uuidResGen = Poco::UUID(query.getColumn(4).getText());
				pProjet->m_uuidClsGen = Poco::UUID(query.getColumn(5).getText());

				Add(pProjet);
			}

			// L'objet est acquis
			if (GetSize()) SetAcquis();
		}

		// L'objet est initialisé
		SetInitaliser();

		return true;
	}

	//! Verification
	bool CProjetListe::Verifier(std::string* sMsg)
	{
		// Vérifications de base
		return CDObjListe::Verifier(sMsg);
	}

	//! Sauvegarde
	bool CProjetListe::Sauver()
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
		__TRANSACTION_AUTO_DEBUT__(CSQLiteSource::Transaction());

		// Sauvegarde des objets
		if (!CDObjListe::Sauver())
		{
			// Fin de la transaction automatique
			__TRANSACTION_AUTO_ANNULE__;
			return DObject::DObjSaveGuard::Error(this);
		}

		// Fin de la transaction automatique
		__TRANSACTION_AUTO_VALIDE__;

		// Les objets sont acquis
		SetAcquis();

		return DObject::DObjSaveGuard::Sucess(this);
	}

	//! Suppression
	bool CProjetListe::Supprimer()
	{
		if (DoitEtreSupprimer() == false) return true;
		if (PeutEtreSupprimer() == false) return false;

		// SaveGuard
		DObject::DObjSaveGuard::Start(this);

		// Gestion automatique des transactions
		__TRANSACTION_AUTO_DEBUT__(CSQLiteSource::Transaction());

		// Suppression des objets
		if (!CDObjListe::Supprimer())
		{
			// Fin de la transaction automatique
			__TRANSACTION_AUTO_ANNULE__;
			return DObject::DObjSaveGuard::Error(this);
		}

		// Fin de la transaction automatique
		__TRANSACTION_AUTO_VALIDE__;


		// Les objets sont supprimés
		SetSupprimer();

		return DObject::DObjSaveGuard::Sucess(this);
	}

}
