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
#include "GyResGen/DObject/Ressource.h"
#include "GyResGen/DObject/SQLiteHelper.h"

// Inclusion des namespaces
using namespace SQLite;

namespace GyResGen
{
	//! Constructeur
	CRessource::CRessource(unsigned long ulId /*= DefULong*/, CDObject* pOwner /*= nullptr*/) : CDObjBase(ulId,pOwner)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Destructeur
	CRessource::~CRessource(void)
	{
		/* Initialisation des données. */
		InitialiserDonnees();
	}

	//! Constructeur par copie.
	CRessource::CRessource(const CRessource &source)
	{
		/* Initialisation des pointeurs. */

		/* Initialisation des données. */
		InitialiserDonnees();

		/* Clonage des données. */
		ClonnerDonnees(source);
	}

	//! Opérateur =
	CRessource & CRessource::operator=(const CRessource &source)
	{
		/* Initialisation des pointeurs. */

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
		m_uuidDocument = source.m_uuidDocument;
		m_sClasseNom = source.m_sClasseNom;
		m_bDbMandatory = source.m_bDbMandatory;
		m_bChangeHandler = source.m_bChangeHandler;
		m_bWndResizer = source.m_bWndResizer;
		m_bXSuperTooltip = source.m_bXSuperTooltip;
	}

	//! Initialisation des données membres de la classe
	void CRessource::InitialiserDonnees()
	{
		m_uuidDocument = Poco::UUID();
		m_sClasseNom = std::string();
		m_bDbMandatory = false;
		m_bChangeHandler = false;
		m_bWndResizer = false;
		m_bXSuperTooltip = false;
	}

	//! Initialisation de l'objet
	bool CRessource::Initialiser()
	{
		if (DoitEtreInitialiser() == false) return true;

		// Initialisation depuis la base
		if (!EstAcquis() && m_ulId!=DefULong)
		{
			std::ostringstream osQuery;
			osQuery << "select RES_UUID_DOCUMENT, RES_CLASSE_NOM, RES_DB_MANDATORY, RES_CHANGE_HANDLER, RES_WND_RESIZER, RES_DB_XSUPER_TOOLTIP from GRG_RESSOURCE where RES_IDENT = " << ToQuery(m_ulId);
			
			SQLite::Statement query(*CSQLiteHelper::Database(), osQuery.str());
			if (query.executeStep())
			{
				m_uuidDocument		= query.getColumn(0).isNull() ? Poco::UUID() : Poco::UUID(query.getColumn(0).getText());
				m_sClasseNom		= query.getColumn(1).isNull() ? std::string() : query.getColumn(1).getText();
				m_bDbMandatory		= query.getColumn(2).isNull() ? false : (bool)query.getColumn(2).getInt();
				m_bChangeHandler	= query.getColumn(3).isNull() ? false : (bool)query.getColumn(3).getInt();
				m_bWndResizer		= query.getColumn(4).isNull() ? false : (bool)query.getColumn(4).getInt();
				m_bXSuperTooltip	= query.getColumn(5).isNull() ? false : (bool)query.getColumn(5).getInt();

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

		return true;
	}

	bool CRessource::Sauver()
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
					osQuery << "insert into GRG_RESSOURCE (RES_IDENT, RES_UUID_DOCUMENT, RES_CLASSE_NOM, RES_DB_MANDATORY, RES_CHANGE_HANDLER, RES_WND_RESIZER, RES_DB_XSUPER_TOOLTIP)";
					osQuery << " values (";
					osQuery << "	" << ToQuery(m_ulId) << ",";
					osQuery << "	" << ToQuery(m_uuidDocument.toString()) << ",";
					osQuery << "	" << ToQuery(m_sClasseNom) << ",";
					osQuery << "	" << ToQuery(m_bDbMandatory) << ",";
					osQuery << "	" << ToQuery(m_bChangeHandler) << ",";
					osQuery << "	" << ToQuery(m_bWndResizer) << ",";
					osQuery << "	" << ToQuery(m_bXSuperTooltip) << " ";
					osQuery << ");";

					CSQLiteHelper::Database()->exec(osQuery.str());
				}

				else if (EstModifier())
				{
					std::ostringstream osQuery;
					osQuery << "update GRG_RESSOURCE set";
					osQuery << "	RES_UUID_DOCUMENT = "		<< ToQuery(m_uuidDocument.toString()) << ",";
					osQuery << "	RES_CLASSE_NOM = "			<< ToQuery(m_sClasseNom) << ",";
					osQuery << "	RES_DB_MANDATORY = "		<< ToQuery(m_bDbMandatory) << ",";
					osQuery << "	RES_CHANGE_HANDLER = "		<< ToQuery(m_bChangeHandler) << ",";
					osQuery << "	RES_WND_RESIZER = "			<< ToQuery(m_bWndResizer) << ",";
					osQuery << "	RES_DB_XSUPER_TOOLTIP = "	<< ToQuery(m_bXSuperTooltip) << " ";
					osQuery << "where";
					osQuery << "	RES_IDENT = "				<< ToQuery(m_ulId) << ";";

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

	bool CRessource::Supprimer()
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
			osQuery << "delete from GRG_RESSOURCE where RES_IDENT = " << ToQuery(m_ulId);

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
	
	void CRessource::OnSupprimer(CDObject* pDObject,CDObject* sender)
	{
	}

	Poco::UUID CRessource::GetUuidDocument()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return Poco::UUID();

		return m_uuidDocument;
	}

	bool CRessource::SetUuidDocument(Poco::UUID uuid)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_uuidDocument != uuid)
		{
			// Affectation de la nouvelle valeur.
			m_uuidDocument = uuid;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	bool CRessource::SetUuidDocument(std::string uuid)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_uuidDocument.toString() != uuid)
		{
			// Affectation de la nouvelle valeur.
			m_uuidDocument = Poco::UUID(uuid);

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}
	
	std::string CRessource::GetClasseNom()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return std::string();

		return m_sClasseNom;
	}

	bool CRessource::SetClasseNom(std::string sClasseNom)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

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

	bool CRessource::GetDbMandatory()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		return m_bDbMandatory;
	}

	bool CRessource::SetDbMandatory(bool bDbMandatory)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_bDbMandatory != bDbMandatory)
		{
			// Affectation de la nouvelle valeur.
			m_bDbMandatory = bDbMandatory;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	bool CRessource::GetChangeHandler()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		return m_bChangeHandler;
	}

	bool CRessource::SetChangeHandler(bool bChangeHandler)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_bChangeHandler != bChangeHandler)
		{
			// Affectation de la nouvelle valeur.
			m_bChangeHandler = bChangeHandler;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	bool CRessource::GetWndResizer()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		return m_bWndResizer;
	}

	bool CRessource::SetWndResizer(bool bWndResizer)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_bWndResizer != bWndResizer)
		{
			// Affectation de la nouvelle valeur.
			m_bWndResizer = bWndResizer;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

	bool CRessource::GetXSuperTooltip()
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		return m_bXSuperTooltip;
	}

	bool CRessource::SetXSuperTooltip(bool bXSuperTooltip)
	{
		// L'objet doit être initialisé
		if (!Initialiser()) return false;

		// Le champ est modifié uniquement si sa valeur change.
		if (m_bXSuperTooltip != bXSuperTooltip)
		{
			// Affectation de la nouvelle valeur.
			m_bXSuperTooltip = bXSuperTooltip;

			// Marquer l'objet comme modifié.
			SetModifier();
		}

		// Le changement de valeur a réussi.
		return true;
	}

}
