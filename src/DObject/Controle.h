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
//	 R�visions		:	16/7/2014 : 
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
	class CControleListe;
	
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
	class CControle : public DObject::CDObjBase
	{
		friend class CControleListe;

	public:
		//! Constructeur
		CControle(unsigned long ulId = DefULong);
		//! Destructeur
		~CControle(void);

		//! Constructeur par copie.
		CControle(const CControle &source);
		//! Op�rateur =
		CControle &operator=(const CControle &source);

		//! Clonage des donn�es utilis�e par le constructeur par copie ainsi que l'op�rateur =
		void ClonnerDonnees(const CControle &source);

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

		std::string GetType();
		bool SetType(std::string sType);

		unsigned long GetResIdent();
		bool SetResIdent(unsigned long ulResIdent);
		
		ControleType GetControleType();

	protected:
		// Donn�es membres
		std::string		m_sLibelle;
		std::string		m_sType;
		unsigned long	m_ulResdent;				// Identifiant du filtre parent

		ControleType	m_controlType = ControleType::Inconnu;
	};



	// Classe CDObjTestListe
	class CControleListe : public DObject::CDObjListe<CControle>
	{
	public:
		//! Constructeur
		CControleListe();
		//! Destructeur
		~CControleListe(void);

		//! Constructeur par copie.
		CControleListe(const CControleListe &source);
		//! Op�rateur =
		CControleListe &operator=(const CControleListe &source);
		//! Clonage des donn�es utilis�e par le constructeur par copie ainsi que l'op�rateur =
		void ClonnerDonnees(const CControleListe &source);

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
		bool InitialiserAPartirDeResIdent(unsigned long ulResIdent);


	public:
		unsigned long GetResIdent();
		bool SetResIdent(unsigned long ulResIdent);


	protected:
		// Donn�es membres
		unsigned long	m_ulResIdent;		// Identifiant du filtre parent
	};

}
