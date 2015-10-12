
#pragma once


// Inculsions
#include "SItemStructure.h"
#include "GDevStudioApi/Controle.h"

//
using GDSAPI::ControleType;
using GDSAPI::CControle;
using GDSAPI::CControleListe;

//
class CSItemRessource;

class CSItemControle : public CSItemStructure, public CControle
{
public:
	//! Constructeur.
	CSItemControle(CStructureMgr* pStructureMgr, const CControle &source, CSItemRessource* pSItemRessource);
	// Destructeur
	virtual ~CSItemControle();

public:
	// Image 
	void SetImage(ControleType controleType);

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
