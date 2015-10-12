

// Inclusions
#include "Stdafx.h"
#include "GDevStudioModulesManager\ClassesServer.h"
#include "GDevStudioApi\SQLiteSource.h"

// Inclusions STL
#include <algorithm>


// Constructeur
GDSMM::CClassesServer::CClassesServer()
{

}

// Destructeur
GDSMM::CClassesServer::~CClassesServer()
{
	//for(	ClasseModuleVector::const_iterator it = this->_ClasseModules.begin();
	//		it != this->_ClasseModules.end();
	//		++it
	//	)
	//{
	//	delete *it;
	//}
}

// Ajout d'un module
void GDSMM::CClassesServer::addCClasseModule(CClassesServer::CClasseModule& ClasseModule)
{
	this->_ClasseModules.push_back(&ClasseModule);
}

// Activation du module
void GDSMM::CClassesServer::ActiverModule(Poco::UUID uuid)
{
	for(auto& module : this->_ClasseModules)
	{
		module->OpenDatabase(GDSAPI::CSQLiteSource::SQLiteSource().GetDataBase()->getFilename());
		module->Activer(module->uuid()==uuid);
	}
}

// Désactivation des modules
void GDSMM::CClassesServer::DesactiverModules()
{
	for(auto& module : this->_ClasseModules)
	{
		module->CloseDatabase();
		module->Activer(false);
	}
}

//
GDSMM::CClassesServer::ClasseModuleVector& GDSMM::CClassesServer::getModules()
{
	return this->_ClasseModules;
}

// Nombre total de modules enregistrés
size_t GDSMM::CClassesServer::getModulesCount() const
{
	return this->_ClasseModules.size();
}

// Récupère le module par son index
GDSMM::CClassesServer::CClasseModule* GDSMM::CClassesServer::getModule(size_t Index)
{
	return this->_ClasseModules.at(Index);
}

GDSMM::CClassesServer::CClasseModule* GDSMM::CClassesServer::getModule(Poco::UUID uuid)
{
	auto it = std::find_if(_ClasseModules.begin(),_ClasseModules.end(),[=](GDSMM::CClassesServer::CClasseModule* pModule) { return pModule->uuid() == uuid; });
	return (it != _ClasseModules.end()) ? *it : nullptr;
}
