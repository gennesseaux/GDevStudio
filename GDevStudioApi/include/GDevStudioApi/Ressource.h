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
//	 R�visions		:	16/7/2014 : 
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
	class CRessourceListe;
	class CControleListe;
	class CRessourceOptionListe;
	class CProjet;

	// Classe CDObjTest
	class GDEVSTUDIOAPI_API CRessource : public DObject::CDObjBase
	{
		friend class CRessourceListe;

	public:
		//! Constructeur
		CRessource(unsigned long ulId = DefULong, CDObject* pOwner = nullptr);
		//! Destructeur
		~CRessource(void);

		//! Constructeur par copie.
		CRessource(const CRessource &source);
		//! Op�rateur =
		CRessource &operator=(const CRessource &source);

		//! Clonage des donn�es utilis�e par le constructeur par copie ainsi que l'op�rateur =
		void ClonnerDonnees(const CRessource &source);

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

	// Gestion des �v�nements
	public:
		//! Notification d'�v�nement
		virtual void OnSupprimer(CDObject* pDObject, CDObject* sender);

	public:
		std::string GetLibelle();
		bool SetLibelle(std::string sName);

		Poco::File GetFile();
		bool SetFile(Poco::File file);

		unsigned long GetFtrIdent();
		bool SetFtrIdent(unsigned long ulFtrIdent);

		CControleListe* GetControleListe(bool bInit = true);
		
		CProjet* GetProjet();

	protected:
		// Donn�es membres
		std::string		m_sLibelle;
		Poco::File		m_file;
		unsigned long	m_ulFtrIdent;			// Identifiant du filtre parent
		CControleListe*	m_pControleListe;		// Liste des contr�les de la ressource
	};



	// Classe CDObjTestListe
	class CRessourceListe : public DObject::CDObjListe<CRessource>
	{
	public:
		//! Constructeur
		CRessourceListe(CDObject* pOwner = nullptr);
		//! Destructeur
		~CRessourceListe(void);

		//! Constructeur par copie.
		CRessourceListe(const CRessourceListe &source);
		//! Op�rateur =
		CRessourceListe &operator=(const CRessourceListe &source);
		//! Clonage des donn�es utilis�e par le constructeur par copie ainsi que l'op�rateur =
		void ClonnerDonnees(const CRessourceListe &source);

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

	public:
		//
		bool InitialiserAPartirDeFtrIdent(unsigned long ulFtrIdent);


	public:
		unsigned long GetFtrIdent();
		bool SetFtrIdent(unsigned long ulFtrIdent);


	protected:
		// Donn�es membres
		unsigned long	m_ulFtrIdent;		// Identifiant du filtre parent
	};

}
