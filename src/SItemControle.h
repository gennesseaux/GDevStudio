
#pragma once


// Inculsions
#include "SItemStructure.h"
#include "DObject/Controle.h"

//
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
	void UpdateTreeItem();
};
