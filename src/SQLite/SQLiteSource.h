
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
	// Retourne le pointeur sur la base de donn�e en cours d'utilisation
	static SQLite::Database*	database();

	// Cr�ation d'une base de donn�es par d�faut
	SQLite::Database*			New();
	// Ouverture d'une base de donn�es
	SQLite::Database*			Open(std::string sFileName);
	// d�place la base de donn�es
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
	//! Op�rateur =
	CSQLiteSource& operator = (const CSQLiteSource&) = delete;

protected:
	// Initialisation de la base de donn�e
	bool Init();

protected:
	// Cr�ation des tables
	void CreateTablePROJET();
	void CreateTableFILTRE();

private:
	static std::string		m_sDefaultDatabase;

	Poco::File				m_fDataBase;
	SQLite::Database*		m_pDatabase;
	SQLite::TransactionEx*	m_pTransaction;

	bool					m_bDefault;
};

// Fonctions d'aide � la cr�ation de requ�te
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
	//! Op�rateur =
	AutoTransaction& operator = (const AutoTransaction&) = delete;

private:
	bool _bAutoTransaction = true;
};


// D�but d'une transaction automatique
#define __TRANSACTION_AUTO_DEBUT__				\
 		AutoTransaction _Autotransaction;

// fin d'une transaction automatique avec annulation de la transaction
#define __TRANSACTION_AUTO_ANNULE__			\
 		_Autotransaction.rollback();

// fin d'une transaction automatique avec validation de la transaction
#define __TRANSACTION_AUTO_VALIDE__			\
 		_Autotransaction.commit();
