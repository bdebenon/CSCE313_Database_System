//DatabaseLibrary.h - Contains declaration of Function class  
#include<set>
#include<map>
#include<exception>
#include<iostream>
#include<vector>
#pragma once  

#define DATABASELIBRARY_API __declspec(dllexport)   

namespace DatabaseLibrary
{
	class Record {
	private:
		int size;
		std::string *entries;
		std::map<std::string, std::string> attrEntryMap;
	public:
		DATABASELIBRARY_API Record(int s);
		DATABASELIBRARY_API ~Record();
		DATABASELIBRARY_API int getSize();
		DATABASELIBRARY_API std::string& operator[](size_t index);
		DATABASELIBRARY_API const std::string& operator[](size_t index) const;
		DATABASELIBRARY_API void setMap(std::vector<std::string> attributes);
		DATABASELIBRARY_API std::string getKeyVal(std::string s);
	};

	class Table {
	private:
		std::vector<std::string> attributes;
		std::set<Record*> records;
		std::string key;
	public:
		DATABASELIBRARY_API Table(); //Create table with no rows or columns
		DATABASELIBRARY_API Table(std::vector<std::string> names); //attribute names
		DATABASELIBRARY_API void addAttribute(std::string name);	//adds column to END of table with that new attrib
																		//entries currently in table get NULL for this attrib
		DATABASELIBRARY_API void deleteAttribute(std::string name);
		DATABASELIBRARY_API void insertRecord(Record* r);
		DATABASELIBRARY_API std::vector<std::string> getAttributes(); //Returns a list of the attributes for a table, in order
		DATABASELIBRARY_API int getSize(); //returns number of records
		DATABASELIBRARY_API Record* getRecord(std::string k);	//An iterator of some sort that can be used to return individual records from the 
																		//table. There are many ways this can be done.
		DATABASELIBRARY_API void setKey(std::string attribName); //Allows attribute name to be designeded as a key for the table
		DATABASELIBRARY_API Table* crossJoin(Table* t1, Table* t2); //Takes two tables as input and produces one as output
		DATABASELIBRARY_API Table* naturalJoin(Table* t1, Table* t2); //See Note(1) at bottom
		DATABASELIBRARY_API int count(std::string attribName); //Counts non-null entries
		DATABASELIBRARY_API std::string getMax(std::string attribName);
		DATABASELIBRARY_API std::string getMin(std::string attribName);
	};

	// This class is exported from the MathLibrary.dll  
	class Database {
	private:
		std::set<Table*> tables;
	public:
		DATABASELIBRARY_API Database(); //Creates Empty Database
		DATABASELIBRARY_API void addTable(Table* t, std::string name); //Adds table t to database
		DATABASELIBRARY_API void dropTable(std::string name); //Deletes table from database
		DATABASELIBRARY_API std::set<std::string> printTableNames();
		DATABASELIBRARY_API std::set<Table*> getTables();
		DATABASELIBRARY_API Table* query(std::string SELECT, std::string FROM, std::string WHERE); //See Note (2) at bottom
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