/*
 *		G�n�rateur de fichier li� aux ressources : GOYER
 **/


#pragma once


// Inclusions des �v�nements
#include "GyResGen/events/PropertyGridListener.h"

// Inclusions GDevStudioModulesManager
#include "GDevStudioModulesManager/ModuleInfo.h"
#include "GDevStudioModulesManager/RessourcesServer.h"

// Inclusions STL
#include <array>

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/UUID.h>

// Inclusions SQLite
#include <SQLiteCpp/Database.h>
#include <SQLite/TransactionEx.h>


namespace GyResGen 
{
	class CRessourceGenerateur : public GDSMM::CRessourcesServer::CRessourceModule
	{
	public:
		// Constructeur
		CRessourceGenerateur();
		// Destructeur
		virtual ~CRessourceGenerateur();

	public:
		// Informations sur le module
		virtual GDSMM::ModuleInfo& GetModuleInfo();
		// Ouverture de la connection � la base
		// (Si utilis� par le module)
		virtual void OpenDatabase(std::string sDatabaseFileName);
		// Fermeture de la connection � la base
		// (Si utilis� par le module)
		virtual void CloseDatabase();
		// M�thode d'activation du module
		virtual void Activer(bool bActive);

		// Listeners
		CPropertyGridListener*			PropertyGridListener() { return pPropertyGridListener; }

	public:
		// Initialisation du module
		void OnInit();

	protected:
		// Informations sur le module
		GDSMM::ModuleInfo moduleInfo;
		//	
		CPropertyGridListener*			pPropertyGridListener;
	};
}
