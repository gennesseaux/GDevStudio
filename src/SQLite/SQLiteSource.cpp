
// Inclusions
#include "Stdafx.h"
#include "SQLiteSource.h"
#include "Poco/Foundation.h"
#include "Poco/File.h"
#include "Poco/TemporaryFile.h"
#include "Poco/Util/Application.h"



std::string CSQLiteSource::m_sDefaultDatabase = Poco::Path::temp() + std::string("default.gdsproj");


// Instance
CSQLiteSource& CSQLiteSource::instance()
{
	static Outils::SafeSingletonHolder<CSQLiteSource> singleton;
	return singleton.getInstance();
}

// Retourne le pointeur sur la base de donn�e en cours d'utilisation
SQLite::Database* CSQLiteSource::database()
{
	return instance().GetDataBase();
}


// Instance
SQLite::Database* CSQLiteSource::GetDataBase()
{
	return m_pDatabase ? m_pDatabase : New();
}

// Cr�ation d'une base de donn�es par d�faut
SQLite::Database* CSQLiteSource::New()
{
	// Chemin de la base de donn�es par d�faut
	Poco::File fDefaultDatabase = m_sDefaultDatabase;

	// Suppression du pointeur vers la base de donn�e
	if (m_pDatabase)
	{
		delete m_pTransaction;	m_pTransaction = nullptr;
		delete m_pDatabase;		m_pDatabase = nullptr;
	}

	// Suppression automatique du fichier � la sortie de l'application
	Poco::TemporaryFile::registerForDeletion(m_sDefaultDatabase);
	
	// Suppression de la base par d�faut si elle existe
	if (fDefaultDatabase.exists())
		fDefaultDatabase.remove();

	// Ouverture de la base de donn�e par d�faut
	return Open(fDefaultDatabase.path());
}

