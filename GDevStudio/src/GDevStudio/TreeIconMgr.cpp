

// Inclusions
#include "Stdafx.h"
#include "GDevStudio/GDevStudio.h"
#include "GDevStudio/TreeIconMgr.h"

// Inclusions
#include "GDevStudio/TreeGrille.h"



//! Constructeur
CTreeIconMgr::CTreeIconMgr(CTreeGrille* pTree)
{
	// Création de la liste
	CSize imgSize (16, 16);
	m_ImagesList.Create(imgSize.cx, imgSize.cy, ILC_COLOR32, (int)TreeImage::Count, 0);

	// Ajout des images
	m_mapImageIndex[TreeImage::Projet]						= AddPng(IDB_PROJET,					&m_ImagesList);

	m_mapImageIndex[TreeImage::FiltreSql]					= AddPng(IDB_FILTRE_SQL,				&m_ImagesList);
	m_mapImageIndex[TreeImage::FiltreSQLite]				= AddPng(IDB_FILTRE_SQLITE,				&m_ImagesList);
	m_mapImageIndex[TreeImage::FiltreRessource]				= AddPng(IDB_FILTRE_RESSOURCE,			&m_ImagesList);
	m_mapImageIndex[TreeImage::Filtre]						= AddPng(IDB_FILTRE,					&m_ImagesList);

	m_mapImageIndex[TreeImage::ResDialog]					= AddPng(IDB_RES_DIALOG,				&m_ImagesList);

	m_mapImageIndex[TreeImage::ControleBoutton]				= AddPng(IDB_RES_BUTTON,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleCheckBox]			= AddPng(IDB_RES_CHECKBOX,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleEdit]				= AddPng(IDB_RES_EDIT,					&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleComboBox]			= AddPng(IDB_RES_COMBOBOX,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleListBox]				= AddPng(IDB_RES_LISTBOX,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleGroupBox]			= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleRadioButton]			= AddPng(IDB_RES_RADIO_BUTTON,			&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleStaticText]			= AddPng(IDB_RES_STATIC_TEXT,			&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleImage]				= AddPng(IDB_RES_IMAGE,					&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleScrollBarHorizontal]	= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleScrollBarVertical]	= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleSlider]				= AddPng(IDB_RES_SLIDER,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleSpin]				= AddPng(IDB_CTRL_INCONNU, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleProgress]			= AddPng(IDB_RES_PROGRESS,				&m_ImagesList);
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
	m_mapImageIndex[TreeImage::ControleMfcButton]			= AddPng(IDB_RES_MENU_BUTTON,			&m_ImagesList);
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

	m_mapImageIndex[TreeImage::ControleBouttonRemoved]				= AddPng(IDB_RES_BUTTON,		IDB_REMOVE_OVERLAY,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleCheckBoxRemoved]				= AddPng(IDB_RES_CHECKBOX,		IDB_REMOVE_OVERLAY,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleEditRemoved]					= AddPng(IDB_RES_EDIT,			IDB_REMOVE_OVERLAY,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleComboBoxRemoved]				= AddPng(IDB_RES_COMBOBOX,		IDB_REMOVE_OVERLAY,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleListBoxRemoved]				= AddPng(IDB_RES_LISTBOX,		IDB_REMOVE_OVERLAY,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleGroupBoxRemoved]				= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleRadioButtonRemoved]			= AddPng(IDB_RES_RADIO_BUTTON,	IDB_REMOVE_OVERLAY,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleStaticTextRemoved]			= AddPng(IDB_RES_STATIC_TEXT,	IDB_REMOVE_OVERLAY,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleImageRemoved]				= AddPng(IDB_RES_IMAGE,			IDB_REMOVE_OVERLAY,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleScrollBarHorizontalRemoved]	= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleScrollBarVerticalRemoved]	= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleSliderRemoved]				= AddPng(IDB_RES_SLIDER,		IDB_REMOVE_OVERLAY,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleSpinRemoved]					= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleProgressRemoved]				= AddPng(IDB_RES_PROGRESS,		IDB_REMOVE_OVERLAY,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleHotKeyRemoved]				= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleListRemoved]					= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleTreeRemoved]					= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleTabRemoved]					= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleAnimationRemoved]			= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleRichEditRemoved]				= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleDateTimePickerRemoved]		= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMontCalendarRemoved]			= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleIpAdressRemoved]				= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleExtendedComboBoxRemoved]		= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleCustomRemoved]				= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleSyslinkRemoved]				= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleSplitButtonRemoved]			= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleNetworkAdressRemoved]		= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleCommandButtonRemoved]		= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcButtonRemoved]			= AddPng(IDB_RES_MENU_BUTTON,	IDB_REMOVE_OVERLAY,				&m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcColorButtonRemoved]		= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcEditBrowseRemoved]		= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcVsListBoxRemoved]			= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcFontComboBoxRemoved]		= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcMaskedEditRemoved]		= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcMenuButtonRemoved]		= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcPropertyGridRemoved]		= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcShellListRemoved]			= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleMfcLinkRemoved]				= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);
	m_mapImageIndex[TreeImage::ControleInconnuRemoved]				= AddPng(IDB_CTRL_INCONNU,	IDB_REMOVE_OVERLAY, &m_ImagesList);



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

int CTreeIconMgr::AddPng(UINT uiIdRes, UINT uiIdResOverlay, CImageList* pImageList)
{
	CSize imgSize (16, 16);

	CImageList	ilImage;
	ilImage.Create (imgSize.cx, imgSize.cy, ILC_COLOR32, 1, 0);
	AddPng(uiIdRes, &ilImage);

	CImageList	ilOverlay;
	ilOverlay.Create (imgSize.cx, imgSize.cy, ILC_COLOR32, 1, 0);
	AddPng(uiIdResOverlay, &ilOverlay);

	CBitmap bmpOverlayed;

	HDC hDC = ::GetDC(NULL);
	CDC* pDC = CDC::FromHandle(hDC);
	CDC dc;

	if(dc.CreateCompatibleDC(pDC))
	{
		if(bmpOverlayed.CreateCompatibleBitmap(pDC, imgSize.cx, imgSize.cy))
		{
			CBitmap* pOld = dc.SelectObject(&bmpOverlayed);

			ilImage.Draw(&dc, 0, CPoint(0, 0), ILD_IMAGE);
			ilOverlay.DrawIndirect(&dc, 0, CPoint(0, 0), imgSize, CPoint(0, 0), ILD_IMAGE | ILD_ROP, /*SRCPAINT*/ SRCAND);

			dc.SelectObject(pOld);
		}
	}

	::ReleaseDC(NULL, hDC);
	
	// Ajout du bitmap à la liste
	return pImageList->Add(&bmpOverlayed, (CBitmap*)NULL);
}

int CTreeIconMgr::GetIndex(TreeImage treeImage)
{
	return m_mapImageIndex[treeImage];
}
