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
//	 R�visions		:	16/7/2014 : 
//	-----------------------------------------------------------------------
//*/

// Inclusions
#include "Stdafx.h"
#include "Controle.h"

// Inclusions
#include <SQLite/SQLiteSource.h>
#include <Poco/NumberFormatter.h>


namespace GDSObject
{
	//! Constructeur
	CControle::CControle(unsigned long ulId) : CDObjBase(ulId)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des donn�es. */
		InitialiserDonnees();
	}

	//! Destructeur
	CControle::~CControle(void)
	{
		//
		RemoveEnfants();

		/* Initialisation des donn�es. */
		InitialiserDonnees();
	}

	//! Constructeur par copie.
	CControle::CControle(const CControle &source)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des donn�es. */
		InitialiserDonnees();

		/* Clonage des donn�es. */
		ClonnerDonnees(source);
	}

	//! Op�rateur =
	CControle & CControle::operator=(const CControle &source)
	{
		/* Clonage des donn�es. */
		ClonnerDonnees(source);

		return *this;
	}

	//! Clonage des donn�es utilis�e par le constructeur par copie ainsi que l'op�rateur =
	void CControle::ClonnerDonnees(const CControle &source)
	{
		CDObjBase::ClonnerDonnees(source);

		/* Initialisation des donn�es. */
		InitialiserDonnees();

		/* Copie des variables membres de l'objet. */
		m_sLibelle = source.m_sLibelle;
		m_sType = source.m_sType;
		m_ulResdent = source.m_ulResdent;
	}

	//! Initialisation des donn�es membres de la classe
	void CControle::InitialiserDonnees()
	{
		m_sLibelle = std::string();
		m_sType = std::string();
		m_ulResdent = DefULong;
	}

	//! Initialisation de l'objet
	bool CControle::Initialiser()
	{
		if (DoitEtreInitialiser() == false) return true;

		// Initialisation depuis la base
		if (!EstAcquis() && m_ulId!=DefULong)
		{
			std::ostringstream osQuery;
			osQuery << "select CTR_LIBELLE, CTR_TYPE, CTR_RES_IDENT from CONTROLE where RES_IDENT = " << ToQuery(m_ulId);
			
			SQLite::Statement query(*CSQLiteSource::database(), osQuery.str());
			if (query.executeStep())
			{
				m_sLibelle		= query.getColumn(0).getText();
				m_sType			= query.getColumn(1).getText();
				m_ulResdent		= query.getColumn(2).getInt();

				// L'objet est acquis
				SetAcquis();
			}
		}

		// L'objet est initialis�
		SetInitaliser();

		return true;
	}

	bool CControle::Verifier(std::string* sMsg)
	{
		// Les objets qui d�pendent de cette objet ne doivent
		// pas �tre v�rifi�s lors de la cr�ation.
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

		// M�morisation de l'etat de l'objet avant sauvegarde
		DObject::CDObjState state(this);

		// Gestion automatique des transactions
		__TRANSACTION_AUTO_DEBUT__;

		// Sauvegarde de l'objet
		if (EstModifier())
		{
			if (!Verifier())
			{
				// Restauration de l'�tat pr�c�dent
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
					osQuery << "insert into CONTROLE (CTR_IDENT, CTR_LIBELLE, CTR_TYPE, CTR_RES_IDENT)";
					osQuery << " values (";
					osQuery << "	" << ToQuery(DefULong) << ",";
					osQuery << "	" << ToQuery(m_sLibelle) << ",";
					osQuery << "	" << ToQuery(m_sType) << ",";
					osQuery << "	" << ToQuery(m_ulResdent) << "";
					osQuery << ");";

					CSQLiteSource::database()->exec(osQuery.str());

					m_ulId = static_cast<unsigned long>(CSQLiteSource::database()->getLastInsertRowid());
				}

				else if (EstModifier())
				{
					std::ostringstream osQuery;
					osQuery << "update CONTROLE set";
					osQuery << "	CTR_LIBELLE = "		<< ToQuery(m_sLibelle) << ",";
					osQuery << "	CTR_TYPE = "		<< ToQuery(m_sType) << ",";
					osQuery << "	CTR_RES_IDENT = "	<< ToQuery(m_ulResdent) << ",";
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
				// Restauration de l'�tat pr�c�dent
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

		// M�morisation de l'etat de l'objet avant sauvegarde
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
			// Restauration de l'�tat pr�c�dent
			state.Restore();
			// Fin de la transaction automatique
			__TRANSACTION_AUTO_ANNULE__;
			return false;
		}

		// Fin de la transaction automatique
		__TRANSACTION_AUTO_VALIDE__;

		// L'objet est supprim�
		SetSupprimer();

		return true;
	}

	std::string CControle::GetLibelle()
	{
		// L'objet doit �tre initialis�
		if (!Initialiser()) return std::string();

		return m_sLibelle;
	}

	bool CControle::SetLibelle(std::string sName)
	{
		// L'objet doit �tre initialis�
		if (!Initialiser()) return false;

		// Le champ est modifi� uniquement si sa valeur change.
		if (m_sLibelle != sName)
		{
			// Affectation de la nouvelle valeur.
			m_sLibelle = sName;

			// Marquer l'objet comme modifi�.
			SetModifier();
		}

		// Le changement de valeur a r�ussi.
		return true;
	}

	std::string CControle::GetType()
	{
		// L'objet doit �tre initialis�
		if (!Initialiser()) return std::string();

		return m_sType;
	}

	bool CControle::SetType(std::string sType)
	{
		// L'objet doit �tre initialis�
		if (!Initialiser()) return false;

		// Le champ est modifi� uniquement si sa valeur change.
		if (m_sType != sType)
		{
			// Affectation de la nouvelle valeur.
			m_sType = sType;

			// Marquer l'objet comme modifi�.
			SetModifier();
		}

		// Le changement de valeur a r�ussi.
		return true;
	}

	unsigned long CControle::GetResIdent()
	{
		// L'objet doit �tre initialis�
		if (!Initialiser()) return DefULong;

		return m_ulResdent;
	}

	bool CControle::SetResIdent(unsigned long ulResIdent)
	{
		// L'objet doit �tre initialis�
		if (!Initialiser()) return false;

		// Le champ est modifi� uniquement si sa valeur change.
		if (m_ulResdent != ulResIdent)
		{
			// Affectation de la nouvelle valeur.
			m_ulResdent = ulResIdent;

			// Marquer l'objet comme modifi�.
			SetModifier();
		}

		// Le changement de valeur a r�ussi.
		return true;
	}










	//! Constructeur
	CControleListe::CControleListe()
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des donn�es. */
		InitialiserDonnees();
	}

	//! Destructeur
	CControleListe::~CControleListe(void)
	{
		/* Initialisation des donn�es. */
		InitialiserDonnees();
	}

	//! Constructeur par copie.
	CControleListe::CControleListe(const CControleListe &source)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des donn�es. */
		InitialiserDonnees();

		/* Clonage des donn�es. */
		ClonnerDonnees(source);
	}

	//! Op�rateur =
	CControleListe & CControleListe::operator=(const CControleListe &source)
	{
		/* Clonage des donn�es. */
		ClonnerDonnees(source);

		return *this;
	}

	//! Clonage des donn�es utilis�e par le constructeur par copie ainsi que l'op�rateur =
	void CControleListe::ClonnerDonnees(const CControleListe &source)
	{
		/* Initialisation des donn�es. */
		InitialiserDonnees();

		/* Copie des variables membres de l'objet. */
		m_ulResIdent = source.m_ulResIdent;

		/* Copie des pointeurs membres de l'objet. */
	}

	//! Initialisation des donn�es membres de la classe
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
			osQuery << "select CTR_IDENT, CTR_LIBELLE, CTR_TYPE, CTR_RES_IDENT from CONTROLE";

			SQLite::Statement query(*CSQLiteSource::database(), osQuery.str());
			while (query.executeStep())
			{
				CControle* pControle		= new CControle(query.getColumn(0).getInt());
				pControle->m_sLibelle		= query.getColumn(1).getText();
				pControle->m_sType			= query.getColumn(2).getText();
				pControle->m_ulResdent		= query.getColumn(3).getInt();

				// L'objet est acquis
				pControle->SetAcquis();

				Add(pControle);
			}

			// L'objet est acquis
			if (GetSize()) SetAcquis();
		}

		// L'objet est initialis�
		SetInitaliser();

		return true;
	}

	//! Verification
	bool CControleListe::Verifier(std::string* sMsg)
	{
		// V�rifications de base
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


		// Les objets sont supprim�s
		SetSupprimer();

		return true;
	}

	bool CControleListe::InitialiserAPartirDeResIdent(unsigned long ulResIdent)
	{
		if (DoitEtreInitialiser() == false) return true;
		if (PeutEtreInitialiser() == false) return false;

		//! Initialisation des donn�es membres de la classe
		InitialiserDonnees();
		
		m_ulResIdent = ulResIdent;

		// Initialisation depuis la base
		if (!EstAcquis())
		{
			std::ostringstream osQuery;
			osQuery << "select CTR_IDENT, CTR_LIBELLE, CTR_TYPE, CTR_RES_IDENT from CONTROLE where CTR_RES_IDENT = " << ToQuery(ulResIdent);

			SQLite::Statement query(*CSQLiteSource::database(), osQuery.str());
			while (query.executeStep())
			{
				CControle* pControle		= new CControle(query.getColumn(0).getInt());
				pControle->m_sLibelle		= query.getColumn(1).getText();
				pControle->m_sType			= query.getColumn(2).getText();
				pControle->m_ulResdent		= query.getColumn(3).getInt();

				// L'objet est acquis
				pControle->SetAcquis();

				Add(pControle);
			}

			// L'objet est acquis
			if (GetSize()) SetAcquis();
		}

		// L'objet est initialis�
		SetInitaliser();

		return true;
	}

	unsigned long CControleListe::GetResIdent()
	{
		// L'objet doit �tre initialis�
		if (!Initialiser()) return DefULong;

		return m_ulResIdent;
	}

	bool CControleListe::SetResIdent(unsigned long ulResIdent)
	{
		if (!Initialiser()) return false;

		// Mise � jour de la variable
		if (m_ulResIdent != ulResIdent)
		{
			m_ulResIdent = ulResIdent;
			SetModifier();
		}

		// Mise � jour de la liste
		for (int i = 0; i < GetSize(); i++)
			if (GetAt(i)->SetResIdent(ulResIdent) == false)
				return false;

		return true;
	}

}
