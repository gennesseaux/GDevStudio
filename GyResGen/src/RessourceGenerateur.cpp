

// Inclusions
#include "RessourceGenerateur.h"



// Constructeur
GyResGen::CRessourceGenerateur::CRessourceGenerateur()
{

}

// Destructeur
GyResGen::CRessourceGenerateur::~CRessourceGenerateur()
{

}

// uuid du plugin
Poco::UUID GyResGen::CRessourceGenerateur::uuid()
{
	return Poco::UUID("b49589d4-aae9-11e4-89d3-123b93f75cba");
}

// Nom COURT donné au plugin
std::string GyResGen::CRessourceGenerateur::name() const
{
	return "GyResGen";
}

// Description du plugin
std::string GyResGen::CRessourceGenerateur::description() const
{
	return "Génératueur de classe lié au ressources pour les application GOYER";
}

// Méthode d'initialisation (Attention l'initialisation doit se faire ici et non dans le constructeur)
void GyResGen::CRessourceGenerateur::init()
{

}
