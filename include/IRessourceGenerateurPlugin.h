///*
//
//	-----------------------------------------------------------------------
//
//	 Fichier		: 	IRessourceGenerateurPlugin.h
//
//	 Auteur			:	GENNESSEAUX Jocelyn
//
//	 Description	:	Interface pour le plugin de g�n�ration des classes li�es aux ressources
//
//	-----------------------------------------------------------------------
//	 R�visions		:	30/01/2015 : 
//	-----------------------------------------------------------------------
//*/

#pragma once

// Inclusions
#include "IGenerateurPlugin.h"

class IRessourceGenerateurPlugin : public IGenerateurPlugin
{
public:
	// Type de plugin
	virtual Type type() const { return Ressource; };
};
