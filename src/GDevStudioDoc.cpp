// GDevStudioDoc.cpp : implementation of the CGDevStudioDoc class
//

#include "stdafx.h"
#include "GDevStudio.h"

#include "GDevStudioDoc.h"

// Inclusions
#include "SQLite/SQLiteSource.h"
#include "ProjetDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDevStudioDoc

IMPLEMENT_DYNCREATE(CGDevStudioDoc, CDocument)

BEGIN_MESSAGE_MAP(CGDevStudioDoc, CDocument)
END_MESSAGE_MAP()


// CGDevStudioDoc construction/destruction

CGDevStudioDoc::CGDevStudioDoc()
{
}

CGDevStudioDoc::~CGDevStudioDoc()
{
	delete m_pProjet;
}

BOOL CGDevStudioDoc::OnNewDocument()
{
	// Création d'une base de données par défaut
	CSQLiteSource::instance().New();

	// Création du projet par défault
	delete m_pProjet;
	m_pProjet = new GDSObject::CProjet();
	m_pProjet->SetLibelle("Nouveau projet");

	GDSObject::CFiltre* pFiltreSql = new GDSObject::CFiltre();
	pFiltreSql->SetLibelle("SQL");
	pFiltreSql->SetType(GDSObject::FiltreType::SQL);

	GDSObject::CFiltre* pFiltreSqlite = new GDSObject::CFiltre();
	pFiltreSqlite->SetLibelle("SQLite");
	pFiltreSqlite->SetType(GDSObject::FiltreType::SQLite);

	GDSObject::CFiltre* pFiltreRessource = new GDSObject::CFiltre();
	pFiltreRessource->SetLibelle("Ressources");
	pFiltreRessource->SetType(GDSObject::FiltreType::Ressource);

	m_pProjet->GetFiltreListe(false)->Add(pFiltreSql);
	m_pProjet->GetFiltreListe(false)->Add(pFiltreSqlite);
	m_pProjet->GetFiltreListe(false)->Add(pFiltreRessource);
	m_pProjet->Sauver();

	return TRUE;
}

BOOL CGDevStudioDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	// Ouverture d'une base de données existante
	std::string sFile = CT2A(lpszPathName);
	CSQLiteSource::instance().Open(sFile);

// 	// Initilialisation de la structure
// 	m_pStructureMgr->Initialiser(m_pProjet);

	return TRUE;
}

BOOL CGDevStudioDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// Sauvegarde de la base
	std::string sFile = CT2A(lpszPathName);
	CSQLiteSource::instance().SaveAs(sFile);

	return TRUE;
}

void CGDevStudioDoc::OnCloseDocument()
{
	// Destruction du projet par défaut
	delete m_pProjet;
	m_pProjet = nullptr;
}



// CGDevStudioDoc serialization
void CGDevStudioDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

// CGDevStudioDoc diagnostics
#ifdef _DEBUG
void CGDevStudioDoc::AssertValid() const
{
	CDocument::AssertValid();
}
void CGDevStudioDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
