

// Inclusions
#include "Stdafx.h"
#include "SItemRessource.h"
#include "SItemFiltre.h"
#include "SItemControle.h"

//
using GDSObject::CControle;
using GDSObject::CControleListe;

enum PropID
{
	Nom,
	Chemin,
};


// Constructeur
CSItemRessource::CSItemRessource(CStructureMgr* pStructureMgr, const CRessource &source, CSItemFiltre* pSItemFiltre) : CSItemStructure(SItemType::Ressource,pStructureMgr), CRessource(source)
{
	// Ajout du Ressource dans la grille
	CSItemStructure::SetLibelle(CRessource::GetLibelle().c_str());
	CSItemStructure::SetImage(TreeImage::ResDialog);
	CSItemStructure::AjouterLigneGrille(pSItemFiltre);
	
	//
	pSItemFiltre->Expand(FALSE);

 	// Ajout des controles de la Ressource
 	CControleListe* pControleListe = GetControleListe();
 	for (int i = 0; i < pControleListe->GetCount() ; i++)
 	{
 		CControle* pControle = pControleListe->GetAt(i);
 		pControle->Initialiser();
 
 		CSItemControle* pSItemControle = new CSItemControle(pStructureMgr,*pControle, this);
 
 		pControleListe->RemoveAt(i);
 		pControleListe->InsertAt(i,pSItemControle);
 	}

	//
	this->Expand(FALSE);
}

// Destructeur
CSItemRessource::~CSItemRessource()
{
}

// Mise à jour de l'item
void CSItemRessource::UpdateTreeItem()
{
	// Force l'objet à croire qu'il n'est pas initialisé
	SetInitaliser(false);
	SetAcquis(false);

	// Mise à jour du libelle dans la grille
	CSItemStructure::SetLibelle(CRessource::GetLibelle().c_str());
}

// Interface pour la mise à jour du property grid
void CSItemRessource::UpdatePropertyGrid(CBCGPPropList* pPropList)
{
	CSItemStructure::UpdatePropertyGrid(pPropList);

	// Ajout des propriétés
	CBCGPProp* pGroupDivers = new CBCGPProp(_T("Divers"));
	CBCGPProp* pNom		= new CBCGPProp(_T("Nom"),									(UINT)Nom,		(_variant_t)ToString(GetLibelle()),						_T(""));
	CBCGPProp* pCh		= new CBCGPFileProp(_T("Chemin du fichier de ressource"),	(UINT)Chemin,	(_variant_t)ToString((std::string)GetFile().path()),0,	_T(""));

	pNom->Enable(FALSE);
	pCh->Enable(FALSE);
	pGroupDivers->AddSubItem(pNom);
	pGroupDivers->AddSubItem(pCh);

	pPropList->AddProperty (pGroupDivers);

	// Mise à jour de l'affichage
	pPropList->Invalidate();
}

LRESULT CSItemRessource::OnPropertyChanged(CBCGPProp* pProp)
{
	PropID id = (PropID)pProp->GetID();
	return 0;
}

bool CSItemRessource::CanDrag()
{
	return true;
}

bool CSItemRessource::CanDrop(CSItemStructure* pSItemDrag)
{
	return false;
}
