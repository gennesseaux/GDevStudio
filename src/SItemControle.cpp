

// Inclusions
#include "Stdafx.h"
#include "SItemControle.h"
#include "SItemRessource.h"

//
using GDSObject::CControle;
using GDSObject::CControleListe;


// Constructeur
CSItemControle::CSItemControle(CStructureMgr* pStructureMgr, const CControle &source, CSItemRessource* pSItemRessource) : CSItemStructure(SItemType::Controle,pStructureMgr), CControle(source)
{
	// Ajout du Controle dans la grille
	CSItemStructure::SetLibelle(CControle::GetLibelle().c_str());
	CSItemStructure::SetImage(TreeImage::Controle);
	CSItemStructure::AjouterLigneGrille(pSItemRessource);
	
	// Parent
	this->AddParent(pSItemRessource);
}

// Destructeur
CSItemControle::~CSItemControle()
{
}

void CSItemControle::UpdateTreeItem()
{
	// Force l'objet à croire qu'il n'est pas initialisé
	SetInitaliser(false);
	SetAcquis(false);

	// Mise à jour du libelle dans la grille
	CSItemStructure::SetLibelle(CControle::GetLibelle().c_str());
}
