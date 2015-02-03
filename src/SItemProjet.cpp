

// Inclusions
#include "Stdafx.h"
#include "GDevStudio.h"
#include "SItemProjet.h"
#include "SItemFiltre.h"

// Inclusions Poco
#include <Poco/Path.h>
#include <Poco/File.h>

//
using GDSObject::CFiltre;
using GDSObject::CFiltreListe;

enum PropID
{
	Nom,
	Description,
	CheminH,
	CheminCpp,

	GenerateurRessource,
	GenerateurClasse,
};


// Constructeur
CSItemProjet::CSItemProjet(CStructureMgr* pStructureMgr, unsigned long ulIdProjet) : CSItemStructure(SItemType::Projet,pStructureMgr), CProjet(ulIdProjet)
{
	// Ajout du projet dans la grille
	CSItemStructure::SetLibelle(CProjet::GetLibelle().c_str());
	CSItemStructure::SetImage(TreeImage::Projet);
	CSItemStructure::AjouterLigneGrille();

	// Ajout des filtres du projet
	CFiltreListe* pFiltreListe = GetFiltreListe();
	for (int i = 0; i < pFiltreListe->GetCount() ; i++)
	{
		CFiltre* pFiltre = pFiltreListe->GetAt(i);
		pFiltre->Initialiser();

		CSItemFiltre* pSItemFiltre = new CSItemFiltre(pStructureMgr,*pFiltre, this);

		pFiltreListe->RemoveAt(i);
		pFiltreListe->InsertAt(i,pSItemFiltre);
	}
}

// Destructeur
CSItemProjet::~CSItemProjet()
{
}

// Mise à jour de l'item
void CSItemProjet::UpdateTreeItem()
{
	// Force l'objet à croire qu'il n'est pas initialisé
	SetInitaliser(false);
	SetAcquis(false);

	// Mise à jour du libelle dans la grille
	CSItemStructure::SetLibelle(CProjet::GetLibelle().c_str());
}

// Interface pour la mise à jour du property grid
void CSItemProjet::UpdatePropertyGrid(CBCGPPropList* pPropList)
{
	CSItemStructure::UpdatePropertyGrid(pPropList);

	// Divers
	CBCGPProp* pGroupDivers = new CBCGPProp(_T("Divers"));
	CBCGPProp* pNom		= new CBCGPProp(_T("Nom"),							(UINT)Nom,			(_variant_t)ToString(GetLibelle()),					_T(""));
	CBCGPProp* pDesc	= new CBCGPProp(_T("Description"),					(UINT)Description,	(_variant_t)ToString(GetDescription()),				_T(""));
	CBCGPProp* pChH		= new CBCGPFileProp(_T("Chemin des fichiers .h"),	(UINT)CheminH,		(_variant_t)ToString(GetHFolder().toString()),	0,	_T(""));
	CBCGPProp* pChCpp	= new CBCGPFileProp(_T("Chemin des fichiers .cpp"),	(UINT)CheminCpp,	(_variant_t)ToString(GetCppFolder().toString()),0,	_T(""));

	pGroupDivers->AddSubItem(pNom);
	pGroupDivers->AddSubItem(pDesc);
	pGroupDivers->AddSubItem(pChH);
	pGroupDivers->AddSubItem(pChCpp);

	pPropList->AddProperty (pGroupDivers);
	
	// Générateurs
	std::vector<CPluginLoader::PluginDesc>& vClsPlugin = theApp.GetClassePlugins();
	std::vector<CPluginLoader::PluginDesc>& vResPlugin = theApp.GetRessourcePlugins();

 	CBCGPProp* pGroupGenerateurs = new CBCGPProp(_T("Générateurs"));
 	CBCGPProp* pCls		= new CBCGPProp(_T("Classes"),						(UINT)GenerateurClasse,		(_variant_t)"",		_T(""),		(DWORD_PTR)&vClsPlugin);
 	CBCGPProp* pRes		= new CBCGPProp(_T("Ressources"),					(UINT)GenerateurRessource,	(_variant_t)"",		_T(""),		(DWORD_PTR)&vResPlugin);

	for(auto &plugin : vClsPlugin)
		pCls->AddOption(ToString(plugin._pluginName),0,(DWORD_PTR)&plugin);
	pCls->AllowEdit(FALSE);

	if(GetUuidClsGen().isNull()==false)	pCls->SetValue((_variant_t)ToString(theApp.GetPlugin(GetUuidClsGen())._pluginName));

	for(auto &plugin : vResPlugin)
		pRes->AddOption(ToString(plugin._pluginName),0,(DWORD_PTR)&plugin);
	pRes->AllowEdit(FALSE);

 	if(GetUuidResGen().isNull()==false)	pRes->SetValue((_variant_t)ToString(theApp.GetPlugin(GetUuidResGen())._pluginName));

 	pGroupGenerateurs->AddSubItem(pCls);
 	pGroupGenerateurs->AddSubItem(pRes);
 
 	pPropList->AddProperty (pGroupGenerateurs);

	// Mise à jour de l'affichage
	pPropList->Invalidate();
}

