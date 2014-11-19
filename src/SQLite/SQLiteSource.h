
#pragma once

// Inclusions STL
#include <string>
#include <sstream>
#include <memory>
#include <cassert>

// Inclusions POCO
#include <Poco/File.h>
#include <Poco/Logger.h>
#include <Poco/NumberFormatter.h>

// Inclusions
#include <DObject/DObjBase.h>
#include <Outils/SafeSingletonHolder.h>
#include <SQLiteCpp/Database.h>
#include <SQLite/TransactionEx.h>

class CSQLiteSource
{
	friend class Outils::SafeSingletonHolder < CSQLiteSource > ;

public:
	// Instance
	static CSQLiteSource&		instance();
	// Retourne le pointeur sur la base de donnée en cours d'utilisation
	static SQLite::Database*	database();

	// Création d'une base de données par défaut
	SQLite::Database*			New();
	// Ouverture d'une base de données
	SQLite::Database*			Open(std::string sFileName);
	// déplace la base de données
	SQLite::Database*			SaveAs(std::string sFileName);
	// 
	SQLite::Database*			GetDataBase();
	//
	SQLite::TransactionEx*		GetTransaction();

public:
	// Destructeur
	~CSQLiteSource();

protected:
	// Constructeur
	CSQLiteSource();
	//! Constructeur par copie
	CSQLiteSource(const CSQLiteSource&) = delete;
	//! Opérateur =
	CSQLiteSource& operator = (const CSQLiteSource&) = delete;

protected:
	// Initialisation de la base de donnée
	bool Init();

protected:
	// Création des tables
	void CreateTablePROJET();
	void CreateTableFILTRE();

private:
	static std::string		m_sDefaultDatabase;

	Poco::File				m_fDataBase;
	SQLite::Database*		m_pDatabase;
	SQLite::TransactionEx*	m_pTransaction;

	bool					m_bDefault;
};

// Fonctions d'aide à la création de requête
inline std::string ToQuery(std::string sString)
{
	if (sString.length()==0)
		return "null";

	std::ostringstream toQuery;
	toQuery << "'" << sString << "'";
	return toQuery.str();
}
inline std::string ToQuery(unsigned long ul)
{
	if (ul==DefULong)
		return "null";
	return Poco::NumberFormatter::format(ul);
}


class AutoTransaction
{
public:
	// Constructeur
	AutoTransaction();
	// Destructeur
	~AutoTransaction();

	// Commit
	void commit();
	// Rollback
	void rollback();

protected:
	//! Constructeur par copie
	AutoTransaction(const AutoTransaction&) = delete;
	//! Opérateur =
	AutoTransaction& operator = (const AutoTransaction&) = delete;

private:
	bool _bAutoTransaction = true;
};


// Début d'une transaction automatique
#define __TRANSACTION_AUTO_DEBUT__				\
 		AutoTransaction _Autotransaction;

// fin d'une transaction automatique avec annulation de la transaction
#define __TRANSACTION_AUTO_ANNULE__			\
 		_Autotransaction.rollback();

// fin d'une transaction automatique avec validation de la transaction
#define __TRANSACTION_AUTO_VALIDE__			\
 		_Autotransaction.commit();
