///*
//
//	-----------------------------------------------------------------------
//
//	 Fichier		: 	Filtre.h
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
#include <Poco/Path.h>

namespace GDSObject
{
	class CFiltreListe;
	class CRessourceListe;

	enum class FiltreType
	{
		Filtre,
		SQL,
		SQLite,
		Ressource
	};

	// Classe CDObjTest
	class CFiltre : public DObject::CDObjBase
	{
		friend class CFiltreListe;

	public:
		//! Constructeur
		CFiltre(unsigned long ulId = DefULong);
		//! Destructeur
		~CFiltre(void);

		//! Constructeur par copie.
		CFiltre(const CFiltre &source);
		//! Opérateur =
		CFiltre &operator=(const CFiltre &source);

		//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
		void ClonnerDonnees(const CFiltre &source);

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

	public:
		std::string GetLibelle();
		bool SetLibelle(std::string sName);

		GDSObject::FiltreType GetType();
		bool SetType(GDSObject::FiltreType iType);

		unsigned long GetPrjIdent();
		bool SetPrjIdent(unsigned long ulPrjIdent);

		unsigned long GetFtrIdent();
		bool SetFtrIdent(unsigned long ulFtrIdent);

		Poco::Path GetHFolder();
		bool SetHFolder(Poco::Path ptHFolder);

		Poco::Path GetCppFolder();
		bool SetCppFolder(Poco::Path ptCppFolder);
		
		CFiltreListe* GetFiltreListe(bool bInit = true);
		CRessourceListe* GetRessourceListe(bool bInit = true);

	protected:
		// Données membres
		std::string			m_sLibelle;
		FiltreType			m_iType;
		unsigned long		m_ulPrjIdent;		// Identifiant du projet parent
		unsigned long		m_ulFtrIdent;		// Identifiant du filtre parent
		Poco::Path			m_ptHFolder;
		Poco::Path			m_ptCppFolder;
		// Pointeurs
		CFiltreListe*		m_pFiltreListe = nullptr;		// Liste des filtres
		CRessourceListe*	m_pRessourceListe = nullptr;	// Liste des ressouurces
	};



	// Classe CDObjTestListe
	class CFiltreListe : public DObject::CDObjListe<CFiltre>
	{
	public:
		//! Constructeur
		CFiltreListe();
		//! Destructeur
		~CFiltreListe(void);

		//! Constructeur par copie.
		CFiltreListe(const CFiltreListe &source);
		//! Opérateur =
		CFiltreListe &operator=(const CFiltreListe &source);
		//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
		void ClonnerDonnees(const CFiltreListe &source);

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

	public:
		//
		bool InitialiserAPartirDePrjIdent(unsigned long ulPrjIdent);
		//
		bool InitialiserAPartirDeFtrIdent(unsigned long ulFtrIdent);


	public:
		unsigned long GetPrjIdent();
		bool SetPrjIdent(unsigned long ulPrjIdent);

		unsigned long GetFtrIdent();
		bool SetFtrIdent(unsigned long ulFtrIdent);


	protected:
		// Données membres
		unsigned long	m_ulPrjIdent;		// Identifiant du projet parent
		unsigned long	m_ulFtrIdent;		// Identifiant du filtre parent
	};

}
