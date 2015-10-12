
#pragma once


// Inculsions
#include "SItemStructure.h"
#include "GDevStudioApi/Filtre.h"

//
using GDSAPI::FiltreType;
using GDSAPI::CFiltre;
using GDSAPI::CFiltreListe;

//
class CSItemProjet;

class CSItemFiltre : public CSItemStructure, public CFiltre
{
public:
	//! Constructeur.
	CSItemFiltre(CStructureMgr* pStructureMgr, const CFiltre &source, CSItemProjet* pSItemProjet);
	//! Constructeur.
	CSItemFiltre(CStructureMgr* pStructureMgr, const CFiltre &source, CSItemFiltre* pSItemFiltre);
	// Destructeur
	virtual ~CSItemFiltre();

protected:
	//! Constructeur.
	CSItemFiltre(CStructureMgr* pStructureMgr, const CFiltre &source);

public:
	// Image 
	void SetImage(FiltreType filtreType);

protected:
	// Mise à jour de l'item
	void UpdateTreeItem();
	// Appelé avant que l'expand soit fait
	void OnExpand (BOOL bExpand);

public:
	// Interface pour la mise à jour du property grid
	virtual void UpdatePropertyGrid(CBCGPPropList* pPropList);
	virtual LRESULT OnPropertyChanged(CBCGPProp* pProp);

	// Drag & Drop
 	virtual bool CanDrag();
 	virtual bool CanDrop(CSItemStructure* pSItemDrag);
};
