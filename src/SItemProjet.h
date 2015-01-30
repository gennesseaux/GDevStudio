
#pragma once


// Inculsions
#include "SItemStructure.h"
#include "DObject/Projet.h"

//
using GDSObject::CProjet;


class CSItemProjet : public CSItemStructure, public CProjet
{
public:
	// Constructeur
	CSItemProjet(CStructureMgr* pStructureMgr, unsigned long ulIdProjet);
	// Destructeur
	virtual ~CSItemProjet();

public:
	// Mise à jour de l'item
	void UpdateTreeItem();
	// Interface pour la mise à jour du property grid
	virtual void UpdatePropertyGrid(CBCGPPropList* pPropList);
	virtual LRESULT OnPropertyChanged(CBCGPProp* pProp);
};
