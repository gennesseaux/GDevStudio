
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
	//! Charge une icone depuis les ressources
	int AddIco(UINT uiIdRes, CImageList* pImageList);


protected:
	CImageList								m_ImagesList;
	CMap<TreeImage, TreeImage, int, int>	m_mapImageIndex;
};
