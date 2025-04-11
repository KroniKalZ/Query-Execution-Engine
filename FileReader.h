#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
#include "Record.h"
#include "Operator.h"


// This function takes in a string with items delimited by commas
// and returns a vector of those items.
// Example - input: "str1,str2,str3,str4"
//          output: {"str1", "str2", "str3", "str4"}
vector<string> split(string line) {
  vector<string> v;
  string s;
  istringstream is(line);
  while (getline(is, s, ','))
    v.push_back(s);
  return v;
}


class FileReader : public Operator {
  private:
    fstream fin;
    string fileName;

    vector<string> attrNames;
    vector<string> attrTypes;


  public:

    FileReader() { }
    FileReader(string fileName) : fileName(fileName) {}

    
	void setFilename(string s){
		fileName = s;
	}

    void open() {
      fin.open(fileName);

      string line;

      // Read in names
      getline(fin, line);
      attrNames = split(line);

      // Read in types
      getline(fin, line);
      attrTypes = split(line);

      // Read in junk line delimiter
      getline(fin, line);
    }

    vector<Record> next() {
      vector<Record> outPage;

      string line;
      for(size_t i = 0; i < pageSize && getline(fin, line); i++) {
        vector<string> values = split(line);
        outPage.push_back( Record(attrNames, attrTypes, values) );
      }
      return outPage;
    }

    void close() {
      fin.close();
    }
};

#endif
