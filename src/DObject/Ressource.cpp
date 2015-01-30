///*
//
//	-----------------------------------------------------------------------
//
//	 Fichier		: 	Ressource.cpp
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
#include "Ressource.h"
#include "Controle.h"

// Inclusions
#include <SQLite/SQLiteSource.h>
#include <Poco/NumberFormatter.h>


namespace GDSObject
{
	//! Constructeur
	CRessource::CRessource(unsigned long ulId) : CDObjBase(ulId)
	{
		/* Initialisation des pointeurs. */
		m_pControleListe = nullptr;

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Destructeur
	CRessource::~CRessource(void)
	{
		//
		RemoveEnfants();

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Constructeur par copie.
	CRessource::CRessource(const CRessource &source)
	{
		/* Initialisation des pointeurs. */
		m_pControleListe = nullptr;

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CRessource & CRessource::operator=(const CRessource &source)
	{
		/* Initialisation des pointeurs. */
		m_pControleListe = nullptr;

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);

		return *this;
	}

	//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
	void CRessource::ClonnerDonnees(const CRessource &source)
	{
		CDObjBase::ClonnerDonnees(source);

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Copie des variables membres de l'objet. */
		m_sLibelle = source.m_sLibelle;
		m_file = source.m_file;
		m_ulFtrIdent = source.m_ulFtrIdent;

		/* Copie des pointeurs membres de l'objet. */
 		if (source.m_pControleListe)
 			m_pControleListe = new CControleListe(*source.m_pControleListe);
	}

	//! Initialisation des données membres de la classe
	void CRessource::InitialiserDonnees()
	{
		m_sLibelle = std::string();
		m_file = Poco::File();
		m_ulFtrIdent = DefULong;

		delete m_pControleListe; m_pControleListe = nullptr;
	}

	//! Initialisation de l'objet
	bool CRessource::Initialiser()
	{
		if (DoitEtreInitialiser() == false) return true;

		// Initialisation depuis la base
		if (!EstAcquis() && m_ulId!=DefULong)
		{
			std::ostringstream osQuery;
			osQuery << "select RES_LIBELLE, RES_FILE, RES_FTR_IDENT from RESSOURCE where RES_IDENT = " << ToQuery(m_ulId);
			
			SQLite::Statement query(*CSQLiteSource::database(), osQuery.str());
			if (query.executeStep())
			{
				m_sLibelle		= query.getColumn(0).getText();
				m_file			= query.getColumn(1).getText();
				m_ulFtrIdent	= query.getColumn(2).getInt();

				// L'objet est acquis
				SetAcquis();
			}
		}

		// L'objet est initialisé
		SetInitaliser();

		return true;
	}

	bool CRessource::Verifier(std::string* sMsg)
	{
		// Les objets qui dépendent de cette objet ne doivent
		// pas être vérifiés lors de la création.
		if (!EstNouveau())
		{
		}

		if (!Initialiser())				{ if (sMsg) sMsg->assign("Erreur lors de l'initialisation."); return false; }
		if (m_sLibelle.empty())			{ if (sMsg) sMsg->assign("Erreur : m_sLibelle est vide."); return false; }
		if (m_ulFtrIdent==DefULong)		{ if (sMsg) sMsg->assign("Erreur : m_ulFtrIdent est vide."); return false; }

		return true;
	}

	bool CRessource::Sauver()
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
					osQuery << "insert into RESSOURCE (RES_IDENT, RES_LIBELLE, RES_FILE, RES_FTR_IDENT)";
					osQuery << " values (";
					osQuery << "	" << ToQuery(DefULong) << ",";
					osQuery << "	" << ToQuery(m_sLibelle) << ",";
					osQuery << "	" << ToQuery(m_file.path()) << ",";
					osQuery << "	" << ToQuery(m_ulFtrIdent) << "";
					osQuery << ");";

					CSQLiteSource::database()->exec(osQuery.str());

					m_ulId = static_cast<unsigned long>(CSQLiteSource::database()->getLastInsertRowid());
				}

				else if (EstModifier())
				{
					std::ostringstream osQuery;
					osQuery << "update Ressource set";
					osQuery << "	RES_LIBELLE = "		<< ToQuery(m_sLibelle) << ",";
					osQuery << "	RES_FILE = "		<< ToQuery(m_file.path()) << ",";
					osQuery << "	RES_FTR_IDENT = "	<< ToQuery(m_ulFtrIdent) << ",";
					osQuery << "where";
					osQuery << "	RES_IDENT = "		<< ToQuery(m_ulId) << ";";

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

		//
		if (m_pControleListe && (!((m_pControleListe->SetResIdent(m_ulId)) && (m_pControleListe->Sauver()))))
		{
			// Restauration de l'état précédent
			state.Restore();
			// Fin de la transaction automatique
			__TRANSACTION_AUTO_ANNULE__;
			return false;
		}

		// Fin de la transaction automatique
		__TRANSACTION_AUTO_VALIDE__;

		return true;
	}

	bool CRessource::Supprimer()
	{
		if (DoitEtreSupprimer() == false) { SetSupprimer(true);  return true; }
		if (PeutEtreSupprimer() == false) { SetSupprimer(false); return false; }

		// Mémorisation de l'etat de l'objet avant sauvegarde
		DObject::CDObjState state(this);

		// Gestion automatique des transactions
		__TRANSACTION_AUTO_DEBUT__;

		if(m_pControleListe)
		{
			m_pControleListe->SetPourSupprimer(true,true);

			if(!m_pControleListe->Supprimer())
			{
				// Fin de la transaction automatique
				__TRANSACTION_AUTO_ANNULE__;
				return false;
			}
		}

		try
		{
			std::ostringstream osQuery;
			osQuery << "delete from RESSOURCE where RES_IDENT = " << ToQuery(m_ulId);

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

	std::string CRessource::GetLibelle()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return std::string();

		return m_sLibelle;
	}

	bool CRessource::SetLibelle(std::string sName)
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

	Poco::File CRessource::GetFile()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return Poco::File();

		return m_file;
	}

	bool CRessource::SetFile(Poco::File file)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_file.path() != file.path())
		{
			// Affectation de la nouvelle valeur.
			m_file = file;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	unsigned long CRessource::GetFtrIdent()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return DefULong;

		return m_ulFtrIdent;
	}

