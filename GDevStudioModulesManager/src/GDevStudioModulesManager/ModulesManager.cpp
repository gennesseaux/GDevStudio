

// Inclusions
#include "Stdafx.h"
#include "GDevStudioModulesManager\ModulesManager.h"
#include "GDevStudioModulesManager\events\PropertyGridEvent.h"

// Inclusions Poco
#include <Poco/DirectoryIterator.h>
#include <Poco/File.h>
#include <Poco/Path.h>


// Singleton
GDSMM::CModulesManager& GDSMM::CModulesManager::ModulesManager()
{
	// Since it's a static variable, if the class has already been created,
	// It won't be created again.
	// And it **is** thread-safe in C++11.
	static CModulesManager _instance;
	// Return a reference to our instance.
	return _instance;
}

// Constructeur
GDSMM::CModulesManager::CModulesManager()
{
	// Chemin du répertoire plugins
	Poco::Path modulesFolder = Poco::Path::current();
	modulesFolder.pushDirectory("modules");

	// Création du répertoire
	Poco::File(modulesFolder).createDirectories();

	// Chargement des modules
	loadModules();
}

// Destructeur
GDSMM::CModulesManager::~CModulesManager()
{
	// Déchargement des modules
 	for(auto &file : _RessourcesFiles)
	{
		try { _ressourceLoader.unloadLibrary(file); }
		catch (...){}
	}
 	for(auto &file : _ClassesFiles)
	{
		try { _classeLoader.unloadLibrary(file); }
		catch (...){}
	}
}

void GDSMM::CModulesManager::loadModules()
{
	loadRessourceModules();
	loadClassesModules();
}

void GDSMM::CModulesManager::loadRessourceModules()
{
	// Chemin du répertoire plugins
	Poco::Path modulesFolder = Poco::Path::current();
	modulesFolder.pushDirectory("modules");

	// Enumérations des DLL du répertoire plugins
	Poco::DirectoryIterator dirIterator(modulesFolder.toString());
	Poco::DirectoryIterator end;
	std::vector<std::string> _vDllFiles;
	while (dirIterator != end)
	{
		Poco::Path file = dirIterator->path();
		++dirIterator;
		if(file.getExtension()=="dll")
			_vDllFiles.emplace_back(file.toString());
	}

	// Itération de chaque dll
	for(auto &file : _vDllFiles)
	{
		// Tente de charger les plugins
		try
		{
			_ressourceLoader.loadLibrary(file);

			RessourceLoader::Iterator it(_ressourceLoader.begin());
			RessourceLoader::Iterator end(_ressourceLoader.end());

			for(; it != end; ++it)
			{
				RessourceManifest::Iterator itManifest(it->second->begin());
				RessourceManifest::Iterator endManifest(it->second->end());

				for(; itManifest != endManifest; ++itManifest)
				{
					CRessourcesServer::CRessourceModule& module = _ressourceLoader.instance(itManifest->name());
					_RessourceServer.addCRessourceModule(module);
				}

			}
			
			_RessourcesFiles.push_back(file);
		}
		catch(...) {}
	}
}

void GDSMM::CModulesManager::loadClassesModules()
{
	Poco::Path modulesFolder = Poco::Path::current();
	modulesFolder.pushDirectory("modules");

	// Enumérations des DLL du répertoire plugins
	Poco::DirectoryIterator dirIterator(modulesFolder.toString());
	Poco::DirectoryIterator end;
	std::vector<std::string> _vDllFiles;
	while (dirIterator != end)
	{
		Poco::Path file = dirIterator->path();
		++dirIterator;
		if(file.getExtension()=="dll")
			_vDllFiles.emplace_back(file.toString());
	}

	// Itération de chaque dll
	for(auto &file : _vDllFiles)
	{
		// Tente de charger les plugins
		try
		{
			_classeLoader.loadLibrary(file);

			ClasseLoader::Iterator it(_classeLoader.begin());
			ClasseLoader::Iterator end(_classeLoader.end());

			for(; it != end; ++it)
			{
				ClasseManifest::Iterator itManifest(it->second->begin());
				ClasseManifest::Iterator endManifest(it->second->end());

				for(; itManifest != endManifest; ++itManifest)
				{
					CClassesServer::CClasseModule& module = _classeLoader.instance(itManifest->name());
					_ClasseServer.addCClasseModule(module);
				}

			}
			
			_ClassesFiles.push_back(file);
		}
		catch(...) {}
	}
}

void GDSMM::CModulesManager::ActiverModuleClasse(Poco::UUID uuid)
{
	getClassesServer().ActiverModule(uuid);
}

void GDSMM::CModulesManager::ActiverModuleRessource(Poco::UUID uuid)
{
	getRessourcesServer().ActiverModule(uuid);
}

void GDSMM::CModulesManager::DesactiverModulesClasse()
{
	getClassesServer().DesactiverModules();
}

void GDSMM::CModulesManager::DesactiverModulesRessource()
{
	getRessourcesServer().DesactiverModules();
}

