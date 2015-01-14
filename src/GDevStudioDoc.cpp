// GDevStudioDoc.cpp : implementation of the CGDevStudioDoc class
//


// Inclusions
#include "Stdafx.h"
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
}

BOOL CGDevStudioDoc::OnNewDocument()
{
 	// Création d'une base de données par défaut
 	CSQLiteSource::instance().New();
 
 	// Création du projet par défault
 	GDSObject::CProjet projet;
 	projet.SetLibelle("Nouveau projet");
 
 	GDSObject::CFiltre* pFiltreSql = new GDSObject::CFiltre();
 	pFiltreSql->SetLibelle("SQL");
 	pFiltreSql->SetType(GDSObject::FiltreType::SQL);
 
 	#ifdef _DEBUG
 		GDSObject::CFiltre* pFiltre01 = new GDSObject::CFiltre();
 		pFiltre01->SetLibelle("Filtre 01");
 		pFiltre01->SetType(GDSObject::FiltreType::Filtre);
 		pFiltreSql->GetFiltreListe(false)->Add(pFiltre01);
		pFiltre01->AddParent(pFiltreSql);
 
 		GDSObject::CFiltre* pFiltre02 = new GDSObject::CFiltre();
 		pFiltre02->SetLibelle("Filtre 02");
 		pFiltre02->SetType(GDSObject::FiltreType::Filtre);
 		pFiltreSql->GetFiltreListe(false)->Add(pFiltre02);
		pFiltre02->AddParent(pFiltreSql);
 
 		GDSObject::CFiltre* pFiltre03 = new GDSObject::CFiltre();
 		pFiltre03->SetLibelle("Filtre 03");
 		pFiltre03->SetType(GDSObject::FiltreType::Filtre);
 		pFiltreSql->GetFiltreListe(false)->Add(pFiltre03);
		pFiltre03->AddParent(pFiltreSql);
 	#endif
 
 	GDSObject::CFiltre* pFiltreSqlite = new GDSObject::CFiltre();
 	pFiltreSqlite->SetLibelle("SQLite");
 	pFiltreSqlite->SetType(GDSObject::FiltreType::SQLite);
 
 	GDSObject::CFiltre* pFiltreRessource = new GDSObject::CFiltre();
 	pFiltreRessource->SetLibelle("Ressources");
 	pFiltreRessource->SetType(GDSObject::FiltreType::Ressource);
 
 	projet.GetFiltreListe(false)->Add(pFiltreSql);
 	projet.GetFiltreListe(false)->Add(pFiltreSqlite);
 	projet.GetFiltreListe(false)->Add(pFiltreRessource);
 	projet.Sauver();

	//
	m_ulProjetId = projet.GetId();
	OnUpdateAllViews();

	return TRUE;
}

BOOL CGDevStudioDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	// Ouverture d'une base de données existante
	std::string sFile = CT2A(lpszPathName);
	CSQLiteSource::instance().Open(sFile);

 	// Initilialisation de la structure
 	m_ulProjetId = 1;
	OnUpdateAllViews();

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
	//
	m_ulProjetId = DefULong;

	// Fermeture du document
	CDocument::OnCloseDocument();
}

void CGDevStudioDoc::OnUpdateAllViews()
{
	UpdateAllViews(NULL);
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
