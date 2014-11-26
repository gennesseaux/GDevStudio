

// Inclusions
#include "Stdafx.h"
#include "SItemProjet.h"
#include "SItemFiltre.h"

//
using GDSObject::CFiltre;
using GDSObject::CFiltreListe;


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

		CSItemFiltre* pSItemFiltre = new CSItemFiltre(pStructureMgr,*pFiltre);

		pFiltreListe->RemoveAt(i);
		pFiltreListe->InsertAt(i,pSItemFiltre);
	}
}

// Destructeur
CSItemProjet::~CSItemProjet()
{
}
