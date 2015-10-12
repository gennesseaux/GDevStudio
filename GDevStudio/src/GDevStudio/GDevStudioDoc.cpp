// GDevStudioDoc.cpp : implementation of the CGDevStudioDoc class
//


// Inclusions
#include "Stdafx.h"
#include "GDevStudio/GDevStudio.h"
#include "GDevStudio/GDevStudioDoc.h"

// Inclusions
#include "GDevStudio/ProjetDlg.h"
#include "GDevStudioApi/SQLiteSource.h"


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
	// Désactivation des modules
	theApp.ModulesManager()->DesactiverModulesClasse();
	theApp.ModulesManager()->DesactiverModulesRessource();

 	// Création d'une base de données par défaut
 	GDSAPI::CSQLiteSource::SQLiteSource().New();

 	// Création du projet par défault
 	GDSAPI::CProjet projet;
 	projet.SetLibelle("Nouveau projet");
 	projet.SetUuidClsGen(theApp.ModulesManager()->getClassesServer().getModulesCount()>0?theApp.ModulesManager()->getClassesServer().getModule(0)->uuid():Poco::UUID());
 	projet.SetUuidResGen(theApp.ModulesManager()->getRessourcesServer().getModulesCount()>0?theApp.ModulesManager()->getRessourcesServer().getModule(0)->uuid():Poco::UUID());
 
 	GDSAPI::CFiltre* pFiltreSql = new GDSAPI::CFiltre();
 	pFiltreSql->SetLibelle("SQL");
 	pFiltreSql->SetType(GDSAPI::FiltreType::SQL);
 
 	#ifdef _DEBUG
 		GDSAPI::CFiltre* pFiltre01 = new GDSAPI::CFiltre();
 		pFiltre01->SetLibelle("Filtre 01");
 		pFiltre01->SetType(GDSAPI::FiltreType::Filtre);
 		pFiltreSql->GetFiltreListe(false)->Add(pFiltre01);
 
 		GDSAPI::CFiltre* pFiltre011 = new GDSAPI::CFiltre();
 		pFiltre011->SetLibelle("Filtre 01 1");
 		pFiltre011->SetType(GDSAPI::FiltreType::Filtre);
 		pFiltre01->GetFiltreListe(false)->Add(pFiltre011);
 	#endif
 
 	GDSAPI::CFiltre* pFiltreSqlite = new GDSAPI::CFiltre();
 	pFiltreSqlite->SetLibelle("SQLite");
 	pFiltreSqlite->SetType(GDSAPI::FiltreType::SQLite);
 
 	GDSAPI::CFiltre* pFiltreRessource = new GDSAPI::CFiltre();
 	pFiltreRessource->SetLibelle("Ressources");
 	pFiltreRessource->SetType(GDSAPI::FiltreType::Ressource);
 
 	projet.GetFiltreListe(false)->Add(pFiltreSql);
 	projet.GetFiltreListe(false)->Add(pFiltreSqlite);
 	projet.GetFiltreListe(false)->Add(pFiltreRessource);
 	projet.Sauver();
							
	// Changement du générateur
	theApp.ModulesManager()->ActiverModuleClasse(projet.GetUuidClsGen());
	theApp.ModulesManager()->ActiverModuleRessource(projet.GetUuidResGen());

	//
	m_ulProjetId = projet.GetId();
	OnUpdateAllViews();

	return TRUE;
}

BOOL CGDevStudioDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	// Désactivation des modules
	theApp.ModulesManager()->DesactiverModulesClasse();
	theApp.ModulesManager()->DesactiverModulesRessource();

	// Ouverture d'une base de données existante
	std::string sFile = CT2A(lpszPathName);
	GDSAPI::CSQLiteSource::SQLiteSource().Open(sFile);
								
	// Changement du générateur
	GDSAPI::CProjet projet(1);
	theApp.ModulesManager()->ActiverModuleClasse(projet.GetUuidClsGen());
	theApp.ModulesManager()->ActiverModuleRessource(projet.GetUuidResGen());

 	// Initilialisation de la structure
 	m_ulProjetId = projet.GetId();
	OnUpdateAllViews();

	return TRUE;
}

BOOL CGDevStudioDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// Désactivation des modules
	theApp.ModulesManager()->DesactiverModulesClasse();
	theApp.ModulesManager()->DesactiverModulesRessource();

	// Sauvegarde de la base
	std::string sFile = CT2A(lpszPathName);
	GDSAPI::CSQLiteSource::SQLiteSource().SaveAs(sFile);
								
	// Changement du générateur
	if(m_ulProjetId != DefULong)
	{
		GDSAPI::CProjet projet(m_ulProjetId);
		theApp.ModulesManager()->ActiverModuleClasse(projet.GetUuidClsGen());
		theApp.ModulesManager()->ActiverModuleRessource(projet.GetUuidResGen());
	}

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
