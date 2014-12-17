

// Inclusions
#include "Stdafx.h"
#include "SItemStructure.h"

// Inclusions
#include "StructureMgr.h"


// Constructeur
CSItemStructure::CSItemStructure(SItemType sitemType, CStructureMgr* pStructureMgr)
{
	m_pStructureMgr = pStructureMgr;
	m_pTreeGrille = pStructureMgr->GetTreeGrille();

	m_pRow = m_pTreeGrille->CreateRow(1);
	m_pRow->AllowSubItems();
	m_pRow->SetData((DWORD_PTR)this);

	m_SItemType = sitemType;

	//pStructureMgr->AddToMap(sitemType, this);
}

// Destructeur
CSItemStructure::~CSItemStructure()
{
	m_pStructureMgr = nullptr;
	m_pTreeGrille = nullptr;
	m_pRow = nullptr;
}

// Libellé
void CSItemStructure::SetLibelle(const char* sLibelle)
{
	m_pRow->GetItem(0)->SetValue(sLibelle);
}

// Image 
void CSItemStructure::SetImage(TreeImage image)
{
	m_pRow->GetItem(0)->SetImage(m_pTreeGrille->GetTreeImageMgr()->GetIndex(image));
}

void CSItemStructure::AjouterLigneGrille()
{
	m_pTreeGrille->AddRow(m_pRow);
}

void CSItemStructure::AjouterLigneGrille(CSItemStructure* pParent)
{
	pParent->GetLigne()->AddSubItem(m_pRow);
}

CBCGPGridRow* CSItemStructure::GetLigne()
{
	return m_pRow;
}
