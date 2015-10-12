
#pragma once

// Inculsions
#include <map>

// Inclusions
#include "GDevStudioApi/Controle.h"
#include "GDevStudioApi/Ressource.h"

// Inclusions
#include <RcReader/RcReader.h>


class CRessourceChecker
{
public:
	// Singleton
	static CRessourceChecker& RessourceChecker();

	// Test si une ressource existe
	bool exists(GDSAPI::CRessource* pRessource);
	// Test si un contrôle existe
	bool exists(GDSAPI::CControle* pControle);

protected:
	// Constructeur
	CRessourceChecker();
	// Desctructeur
	~CRessourceChecker();

	//! Constructeur par copie
	CRessourceChecker(const CRessourceChecker&) = delete;
	//! Opérateur =
	CRessourceChecker &operator=(const CRessourceChecker&) = delete;
	
protected:
	//
	RcReader::CRcReader* GetRcReader(std::string fileName);

protected:
	typedef std::shared_ptr<RcReader::CRcReader> CRcReaderPtr;
	std::map<std::string,CRcReaderPtr> m_mRcReader;
};

