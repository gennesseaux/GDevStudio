

// Inclusions
#include "Stdafx.h"
#include "GDevStudio/GDevStudio.h"
#include "GDevStudio/SItemFiltre.h"
#include "GDevStudio/SItemProjet.h"
#include "GDevStudio/SItemRessource.h"
#include "GDevStudio/RessourceChecker.h"

enum PropID
{
	Nom,
	CheminH,
	CheminCpp,
};


// Constructeur
CSItemFiltre::CSItemFiltre(CStructureMgr* pStructureMgr, const CFiltre &source) : CSItemStructure(SItemType::Filtre,pStructureMgr), CFiltre(source)
{
	// Ajout du Filtre dans la grille
	CSItemStructure::SetLibelle(CFiltre::GetLibelle().c_str());
	SetImage(GetType());
}

// Constructeur
CSItemFiltre::CSItemFiltre(CStructureMgr* pStructureMgr, const CFiltre &source, CSItemProjet* pSItemProjet) : CSItemFiltre(pStructureMgr,source)
{
	// Ajout du Filtre dans la grille
	CSItemStructure::AjouterLigneGrille(pSItemProjet);

	// Ajout des filtres du filtre
	CFiltreListe* pFiltreListe = GetFiltreListe();
	for (int i = 0; i < pFiltreListe->GetCount() ; i++)
	{
		CFiltre* pFiltre = pFiltreListe->GetAt(i);
		pFiltre->Initialiser();

		CSItemFiltre* pSItemFiltre = new CSItemFiltre(pStructureMgr,*pFiltre, this);

		pFiltreListe->RemoveAt(i);
		pFiltreListe->InsertAt(i,pSItemFiltre);
	}

	// Ajout des ressources du filtre
	CRessourceListe* pRessourceListe = GetRessourceListe();
	for (int i = 0; i < pRessourceListe->GetCount() ; i++)
	{
		CRessource* pRessource = pRessourceListe->GetAt(i);
		pRessource->Initialiser();

		CSItemRessource* pSItemRessource = new CSItemRessource(pStructureMgr,*pRessource, this);

		pRessourceListe->RemoveAt(i);
		pRessourceListe->InsertAt(i,pSItemRessource);
	}
}

// Constructeur
CSItemFiltre::CSItemFiltre(CStructureMgr* pStructureMgr, const CFiltre &source, CSItemFiltre* pSItemFiltre) : CSItemFiltre(pStructureMgr,source)
{
	// Ajout du Filtre dans la grille
	CSItemStructure::AjouterLigneGrille(pSItemFiltre);

	//
	pSItemFiltre->Expand(FALSE);

	// Ajout des filtres du filtre
	CFiltreListe* pFiltreListe = GetFiltreListe();
	for (int i = 0; i < pFiltreListe->GetCount() ; i++)
	{
		CFiltre* pFiltre = pFiltreListe->GetAt(i);
		pFiltre->Initialiser();

		CSItemFiltre* pSItemFiltre = new CSItemFiltre(pStructureMgr,*pFiltre, this);

		pFiltreListe->RemoveAt(i);
		pFiltreListe->InsertAt(i,pSItemFiltre);
	}

	// Ajout des ressources du filtre
	CRessourceListe* pRessourceListe = GetRessourceListe();
	for (int i = 0; i < pRessourceListe->GetCount() ; i++)
	{
		CRessource* pRessource = pRessourceListe->GetAt(i);
		pRessource->Initialiser();

		CSItemRessource* pSItemRessource = new CSItemRessource(pStructureMgr,*pRessource, this);

		pRessourceListe->RemoveAt(i);
		pRessourceListe->InsertAt(i,pSItemRessource);
	}
}

// Destructeur
CSItemFiltre::~CSItemFiltre()
{
}

void CSItemFiltre::SetImage(FiltreType filtreType)
{
	switch(filtreType)
	{
		case FiltreType::Filtre:		CSItemStructure::SetImage(TreeImage::Filtre);			break;
		case FiltreType::SQL:			CSItemStructure::SetImage(TreeImage::FiltreSql);		break;
		case FiltreType::SQLite:		CSItemStructure::SetImage(TreeImage::FiltreSQLite);		break;
		case FiltreType::Ressource:		CSItemStructure::SetImage(TreeImage::FiltreRessource);	break;
	}
}

// Mise à jour de l'item
void CSItemFiltre::UpdateTreeItem()
{
	// Force l'objet à croire qu'il n'est pas initialisé
	SetInitaliser(false);
	SetAcquis(false);

	// Mise à jour du libelle dans la grille
	CSItemStructure::SetLibelle(CFiltre::GetLibelle().c_str());
}

