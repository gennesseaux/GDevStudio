

// Inclusions
#include "Stdafx.h"
#include "GDevStudioModulesManager\RessourcesServer.h"
#include "GDevStudioApi\SQLiteSource.h"

// Inclusions STL
#include <algorithm>


// Constructeur
GDSMM::CRessourcesServer::CRessourcesServer()
{

}

// Destructeur
GDSMM::CRessourcesServer::~CRessourcesServer()
{
}

// Ajout d'un module
void GDSMM::CRessourcesServer::addCRessourceModule(CRessourcesServer::CRessourceModule& ressourceModule)
{
	// Ajout du module à la liste
	this->_RessourceModules.push_back(&ressourceModule);
	// Initialisation du module
	ressourceModule.init();
}

// Activation du module
void GDSMM::CRessourcesServer::ActiverModule(Poco::UUID uuid)
{
	for(auto& module : this->_RessourceModules)
	{
		module->OpenDatabase(GDSAPI::CSQLiteSource::SQLiteSource().GetDataBase()->getFilename());
		module->Activer(module->uuid()==uuid);
	}
}

// Désactivation des modules
void GDSMM::CRessourcesServer::DesactiverModules()
{
	for(auto& module : this->_RessourceModules)
	{
		module->CloseDatabase();
		module->Activer(false);
	}
}

//
GDSMM::CRessourcesServer::RessourceModuleVector& GDSMM::CRessourcesServer::getModules()
{
	return this->_RessourceModules;
}

// Nombre total de modules enregistrés
size_t GDSMM::CRessourcesServer::getModulesCount() const
{
	return this->_RessourceModules.size();
}

// Récupère le module par son index
GDSMM::CRessourcesServer::CRessourceModule* GDSMM::CRessourcesServer::getModule(size_t Index)
{
	return this->_RessourceModules.at(Index);
}

GDSMM::CRessourcesServer::CRessourceModule* GDSMM::CRessourcesServer::getModule(Poco::UUID uuid)
{
	auto it = std::find_if(_RessourceModules.begin(),_RessourceModules.end(),[=](GDSMM::CRessourcesServer::CRessourceModule* pModule) { return pModule->uuid() == uuid; });
	return (it != _RessourceModules.end()) ? *it : nullptr;
}

