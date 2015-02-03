

// Inclusions
#include "Stdafx.h"
#include "PluginLoader.h"

// Inclusions Poco
#include <Poco/DirectoryIterator.h>
#include <Poco/Path.h>


// Constructeur
CPluginLoader::CPluginLoader()
{
	// Chemin du répertoire plugins
	Poco::Path pluginsFolder = Poco::Path::current();
	pluginsFolder.pushDirectory("plugins");
	_sFolder = pluginsFolder.toString();


	// Enumérations des DLL du répertoire plugins
	Poco::DirectoryIterator dirIterator(_sFolder);
	Poco::DirectoryIterator end;
	std::vector<std::string> _vFiles;
	while (dirIterator != end)
	{
		Poco::Path file = dirIterator->path();
		++dirIterator;
		if(file.getExtension()=="dll")
			_vFiles.emplace_back(file.toString());
	}


	// Itération de chaque dll
	for(auto &file : _vFiles)
	{
		// Tente de charger les plugins
		try
		{
			_Loader.loadLibrary(file);

			PluginLoader::Iterator it(_Loader.begin());
			PluginLoader::Iterator end(_Loader.end());

			for(; it != end; ++it)
			{
				PluginManifest::Iterator itManifest(it->second->begin());
				PluginManifest::Iterator endManifest(it->second->end());

				for(; itManifest != endManifest; ++itManifest)
				{
					PluginDesc pluginDesc;
					pluginDesc._file = file;
					pluginDesc._classeName = itManifest->name();

					IGenerateurPlugin* pPlugin = _Loader.create(pluginDesc._classeName);
					pluginDesc._uuid = pPlugin->uuid();
					pluginDesc._type= pPlugin->type();
					pluginDesc._pluginName = pPlugin->name();
					pluginDesc._pluginDescription = pPlugin->description();
					delete pPlugin;
			
					_vPlugin.emplace_back(pluginDesc);
				}
			}
		}
		catch(...)
		{
			int toto = 0;
		}
	}
}

// Destructeur
CPluginLoader::~CPluginLoader()
{
	// Déchargement des plugins
 	for(auto &pluginDesc : _vPlugin)
	{
		try
		{
			_Loader.unloadLibrary(pluginDesc._file);
		}
		catch (...){}
	}
}

std::vector<CPluginLoader::PluginDesc>& CPluginLoader::GetPluginsDesc()
{
	return _vPlugin;
}
