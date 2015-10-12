#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//
#include "GDevStudioApi\Projet.h"
#include "GDevStudioApi\Filtre.h"

using namespace GDSAPI;

namespace GDevStudio_test
{
	TEST_CLASS(GDevStudioApiTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			//// Création d'une base de données par défaut
			//CSQLiteSource::instance().New();

			//// Création du projet par défault
			//CProjet projet;
			//projet.SetLibelle("Nouveau projet");

			//CFiltre* pFiltreSql = new CFiltre();
			//pFiltreSql->SetLibelle("SQL");
			//pFiltreSql->SetType(FiltreType::SQL);

			//CFiltre* pFiltre01 = new CFiltre();
			//pFiltre01->SetLibelle("Filtre 01");
			//pFiltre01->SetType(FiltreType::Filtre);
			//pFiltreSql->GetFiltreListe(false)->Add(pFiltre01);

			//CFiltre* pFiltre02 = new CFiltre();
			//pFiltre02->SetLibelle("Filtre 02");
			//pFiltre02->SetType(FiltreType::Filtre);
			//pFiltreSql->GetFiltreListe(false)->Add(pFiltre02);

			//CFiltre* pFiltre03 = new CFiltre();
			//pFiltre03->SetLibelle("Filtre 03");
			//pFiltre03->SetType(FiltreType::Filtre);
			//pFiltreSql->GetFiltreListe(false)->Add(pFiltre03);
		}

	};
}