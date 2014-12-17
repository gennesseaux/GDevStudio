

// Inclusions
#include "Stdafx.h"
#include "SItemFiltre.h"
#include "SItemProjet.h"


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
}

// Constructeur
CSItemFiltre::CSItemFiltre(CStructureMgr* pStructureMgr, const CFiltre &source, CSItemFiltre* pSItemFiltre) : CSItemFiltre(pStructureMgr,source)
{
	// Ajout du Filtre dans la grille
	CSItemStructure::AjouterLigneGrille(pSItemFiltre);

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

void CSItemFiltre::UpdateTreeItem()
{
	// Force l'objet à croire qu'il n'est pas initialisé
	SetInitaliser(false);
	SetAcquis(false);

	// Mise à jour du libelle dans la grille
	CSItemStructure::SetLibelle(CFiltre::GetLibelle().c_str());
}
