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
		// Donn�es membres
		Poco::UUID	m_uuidDocument;				// Identifiant du type de document � g�n�rer
		std::string	m_sClasseNom;
		bool		m_bDbMandatory;
		bool		m_bChangeHandler;
		bool		m_bWndResizer;
		bool		m_bXSuperTooltip;
	};
}
