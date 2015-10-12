
// Inclusions
#include "Stdafx.h"
#include "GDevStudio/TreeRow.h"
#include "GDevStudio/TreeGrille.h"
#include "GDevStudio/SItemStructure.h"


IMPLEMENT_SERIAL(CTreeRow, CBCGPGridRow, VERSIONABLE_SCHEMA | 1)

// Constructeur
CTreeRow::CTreeRow(CSItemStructure* pOwner) : CBCGPGridRow(1)
{
	m_pOwner = pOwner;
	
	AllowSubItems();
	SetData((DWORD_PTR)pOwner);
}

// Destructeur
CTreeRow::~CTreeRow()
{

}

void CTreeRow::OnExpand(BOOL bExpand)
{
	CTreeGrille* pTreeGrille = DYNAMIC_DOWNCAST(CTreeGrille,GetOwnerList());

	if(m_pOwner) m_pOwner->OnExpand(bExpand);
}

void CTreeRow::ReadFromArchive(CArchive& ar,BOOL bTestMode /*= FALSE*/)
{
	CBCGPGridRow::ReadFromArchive(ar, bTestMode);
}

void CTreeRow::WriteToArchive(CArchive& ar)
{
	CBCGPGridRow::WriteToArchive(ar);
}
