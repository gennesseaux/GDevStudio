
#pragma once

// Inclusions
class CTreeGrille;

//
enum class TreeImage
{
	Projet,

	FiltreSql,
	FiltreSQLite,
	FiltreRessource,
	Filtre,

	ResDialog,

	ControleBoutton,
	ControleCheckBox,
	ControleEdit,
	ControleComboBox,
	ControleListBox,
	ControleGroupBox,
	ControleRadioButton,
	ControleStaticText,
	ControleImage,
	ControleScrollBarHorizontal,
	ControleScrollBarVertical,
	ControleSlider,
	ControleSpin,
	ControleProgress,
	ControleHotKey,
	ControleList,
	ControleTree,
	ControleTab,
	ControleAnimation,
	ControleRichEdit,
	ControleDateTimePicker,
	ControleMontCalendar,
	ControleIpAdress,
	ControleExtendedComboBox,
	ControleCustom,
	ControleSyslink,
	ControleSplitButton,
	ControleNetworkAdress,
	ControleCommandButton,
	ControleMfcButton,
	ControleMfcColorButton,
	ControleMfcEditBrowse,
	ControleMfcVsListBox,
	ControleMfcFontComboBox,
	ControleMfcMaskedEdit,
	ControleMfcMenuButton,
	ControleMfcPropertyGrid,
	ControleMfcShellList,
	ControleMfcLink,
	ControleInconnu,

	ControleBouttonRemoved,
	ControleCheckBoxRemoved,
	ControleEditRemoved,
	ControleComboBoxRemoved,
	ControleListBoxRemoved,
	ControleGroupBoxRemoved,
	ControleRadioButtonRemoved,
	ControleStaticTextRemoved,
	ControleImageRemoved,
	ControleScrollBarHorizontalRemoved,
	ControleScrollBarVerticalRemoved,
	ControleSliderRemoved,
	ControleSpinRemoved,
	ControleProgressRemoved,
	ControleHotKeyRemoved,
	ControleListRemoved,
	ControleTreeRemoved,
	ControleTabRemoved,
	ControleAnimationRemoved,
	ControleRichEditRemoved,
	ControleDateTimePickerRemoved,
	ControleMontCalendarRemoved,
	ControleIpAdressRemoved,
	ControleExtendedComboBoxRemoved,
	ControleCustomRemoved,
	ControleSyslinkRemoved,
	ControleSplitButtonRemoved,
	ControleNetworkAdressRemoved,
	ControleCommandButtonRemoved,
	ControleMfcButtonRemoved,
	ControleMfcColorButtonRemoved,
	ControleMfcEditBrowseRemoved,
	ControleMfcVsListBoxRemoved,
	ControleMfcFontComboBoxRemoved,
	ControleMfcMaskedEditRemoved,
	ControleMfcMenuButtonRemoved,
	ControleMfcPropertyGridRemoved,
	ControleMfcShellListRemoved,
	ControleMfcLinkRemoved,
	ControleInconnuRemoved,

	Count
};


class CTreeIconMgr
{
public:
	//! Constructeur
	CTreeIconMgr(CTreeGrille* pTree);
	//! Destructeur
	~CTreeIconMgr(void);


public:
	//! Retourne l'index de l'image
	int GetIndex(TreeImage treeImage);


protected:
	//! Charge une image PNG depuis les ressources
	int AddPng(UINT uiIdRes, CImageList* pImageList);
	//! Charge une image PNG depuis les ressources et lui ajout un overlay
	int AddPng(UINT uiIdRes, UINT uiIdResOverlay, CImageList* pImageList);


protected:
	CImageList								m_ImagesList;
	CMap<TreeImage, TreeImage, int, int>	m_mapImageIndex;
};
