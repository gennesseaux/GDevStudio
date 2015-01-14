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
#include <Poco/File.h>

namespace GDSObject
{
	class CRessourceListe;
	class CControleListe;

	// Classe CDObjTest
	class CRessource : public DObject::CDObjBase
	{
		friend class CRessourceListe;

	public:
		//! Constructeur
		CRessource(unsigned long ulId = DefULong);
		//! Destructeur
		~CRessource(void);

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

	public:
		std::string GetLibelle();
		bool SetLibelle(std::string sName);

		Poco::File GetFile();
		bool SetFile(Poco::File file);

		unsigned long GetFtrIdent();
		bool SetFtrIdent(unsigned long ulFtrIdent);
		
		CControleListe* GetControleListe(bool bInit = true);

	protected:
		// Données membres
		std::string		m_sLibelle;
		Poco::File		m_file;
		unsigned long	m_ulFtrIdent;			// Identifiant du filtre parent
		// Pointeurs
		CControleListe*	m_pControleListe;		// Liste des contrôles de la ressource
	};



	// Classe CDObjTestListe
	class CRessourceListe : public DObject::CDObjListe<CRessource>
	{
	public:
		//! Constructeur
		CRessourceListe();
		//! Destructeur
		~CRessourceListe(void);

		//! Constructeur par copie.
		CRessourceListe(const CRessourceListe &source);
		//! Opérateur =
		CRessourceListe &operator=(const CRessourceListe &source);
		//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
		void ClonnerDonnees(const CRessourceListe &source);

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
		bool InitialiserAPartirDeFtrIdent(unsigned long ulFtrIdent);


	public:
		unsigned long GetFtrIdent();
		bool SetFtrIdent(unsigned long ulFtrIdent);


	protected:
		// Données membres
		unsigned long	m_ulFtrIdent;		// Identifiant du filtre parent
	};

}
