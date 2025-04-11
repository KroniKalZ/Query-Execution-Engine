#ifndef PROJECT_H
#define PROJECT_H

#include <vector>
using namespace std;
#include "Record.h"
#include "Operator.h"
#include "FileReader.h"

class Project : public Operator {
  private:
    Operator* input;
    FileReader fr;
    vector<string> fieldNames;

  public:
    // Project constructors
    Project(string fileName, vector<string> fieldNames) :
      fr(fileName),
      input(&fr),
      fieldNames(fieldNames)
    { }

    Project(Operator *op, vector<string> fieldNames) :
      input(op),
      fieldNames(fieldNames)
    { }

    void open() {
      input->open();
    }

    vector<Record> next() {
      vector<Record> inPage = input->next();
      vector<Record> outPage;

      for(const Record& inRecord : inPage) {
        Record outRecord;
        for(const string& name : fieldNames) {
          outRecord.addAttribute(inRecord.getAttribute(name));
        }
        outPage.push_back(outRecord);
      }

      return outPage;
    }

    void close() {
      input->close();
    }
};

#endif
