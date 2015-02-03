


#pragma once


// Inclusions
#include "IClasseGenerateurPlugin.h"
#include "IRessourceGenerateurPlugin.h"

// Inclusions STL
#include <vector>

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/ClassLoader.h>
#include <Poco/Manifest.h>
#include <Poco/UUID.h>

//
typedef Poco::ClassLoader<IGenerateurPlugin>	PluginLoader;
typedef Poco::Manifest<IGenerateurPlugin>		PluginManifest;

class CPluginLoader
{

public:
	struct PluginDesc
	{
		Poco::UUID	_uuid;
		std::string	_file;
		std::string	_classeName;
		std::string	_pluginName;
		std::string	_pluginDescription;
		IGenerateurPlugin::Type _type;
	};

public:
	// Constructeur
	CPluginLoader();
	// Destructuer
	~CPluginLoader();

public:
	std::vector<PluginDesc>& GetPluginsDesc();

protected:
	std::vector<PluginDesc> _vPlugin;

private:
	std::string _sFolder;
	PluginLoader _Loader;
};
