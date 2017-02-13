//DatabaseLibrary.h - Contains declaration of Function class  
#include<set>
#include<list>
#pragma once  

#ifdef DATABASELIBRARY_EXPORTS  
#define DATABASELIBRARY_API __declspec(dllexport)   
#else  
#define DATABASELIBRARY_API __declspec(dllimport)   
#endif  

namespace DatabaseLibrary
{
	// This class is exported from the MathLibrary.dll  
	class Database {
	private:
		static DATABASELIBRARY_API std::set<Table*> tables;
	public:
		static DATABASELIBRARY_API Database();
		static DATABASELIBRARY_API void addTable(Table* t, std::string name);
		static DATABASELIBRARY_API void dropTable(std::string name);
		static DATABASELIBRARY_API std::set<std::string> printTableNames();
		static DATABASELIBRARY_API std::set<Table*> getTables();
		static DATABASELIBRARY_API Table* query(std::string select, std::string from, std::string where);
	};

	class Table {
	private:
		static DATABASELIBRARY_API std::set<std::string> attributes;
		static DATABASELIBRARY_API std::set<Record*> records;
	public:
		static DATABASELIBRARY_API Table();
		static DATABASELIBRARY_API Table(std::list<std::string> names); //attribute names
		static DATABASELIBRARY_API void addAttrib(std::string name);
		//adds column to END of table with that new attrib
		//entries currently in table get NULL for this attrib
		static DATABASELIBRARY_API void deleteAttrib(std::string name);
		static DATABASELIBRARY_API void insertRec(Record* r);
		static DATABASELIBRARY_API set<string> getAttrib();
		static DATABASELIBRARY_API int getSize(); //returns number of records
											 //An iterator of some sort that can be used to return individual records from the 
											 //table. There are many ways this can be done.
		static DATABASELIBRARY_API void setKey(string attribName);
		static DATABASELIBRARY_API Table* crossJoin(Table* t1, Table* t2);
		static DATABASELIBRARY_API Table* naturalJoin(Table* t1, Table* t2);
		static DATABASELIBRARY_API int count(string attribName);
		static DATABASELIBRARY_API std::string getMax(string attribName); //idk if int
		static DATABASELIBRARY_API std::string getMin(string attribName); //idk if int
	};

	class Record {
	private:
		static DATABASELIBRARY_API int size;
		static DATABASELIBRARY_API std::list<std::string> entries;
	public:
		static DATABASELIBRARY_API Record(int s) : size(s);
		static DATABASELIBRARY_API int getSize();
		//Accessor function, like r[i]
	};
}

