
#pragma once

// Inclusions
#include "GDevStudioApi/Config.h"

// Inclusions
#include <SQLite/SQLiteSource.h>


namespace GDSAPI
{

	class CSQLiteSource : public SQLite::CSQLiteSource
	{
	public:
		// Singleton
		static GDEVSTUDIOAPI_API CSQLiteSource&			SQLiteSource();
		// Retourne le pointeur sur la base de donnée en cours d'utilisation
		static GDEVSTUDIOAPI_API SQLite::Database*		Database();
		// Retourne le pointeur sur la transaction active
		static GDEVSTUDIOAPI_API SQLite::TransactionEx*	Transaction();

		// Création d'une base de données par défaut
		GDEVSTUDIOAPI_API SQLite::Database*				New();

	protected:
		// Constructeur
		CSQLiteSource();
		// Destructeur
		~CSQLiteSource();
		//! Constructeur par copie
		CSQLiteSource(const CSQLiteSource&) = delete;
		//! Opérateur =
		CSQLiteSource& operator = (const CSQLiteSource&) = delete;

	protected:
		// Initialisation de la base de donnée
		virtual void Init();

	protected:
		// Création des tables
		void CreateTablePROJET();
		void CreateTableFILTRE();
		void CreateTableRESSOURCE();
		void CreateTableCONTROLE();

	private:
		static std::string		m_sDefaultDatabase;
	};
}
