//DatabaseLibrary.h - Contains declaration of Function class
#include "stdafx.h"
#include "DatabaseLibrary.h"

namespace DatabaseLibrary
{
	Record::Record(size_t s)
	{
		size = s;
		if (size != 0) {
			for (int i = 0; i < size; i++) {
				entries[i] = "-1";
			}		
		}
	}

	Record::~Record() {
		entries.clear();
	}

	size_t Record::getSize()
	{
		return size;
	}

	//Mutator
	//Consider: how a mutation will change the entry in the attribute->entry map
	std::string& Record::operator[](size_t index)
	{
		try {
			entries.at(index);
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	/*
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
	*/

	void Record::setMap(std::vector<std::string> attributes) {
		int smaller;
		if (attributes.size() < getSize()) {
			smaller = attributes.size();
		}
		else {
			smaller = getSize();
		}
		for (int i = 0; i < smaller; i++) {
			attrEntryMap[attributes[i]] = entries[i];
		}

	}

	std::string Record::getKeyVal(std::string s) {
		auto it = attrEntryMap.find(s);
		if (it == attrEntryMap.end() || attrEntryMap[s] == "-1") {
			return "-1";
		}
		else{
			return attrEntryMap[s];
		}
	}

	std::map<std::string, std::string>::iterator Record::attr_begin() {
		return attrEntryMap.begin();
	}

	std::map<std::string, std::string>::iterator Record::attr_end() {
		return attrEntryMap.end();
	}

	Table::Table()
	{
		key = "-1";
	}

	Table::Table(std::vector<std::string> names)
	{
		//Consider: find a way to check for duplicates
		attributes.insert(attributes.begin(), names.begin(), names.end());
		key = "-1";
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
		try {
			if (key != "-1"){ //if it has a key, check for an addition of a duplicate key entry
				for (auto it = records.begin(); it != records.end(); ++it) {
					if ((*it)->getKeyVal(key) == r[keyIndex]) {
						throw 1;
					}
				}
			}
			r->setMap(attributes);
			records.insert(r);
		}
		catch (int i) {
			std::cout << "duplicate_key_entry" << std::endl;
		}
	}

	std::vector<std::string> Table::getAttributes()
	{
		return attributes;
	}

	size_t Table::getSize()
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

	std::set<Record*> Table::getRecords() {
		return records;
	}

	void Table::setKey(std::string attribName)
	{
		//Consider: when setting a key to an established table, with duplicate entries for that key to-be set
		try {
			bool exists = false;
			int index;
			for (auto it = attributes.begin(); it != attributes.end(); ++it) {
				index++;
				if (*it == attribName) {
					exists = true;
					keyIndex = index;
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

	std::string Table::getKey() {
		return key;
	}

	Table* Table::crossJoin(Table* t1, Table* t2)
	{
		std::set<Record*> r1 = t1->getRecords();
		std::set<Record*> r2 = t2->getRecords();

		std::vector<std::string> attr = t1->getAttributes();
		attr.insert(attr.end(), t2->getAttributes().begin(), t2->getAttributes().end());

		Table* tableEntry = new Table(attr);
		Record* insertion;

		for (auto it1 = r1.begin(); it1 != r1.end(); ++it1) {
			for (auto it2 = r2.begin; it2 != r2.end(); ++it2) {
				insertion = new Record((*it1)->getSize() + (*it2)->getSize());
				for (int k = 0; k < t1->getAttributes().size(); ++k) {
					insertion[k] = (*it1)[k];
				}
				for (int l = 0; l < t2->getAttributes().size(); ++l) {
					insertion[l + t1->getAttributes().size()] = (*it2)[l];
				}
				tableEntry->insertRecord(insertion);
			}
		}

		return tableEntry;
	}

	Table * Table::naturalJoin(Table* t1, Table* t2)
	{
		try {
			std::string k = t2->getKey();
			if (k == "-1") { //checks if t2 has a key
				std::cout << "Table two does not have a key" << std::endl;
				throw 1;
			}
			else {
				std::string k2 = "-1";
				for (auto it = t1->getAttributes().begin(); it != t1->getAttributes().end(); ++it) {
					if (*it == k) {
						k2 = *it;
						break;
					}
				}
				if (k2 == "-1") { //did not find attribute matching key from t1
					throw 1;
				}
				else {
					std::set<Record*> r1 = t1->getRecords();
					std::set<Record*> r2 = t2->getRecords();
					std::vector<std::string> attr;

					attr.push_back(k);
					//adds elements of t1 to the attribute list
					for (auto it = t1->getAttributes().begin(); it != t1->getAttributes().end(); ++it) {
						if (*it != k) {
							attr.push_back(*it);
						}
					}
					//adds elements of t2 to the attribute list
					for (auto it = t2->getAttributes().begin(); it != t2->getAttributes().end(); ++it) {
						if (*it != k) {
							attr.push_back(*it);
						}
					}
					Table* tableEntry = new Table(attr);
					Record* insertion;

					for (auto it2 = r2.begin(); it2 != r2.end(); ++it2) {
						for (auto it1 = r1.begin(); it1 != r1.end(); ++it1) {
							if ((*it1)->getKeyVal(k) == (*it2)->getKeyVal(k)) {

								insertion = new Record((*it1)->getSize() + (*it2)->getSize());
								std::string s = (*it2)->getKeyVal(k);
								int i = 0;
								insertion[i] = s;

								for (int i = 0; i < attr.size(); ++i) {
									for (auto it = (*it1)->attr_begin(); it != (*it1)->attr_end(); ++it) {
										if (attr[i] == it->first) {
											insertion[i] = it->second;
										}
									}
									for (auto it = (*it2)->attr_begin(); it != (*it2)->attr_end(); ++it) {
										if (attr[i] == it->first) {
											insertion[i] = it->second;
										}
									}
								}


								tableEntry->insertRecord(insertion);
							}
						}
					}

				}

			}


		}
		catch (int i) {
			std::cout << "Tables not a match" << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}

	}

	size_t Table::count(std::string attribName)
	{
		try {
			//check if attribute exists
			if ((std::find(attributes.begin(), attributes.end(), attribName) == attributes.end())) {
				throw 1;
			}
			else {
				size_t count = 0;
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
		//via string comparison
		std::string max = "";
		for (auto it = records.begin(); it != records.end(); ++it) {
			if (it == records.begin()) {
				max = (*it)->getKeyVal(attribName); //set max to first
			}
			if ((*it)->getKeyVal(attribName) > max) { //string comparison
				max = (*it)->getKeyVal(attribName);
			}
		}

		return max;
	}

	std::string Table::getMin(std::string attribName)
	{
		//via string comparison
		std::string min = "";
		for (auto it = records.begin(); it != records.end(); ++it) {
			if (it == records.begin()) {
				min = (*it)->getKeyVal(attribName); //set max to first
			}
			if ((*it)->getKeyVal(attribName) < min) { //string comparison
				min = (*it)->getKeyVal(attribName);
			}
		}

		return min;
	}

	Database::Database()
	{
	}

	void Database::addTable(Table * t, std::string name)
	{
		tables[name] = t;
	}

	void Database::dropTable(std::string name)
	{
		try {
			if (tables.find(name) == tables.end())
			{
				throw 1;
			}
			else{
				tables.erase(name);
			}
		}
		catch (int i){
			std::cout << "table_not_found" << std::endl;
		}
	}

	std::vector<std::string> Database::printTableNames()
	{
		//return table names
		
	}

	std::map<std::string, Table*> Database::getTables()
	{
		//return table map
		return tables;
	}

	Table * Database::query(std::string SELECT, std::string FROM, std::string WHERE)
	{
		Table* tBrady = new Table();
		return tBrady;
	}
}