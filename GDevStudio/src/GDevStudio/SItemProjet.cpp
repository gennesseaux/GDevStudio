

// Inclusions
#include "Stdafx.h"
#include "GDevStudio/GDevStudio.h"
#include "GDevStudio/StructureMgr.h"
#include "GDevStudio/SItemProjet.h"
#include "GDevStudio/SItemFiltre.h"

// Inclusions Poco
#include <Poco/Path.h>
#include <Poco/File.h>

//
using GDSAPI::CFiltre;
using GDSAPI::CFiltreListe;

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
	GDSMM::CClassesServer& classeServer = theApp.ModulesManager()->getClassesServer();
	GDSMM::CRessourcesServer& ressourceServer = theApp.ModulesManager()->getRessourcesServer();

 	CBCGPProp* pGroupGenerateurs = new CBCGPProp(_T("Générateurs"));
 	CBCGPProp* pCls		= new CBCGPProp(_T("Classes"),						(UINT)GenerateurClasse,		(_variant_t)"",		_T(""),		(DWORD_PTR)&classeServer);
 	CBCGPProp* pRes		= new CBCGPProp(_T("Ressources"),					(UINT)GenerateurRessource,	(_variant_t)"",		_T(""),		(DWORD_PTR)&ressourceServer);


	for(auto pModule : classeServer.getModules())
		pCls->AddOption(ToString(pModule->name()),0,(DWORD_PTR)pModule);
	pCls->AllowEdit(FALSE);

	if(GetUuidClsGen().isNull()==false)
	{
		pCls->SetValue((_variant_t)ToString(classeServer.getModule(GetUuidClsGen())->name()));
		pCls->SetDescription((_variant_t)ToString(classeServer.getModule(GetUuidClsGen())->description()));
	}

	for(auto pModule : ressourceServer.getModules())
		pRes->AddOption(ToString(pModule->name()),0,(DWORD_PTR)pModule);
	pRes->AllowEdit(FALSE);

 	if(GetUuidResGen().isNull()==false)
	{
		pRes->SetValue((_variant_t)ToString(ressourceServer.getModule(GetUuidResGen())->name()));
		pRes->SetDescription((_variant_t)ToString(ressourceServer.getModule(GetUuidResGen())->description()));
	}

 	pGroupGenerateurs->AddSubItem(pCls);
 	pGroupGenerateurs->AddSubItem(pRes);
 
 	pPropList->AddProperty (pGroupGenerateurs);
	
	// PropertyGridEvent
	GDSMM::PropertyGridEvent event(this,pPropList);
	theApp.ModulesEvents()->NotifyUpdatePropertyGrid(event);

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
			GDSAPI::CProjet projet(this->GetId());
			projet.SetLibelle(ToStdString(sLibelle));
			projet.Sauver();

			//
			m_pStructureMgr->UpdateTitle(sLibelle);
			UpdateTreeItem();

			break;
		}

		case Description:
		{
			//
			CString sDescription = (LPCTSTR)(_bstr_t)pProp->GetValue();

			//
			GDSAPI::CProjet projet(this->GetId());
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
			GDSAPI::CProjet projet(this->GetId());
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
			GDSAPI::CProjet projet(this->GetId());
			projet.SetCppFolder(sChemin);
			projet.Sauver();

			//
			UpdateTreeItem();

			break;
		}

		case GenerateurClasse:
		{
			// Option selectionnée
			int iIndex = pProp->GetSelectedOption();
			DWORD_PTR dataOption  = pProp->GetOptionData(iIndex);
			GDSMM::CClassesServer::CClasseModule* pModule = (GDSMM::CClassesServer::CClasseModule*)dataOption;

			//
			GDSAPI::CProjet projet(this->GetId());
			projet.SetUuidClsGen(pModule->uuid());
			projet.Sauver();
				
			// Changement du générateur
			theApp.ModulesManager()->ActiverModuleClasse(pModule->uuid());

			//
			UpdateTreeItem();

			break;
		}

		case GenerateurRessource:
		{
			// Option selectionnée
			int iIndex = pProp->GetSelectedOption();
			DWORD_PTR dataOption  = pProp->GetOptionData(iIndex);
			GDSMM::CRessourcesServer::CRessourceModule* pModule = (GDSMM::CRessourcesServer::CRessourceModule*)dataOption;

			//
			GDSAPI::CProjet projet(this->GetId());
			projet.SetUuidResGen(pModule->uuid());
			projet.Sauver();
							
			// Changement du générateur
			theApp.ModulesManager()->ActiverModuleRessource(pModule->uuid());

			//
			UpdateTreeItem();

			break;
		}
	}

	// PropertyEvent
	GDSMM::PropertyEvent event(this,pProp);
	theApp.ModulesEvents()->NotifyUpdateProperty(event);
	
	// Mise à jour dans la grille
	UpdateTreeItem();

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
