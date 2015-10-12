///*
//
//	-----------------------------------------------------------------------
//
//	 Fichier		: 	Controle.h
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
	class CControleListe;
	class CProjet;
	
	enum class ControleType
	{
		Boutton,
		CheckBox,
		Edit,
		ComboBox,
		ListBox,
		GroupBox,
		RadioButton,
		StaticText,
		Image,
		ScrollBarHorizontal,
		ScrollBarVertical,
		Slider,
		Spin,
		Progress,
		HotKey,
		List,
		Tree,
		Tab,
		Animation,
		RichEdit,
		DateTimePicker,
		MontCalendar,
		IpAdress,
		ExtendedComboBox,
		Custom,
		Syslink,
		SplitButton,
		NetworkAdress,
		CommandButton,
		MfcButton,
		MfcColorButton,
		MfcEditBrowse,
		MfcVsListBox,
		MfcFontComboBox,
		MfcMaskedEdit,
		MfcMenuButton,
		MfcPropertyGrid,
		MfcShellList,
		MfcLink,

		// Compteur et type inconnu
		Count, Inconnu
	};

	// Classe CDObjTest
	class GDEVSTUDIOAPI_API CControle : public DObject::CDObjBase
	{
		friend class CControleListe;

	public:
		//! Constructeur
		CControle(unsigned long ulId = DefULong, CDObject* pOwner = nullptr);
		//! Destructeur
		~CControle(void);

		//! Constructeur par copie.
		CControle(const CControle &source);
		//! Opérateur =
		CControle &operator=(const CControle &source);

		//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
		void ClonnerDonnees(const CControle &source);

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

		std::string GetType();
		bool SetType(std::string sType);

		unsigned long GetResIdent();
		bool SetResIdent(unsigned long ulResIdent);

		bool GetExclu();
		bool SetExclu(bool bExclu);
		
		ControleType GetControleType();
		
		CProjet* GetProjet();

	public:
		// Classe par défaut
		std::string GetDefClasse();
		// Nom de variable par défaut
		std::string GetDefName();

	protected:
		// Conversion de l'Id du controle en string
		std::string IdToString();

	protected:
		// Données membres
		std::string		m_sLibelle;
		std::string		m_sType;
		unsigned long	m_ulResdent;				// Identifiant du filtre parent

		ControleType	m_controlType = ControleType::Inconnu;

		bool			m_bExclu;
	};



	// Classe CDObjTestListe
	class CControleListe : public DObject::CDObjListe<CControle>
	{
	public:
		//! Constructeur
		CControleListe(CDObject* pOwner = nullptr);
		//! Destructeur
		~CControleListe(void);

		//! Constructeur par copie.
		CControleListe(const CControleListe &source);
		//! Opérateur =
		CControleListe &operator=(const CControleListe &source);
		//! Clonage des données utilisée par le constructeur par copie ainsi que l'opérateur =
		void ClonnerDonnees(const CControleListe &source);

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
		bool InitialiserAPartirDeResIdent(unsigned long ulResIdent);


	public:
		unsigned long GetResIdent();
		bool SetResIdent(unsigned long ulResIdent);


	protected:
		// Données membres
		unsigned long	m_ulResIdent;		// Identifiant du filtre parent
	};

}
