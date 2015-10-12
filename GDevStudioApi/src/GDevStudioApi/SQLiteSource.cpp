
// Inclusions
#include "GDevStudioApi/SQLiteSource.h"

// Inclusions Poco
#include "Poco/Foundation.h"
#include "Poco/File.h"
#include "Poco/TemporaryFile.h"
#include "Poco/Util/Application.h"

//
using namespace GDSAPI;


std::string CSQLiteSource::m_sDefaultDatabase = Poco::Path::temp() + std::string("default.gdsproj");


// Instance
CSQLiteSource& CSQLiteSource::SQLiteSource()
{
	// Since it's a static variable, if the class has already been created,
	// It won't be created again.
	// And it **is** thread-safe in C++11.
	static CSQLiteSource _instance;
	// Return a reference to our instance.
	return _instance;
}

// Retourne le pointeur sur la base de donnée en cours d'utilisation
SQLite::Database* CSQLiteSource::Database()
{
	return SQLiteSource().GetDataBase();
}

// Retourne le pointeur sur la base de donnée en cours d'utilisation
SQLite::TransactionEx* CSQLiteSource::Transaction()
{
	return SQLiteSource().GetTransaction();
}

// Constructeur
CSQLiteSource::CSQLiteSource() : SQLite::CSQLiteSource()
{
}

// Destructeur
CSQLiteSource::~CSQLiteSource()
{
}

// Création d'une base de données par défaut
SQLite::Database* CSQLiteSource::New()
{
	// Chemin de la base de données par défaut
	Poco::File fDefaultDatabase = m_sDefaultDatabase;

	// Ouverture de la base de donnée par défaut
	return SQLite::CSQLiteSource::New(fDefaultDatabase.path());
}

// Initialisation de la base de données
void CSQLiteSource::Init()
{
	// Table PROJET
	if (!GetDataBase()->tableExists("PROJET"))
		CreateTablePROJET();

	// Table FILTRE
	if (!GetDataBase()->tableExists("FILTRE"))
		CreateTableFILTRE();

	// Table RESSOURCE
	if (!GetDataBase()->tableExists("RESSOURCE"))
		CreateTableRESSOURCE();

	// Table CONTROLE
	if (!GetDataBase()->tableExists("CONTROLE"))
		CreateTableCONTROLE();
}

void CSQLiteSource::CreateTablePROJET()
{
	// Création de la table
	std::ostringstream osTable;
	osTable << "create table PROJET (						";
	osTable << "PRJ_IDENT			INTEGER		NOT NULL	PRIMARY KEY AUTOINCREMENT,	";
	osTable << "PRJ_LIBELLE			TEXT		NOT NULL	UNIQUE,	";
	osTable << "PRJ_DESCRIPTION		TEXT		NULL,		";
	osTable << "PRJ_H_FOLDER		TEXT		NULL,		";
	osTable << "PRJ_CPP_FOLDER		TEXT		NULL,		";
	osTable << "PRJ_UUID_RES_GEN	TEXT		NULL,		";
	osTable << "PRJ_UUID_CLS_GEN	TEXT		NULL		";
	osTable << ");";
	GetDataBase()->exec(osTable.str());

	// Création de l'index
	std::ostringstream osIndex;
	osIndex << "Create Index IX_PROJET on PROJET(PRJ_IDENT);";
	GetDataBase()->exec(osIndex.str());
}

void CSQLiteSource::CreateTableFILTRE()
{
	// Création de la table
	std::ostringstream osTable;
	osTable << "create table FILTRE (						";
	osTable << "FTR_IDENT			INTEGER		NOT NULL	PRIMARY KEY AUTOINCREMENT,	";
	osTable << "FTR_LIBELLE			TEXT		NOT NULL,	";
	osTable << "FTR_TYPE			INTEGER		NULL,		";
	osTable << "FTR_PRJ_IDENT		INTEGER		NULL,		";
	osTable << "FTR_FTR_IDENT		INTEGER		NULL,		";
	osTable << "FTR_H_FOLDER		TEXT		NULL,		";
	osTable << "FTR_CPP_FOLDER		TEXT		NULL,		";
	//osTable << "CONSTRAINT UX_FILTRE_LIBELLE1	UNIQUE(FTR_LIBELLE,FTR_PRJ_IDENT),";
	//osTable << "CONSTRAINT UX_FILTRE_LIBELLE2	UNIQUE(FTR_LIBELLE,FTR_FTR_IDENT),";
	osTable << "CONSTRAINT FK_FILTRE_PROJET		FOREIGN KEY(FTR_PRJ_IDENT) REFERENCES PROJET(PRJ_IDENT),";
	osTable << "CONSTRAINT FK_FILTRE_FILTRE		FOREIGN KEY(FTR_FTR_IDENT) REFERENCES FILTRE(FTR_IDENT)";
	osTable << ");";
	GetDataBase()->exec(osTable.str());

	// Création de l'index
	std::ostringstream osIndex;
	osIndex << "Create Index IX_FILTRE on FILTRE(FTR_IDENT);";
	GetDataBase()->exec(osIndex.str());
}

void CSQLiteSource::CreateTableRESSOURCE()
{
	// Création de la table
	std::ostringstream osTable;
	osTable << "create table RESSOURCE (						";
	osTable << "RES_IDENT			INTEGER		NOT NULL	PRIMARY KEY AUTOINCREMENT,	";
	osTable << "RES_LIBELLE			TEXT		NOT NULL,	";
	osTable << "RES_FILE			TEXT		NOT NULL,	";
	osTable << "RES_FTR_IDENT		INTEGER		NOT NULL,	";				// Identifiant du filtre
	osTable << "CONSTRAINT FK_RESSOURCE_FILTRE		FOREIGN KEY(RES_FTR_IDENT) REFERENCES FILTRE(FTR_IDENT)";
	osTable << ");";
	GetDataBase()->exec(osTable.str());

	// Création de l'index
	std::ostringstream osIndex;
	osIndex << "Create Index IX_RESSOURCE on RESSOURCE(RES_IDENT);";
	GetDataBase()->exec(osIndex.str());
}

void CSQLiteSource::CreateTableCONTROLE()
{
	// Création de la table
	std::ostringstream osTable;
	osTable << "create table CONTROLE (						";
	osTable << "CTR_IDENT			INTEGER		NOT NULL	PRIMARY KEY AUTOINCREMENT,	";
	osTable << "CTR_RES_IDENT		INTEGER		NOT NULL,	";
	osTable << "CTR_LIBELLE			TEXT		NOT NULL,	";
	osTable << "CTR_TYPE			TEXT		NOT NULL,	";
	osTable << "CTR_EXCLU			INTEGER		NOT NULL,	";
	osTable << "CONSTRAINT FK_CONTROLE_RESSOURCE		FOREIGN KEY(CTR_RES_IDENT) REFERENCES RESSOURCE(RES_IDENT)";
	osTable << ");";
	GetDataBase()->exec(osTable.str());

	// Création de l'index
	std::ostringstream osIndex;
	osIndex << "Create Index IX_CONTROLE on CONTROLE(CTR_IDENT);";
	GetDataBase()->exec(osIndex.str());
}
