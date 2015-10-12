
#pragma once

// Inclusions
#include "Config.h"
#include "ModuleInfo.h"

// Inclusions STL
#include <string>
#include <vector>

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/UUID.h>



namespace GDSMM
{
	class CClassesServer
	{

	// Class de définition d'un module de type générateur de Classe
	public: class CClasseModule
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

    // Liste des modules
    private: typedef std::vector<CClasseModule*> ClasseModuleVector;


	public:
		// Constructeur
		CClassesServer();
		// Destructeur
		virtual ~CClassesServer();
		// Ajout d'un module
		void addCClasseModule(CClassesServer::CClasseModule& ClasseModule);
		// Activation du module
		void ActiverModule(Poco::UUID uuid);
		// Désactivation des modules
		void DesactiverModules();

		// Nombre total de modules enregistrés
		GDEVSTUDIOMM_API ClasseModuleVector& getModules();
		// Nombre total de modules enregistrés
		GDEVSTUDIOMM_API size_t getModulesCount() const;
		// Retourne le module par son index
		GDEVSTUDIOMM_API CClasseModule* getModule(size_t Index);
		// Retourne le module par son uuid
		GDEVSTUDIOMM_API CClasseModule* getModule(Poco::UUID _uuid);

	private:
		// Liste des modules existants
		ClasseModuleVector _ClasseModules;
	};
}