	bool CRessource::SetFtrIdent(unsigned long ulFtrIdent)
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

 	CControleListe* CRessource::GetControleListe(bool bInit)
 	{
 		// L'objet doit être initialisé
 		if (!Initialiser()) return nullptr;
 
 		// Si la liste n'existe pas, alosr on la crée. 
 		if (m_pControleListe == nullptr)
 		{
 			m_pControleListe = new CControleListe();
 			m_pControleListe->AddParent(this);
 			if (bInit) m_pControleListe->InitialiserAPartirDeResIdent(m_ulId);
 		}
 		// 
 		else if (m_pControleListe && m_pControleListe->GetResIdent() != m_ulId)
 		{
 			delete m_pControleListe; m_pControleListe = nullptr;
 			return GetControleListe(bInit);
 		}
 
 		return m_pControleListe;
 	}










	//! Constructeur
	CRessourceListe::CRessourceListe()
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Destructeur
	CRessourceListe::~CRessourceListe(void)
	{
		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Constructeur par copie.
	CRessourceListe::CRessourceListe(const CRessourceListe &source)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CRessourceListe & CRessourceListe::operator=(const CRessourceListe &source)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);

		return *this;
	}

	//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
	void CRessourceListe::ClonnerDonnees(const CRessourceListe &source)
	{
		/* Copie des éléments de la liste */
		__super::ClonnerDonnees(source);

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Copie des variables membres de l'objet. */
		m_ulFtrIdent = source.m_ulFtrIdent;

		/* Copie des pointeurs membres de l'objet. */
	}

	//! Initialisation des données membres de la classe
	void CRessourceListe::InitialiserDonnees()
	{
		m_ulFtrIdent = DefULong;
	}

	//! Initialisation de la liste d'objet
	bool CRessourceListe::Initialiser()
	{
		if (DoitEtreInitialiser() == false) return true;
		if (PeutEtreInitialiser() == false) return false;

		// Initialisation depuis la base
		if (!EstAcquis())
		{
			std::ostringstream osQuery;
			osQuery << "select RES_IDENT, RES_LIBELLE, RES_FILE, RES_FTR_IDENT from RESSOURCE";

			SQLite::Statement query(*CSQLiteSource::database(), osQuery.str());
			while (query.executeStep())
			{
				CRessource* pRessource		= new CRessource(query.getColumn(0).getInt());
				pRessource->m_sLibelle		= query.getColumn(1).getText();
				pRessource->m_file			= query.getColumn(2).getText();
				pRessource->m_ulFtrIdent	= query.getColumn(3).getInt();

				// L'objet est acquis
				pRessource->SetAcquis();

				Add(pRessource);
			}

			// L'objet est acquis
			if (GetSize()) SetAcquis();
		}

		// L'objet est initialisé
		SetInitaliser();

		return true;
	}

	//! Verification
	bool CRessourceListe::Verifier(std::string* sMsg)
	{
		// Vérifications de base
		return CDObjListe::Verifier(sMsg);
	}

	//! Sauvegarde
	bool CRessourceListe::Sauver()
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
	bool CRessourceListe::Supprimer()
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

	bool CRessourceListe::InitialiserAPartirDeFtrIdent(unsigned long ulFtrIdent)
	{
		if (DoitEtreInitialiser() == false) return true;
		if (PeutEtreInitialiser() == false) return false;

		//! Initialisation des données membres de la classe
		InitialiserDonnees();
		
		m_ulFtrIdent = ulFtrIdent;

		// Initialisation depuis la base
		if (!EstAcquis())
		{
			std::ostringstream osQuery;
			osQuery << "select RES_IDENT, RES_LIBELLE, RES_FILE, RES_FTR_IDENT from RESSOURCE where RES_FTR_IDENT = " << ToQuery(ulFtrIdent);

			SQLite::Statement query(*CSQLiteSource::database(), osQuery.str());
			while (query.executeStep())
			{
				CRessource* pRessource		= new CRessource(query.getColumn(0).getInt());
				pRessource->m_sLibelle		= query.getColumn(1).getText();
				pRessource->m_file			= query.getColumn(2).getText();
				pRessource->m_ulFtrIdent	= query.getColumn(3).getInt();

				// L'objet est acquis
				pRessource->SetAcquis();

				Add(pRessource);
			}

			// L'objet est acquis
			if (GetSize()) SetAcquis();
		}

		// L'objet est initialisé
		SetInitaliser();

		return true;
	}

	unsigned long CRessourceListe::GetFtrIdent()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return DefULong;

		return m_ulFtrIdent;
	}

	bool CRessourceListe::SetFtrIdent(unsigned long ulFtrIdent)
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
