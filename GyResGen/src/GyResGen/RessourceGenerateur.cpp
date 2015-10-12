

// Inclusions
#include "Stdafx.h"
#include "GyResGen/RessourceGenerateur.h"
#include "GyResGen/DObject/SQLiteHelper.h"

// Constructeur
GyResGen::CRessourceGenerateur::CRessourceGenerateur()
{
	moduleInfo._uuid = Poco::UUID("b49589d4-aae9-11e4-89d3-123b93f75cba");
	moduleInfo._code = "GRG";
	moduleInfo._name = "GyResGen";
	moduleInfo._description = "Générateur de ressources lié aux ressources pour les applications GOYER";
	moduleInfo._init = std::bind(&GyResGen::CRessourceGenerateur::OnInit, this);

	pPropertyGridListener = new CPropertyGridListener(this);
}

// Destructeur
GyResGen::CRessourceGenerateur::~CRessourceGenerateur()
{
	delete pPropertyGridListener; pPropertyGridListener = nullptr;
}

// Initialisation du module
void GyResGen::CRessourceGenerateur::OnInit()
{
}

// Informations sur le module
GDSMM::ModuleInfo& GyResGen::CRessourceGenerateur::GetModuleInfo()
{
	return moduleInfo;
}

// Ouverture de la connection à la base
// (Si utilisé par le module)
void GyResGen::CRessourceGenerateur::OpenDatabase(std::string sDatabaseFileName)
{
	CSQLiteHelper::SQLiteHelper().InitConnexion(sDatabaseFileName);
}

// Fermeture de la connection à la base
// (Si utilisé par le module)
void GyResGen::CRessourceGenerateur::CloseDatabase()
{
	CSQLiteHelper::SQLiteHelper().Close();
}

// Méthode d'activation du module
void GyResGen::CRessourceGenerateur::Activer(bool bActive)
{
	pPropertyGridListener->Register(bActive);
}
