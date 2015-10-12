
#pragma once

// Inculsions
#include <BCGPGridCtrl.h>

// Inclusions
class CSItemStructure;


class CTreeRow : public CBCGPGridRow
{
	DECLARE_SERIAL(CTreeRow)

public:
	// Constructeur
	CTreeRow(CSItemStructure* pOwner = nullptr);
	// Destructeur
	virtual ~CTreeRow();

protected:
	// Appelé avant que l'expand soit fait
	virtual void OnExpand (BOOL bExpand);

// Overrides
public:
	virtual void ReadFromArchive(CArchive& ar, BOOL bTestMode = FALSE);
	virtual void WriteToArchive(CArchive& ar);

protected:
	CSItemStructure* m_pOwner;
};

