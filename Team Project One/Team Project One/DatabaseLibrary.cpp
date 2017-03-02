//DatabaseLibrary.h - Contains declaration of Function class
#include "stdafx.h"
#include "DatabaseLibrary.h"

namespace DatabaseLibrary
{
	Record::Record(size_t s)
	{
		size = s;
		std::string default = "-1";
		if (size != 0) {
			for (int i = 0; i < size; i++) {
				entries.push_back(default);
			}		
		}
	}

	Record::~Record() {
		entries.clear();
	}

	/*void Record::initilizeRecord(size_t s) {
		size = s;
		std::string default = "-1";
		if (size != 0) {
			for (int i = 0; i < size; i++) {
				//entries.push_back(default);
			}
		}
	}*/

	size_t Record::getSize()
	{
		return size;
	}

	//Mutator
	void Record::set(int i, std::string s) {
		try {
			if (i < entries.size() && i >= 0)
				entries.at(i) = s;
			else
				throw 1; //INVALID TEST NUMBER SPECIFIED
		}
		catch (int i) {
			switch (i) {
			case 1: std::cout << "Invalid Insertion at Index." << std::endl; break;
			}
		}
	}
	
	//Access
	std::string const& Record::operator[](size_t index) const {
		try {
			if (index<size) {
				return entries[index];
			}
			else {
				throw 1;
			}
		}
		catch (int i) {
			switch (i) {
			case 1: std::cout << "out_of_bounds" << std::endl; break;
			}
		}
	}

	void Record::setMap(std::vector<std::string> attributes) {
		size_t smaller;
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
		else {
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
			switch (i) {
			case 1: std::cout << "attribute_exists" << std::endl; break;
			default: std::cout << "Unexpected Error" << std::endl; break;
			}
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
			switch (i) {
			case 1: std::cout << "attribute_not_found" << std::endl; break;
			default: std::cout << "Unexpected Error" << std::endl; break;
			}
		}
	}

