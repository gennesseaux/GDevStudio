
// Inclusions
#include "Stdafx.h"
#include "GyResGen/DObject/SQLiteHelper.h"

//
using namespace GyResGen;


// Instance
CSQLiteHelper& CSQLiteHelper::SQLiteHelper()
{
	// Since it's a static variable, if the class has already been created,
	// It won't be created again.
	// And it **is** thread-safe in C++11.
	static CSQLiteHelper _instance;
	// Return a reference to our instance.
	return _instance;
}

// Retourne le pointeur sur la base de donnée en cours d'utilisation
SQLite::Database* CSQLiteHelper::Database()
{
	return SQLiteHelper().GetDataBase();
}

// Retourne le pointeur sur la base de donnée en cours d'utilisation
SQLite::TransactionEx* CSQLiteHelper::Transaction()
{
	return SQLiteHelper().GetTransaction();
}
// Initialisation de la base de donnée
void GyResGen::CSQLiteHelper::InitConnexion(std::string filename)
{
	Open(filename);
}

// Constructeur
CSQLiteHelper::CSQLiteHelper() : SQLite::CSQLiteSource()
{
}

// Destructeur
CSQLiteHelper::~CSQLiteHelper()
{
}

// Initialisation de la base de données
void CSQLiteHelper::Init()
{
	// Table RESSOURCE
	if (!GetDataBase()->tableExists("GRG_RESSOURCE"))
		CreateTableRESSOURCE();

	// Table CONTROLE
	if (!GetDataBase()->tableExists("GRG_CONTROLE"))
		CreateTableCONTROLE();
}

void CSQLiteHelper::CreateTableRESSOURCE()
{
	assert(GetDataBase());

	// Création de la table
	std::ostringstream osTable;
	osTable << "create table GRG_RESSOURCE (				";
	osTable << "RES_IDENT				INTEGER		NOT NULL	PRIMARY KEY, ";
	osTable << "RES_UUID_DOCUMENT		TEXT		NULL,		";
	osTable << "RES_CLASSE_NOM			TEXT		NULL,		";
	osTable << "RES_DB_MANDATORY		INTEGER		NULL,		";
	osTable << "RES_CHANGE_HANDLER		INTEGER		NULL,		";
	osTable << "RES_WND_RESIZER			INTEGER		NULL,		";
	osTable << "RES_DB_XSUPER_TOOLTIP	INTEGER		NULL		";
	osTable << ");";
	GetDataBase()->exec(osTable.str());

	// Création de l'index
	std::ostringstream osIndex;
	osIndex << "Create Index IX_GRG_RESSOURCE on GRG_RESSOURCE(RES_IDENT);";
	GetDataBase()->exec(osIndex.str());

	// Création du trigger delete
	std::ostringstream osTrigger;
	osTrigger << "CREATE TRIGGER DELETE_GRG_RESSOURCE BEFORE DELETE on RESSOURCE FOR EACH ROW ";
	osTrigger << "  Begin ";
	osTrigger << "    DELETE FROM GRG_RESSOURCE where GRG_RESSOURCE.RES_IDENT = old.RES_IDENT;";
	osTrigger << "  END; ";
	GetDataBase()->exec(osTrigger.str());
}

void CSQLiteHelper::CreateTableCONTROLE()
{
	assert(GetDataBase());

	// Création de la table
	std::ostringstream osTable;
	osTable << "create table GRG_CONTROLE (					";
	osTable << "CTR_IDENT			INTEGER		NOT NULL	PRIMARY KEY,	";
	osTable << "CTR_CLASSE_NOM		TEXT		NULL,	";
	osTable << "CTR_VARIABLE_NOM	TEXT		NULL	";
	osTable << ");";
	GetDataBase()->exec(osTable.str());

	// Création de l'index
	std::ostringstream osIndex;
	osIndex << "Create Index IX_GRG_CONTROLE on GRG_CONTROLE(CTR_IDENT);";
	GetDataBase()->exec(osIndex.str());

	// Création du trigger delete
	std::ostringstream osTrigger;
	osTrigger << "CREATE TRIGGER DELETE_GRG_CONTROLE BEFORE DELETE on CONTROLE FOR EACH ROW ";
	osTrigger << "  Begin ";
	osTrigger << "    DELETE FROM GRG_CONTROLE where GRG_CONTROLE.CTR_IDENT = old.CTR_IDENT;";
	osTrigger << "  END; ";
	GetDataBase()->exec(osTrigger.str());
}
