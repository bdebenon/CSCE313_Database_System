//DatabaseLibrary.h - Contains declaration of Function class
#include "stdafx.h"
#include "DatabaseLibrary.h"

namespace DatabaseLibrary
{
	Record::Record(int s)
	{
		size = s;
		entries = NULL;

		if (size != 0) {
			entries = new std::string[size];
			for (int i = 0; i < size; i++) {
				entries[i] = "-1";
			}		
		}
	}

	Record::~Record() {
		delete[] entries;
	}

	int Record::getSize()
	{
		return size;
	}

	//Mutator
	//Consider: how a mutation will change the entry in the attribute->entry map
	std::string& Record::operator[](size_t index)
	{
		try {
			if (index < size) {
				return entries[index];
			}
			else {
				throw 1;
			}
		}
		catch (int i) {
			std::cout << "out_of_bounds" << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	//Access
	const std::string& Record::operator[](size_t index) const {
		try {
			if (index<size) {
				return entries[index];
			}
			else {
				throw 1;
			}
		}
		catch (int i) {
			std::cout << "out_of_bounds" << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	void Record::setMap(std::vector<std::string> attributes) {
		int smaller;
		if (attributes.size() < getSize()) {
			smaller = attributes.size();
		}
		else {
			smaller = getSize();
		}
		for (int i = 0; i < smaller; i++) {
			if (entries[i] != "-1") {
				attrEntryMap[attributes[i]] = entries[i];
			}
		}

	}

	std::string Record::getKeyVal(std::string s) {
		auto it = attrEntryMap.find(s);
		if (it == attrEntryMap.end()) {
			return "-1";
		}
		else {
			return attrEntryMap[s];
		}
	}

	Table::Table()
	{
		key = "-1";
	}

	Table::Table(std::vector<std::string> names)
	{
		//Consider: find a way to check for duplicates
		attributes.insert(attributes.begin(), names.begin(), names.end());
	}

	void Table::addAttribute(std::string name)
	{
		try {
			for (auto it = attributes.begin(); it != attributes.end(); ++it) {
				if (*it == name) {
					throw 1;
				}
			}
			attributes.push_back(name);
		}
		catch (int i) {
			std::cout << "attribute_exists" << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	void Table::deleteAttribute(std::string name)
	{
		try {
			for (auto it = attributes.begin(); it != attributes.end(); ++it) {
				if (*it == name) {
					attributes.erase(it);
					return;
				}
			}
			throw 1;
		}
		catch (int i) {
			std::cout << "attribute_not_found" << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	void Table::insertRecord(Record* r)
	{
		r->setMap(attributes);
		records.insert(r);
	}

	std::vector<std::string> Table::getAttributes()
	{
		return attributes;
	}

	int Table::getSize()
	{
		//number of records
		return records.size();
	}

	Record* Table::getRecord(std::string k)
	{
		try {
			if (key == "-1") {
				throw 1;
			}
			else {
				for (auto it = records.begin(); it != records.end(); ++it) {
					Record* r = *it;
					if (r->getKeyVal(key) == k) {
						return r;
					}
				}
				throw "1";
			}
		}
		catch (int i) {
			std::cout << "primary_key_not_set" << std::endl;
		}
		catch (std::string s) {
			std::cout << "record_not_found" << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	void Table::setKey(std::string attribName)
	{
		try {
			bool exists = false;
			for (auto it = attributes.begin(); it != attributes.end(); ++it) {
				if (*it == attribName) {
					exists = true;
					break;
				}
			}
			//check if attribute exists
			if (!exists) {
				throw 1;
			}
			else {
				//set key to selected attribute
				key = attribName;
			}
		}
		catch (int i) {
			std::cout << "attribute_not_found" << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	//Not done yet
	Table* Table::crossJoin(Table* t1, Table* t2)
	{
		Table* tableEntry = new Table();
		return tableEntry;
	}

	Table * Table::naturalJoin(Table* t1, Table* t2)
	{
		Table* tableEntry = new Table();
		return tableEntry;
	}

	int Table::count(std::string attribName)
	{
		try {
			//check if attribute exists
			if ((std::find(attributes.begin(), attributes.end(), attribName) == attributes.end())) {
				throw 1;
			}
			else {
				int count = 0;
				for (auto it = records.begin(); it != records.end(); ++it) {
					Record* r = *it;
					if (r->getKeyVal(attribName) != "-1") {
						count++;
					}
				}
				return count;
			}
		}
		catch (int i) {
			std::cout << "attribute_not_found" << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
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