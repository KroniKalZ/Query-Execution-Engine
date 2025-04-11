#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
#include "Record.h"

class FileWriter {
  private:
    ofstream fout;
    string fileName;

  public:
    void open(string fileName) {
        fout.open(fileName);      
    }

	void setFilename(string s){
		fileName = s;
	}
    
    void WritePage(vector<Record> Inpage, bool first_write){
        if(first_write){ //if first time writing true
            //Write attr names
            for(size_t i = 0; i < Inpage[0].getAttributenames().size(); i++){
                fout << Inpage[0].getAttributenames()[i];
                if(i != Inpage[0].getAttributenames().size() - 1){
                    fout << ",";
                }
            }
            fout << endl;
            //Write attr types
            for(size_t i = 0; i < Inpage[0].getAttributetypes().size(); i++){
               fout << Inpage[0].getAttributetypes()[i];
               if(i != Inpage[0].getAttributetypes().size()-1){
                   fout << ",";
               }
            }
            fout << endl;
            //write Junk line
            fout << "----------------------------";
            fout << endl;
        }
        //Writing Values 
        for(auto rec : Inpage){
            for(size_t i = 0; i < rec.attributes.size(); i++){
                if(rec.attributes[i].type == "Double"){
                    fout << any_cast<double>(rec.attributes[i].value);
                }
                else if(rec.attributes[i].type == "Integer"){
                    fout << any_cast<int>(rec.attributes[i].value);
                }
                else if(rec.attributes[i].type == "String"){
                    fout << any_cast<string>(rec.attributes[i].value);
                }
                if(i != rec.getAttributenames().size() - 1){
                    fout << ",";
                }
            }
            fout << endl;
        }
    }

    void close() {
        if(fout.is_open()){
            fout.close();
        }
    }
};

#endif

