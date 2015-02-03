


// Inclusions
#include "RessourceGenerateur.h"

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/ClassLibrary.h>


using GyResGen::CRessourceGenerateur;

POCO_BEGIN_MANIFEST(IGenerateurPlugin)
	POCO_EXPORT_CLASS(CRessourceGenerateur)
POCO_END_MANIFEST


// Fonction appell�e au chargement de la DLL
void pocoInitializeLibrary()
{
}

// Fonction appell�e au d�chargement de la DLL
void pocoUninitializeLibrary()
{
}