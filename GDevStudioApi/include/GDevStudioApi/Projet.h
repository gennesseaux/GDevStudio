///*
//
//	-----------------------------------------------------------------------
//
//	 Fichier		: 	Projet.h
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
#include "GDevStudioApi/Config.h"

// Inclusions
#include <DObject/DObjBase.h>
#include <DObject/DObjListe.h>

namespace GDSAPI
{
	class CProjetListe;
	class CFiltreListe;

	// Classe CDObjTest
	class GDEVSTUDIOAPI_API CProjet : public DObject::CDObjBase
	{
		friend class CProjetListe;

	public:
		//! Constructeur
		CProjet(unsigned long ulId = DefULong, CDObject* pOwner = nullptr);
		//! Destructeur
		~CProjet(void);

		//! Constructeur par copie.
		CProjet(const CProjet &source);
		//! Opérateur =
		CProjet &operator=(const CProjet &source);
		//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
		void ClonnerDonnees(const CProjet &source);

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
		std::string GetLibelle();
		bool SetLibelle(std::string sName);

		std::string GetDescription();
		bool SetDescription(std::string sDesciption);

		Poco::Path GetHFolder();
		bool SetHFolder(Poco::Path ptHFolder);

		Poco::Path GetCppFolder();
		bool SetCppFolder(Poco::Path ptCppFolder);

		Poco::UUID GetUuidResGen();
		bool SetUuidResGen(Poco::UUID uuid);
		bool SetUuidResGen(std::string uuid);

		Poco::UUID GetUuidClsGen();
		bool SetUuidClsGen(Poco::UUID uuid);
		bool SetUuidClsGen(std::string uuid);

		CFiltreListe* GetFiltreListe(bool bInit = true);

	protected:
		// Données membres
		std::string		m_sLibelle;
		std::string		m_sDescription;
		Poco::Path		m_ptHFolder;
		Poco::Path		m_ptCppFolder;
		Poco::UUID		m_uuidResGen;
		Poco::UUID		m_uuidClsGen;
		// Pointeurs
		CFiltreListe*	m_pFiltreListe;		// Liste des diltre directement associés au projet
	};



	// Classe CDObjTestListe
	class CProjetListe : public DObject::CDObjListe<CProjet>
	{
	public:
		//! Constructeur
		CProjetListe(CDObject* pOwner = nullptr);
		//! Destructeur
		~CProjetListe(void);

		//! Constructeur par copie.
		CProjetListe(const CProjetListe &source);
		//! Opérateur =
		CProjetListe &operator=(const CProjetListe &source);
		//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
		void ClonnerDonnees(const CProjetListe &source);

	public:
		//! Initialisation des données membres de la classe
		virtual void InitialiserDonnees();
		//! Initialisation de la liste d'objet
		virtual bool Initialiser();
		//! Verification
		virtual bool Verifier(std::string* sMsg = NULL);
		//! Sauvegarde
		virtual bool Sauver();
		//! Suppression
		virtual bool Supprimer();
	};

}
