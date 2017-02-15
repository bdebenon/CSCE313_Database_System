//DatabaseLibrary.h - Contains declaration of Function class  
#include<set>
#include<map>
#pragma once  

#define DATABASELIBRARY_API __declspec(dllexport)   

namespace DatabaseLibrary
{
	class Record {
	private:
		int size;
		std::map<std::string, std::string> entries;
	public:
		DATABASELIBRARY_API Record(int s);
		static DATABASELIBRARY_API int getSize();
		DATABASELIBRARY_API std::string& operator[](const std::string index);
	};

	class Table {
	private:
		std::set<std::string> attributes;
		std::set<Record*> records;
	public:
		DATABASELIBRARY_API Table(); //Create table with no rows or columns
		DATABASELIBRARY_API Table(std::set<std::string> names); //attribute names
		static DATABASELIBRARY_API void addAttribute(std::string name);	//adds column to END of table with that new attrib
																		//entries currently in table get NULL for this attrib
		static DATABASELIBRARY_API void deleteAttribute(std::string name);
		static DATABASELIBRARY_API void insertRecord(Record* r);
		static DATABASELIBRARY_API std::set<std::string> getAttributes(); //Returns a list of the attributes for a table, in order
		static DATABASELIBRARY_API int getSize(); //returns number of records
		static DATABASELIBRARY_API Record* getRecord(std::string key);	//An iterator of some sort that can be used to return individual records from the 
																		//table. There are many ways this can be done.
		static DATABASELIBRARY_API void setKey(std::string attribName); //Allows attribute name to be designeded as a key for the table
		static DATABASELIBRARY_API Table* crossJoin(Table* t1, Table* t2); //Takes two tables as input and produces one as output
		static DATABASELIBRARY_API Table* naturalJoin(Table* t1, Table* t2); //See Note(1) at bottom
		static DATABASELIBRARY_API int count(std::string attribName); //Counts non-null entries
		static DATABASELIBRARY_API std::string getMax(std::string attribName);
		static DATABASELIBRARY_API std::string getMin(std::string attribName);
	};

	// This class is exported from the MathLibrary.dll  
	class Database {
	private:
		std::set<Table*> tables;
	public:
		DATABASELIBRARY_API Database(); //Creates Empty Database
		static DATABASELIBRARY_API void addTable(Table* t, std::string name); //Adds table t to database
		static DATABASELIBRARY_API void dropTable(std::string name); //Deletes table from database
		static DATABASELIBRARY_API std::set<std::string> printTableNames();
		static DATABASELIBRARY_API std::set<Table*> getTables();
		static DATABASELIBRARY_API Table* query(std::string SELECT, std::string FROM, std::string WHERE); //See Note (2) at bottom
	};

}

/*****NOTES*****
*(1) - Two tables are taken as input, and one is produced
*as output. The first table should have an attribute name(s) matching the key from the
*second table. The join should create one entry for each row of the first table, with the
*additional columns from the matching key in the second table. If the second table does
*not have a key, or the first table does not have an attribute matching the key name, then
*an exception can be thrown, or an error returned.
*
*(2) - Query Command: Returns a table. Takes in three string arguments, SELECT, FROM, and WHERE.
*/

/*----------Start Error Codes----------*
*
*0 - attribute_exists
*1 - invalid_table
*2 - empty_database
*3 - empty_table
*4 - table_not_found
*5 - record_not_found
*6 - attribute_not_found
*7 - attribute_list_error
*8 - mismatched_tables
*9 - out_of_range
*
*----------End Error Codes----------*/