

// Inclusions
#include "StdAfx.h"
#include "GDevStudio.h"
#include "TreeIconMgr.h"

// Inclusions
#include "TreeGrille.h"



//! Constructeur
CTreeIconMgr::CTreeIconMgr(CTreeGrille* pTree)
{
	// Création de la liste
	m_ImagesList.Create(16, 16, ILC_COLOR32, (int)TreeImage::Count, 0);

	// Ajout des images
	m_mapImageIndex[TreeImage::Projet]			= AddPng(IDB_PROJET, &m_ImagesList);
	m_mapImageIndex[TreeImage::FiltreSql]		= AddPng(IDB_FILTRE_SQL, &m_ImagesList);
	m_mapImageIndex[TreeImage::FiltreSQLite]	= AddPng(IDB_FILTRE_SQLITE, &m_ImagesList);
	m_mapImageIndex[TreeImage::FiltreRessource]	= AddPng(IDB_FILTRE_RESSOURCE, &m_ImagesList);
	m_mapImageIndex[TreeImage::Filtre]			= AddPng(IDB_FILTRE, &m_ImagesList);

	// Affectation de la liste des images
	pTree->SetImageList(&m_ImagesList);
}

//! Destructeur
CTreeIconMgr::~CTreeIconMgr(void)
{
}

//! Charge une image PNG depuis les ressources
int CTreeIconMgr::AddPng(UINT uiIdRes, CImageList* pImageList)
{
	// Chargement de l'image
	CBCGPPngImage pngImage;
	pngImage.Load(uiIdRes);
	CBCGPToolBarImages::PreMultiplyAlpha((HBITMAP)pngImage.GetSafeHandle(), FALSE);

	// Ajout du bitmap à la liste
	return pImageList->Add(&pngImage, (CBitmap*)NULL);
}

//! Charge une image PNG depuis les ressources
int CTreeIconMgr::AddIco(UINT uiIdRes, CImageList* pImageList)
{
// 	HICON hBitmap = (HICON)BoiteOutils::LoadIcon(uiIdRes);
// 	return pImageList->Add(hBitmap);
	return -1;
}

int CTreeIconMgr::GetIndex(TreeImage treeImage)
{
	return m_mapImageIndex[treeImage];
}
