#ifndef JOIN_H
#define JOIN_H

#include "Operator.h"
#include "Record.h"
#include "FileWriter.h"

class Join : public Operator {
    private:
        FileWriter FW;
        Operator* input1;
        Operator* input2;
        FileReader fr1;
        FileReader fr2;
        string Sel_attr1;
        string Sel_attr2;
        int rightrecIndex;
        int leftrecIndex;
        vector <Record> leftPage;
        vector <Record> rightPage;
        bool first_time = true;
        bool materializin = false;
        static inline int tempFileCount;
        string tempfileName;
        

    public:
        Join(Operator *op1, Operator *op2, string pAttr1, string pAttr2) 
        {
            input1 = op1;
            input2 = op2;
            Sel_attr1 = pAttr1;
            Sel_attr2 = pAttr2;
            materializin = true;
            tempfileName = "temporary" + to_string(++tempFileCount) + ".txt";
        }
        Join(Operator *op, string fileName, string pAttr1, string pAttr2): 
            fr1(fileName)
    {
        input1 = op;
        input2 = &fr1;
        Sel_attr1 = pAttr1;
        Sel_attr2 = pAttr2;       
    }
        Join(string fileName1, string fileName2, string pAttr1, string pAttr2):
            fr1(fileName1), fr2(fileName2)
    {
        input1 = &fr1;
        input2 = &fr2;
        Sel_attr1 = pAttr1;
        Sel_attr2 = pAttr2;       
    }

        void open() {
            input1->open();
            input2->open();
        }

        vector<Record> next() {
            vector<Record> outPage;
            if(first_time){
                initialize_iterators();
                if(materializin){
                    FW.open(tempfileName);
                    FW.WritePage(rightPage, true);
                }
            }

            while(outPage.size() < pageSize){
                advanceNextPairRec();
                if(leftPage.empty()){
                    break;
                }
                Record leftrec = leftPage[leftrecIndex];
                Record rightrec = rightPage[rightrecIndex];
                if(leftrec.attributes_match(rightrec, Sel_attr1, Sel_attr2)){
                    Record concRec = leftrec.concatonaterecs(rightrec);
                    outPage.push_back(concRec);
                }
            }
        return outPage;
        }

void advanceNextPairRec(){
    rightrecIndex++;
    if(rightrecIndex == rightPage.size()){
        rightrecIndex = 0;
        leftrecIndex++;
        if(leftrecIndex == leftPage.size()){
            leftrecIndex = 0;
            rightPage = input2->next();
            if(!rightPage.empty() && materializin){
                FW.WritePage(rightPage, false);
            }
            if(rightPage.empty()){  
                leftPage = input1->next();
                if(leftPage.empty()){
                    return;
                }
                input2->close();
                if(materializin){
                    materializin = false;
                    FW.close();
                    fr2.setFilename(tempfileName);
                    input2 = &fr2;
                }
                input2->open();
                rightPage = input2->next();
            }
        }
    }
}

void initialize_iterators(){
    leftPage = input1->next();
    rightPage = input2->next();
    first_time = false;
    rightrecIndex = 0;
    leftrecIndex = 0;
}

void close() {
    input1->close();
    input2->close();
}
};


#endif