// Ouverture d'une base de donn�es
SQLite::Database* CSQLiteSource::Open(std::string sFileName)
{
	// Chemin de la base de donn�es
	m_fDataBase = sFileName;

	// Initialisation de la base de donn�es
	if (m_pDatabase == nullptr)
	{
		try
		{
			m_pDatabase = new SQLite::Database(m_fDataBase.path(), SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
		}
		catch (...)
		{
			return nullptr;
		}
	}

	// Si la base de donn�es ne correspond pas au nom alors on ouvre la base de donn�es demand�e
	if (m_pDatabase && m_pDatabase->getFilename() != m_fDataBase.path())
	{
		delete m_pTransaction;	m_pTransaction = nullptr;
		delete m_pDatabase;		m_pDatabase = nullptr;

		return Open(sFileName);
	}

	//
	Init();

	return m_pDatabase;
}

// d�place la base de donn�es
SQLite::Database* CSQLiteSource::SaveAs(std::string sFileName)
{
	// Chemin de la base de donn�es 
	Poco::File fDatabase = sFileName;

	//
	if (m_fDataBase == fDatabase)
		return m_pDatabase;

	// Initialisation de la base de donn�es par d�faut
	if (m_pDatabase == nullptr)
		return nullptr;

	// Suppression du pointeur sur la base opur �viter toute violation d'acc�s
	delete m_pTransaction;	m_pTransaction = nullptr;
	delete m_pDatabase;		m_pDatabase = nullptr;

	// Suppression de la base si elle existe
	if (fDatabase.exists())
		fDatabase.remove();

	// D�placement du fichier
	m_fDataBase.moveTo(sFileName);

	// Ouverture de la base d�plac�e
	return Open(sFileName);
}

//
SQLite::TransactionEx* CSQLiteSource::GetTransaction()
{
	return m_pTransaction;
}

// Constructeur
CSQLiteSource::CSQLiteSource() : m_pDatabase(nullptr), m_pTransaction(nullptr), m_bDefault(true)
{
}

// Destructeur
CSQLiteSource::~CSQLiteSource()
{
	delete m_pTransaction;	m_pTransaction = nullptr;
	delete m_pDatabase;		m_pDatabase = nullptr;
}

// Initialisation de la base de donn�es
bool CSQLiteSource::Init()
{
	// Initialisation des transactions
	delete m_pTransaction;
	m_pTransaction = new SQLite::TransactionEx(*m_pDatabase);

	// Table PROJET
	if (!m_pDatabase->tableExists("PROJET"))
		CreateTablePROJET();

	// Table FILTRE
	if (!m_pDatabase->tableExists("FILTRE"))
		CreateTableFILTRE();

	// Table RESSOURCE
	if (!m_pDatabase->tableExists("RESSOURCE"))
		CreateTableRESSOURCE();

	// Table CONTROLE
	if (!m_pDatabase->tableExists("CONTROLE"))
		CreateTableCONTROLE();

	return true;
}

void CSQLiteSource::CreateTablePROJET()
{
	assert(m_pDatabase);

	// Cr�ation de la table
	std::ostringstream osTable;
	osTable << "create table PROJET (						";
	osTable << "PRJ_IDENT			INTEGER		NOT NULL	PRIMARY KEY AUTOINCREMENT,	";
	osTable << "PRJ_LIBELLE			TEXT		NOT NULL	UNIQUE,	";
	osTable << "PRJ_DESCRIPTION		TEXT		NULL,		";
	osTable << "PRJ_H_FOLDER		TEXT		NULL,		";
	osTable << "PRJ_CPP_FOLDER		TEXT		NULL		";
	osTable << ");";
	m_pDatabase->exec(osTable.str());

	// Cr�ation de l'index
	std::ostringstream osIndex;
	osIndex << "Create Index IX_PROJET on PROJET(PRJ_IDENT);";
	m_pDatabase->exec(osIndex.str());
}

void CSQLiteSource::CreateTableFILTRE()
{
	assert(m_pDatabase);

	// Cr�ation de la table
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
	m_pDatabase->exec(osTable.str());

	// Cr�ation de l'index
	std::ostringstream osIndex;
	osIndex << "Create Index IX_FILTRE on FILTRE(FTR_IDENT);";
	m_pDatabase->exec(osIndex.str());
}

void CSQLiteSource::CreateTableRESSOURCE()
{
	assert(m_pDatabase);

	// Cr�ation de la table
	std::ostringstream osTable;
	osTable << "create table RESSOURCE (						";
	osTable << "RES_IDENT			INTEGER		NOT NULL	PRIMARY KEY AUTOINCREMENT,	";
	osTable << "RES_LIBELLE			TEXT		NOT NULL,	";
	osTable << "RES_FILE			TEXT		NOT NULL,	";
	osTable << "RES_FTR_IDENT		INTEGER		NOT NULL,	";
	osTable << "CONSTRAINT FK_RESSOURCE_FILTRE		FOREIGN KEY(RES_FTR_IDENT) REFERENCES FILTRE(FTR_IDENT)";
	osTable << ");";
	m_pDatabase->exec(osTable.str());

	// Cr�ation de l'index
	std::ostringstream osIndex;
	osIndex << "Create Index IX_RESSOURCE on RESSOURCE(RES_IDENT);";
	m_pDatabase->exec(osIndex.str());
}

void CSQLiteSource::CreateTableCONTROLE()
{
	assert(m_pDatabase);

	// Cr�ation de la table
	std::ostringstream osTable;
	osTable << "create table CONTROLE (						";
	osTable << "CTR_IDENT			INTEGER		NOT NULL	PRIMARY KEY AUTOINCREMENT,	";
	osTable << "CTR_LIBELLE			TEXT		NOT NULL,	";
	osTable << "CTR_TYPE			TEXT		NOT NULL,	";
	osTable << "CTR_RES_IDENT		INTEGER		NOT NULL,	";
	osTable << "CONSTRAINT FK_CONTROLE_RESSOURCE		FOREIGN KEY(CTR_RES_IDENT) REFERENCES RESSOURCE(RES_IDENT)";
	osTable << ");";
	m_pDatabase->exec(osTable.str());

	// Cr�ation de l'index
	std::ostringstream osIndex;
	osIndex << "Create Index IX_CONTROLE on CONTROLE(CTR_IDENT);";
	m_pDatabase->exec(osIndex.str());
}








// Constructeur
AutoTransaction::AutoTransaction()
{
	if (CSQLiteSource::instance().GetTransaction()->IsTransactionActive())
		_bAutoTransaction = false;
	if (_bAutoTransaction)
		CSQLiteSource::instance().GetTransaction()->begin();
}

// Destructeur
AutoTransaction::~AutoTransaction()
{
	if (_bAutoTransaction && CSQLiteSource::instance().GetTransaction()->IsTransactionActive())
		rollback();
}

// Commit
void AutoTransaction::commit()
{
	if (_bAutoTransaction)
		CSQLiteSource::instance().GetTransaction()->commit();
}

// Rollback
void AutoTransaction::rollback()
{
	if (_bAutoTransaction)
		CSQLiteSource::instance().GetTransaction()->rollback();
}
