//DatabaseLibrary.h - Contains declaration of Function class
#include "stdafx.h"
#include "DatabaseLibrary.h"

namespace DatabaseLibrary
{
	Record::Record(int s)
	{
	}
	int Record::getSize()
	{
		return 5;
	}
	std::string & Record::operator[](const std::string index)
	{
		std::string returnValue = "Empty Return";
		return returnValue;
	}
	Table::Table()
	{
	}
	Table::Table(std::set<std::string> names)
	{
	}
	void Table::addAttribute(std::string name)
	{
		return;
	}
	void Table::deleteAttribute(std::string name)
	{
		return;
	}
	void Table::insertRecord(Record * r)
	{
		return;
	}
	std::set<std::string> Table::getAttributes()
	{
		std::set<std::string> fiveRings;
		fiveRings.insert("Empty Input");
		return fiveRings;
	}
	int Table::getSize()
	{
		return 5;
	}
	Record * Table::getRecord(std::string key)
	{
		Record* recordEntry = new Record(5);
		return recordEntry;
	}
	void Table::setKey(std::string attribName)
	{
		return void();
	}
	Table * Table::crossJoin(Table * t1, Table * t2)
	{
		Table* tableEntry = new Table();
		return tableEntry;
	}
	Table * Table::naturalJoin(Table * t1, Table * t2)
	{
		Table* tableEntry = new Table();
		return tableEntry;
	}
	int Table::count(std::string attribName)
	{
		return 5;
	}
	std::string Table::getMax(std::string attribName)
	{
		return "Empty Input";
	}
	std::string Table::getMin(std::string attribName)
	{
		return "Empty Input";
	}
	Database::Database()
	{
	}
	void Database::addTable(Table * t, std::string name)
	{
		return;
	}
	void Database::dropTable(std::string name)
	{
		return;
	}
	std::set<std::string> Database::printTableNames()
	{
		std::set<std::string> tableNames;
		tableNames.insert("34-28");
		return tableNames;
	}
	std::set<Table*> Database::getTables()
	{
		std::set<Table*> allTables;
		Table* tBrady = new Table();
		allTables.insert(tBrady);
		return allTables;
	}
	Table * Database::query(std::string SELECT, std::string FROM, std::string WHERE)
	{
		Table* tBrady = new Table();
		return tBrady;
	}
}