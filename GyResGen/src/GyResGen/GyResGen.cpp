


// Inclusions
#include "Stdafx.h"
#include <vld.h>
#include "GyResGen/RessourceGenerateur.h"

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/ClassLibrary.h>

// Inclusions GDevStudioModulesManager
#include "GDevStudioModulesManager/RessourcesServer.h"


POCO_BEGIN_MANIFEST(GDSMM::CRessourcesServer::CRessourceModule)
	POCO_EXPORT_SINGLETON(GyResGen::CRessourceGenerateur)
POCO_END_MANIFEST


// Fonction appell�e au chargement de la DLL
void pocoInitializeLibrary()
{
}

// Fonction appell�e au d�chargement de la DLL
void pocoUninitializeLibrary()
{
}