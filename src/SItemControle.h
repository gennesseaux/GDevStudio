
#pragma once


// Inculsions
#include "SItemStructure.h"
#include "DObject/Controle.h"

//
using GDSObject::ControleType;
using GDSObject::CControle;
using GDSObject::CControleListe;

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

public:
	// Mise à jour de l'item
	void UpdateTreeItem();
	// Interface pour la mise à jour du property grid
	virtual void UpdatePropertyGrid(CBCGPPropList* pPropList);
	virtual LRESULT OnPropertyChanged(CBCGPProp* pProp);
};
