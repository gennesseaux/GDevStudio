
#pragma once

// Inclusions
#include "Config.h"
#include "ModuleInfo.h"
#include "RessourcesServer.h"
#include "ClassesServer.h"

// Inclusions
#include <string>
#include <vector>

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/ClassLoader.h>
#include <Poco/Manifest.h>
#include <Poco/UUID.h>

namespace GDSMM
{
	//
    typedef std::vector<std::string> ModulesFiles;
	typedef Poco::ClassLoader<CRessourcesServer::CRessourceModule>	RessourceLoader;
	typedef Poco::Manifest<CRessourcesServer::CRessourceModule>		RessourceManifest;
	typedef Poco::ClassLoader<CClassesServer::CClasseModule>		ClasseLoader;
	typedef Poco::Manifest<CClassesServer::CClasseModule>			ClasseManifest;

	//
	class GDEVSTUDIOMM_API CModulesManager
	{
	public:
		static CModulesManager& ModulesManager();

	protected:
		// Constructeur
		CModulesManager();
		// Destructuer
		~CModulesManager();

	protected:
		CModulesManager(CModulesManager const&) = delete;             // Copy construct
		CModulesManager(CModulesManager&&) = delete;                  // Move construct
		CModulesManager& operator=(CModulesManager const&) = delete;  // Copy assign
		CModulesManager& operator=(CModulesManager &&) = delete;      // Move assign


	public:
		// Accès au server de classe
		CClassesServer& getClassesServer() { return this->_ClasseServer; }
		// Accès au server de ressource
		CRessourcesServer& getRessourcesServer() { return this->_RessourceServer; }

	public:
		// Activation du module de classe
		void ActiverModuleClasse(Poco::UUID uuid);
		// Activation du module de ressource
		void ActiverModuleRessource(Poco::UUID uuid);

		// Désactivation des modules de classe
		void DesactiverModulesClasse();
		// Désactivation des modules de ressource
		void DesactiverModulesRessource();


	protected:
		// Chargement des modules
		void loadModules();
			// Chargement des modules de type générateur de ressource
			void loadRessourceModules();
			// Chargement des modules de type générateur de classe
			void loadClassesModules();


	private:
		// Loader
		RessourceLoader	_ressourceLoader;
		ClasseLoader	_classeLoader;

		// server
		CRessourcesServer	_RessourceServer;
		CClassesServer		_ClasseServer;

		// Liste des fichiers
		ModulesFiles	_RessourcesFiles;
		ModulesFiles	_ClassesFiles;
	};

}