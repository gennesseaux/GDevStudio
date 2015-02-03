///*
//
//	-----------------------------------------------------------------------
//
//	 Fichier		: 	IRessourceGenerateurPlugin.h
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Interface pour le plugin de génération des classes liées aux ressources
//
//	-----------------------------------------------------------------------
//	 Révisions		:	30/01/2015 : 
//	-----------------------------------------------------------------------
//*/

#pragma once

// Inclusions STL
#include <string>

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/UUID.h>


class IGenerateurPlugin
{
public:
	enum Type { Ressource,Classe};

public:
	// Type de plugin
	virtual Type type() const = 0;
	// uuid du plugin
	virtual Poco::UUID uuid() = 0;
	// Nom COURT donné au plugin
	virtual std::string name() const = 0;
	// Description du plugin
	virtual std::string description() const = 0;

	// Méthode d'initialisation (Attention l'initialisation doit se faire ici et non dans le constructeur)
	virtual void init() = 0;
};
