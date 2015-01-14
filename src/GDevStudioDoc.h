// GDevStudioDoc.h : interface of the CGDevStudioDoc class
//


#pragma once


// Inclusions
#include "StructureMgr.h"
#include "DObject/Projet.h"
#include "DObject/Filtre.h"


class CGDevStudioDoc : public CDocument
{
protected:
	// Constructeur
	CGDevStudioDoc();

	DECLARE_DYNCREATE(CGDevStudioDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnUpdateAllViews();

	// Implementation
public:
	virtual ~CGDevStudioDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
	unsigned long GetProjetId() const { return m_ulProjetId; }

protected:
	unsigned long m_ulProjetId = DefULong;
};


