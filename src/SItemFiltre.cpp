

// Inclusions
#include "Stdafx.h"
#include "SItemFiltre.h"
#include "SItemProjet.h"
#include "SItemRessource.h"


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

	// Parent
	this->AddParent(pSItemProjet);

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

	//
	this->Expand(FALSE);
}

// Constructeur
CSItemFiltre::CSItemFiltre(CStructureMgr* pStructureMgr, const CFiltre &source, CSItemFiltre* pSItemFiltre) : CSItemFiltre(pStructureMgr,source)
{
	// Ajout du Filtre dans la grille
	CSItemStructure::AjouterLigneGrille(pSItemFiltre);

	// Parent
	this->AddParent(pSItemFiltre);

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