LRESULT CSItemProjet::OnPropertyChanged(CBCGPProp* pProp)
{
	PropID id = (PropID)pProp->GetID();

	switch(id)
	{
		case Nom:
			{
				//
				CString sLibelle = (LPCTSTR)(_bstr_t)pProp->GetValue();

				//
				GDSObject::CProjet projet(this->GetId());
 				projet.SetLibelle(ToStdString(sLibelle));
 				projet.Sauver();

				//
				UpdateTreeItem();

				break;
			}

		case Description:
			{
				//
				CString sDescription = (LPCTSTR)(_bstr_t)pProp->GetValue();

				//
				GDSObject::CProjet projet(this->GetId());
 				projet.SetDescription(ToStdString(sDescription));
 				projet.Sauver();

				//
				UpdateTreeItem();

				break;
			}

		case CheminH:
			{
				//
				std::string sChemin= ToStdString((CString)(LPCTSTR)(_bstr_t)pProp->GetValue());

				//
				Poco::File path(sChemin);
				if(!sChemin.empty() && (!path.exists() || !path.isDirectory()))
				{
					pProp->ResetOriginalValue();
					return 0;
				}

				//
				GDSObject::CProjet projet(this->GetId());
 				projet.SetHFolder(sChemin);
 				projet.Sauver();

				//
				UpdateTreeItem();

				break;
			}

		case CheminCpp:
			{
				//
				std::string sChemin= ToStdString((CString)(LPCTSTR)(_bstr_t)pProp->GetValue());

				//
				Poco::File path(sChemin);
				if(!sChemin.empty() && (!path.exists() || !path.isDirectory()))
				{
					pProp->ResetOriginalValue();
					return 0;
				}

				//
				GDSObject::CProjet projet(this->GetId());
 				projet.SetCppFolder(sChemin);
 				projet.Sauver();

				//
				UpdateTreeItem();

				break;
			}

		case GenerateurClasse:
			{
				// Liste des plugins
				DWORD_PTR data  = pProp->GetData();
				std::vector<CPluginLoader::PluginDesc>* vClslugin = (std::vector<CPluginLoader::PluginDesc>*)data;

				// Option selectionnée
				int iIndex = pProp->GetSelectedOption();
				DWORD_PTR dataOption  = pProp->GetOptionData(iIndex);
				CPluginLoader::PluginDesc* pPlugin = (CPluginLoader::PluginDesc*)dataOption;

				//
				GDSObject::CProjet projet(this->GetId());
 				projet.SetUuidClsGen(pPlugin->_uuid);
 				projet.Sauver();

				//
				UpdateTreeItem();

				break;
			}

		case GenerateurRessource:
			{
				// Liste des plugins
				DWORD_PTR data  = pProp->GetData();
				std::vector<CPluginLoader::PluginDesc>* vResPlugin = (std::vector<CPluginLoader::PluginDesc>*)data;

				// Option selectionnée
				int iIndex = pProp->GetSelectedOption();
				DWORD_PTR dataOption  = pProp->GetOptionData(iIndex);
				CPluginLoader::PluginDesc* pPlugin = (CPluginLoader::PluginDesc*)dataOption;

				//
				GDSObject::CProjet projet(this->GetId());
 				projet.SetUuidResGen(pPlugin->_uuid);
 				projet.Sauver();

				//
				UpdateTreeItem();

				break;
			}
	}

	return 0;
}

bool CSItemProjet::CanDrag()
{
	return false;
}

bool CSItemProjet::CanDrop(CSItemStructure* pSItemDrag)
{
	return false;
}