//
void CSItemFiltre::OnExpand(BOOL bExpand)
{
	// Test si les ressources existent toujours
	CRessourceListe* pRessourceListe = GetRessourceListe();
	for (int i = 0; i < pRessourceListe->GetCount() ; i++)
	{
		// Récupère la ressource
		CRessource* pRessource = pRessourceListe->GetAt(i);

		// Test si la ressource existe
		if(CRessourceChecker::RessourceChecker().exists(pRessource)==false)
		{
			// Message
			CString message; message.Format(_T("La ressource %s n'existe plus;\r\nVoulez-vous la supprimer ?"),ToString(pRessource->GetLibelle()));
			// La ressource n'existe plus
			BCGP_MSGBOXPARAMS params;
			params.lpszCaption = _T("Ressource introuvable");
			params.lpszText = message;
			params.bDrawButtonsBanner = 0;
			params.dwStyle = MB_ICONQUESTION | MB_YESNO;
			int result = BCGPMessageBoxIndirect(&params);

			// Suppression de la ressource
			if(result == IDYES)
			{
			}
		}
	}
	
}

// Interface pour la mise à jour du property grid
void CSItemFiltre::UpdatePropertyGrid(CBCGPPropList* pPropList)
{
	CSItemStructure::UpdatePropertyGrid(pPropList);

	// Ajout des propriétés
	CBCGPProp* pGroupDivers = new CBCGPProp(_T("Divers"));
	CBCGPProp* pNom		= new CBCGPProp(_T("Nom"),							(UINT)Nom,			(_variant_t)ToString(GetLibelle()),					_T(""));
	CBCGPProp* pChH		= new CBCGPFileProp(_T("Chemin des fichiers .h"),	(UINT)CheminH,		(_variant_t)ToString(GetHFolder().toString()),	0,	_T(""));
	CBCGPProp* pChCpp	= new CBCGPFileProp(_T("Chemin des fichiers .cpp"),	(UINT)CheminCpp,	(_variant_t)ToString(GetCppFolder().toString()),0,	_T(""));

	pGroupDivers->AddSubItem(pNom);
	pGroupDivers->AddSubItem(pChH);
	pGroupDivers->AddSubItem(pChCpp);

	pPropList->AddProperty (pGroupDivers);
	
	// PropertyGridEvent
	GDSMM::PropertyGridEvent event(this,pPropList);
	theApp.ModulesEvents()->NotifyUpdatePropertyGrid(event);

	// Mise à jour de l'affichage
	pPropList->Invalidate();
}

LRESULT CSItemFiltre::OnPropertyChanged(CBCGPProp* pProp)
{
	PropID id = (PropID)pProp->GetID();

	switch(id)
	{
		case Nom:
		{
			//
			CString sLibelle = (LPCTSTR)(_bstr_t)pProp->GetValue();

			//
			GDSAPI::CFiltre filtre(this->GetId());
			filtre.SetLibelle(ToStdString(sLibelle));
			filtre.Sauver();

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
			GDSAPI::CFiltre filtre(this->GetId());
			filtre.SetHFolder(sChemin);
			filtre.Sauver();

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
			GDSAPI::CFiltre filtre(this->GetId());
			filtre.SetCppFolder(sChemin);
			filtre.Sauver();

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

bool CSItemFiltre::CanDrag()
{
	if(GetType()==FiltreType::Filtre) return true;
	return false;
}

bool CSItemFiltre::CanDrop(CSItemStructure* pSItemDrag)
{
	if(pSItemDrag->GetTypeItem()==SItemType::Filtre)
	{
		// Recherche le type de filtre parent de l'item drag
		GDSAPI::CFiltre* pFiltreDrag = (GDSAPI::CFiltre*)(CSItemFiltre*)pSItemDrag;
		GDSAPI::CFiltre* pFiltreDragParent = dynamic_cast<GDSAPI::CFiltre*>(pFiltreDrag->GetOwner());
		FiltreType typeFiltreParent = pFiltreDrag->GetType();
		while(pFiltreDragParent)
		{
			typeFiltreParent = pFiltreDragParent->GetType();
			pFiltreDragParent = dynamic_cast<GDSAPI::CFiltre*>(pFiltreDragParent->GetOwner());
		}

		// Recherche le type de filtre parent de l'item
		GDSAPI::CFiltre* pFiltre = (GDSAPI::CFiltre*)(CSItemFiltre*)this;
		GDSAPI::CFiltre* pFiltreParent = dynamic_cast<GDSAPI::CFiltre*>(pFiltre->GetOwner());
		FiltreType typeFiltre = pFiltre->GetType();
		while(pFiltreParent)
		{
			typeFiltre = pFiltreParent->GetType();
			pFiltreParent = dynamic_cast<GDSAPI::CFiltre*>(pFiltreParent->GetOwner());
		}

		if(typeFiltreParent != typeFiltre)
			return false;

		// Le filtre de drop ne doit pas être un enfant du drag
		pFiltre = (GDSAPI::CFiltre*)(CSItemFiltre*)this;
		pFiltreParent = dynamic_cast<GDSAPI::CFiltre*>(pFiltre->GetOwner());
		while(pFiltreParent)
		{
			if(pFiltreParent==pFiltreDrag) return false;
			pFiltreParent = dynamic_cast<GDSAPI::CFiltre*>(pFiltreParent->GetOwner());
		}

		//
		return true;
	}

	return false;
}
