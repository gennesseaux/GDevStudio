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
//	 R�visions		:	16/7/2014 : 
//	-----------------------------------------------------------------------
//*/

#pragma once

// Inclusions
#include <DObject/DObjBase.h>
#include <DObject/DObjListe.h>
#include <Poco/Path.h>

namespace GDSObject
{
	class CProjetListe;
	class CFiltreListe;

	// Classe CDObjTest
	class CProjet : public DObject::CDObjBase
	{
	public:
		//! Constructeur
		CProjet(unsigned long ulId = DefULong);
		//! Destructeur
		~CProjet(void);

		//! Constructeur par copie.
		CProjet(const CProjet &source);
		//! Op�rateur =
		CProjet &operator=(const CProjet &source);
		//! Clonage des donn�es utilis�e par le constructeur par copie ainsi que l'op�rateur =
		void ClonnerDonnees(const CProjet &source);

	public:
		//! Initialisation des donn�es membres de la classe
		virtual void InitialiserDonnees();
		//! Initialisation de l'objet
		virtual bool Initialiser();
		//! V�rifie si toutes les donn�es obligatoire pour 
		//! la sauvegarde sont renseign�es
		virtual bool Verifier(std::string* = NULL);
		//! Sauvegarde de l'objet
		virtual bool Sauver();
		//! Suppression de l'objet
		virtual bool Supprimer();

	public:
		std::string GetLibelle();
		bool SetLibelle(std::string sName);

		std::string GetDesciption();
		bool SetDesciption(std::string sDesciption);

		Poco::Path GetHFolder();
		bool SetHFolder(Poco::Path ptHFolder);

		Poco::Path GetCppFolder();
		bool SetCppFolder(Poco::Path ptCppFolder);

		CFiltreListe* GetFiltreListe(bool bInit = true);

	protected:
		// Donn�es membres
		std::string		m_sLibelle;
		std::string		m_sDescription;
		Poco::Path		m_ptHFolder;
		Poco::Path		m_ptCppFolder;
		// Pointeurs
		CFiltreListe*	m_pFiltreListe;		// Liste des diltre directement associ�s au projet
	};



	// Classe CDObjTestListe
	class CProjetListe : public DObject::CDObjListe<CProjet>
	{
	public:
		//! Constructeur
		CProjetListe();
		//! Destructeur
		~CProjetListe(void);

		//! Constructeur par copie.
		CProjetListe(const CProjetListe &source);
		//! Op�rateur =
		CProjetListe &operator=(const CProjetListe &source);
		//! Clonage des donn�es utilis�e par le constructeur par copie ainsi que l'op�rateur =
		void ClonnerDonnees(const CProjetListe &source);

	public:
		//! Initialisation des donn�es membres de la classe
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