	void Table::insertRecord(Record* r)
	{
		try {
			if (key != "-1"){ //if it has a key, check for an addition of a duplicate key entry
				for (auto it = records.begin(); it != records.end(); ++it) {
					if ((*it)->getKeyVal(key) == (*r)[keyIndex]) {
						throw 1;
					}
				}
			}
			r->setMap(attributes);
			records.insert(r);
		}
		catch (int i) {
			switch (i) {
			case 1: std::cout << "duplicate_key_entry" << std::endl; break;
			default: std::cout << "Unexpected Error" << std::endl; break;
			}
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
				throw 2;
			}
		}
		catch (int i) {
			switch (i) {
			case 1: std::cout << "primary_key_not_set" << std::endl; break;
			case 2: std::cout << "record_not_found" << std::endl; break;
			default: std::cout << "Unexpected Error" << std::endl; break;
			}
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
			int index = 0;
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
			switch (i) {
			case 1: std::cout << "attribute_not_found" << std::endl; break;
			default: std::cout << "Unexpected Error" << std::endl; break;
			}
		}
	}

	std::string Table::getKey() {
		return key;
	}

	Table* Table::crossJoin(Table* t1, Table* t2)
	{
		std::set<Record*> r1 = t1->getRecords();
		std::set<Record*> r2 = t2->getRecords();
		std::vector<std::string> v2 = t2->getAttributes();

		std::vector<std::string> attr = t1->getAttributes();
		//attr.insert(attr.end(), t2->getAttributes().begin(), t2->getAttributes().end());
		for (int i = 0; i < t2->getAttributes().size(); ++i) {
			attr.push_back(v2[i]);
		}

		Table* tableEntry = new Table(attr);
		Record* insertion;
		auto it1 = r1.begin();
		for (it1; it1 != r1.end(); ++it1) {
			auto it2 = r2.begin();
			for (it2; it2 != r2.end(); ++it2) {
				insertion = new Record((*it1)->getSize() + (*it2)->getSize());
				for (int k = 0; k < t1->getAttributes().size(); ++k) {
					insertion->set(k, (**it1)[k]);
				}
				for (int l = 0; l < t2->getAttributes().size(); ++l) {
					insertion->set(l + t1->getAttributes().size(), (**it2)[l]);
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
				std::vector<std::string> v1 = t1->getAttributes();
				for (int i = 0; i < v1.size(); ++i) {
					if (v1[i] == k) {
						k2 = i;
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
					for (int i = 0; i < v1.size(); ++i) {
						if (v1[i] != k) {
							attr.push_back(v1[i]);
						}
					}
					std::vector<std::string> v2 = t2->getAttributes();
					//adds elements of t2 to the attribute list
					for (int i = 0; i < v2.size(); ++i) {
						if (v2[i] != k) {
							attr.push_back(v2[i]);
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
								(*insertion).set(i, s);

								for (int i = 0; i < attr.size(); ++i) {
									for (auto it = (*it1)->attr_begin(); it != (*it1)->attr_end(); ++it) {
										if (attr[i] == it->first && attr[i] != s) {
											(*insertion).set(i, it->second);
										}
									}
									for (auto it = (*it2)->attr_begin(); it != (*it2)->attr_end(); ++it) {
										if (attr[i] == it->first && attr[i] != s) {
											(*insertion).set(i, it->second);
										}
									}
								}
								tableEntry->insertRecord(insertion);
							}
						}
					}
					return tableEntry;
				}
			}
		}
		catch (int i) {
			switch (i) {
			case 1: std::cout << "Tables not a match" << std::endl; break;
			default: std::cout << "Unexpected Error" << std::endl; break;
			}
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
			switch (i) {
			case 1: std::cout << "attribute_not_found" << std::endl; break;
			default: std::cout << "Unexpected Error" << std::endl; break;
			}
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


	std::pair<std::string, std::string> Table::splitString(std::string s, int i, int length) {
		std::string left = "";
		std::string right = "";

		for (int j = 0; j < i; ++j) {
			if (s[j] != ' ') {
				left = left + s[j];
			}
		}
		for (int j = i+length; j < s.size(); ++j) {
			if (s[j] != ' ') {
				right = right + s[j];
			}
		}
		std::pair<std::string, std::string> p(left, right);
		return p;
	}



	std::vector<Record*> Table::stringComparison(std::string s) {
		std::vector<Record*> v;
		if (s[0] == '(') {
			std::string s2 = "";
			for (int i = 1; i < s.size() - 1; ++i) {
				s2 = s2 + s[i];
			}
			return stringComparison(s2);
		}
		else {
			std::pair<std::string, std::string> p;
			std::string attr;
			std::string cond;
			for (int i = 0; i < s.size(); ++i) {
				switch (s[i]) {
				case '=':
					p = splitString(s, i, 1);
					attr = p.first;
					cond = p.second;
					for (auto it = records.begin(); it != records.end(); ++it) {
						if ((*it)->getKeyVal(attr) == cond) {
							v.push_back(*it);
						}
					}
					return v;
				case '<':
					switch (s[i + 1]) {
					case '>': //not equal
						p = splitString(s, i, 2);
						attr = p.first;
						cond = p.second;
						for (auto it = records.begin(); it != records.end(); ++it) {
							if ((*it)->getKeyVal(attr) != cond) {
								v.push_back(*it);
							}
						}
						return v;
					case '=':
						p = splitString(s, i, 2);
						attr = p.first;
						cond = p.second;
						for (auto it = records.begin(); it != records.end(); ++it) {
							if ((*it)->getKeyVal(attr) <= cond) {
								v.push_back(*it);
							}
						}
						return v;
					default:
						p = splitString(s, i, 1);
						attr = p.first;
						cond = p.second;
						for (auto it = records.begin(); it != records.end(); ++it) {
							if ((*it)->getKeyVal(attr) < cond) {
								v.push_back(*it);
							}
						}
						return v;
					}
					break;
				case '>':
					switch (s[i + 1]) {
					case '=':
						p = splitString(s, i, 2);
						attr = p.first;
						cond = p.second;
						for (auto it = records.begin(); it != records.end(); ++it) {
							if ((*it)->getKeyVal(attr) >= cond) {
								v.push_back(*it);
							}
						}
						return v;
					default:
						p = splitString(s, i, 1);
						attr = p.first;
						cond = p.second;
						for (auto it = records.begin(); it != records.end(); ++it) {
							if ((*it)->getKeyVal(attr) > cond) {
								v.push_back(*it);
							}
						}
						return v;
					}
					break;
				}
			} //End For Loop
		} //END ELSE
		return v;
	}

	std::vector<Record*> Table::booleanComparison(std::vector<Record*> v1, std::vector<Record*> v2, char op) {
		std::vector<Record*> v;
		bool check;
		switch (op) {
		case 'A':
			for (int i = 0; i < v1.size(); ++i) {
				for (int j = 0; j < v2.size(); ++j) {
					if (v1[i] == v2[j]) {
						v.push_back(v1[i]);
					}
				}
			}
			return v;
		case 'N':
			check = false;
			for (int i = 0; i < v1.size(); ++i) {
				for (int j = 0; j < v2.size(); ++j) {
					if (v1[i] == v2[j]) {
						check = true;
					}
				}
				if (!check) {
					v.push_back(v1[i]);
				}
				check = false;
			}
			return v;
		case 'O': 
			check = false;
			v = v1;
			for (int i = 0; i < v2.size(); ++i) {
				for (int j = 0; j < v.size(); ++j) {
					if (v[j] == v2[i]) {
						check = true;
					}
				}
				if (!check) {
					v.push_back(v2[i]);
				}
				check = false;
			}
			return v;
		}
		return v;
	}


	std::vector<Record*> Table::whereParse(std::string s) {
		int par = 0;
		int b = 0;
		for (int i = 0; i < s.size(); ++i) {
			switch (s[i]) {
			case '(':
				++par;
				break;
			case ')':
				--par;
				break;
			case 'A':
				if(i > 0 && s.size() > 3) {
					if (s[i - 1] == ' ' && s[i + 1] == 'N' && s[i + 2] == 'D' && s[i + 3] == ' ') {
						if (par == 0) {
							std::string left = "";
							std::string right = "";
							for (int j = 0; j < i - 1; j++) {
								left = left + s[j];
							}
							for (int j = i + 4; j < s.size(); j++) {
								right = right + s[j];
							}
							return booleanComparison(whereParse(left), whereParse(right), 'A');
						}
						else {
							++b;
						}
					}
				} //MAYBE ELSE NEEDED?
				break;
			case 'N':
				if (i > 0 && s.size() > 3) {
					if (s[i - 1] == ' ' && s[i + 1] == 'O' && s[i + 2] == 'T' && s[i + 3] == ' ') {
						if (par == 0) {
							std::string left = "";
							std::string right = "";
							for (int j = 0; j < i - 1; j++) {
								left = left + s[j];
							}
							for (int j = i + 4; j < s.size(); j++) {
								right = right + s[j];
							}
							return booleanComparison(whereParse(left), whereParse(right), 'N');
						}
						else {
							++b;
						}
					}
				}
				break;
			case 'O':
				if (i > 0 && s.size() > 2) {
					if (s[i - 1] == ' ' && s[i + 1] == 'R' && s[i + 2] == ' ') {
						if (par == 0) {
							std::string left = "";
							std::string right = "";
							for (int j = 0; j < i - 1; j++) {
								left = left + s[j];
							}
							for (int j = i + 3; j < s.size(); j++) {
								right = right + s[j];
							}
							return booleanComparison(whereParse(left), whereParse(right), 'O');
						}
						else {
							++b;
						}
					}
				}
				break;
			}
		}
		if (b > 0) {
			std::string s2 = "";
			for (int i = 1; i < s.size() - 1; ++i) {
				s2 = s2 + s[i];
			}
			return whereParse(s2);
		}
		else {
			return stringComparison(s);
		}
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
		catch (int i) { 
			switch (i) {
			case 1: std::cout << "table_not_found" << std::endl; break;
			default: std::cout << "Unexpected Error" << std::endl; break;
			}
		}
	}

	std::vector<std::string> Database::printTableNames()
	{
		//return table names
		std::vector<std::string> tableNames;
		for (auto it = tables.begin(); it != tables.end(); ++it) {
			tableNames.push_back(it->first);
		}
		return tableNames;
	}

	std::map<std::string, Table*> Database::getTables()
	{
		//return table map
		return tables;
	}
	


	Table * Database::query(std::string SELECT, std::string FROM, std::string WHERE)
	{
		try {
			//Checks for balanced parentheses
			std::stack<char> parenCheck;
			std::cout << "Begin Query" << std::endl;
			for (int i = 0; i < WHERE.length(); i++) {
				if (WHERE.at(i) == '(') {
					parenCheck.push('(');
				}
				if (WHERE.at(i) == ')')
				{
					if (parenCheck.empty()) {
						throw 1;
					}
					else {
						parenCheck.pop();
					}
				}
			}
			std::cout << "Query 2" << std::endl;

			if (!parenCheck.empty()) {
				throw 1;
			}
			std::cout << "Query 3" << std::endl;
			//FROM, a single table name
			bool found = false;
			auto it = tables.begin();
			for (it; it != tables.end(); ++it) {
				if (it->first == FROM) {
					found = true;
					break;
				}
			}
			if (!found) {
				throw 2;
			}
			std::cout << "Query 4" << std::endl;

			//WHERE
			std::vector<Record*> fetchedRecords = it->second->whereParse(WHERE);

			std::cout << "Query 5" << std::endl;

			//SELECT, each attribute specified by spaces
			std::stringstream ss(SELECT);
			std::vector<std::string> selectParse;
			std::string tempString;
			while (!ss.eof()) {
				ss >> tempString;
				selectParse.push_back(tempString);
			}
			std::cout << "Query 6" << std::endl;
			Table *returnTable = new Table(selectParse);
			std::cout << "Query 7" << std::endl;
			for (int i = 0; i < fetchedRecords.size(); ++i) {
				returnTable->insertRecord(fetchedRecords.at(i));
			}
			/*for (int i = 0; i < selectParse.size(); ++i) {
				returnTable->deleteAttribute(selectParse.at(i));
			}*/
			return returnTable;
		}
		catch (int i) {
			switch (i) {
			case 1: std::cout << "unbalanced_parentheses" << std::endl; break;
			case 2: std::cout << "table_not_found" << std::endl; break;
			default: std::cout << "Unexpected Error" << std::endl; break;
			}
		}

		//2 more documented errors to be accounted for: empty_table (result of query) and attribute_list_error (attribute(s) is not in the table from FROM)
	}
}