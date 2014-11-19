// GDevStudioDoc.h : interface of the CGDevStudioDoc class
//


#pragma once


// Inclusions
#include "StructureMgr.h"
#include "DObject/Projet.h"
#include "DObject/Filtre.h"


class CGDevStudioDoc : public CDocument
{
protected: // create from serialization only
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
	GDSObject::CProjet* Projet() const { return m_pProjet; }

protected:
	GDSObject::CProjet*	m_pProjet = nullptr;
};


