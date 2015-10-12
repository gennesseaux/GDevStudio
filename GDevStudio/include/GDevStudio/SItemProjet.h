
#pragma once


// Inculsions
#include "SItemStructure.h"
#include "GDevStudioApi/Projet.h"

//
using GDSAPI::CProjet;


class CSItemProjet : public CSItemStructure, public CProjet
{
public:
	// Constructeur
	CSItemProjet(CStructureMgr* pStructureMgr, unsigned long ulIdProjet);
	// Destructeur
	virtual ~CSItemProjet();

protected:
	// Mise � jour de l'item
	void UpdateTreeItem();

public:
	// Interface pour la mise � jour du property grid
	virtual void UpdatePropertyGrid(CBCGPPropList* pPropList);
	virtual LRESULT OnPropertyChanged(CBCGPProp* pProp);

	// Drag & Drop
 	virtual bool CanDrag();
 	virtual bool CanDrop(CSItemStructure* pSItemDrag);
};
