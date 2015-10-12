
#pragma once

// Inclusions
#include "Config.h"
#include "ModuleInfo.h"

// Inclusions STL
#include <string>
#include <vector>

// Inclusions BCGControlBar
#include <BCGPPropList.h>

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/UUID.h>

// Inclusions
#include <GDevStudioApi/Ressource.h>
#include <GDevStudioApi/Controle.h>



namespace GDSMM
{
	class CRessourcesServer
	{

	// Class de définition d'un module de type générateur de ressource
	public: class CRessourceModule
	{
	public:
		// Informations sur le module
		virtual ModuleInfo& GetModuleInfo() = 0;
		// Ouverture de la connection à la base
		// 'Si utilisé par le module)
		virtual void OpenDatabase(std::string sDatabaseFileName) = 0;
		// Fermeture de la connection à la base
		// 'Si utilisé par le module)
		virtual void CloseDatabase() = 0;
		// Méthode d'activation du module
		virtual void Activer(bool bActive) = 0;

	public:
		// uuid du plugin
		virtual Poco::UUID uuid() { return GetModuleInfo()._uuid; };
		// Nom COURT donné au plugin
		virtual std::string name() { return GetModuleInfo()._name; };
		// Description du plugin
		virtual std::string description() { return GetModuleInfo()._description; };
		// Méthode d'initialisation du module
		virtual void init() { if(GetModuleInfo()._init) GetModuleInfo()._init(); };
	};

    /// <summary>A list of archive readers</summary>
    private: typedef std::vector<CRessourceModule*> RessourceModuleVector;


	public:
		// Constructeur
		CRessourcesServer();
		// Destructeur
		virtual ~CRessourcesServer();
		// Ajout d'un module
		void addCRessourceModule(CRessourcesServer::CRessourceModule& ressourceModule);
		// Activation du module
		void ActiverModule(Poco::UUID uuid);
		// Désactivation des modules
		void DesactiverModules();

		// Nombre total de modules enregistrés
		GDEVSTUDIOMM_API RessourceModuleVector& getModules();
		// Nombre total de modules enregistrés
		GDEVSTUDIOMM_API size_t getModulesCount() const;
		// Retourne le module par son index
		GDEVSTUDIOMM_API CRessourceModule* getModule(size_t Index);
		// Retourne le module par son uuid
		GDEVSTUDIOMM_API CRessourceModule* getModule(Poco::UUID uuid);
	private:
		// Liste des modules existants
		RessourceModuleVector _RessourceModules;
	};
}