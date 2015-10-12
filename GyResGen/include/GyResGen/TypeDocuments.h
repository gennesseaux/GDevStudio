
#pragma once

// Inclusions STL
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/UUID.h>


namespace GyResGen
{
	// Type de document pouvant être généré
	class CTypeDocument : public std::vector<std::tuple<int,Poco::UUID,std::string,std::string>>
	{
	public:
		// Constructeur
		CTypeDocument()
		{
			this->push_back(std::make_tuple(0,	Poco::UUID("dcb58164-6757-11e5-9d70-feff819cdc9f"),	"Boîte de dialogue"						,""));
			this->push_back(std::make_tuple(1,	Poco::UUID("dcb583bc-6757-11e5-9d70-feff819cdc9f"),	"Boîte de dialogue redimmensionnable"	,""));
			this->push_back(std::make_tuple(2,	Poco::UUID("dcb584ac-6757-11e5-9d70-feff819cdc9f"),	"FormView (Document et vue"				,""));
			this->push_back(std::make_tuple(3,	Poco::UUID("dcb58588-6757-11e5-9d70-feff819cdc9f"),	"TabPage redimmensionnable"				,""));
		}


		// Retourne l'UUID du document en fonction de l'index
		Poco::UUID uuid(int idx)
		{ 
			return std::get<1>(this->at(idx));
		}
		// Retourne le nom du document en fonction de l'index
		std::string Nom(int idx)
		{ 
			return std::get<2>(this->at(idx));
		}
		// Retourne la description du document en fonction de l'index
		std::string Description(int idx)
		{ 
			return std::get<3>(this->at(idx));
		}

		// Retourne le nom du document en fonction du uuid
		std::string Nom(Poco::UUID uuid)
		{ 
			auto it = std::find_if(this->begin(),this->end(),[=](std::tuple<int,Poco::UUID,std::string,std::string> tuple) { return std::get<1>(tuple) == uuid; });
			return (it != this->end()) ? std::get<2>(*it) : std::string();
		}
		// Retourne la description du document en fonction du uuid
		std::string Description(Poco::UUID uuid)
		{ 
			auto it = std::find_if(this->begin(),this->end(),[=](std::tuple<int,Poco::UUID,std::string,std::string> tuple) { return std::get<1>(tuple) == uuid; });
			return (it != this->end()) ? std::get<3>(*it) : std::string();
		}
	};

	// identifiant des propriétés utilisées dans les property grid
	enum PropID
	{
		ResDocument = 1000,
		ResClasseNom,
		ResDbMandatory,
		ResChangeHandler,
		ResWndResizer,
		ResXSuperTooltip,

		CtlClasseNom,
		CtlVariableNom,
	};
}