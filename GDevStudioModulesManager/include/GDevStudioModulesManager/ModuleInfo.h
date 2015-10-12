
#pragma once

// Inclusions
#include "Config.h"

// Inclusions STL
#include <string>
#include <functional>

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/UUID.h>

namespace GDSMM
{
	// Donn�es expos�es par le module � l'application
	struct GDEVSTUDIOMM_API ModuleInfo
	{
		// uuid
		Poco::UUID		_uuid;
		// Abr�viation (Peut �tre utiliser pour pr�fixer le nom des tables appartenant au module en base)
		std::string		_code;
		// Nom COURT
		std::string		_name;
		// Description
		std::string		_description;

		// M�thode d'initialisation du module
		//	(Attention l'initialisation doit se faire
		//	ici et non dans le constructeur)
		std::function<void()> _init;
	};
}
