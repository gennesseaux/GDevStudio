
#pragma once

// Inclusions STL
#include <string>
#include <sstream>
//#include <memory>
#include <cassert>

// Inclusions
#include <SQLite/SQLiteSource.h>


namespace GyResGen
{

	class CSQLiteHelper : public SQLite::CSQLiteSource
	{
	public:
		// Singleton
		static CSQLiteHelper&		SQLiteHelper();
		// Retourne le pointeur sur la base de donn�e en cours d'utilisation
		static SQLite::Database*	Database();
		// Retourne le pointeur sur la transaction active
		static SQLite::TransactionEx*	Transaction();

		// Initialisation de la base de donn�e
		void						InitConnexion(std::string filename);

	protected:
		// Constructeur
		CSQLiteHelper();
		// Destructeur
		~CSQLiteHelper();
		//! Constructeur par copie
		CSQLiteHelper(const CSQLiteHelper&) = delete;
		//! Op�rateur =
		CSQLiteHelper& operator = (const CSQLiteHelper&) = delete;

	protected:
		// Initialisation de la base de donn�e
		virtual void Init();

	protected:
		// Cr�ation des tables
		void CreateTableRESSOURCE();
		void CreateTableCONTROLE();

	private:
		static std::string		m_sDefaultDatabase;
	};
}
