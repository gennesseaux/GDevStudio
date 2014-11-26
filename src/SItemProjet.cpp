

// Inclusions
#include "Stdafx.h"
#include "SItemProjet.h"


// Constructeur
CSItemProjet::CSItemProjet(CStructureMgr* pStructureMgr, unsigned long ulIdProjet) : CSItemStructure(SItemType::Projet,pStructureMgr), GDSObject::CProjet(ulIdProjet)
{
	// Ajout du projet dans la grille
	CSItemStructure::SetLibelle(GDSObject::CProjet::GetLibelle().c_str());
	CSItemStructure::SetImage(TreeImage::Projet);
	CSItemStructure::AjouterLigneGrille();
}

// Destructeur
CSItemProjet::~CSItemProjet()
{
}
