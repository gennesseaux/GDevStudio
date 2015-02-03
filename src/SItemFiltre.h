
#pragma once


// Inculsions
#include "SItemStructure.h"
#include "DObject/Filtre.h"

//
using GDSObject::FiltreType;
using GDSObject::CFiltre;
using GDSObject::CFiltreListe;

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

public:
	// Mise à jour de l'item
	void UpdateTreeItem();

	// Interface pour la mise à jour du property grid
	virtual void UpdatePropertyGrid(CBCGPPropList* pPropList);
	virtual LRESULT OnPropertyChanged(CBCGPProp* pProp);

	// Drag & Drop
 	virtual bool CanDrag();
 	virtual bool CanDrop(CSItemStructure* pSItemDrag);
};
