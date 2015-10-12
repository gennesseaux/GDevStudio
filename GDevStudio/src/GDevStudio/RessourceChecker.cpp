
// Inclusions
#include "Stdafx.h"
#include "GDevStudio/RessourceChecker.h"

// Inclusions
#include <RcReader/RcReader.h>


// Singleton
CRessourceChecker& CRessourceChecker::RessourceChecker()
{
	// Since it's a static variable, if the class has already been created,
	// It won't be created again.
	// And it **is** thread-safe in C++11.
	static CRessourceChecker _instance;
	// Return a reference to our instance.
	return _instance;
}

// Constructeur
CRessourceChecker::CRessourceChecker()
{
}

// Desctructeur
CRessourceChecker::~CRessourceChecker()
{
	m_mRcReader.clear();
}

// Test si une ressource existe
bool CRessourceChecker::exists(GDSAPI::CRessource* pRessource)
{
	std::string resFile = pRessource->GetFile().path();
	std::string resName = pRessource->GetLibelle();

	// Retrouve le RcReader contenant la ressource
	RcReader::CRcReader* pRcReader = GetRcReader(resFile);

	// Retrouve la ressource
	RcReader::CRcResourceDialog* pResDialog = pRcReader->GetDialog(resName);

	return pResDialog!=nullptr;
}

bool CRessourceChecker::exists(GDSAPI::CControle* pControle)
{
	// Récupère la ressource depuis le contrôle
	GDSAPI::CRessource* pRessource = (GDSAPI::CRessource*)pControle->GetOwner();
	assert(pRessource);

	// Vérifie que la ressource existe
	if(exists(pRessource)) return false;

	// Retrouve le RcReader contenant la ressource
	std::string resFile = pRessource->GetFile().path();
	RcReader::CRcReader* pRcReader = GetRcReader(resFile);

	// Retrouve la ressource
	std::string resName = pRessource->GetLibelle();
	RcReader::CRcResourceDialog* pResDialog = pRcReader->GetDialog(resName);

	// Retrouve le contrôle
	std::string ctrlName = pControle->GetLibelle();
	RcReader::CRcResourceControl* pResControl = pResDialog->GetControl(ctrlName);

	return pResControl!=nullptr;
}

RcReader::CRcReader* CRessourceChecker::GetRcReader(std::string fileName)
{
	CRcReaderPtr pRcReader = m_mRcReader[fileName];

	// Retourne le RcReader si il exist
	if(pRcReader!=nullptr) return pRcReader.get();

	// Charge un nouveau RcReader
	pRcReader = CRcReaderPtr(new RcReader::CRcReader(fileName));

	// Le fichier de ressource n'existe pas
	if(pRcReader->GetFichierRc().empty()) return nullptr;

	//
	m_mRcReader[fileName] = pRcReader;

	// Retourne le RcReader
	return GetRcReader(fileName);
}
