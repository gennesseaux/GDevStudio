
#pragma once


// Inculsions
#include "SItemStructure.h"
#include "DObject/Ressource.h"

//
using GDSObject::CRessource;
using GDSObject::CRessourceListe;

//
class CSItemFiltre;

class CSItemRessource : public CSItemStructure, public CRessource
{
public:
	//! Constructeur.
	CSItemRessource(CStructureMgr* pStructureMgr, const CRessource &source, CSItemFiltre* pSItemFiltre);
	// Destructeur
	virtual ~CSItemRessource();

public:
	// Mise à jour de l'item
	void UpdateTreeItem();
	// Interface pour la mise à jour du property grid
	virtual void UpdatePropertyGrid(CBCGPPropList* pPropList);
	virtual LRESULT OnPropertyChanged(CBCGPProp* pProp);
};
