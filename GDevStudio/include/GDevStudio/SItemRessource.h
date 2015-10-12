
#pragma once


// Inculsions
#include "SItemStructure.h"
#include "GDevStudioApi/Ressource.h"

//
using GDSAPI::CRessource;
using GDSAPI::CRessourceListe;

//
class CSItemFiltre;

class CSItemRessource : public CSItemStructure, public CRessource
{
public:
	//! Constructeur.
	CSItemRessource(CStructureMgr* pStructureMgr, const CRessource &source, CSItemFiltre* pSItemFiltre);
	// Destructeur
	virtual ~CSItemRessource();

protected:
	// Mise à jour de l'item
	void UpdateTreeItem();

public:
	// Interface pour la mise à jour du property grid
	virtual void UpdatePropertyGrid(CBCGPPropList* pPropList);
	virtual LRESULT OnPropertyChanged(CBCGPProp* pProp);

	// Drag & Drop
 	virtual bool CanDrag();
 	virtual bool CanDrop(CSItemStructure* pSItemDrag);
};
