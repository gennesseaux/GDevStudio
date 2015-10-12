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
#include <DObject/DObjBase.h>
#include <DObject/DObjListe.h>

// Inclusions
#include <GDevStudioApi/Controle.h>

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/Logger.h>
#include <Poco/UUID.h>

namespace GyResGen
{
	// Classe CControle
	class CControle : public DObject::CDObjBase
	{
	public:
		//! Constructeur
		CControle(unsigned long ulId, CDObject* pOwner);
		//! Destructeur
		~CControle(void);

		//! Constructeur
		CControle() = delete;
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

	// Gestion des évènements
	public:
		//! Notification d'évènement
		virtual void OnSupprimer(CDObject* pDObject, CDObject* sender);

	public:
		// Classe par défaut
		std::string GetDefClasseNom();
		// Nom de variable par défaut
		std::string GetDefVariableNom();

	protected:
		// Conversion de l'Id du controle en string
		std::string IdToString();

	public:
		std::string GetClasseNom();
		bool SetClasseNom(std::string sClasseNom);

		std::string GetVariableNom();
		bool SetVariableNom(std::string sVariableNom);

	protected:
		// Données membres
		std::string	m_sClasseNom;
		std::string	m_sVariableNom;
	};
}
