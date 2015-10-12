
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
	// Données exposées par le module à l'application
	struct GDEVSTUDIOMM_API ModuleInfo
	{
		// uuid
		Poco::UUID		_uuid;
		// Abréviation (Peut être utiliser pour préfixer le nom des tables appartenant au module en base)
		std::string		_code;
		// Nom COURT
		std::string		_name;
		// Description
		std::string		_description;

		// Méthode d'initialisation du module
		//	(Attention l'initialisation doit se faire
		//	ici et non dans le constructeur)
		std::function<void()> _init;
	};
}
