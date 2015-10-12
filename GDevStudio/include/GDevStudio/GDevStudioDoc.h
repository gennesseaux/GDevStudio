// GDevStudioDoc.h : interface of the CGDevStudioDoc class
//


#pragma once


// Inclusions
#include "StructureMgr.h"
#include "GDevStudioApi/Projet.h"
#include "GDevStudioApi/Filtre.h"
#include "GDevStudioApi/Ressource.h"
#include "GDevStudioApi/Controle.h"


class CGDevStudioDoc : public CDocument
{
protected:
	// Constructeur
	CGDevStudioDoc();
	virtual ~CGDevStudioDoc();

protected:

	DECLARE_DYNCREATE(CGDevStudioDoc)

public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnUpdateAllViews();

public:
	#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	#endif

protected:

	DECLARE_MESSAGE_MAP()

public:
	unsigned long GetProjetId() const { return m_ulProjetId; }

protected:
	unsigned long m_ulProjetId = DefULong;
};


