#ifndef SELECT_H
#define SELECT_H

#include "Operator.h"
#include "Record.h"
#include "FileReader.h"
#include <variant>
#include <any>

class Select : public Operator {
    private:
        Operator* input;
        FileReader fr;
        char Sel_op;
        string Sel_attr;
        string Sel_val;
        int recIndex;
        vector <Record> inputPage;

    public:
        // Select constructors
        Select(string fileName, string p_attr, string p_op, string p_val) :
            fr(fileName)
        {
            input = &fr;
            Sel_attr = p_attr;
            Sel_op = p_op[0];
            Sel_val = p_val;
            recIndex = 0;

        }
        Select(Operator *op, string p_attr, string p_op, string p_val) {
            input = op;
            Sel_attr = p_attr;
            Sel_op = p_op[0];
            Sel_val = p_val;
            recIndex = 0;
        }

        void open() {
            input->open();
            recIndex = 0;
        }

        vector<Record> next() {
            vector<Record> outPage;
            while(outPage.size() < pageSize){
                if(recIndex == 0 || recIndex == inputPage.size()){
                    inputPage = input->next();
                    recIndex = 0;
                }
                if(inputPage.empty()){
                    break;
                }
                Record rec = inputPage[recIndex];
                recIndex++;
                if (rec.evaluate_cond(Sel_attr, Sel_val, Sel_op)){
                    outPage.push_back(rec); 
                }
            }
            return outPage;
        }

        void close() {
            input->close();
            recIndex = 0;
        }
};

#endif
