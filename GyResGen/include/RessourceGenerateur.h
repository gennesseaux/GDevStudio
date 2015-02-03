/*
 *		Générateur de fichier lié aux ressources : GOYER
 **/


#pragma once


// Inclusions
#include <IRessourceGenerateurPlugin.h>

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/UUID.h>


namespace GyResGen 
{
	class CRessourceGenerateur : public IRessourceGenerateurPlugin
	{
	public:
		// Constructeur
		CRessourceGenerateur();
		// Destructeur
		~CRessourceGenerateur();

	public:
		// uuid du plugin
		virtual Poco::UUID uuid();
		// Nom COURT donné au plugin
		virtual std::string name() const;
		// Description du plugin
		virtual std::string description() const;

		// Méthode d'initialisation (Attention l'initialisation doit se faire ici et non dans le constructeur)
		virtual void init();

	protected:

	private:
	};
}