///*
//
//	-----------------------------------------------------------------------
//
//	 Fichier		: 	Ressource.h
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Classe de test
//
//	-----------------------------------------------------------------------
//	 Révisions		:	16/7/2014 : 
//	-----------------------------------------------------------------------
//*/

#pragma once

// Inclusions
#include <DObject/DObjBase.h>
#include <DObject/DObjListe.h>

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/Logger.h>
#include <Poco/UUID.h>

namespace GyResGen
{
	// Classe CRessource
	class CRessource : public DObject::CDObjBase
	{
	public:
		//! Constructeur
		CRessource(unsigned long ulId, CDObject* pOwner);
		//! Destructeur
		~CRessource(void);

		//! Constructeur
		CRessource() = delete;
		//! Constructeur par copie.
		CRessource(const CRessource &source);
		//! Opérateur =
		CRessource &operator=(const CRessource &source);

		//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
		void ClonnerDonnees(const CRessource &source);

	public:
		//! Initialisation des données membres de la classe
		virtual void InitialiserDonnees();
		//! Initialisation de l'objet
		virtual bool Initialiser();
		//! Vérifie si toutes les données obligatoire pour 
		//! la sauvegarde sont renseignées
		virtual bool Verifier(std::string* = NULL);
		//! Sauvegarde de l'objet
		virtual bool Sauver();
		//! Suppression de l'objet
		virtual bool Supprimer();

	// Gestion des évènements
	public:
		//! Notification d'évènement
		virtual void OnSupprimer(CDObject* pDObject, CDObject* sender);

	public:
		Poco::UUID GetUuidDocument();
		bool SetUuidDocument(Poco::UUID uuid);
		bool SetUuidDocument(std::string uuid);
		
		std::string GetClasseNom();
		bool SetClasseNom(std::string sClasseNom);

		bool GetDbMandatory();
		bool SetDbMandatory(bool bDbMandatory);

		bool GetChangeHandler();
		bool SetChangeHandler(bool bChangeHandler);

		bool GetWndResizer();
		bool SetWndResizer(bool bWndResizer);

		bool GetXSuperTooltip();
		bool SetXSuperTooltip(bool bXSuperTooltip);

	protected:
		// Données membres
		Poco::UUID	m_uuidDocument;				// Identifiant du type de document à générer
		std::string	m_sClasseNom;
		bool		m_bDbMandatory;
		bool		m_bChangeHandler;
		bool		m_bWndResizer;
		bool		m_bXSuperTooltip;
	};
}
