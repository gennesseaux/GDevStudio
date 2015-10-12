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

	// Gestion des �v�nements
	public:
		//! Notification d'�v�nement
		virtual void OnSupprimer(CDObject* pDObject, CDObject* sender);

	public:
		// Classe par d�faut
		std::string GetDefClasseNom();
		// Nom de variable par d�faut
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
		// Donn�es membres
		std::string	m_sClasseNom;
		std::string	m_sVariableNom;
	};
}
