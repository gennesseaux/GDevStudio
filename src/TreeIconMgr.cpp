

// Inclusions
#include "Stdafx.h"
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
	m_mapImageIndex[TreeImage::Projet]						= AddPng(IDB_PROJET, &m_ImagesList);

	m_mapImageIndex[TreeImage::FiltreSql]					= AddPng(IDB_FILTRE_SQL,			&m_ImagesList);
	m_mapImageIndex[TreeImage::FiltreSQLite]				= AddPng(IDB_FILTRE_SQLITE,			&m_ImagesList);
	m_mapImageIndex[TreeImage::FiltreRessource]				= AddPng(IDB_FILTRE_RESSOURCE,		&m_ImagesList);
	m_mapImageIndex[TreeImage::Filtre]						= AddPng(IDB_FILTRE,				&m_ImagesList);

	m_mapImageIndex[TreeImage::ResDialog]					= AddPng(IDB_RES_DIALOG,			&m_ImagesList);

	m_mapImageIndex[TreeImage::ControleBoutton]				= AddPng(IDB_RES_BUTTON,			&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleCheckBox]			= AddPng(IDB_RES_CHECKBOX,			&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleEdit]				= AddPng(IDB_RES_EDIT,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleComboBox]			= AddPng(IDB_RES_COMBOBOX,			&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleListBox]				= AddPng(IDB_RES_LISTBOX,			&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleGroupBox]			= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleRadioButton]			= AddPng(IDB_RES_RADIO_BUTTON,		&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleStaticText]			= AddPng(IDB_RES_STATIC_TEXT,		&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleImage]				= AddPng(IDB_RES_IMAGE,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleScrollBarHorizontal]	= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleScrollBarVertical]	= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleSlider]				= AddPng(IDB_RES_SLIDER,			&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleSpin]				= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleProgress]			= AddPng(IDB_RES_PROGRESS,			&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleHotKey]				= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleList]				= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleTree]				= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleTab]					= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleAnimation]			= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleRichEdit]			= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleDateTimePicker]		= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMontCalendar]		= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleIpAdress]			= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleExtendedComboBox]	= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleCustom]				= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleSyslink]				= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleSplitButton]			= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleNetworkAdress]		= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleCommandButton]		= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcButton]			= AddPng(IDB_RES_MENU_BUTTON,		&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcColorButton]		= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcEditBrowse]		= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcVsListBox]		= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcFontComboBox]		= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcMaskedEdit]		= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcMenuButton]		= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcPropertyGrid]		= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcShellList]		= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcLink]				= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleInconnu]				= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);

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
