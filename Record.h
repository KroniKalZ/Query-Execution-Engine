#ifndef RECORD_H
#define RECORD_H

#include <any>
#include <iostream>
#include <vector>
#include <string.h>
#include <variant>
using namespace std;


class Record {
    private:
        class Attribute {
            public:
                string name;
                string type;
                any value;

                Attribute(string name, string type, string strVal) : name(name), type(type) {
                    if (type == "Double")
                        value = stod(strVal);
                    else if (type == "Integer")
                        value = stoi(strVal);
                    else {
                        type = "String"; // Force to String if user provides unknown type
                        value = strVal;
                    }
                }

                friend ostream& operator<< (ostream& os, const Attribute& a) {
                    if (a.type == "Double")
                        os << any_cast<double>(a.value);
                    else if (a.type == "Integer")
                        os << any_cast<int>(a.value);
                    else
                        os << any_cast<string>(a.value);
                    return os;
                }


                bool evaluate_cond(string Sel_val, char Sel_op) {
                    if (type == "String") {
                        string recValue = any_cast<string>(value);
                        string selValue = Sel_val;
                        if(Sel_op == '='){return recValue == selValue;}
                        else if(Sel_op == '!'){return recValue != selValue;}
                    }
                    else if (type == "Double") {
                        double recValue = any_cast<double>(value);
                        double selValue = stod(Sel_val);
                        if(Sel_op == '='){return recValue == selValue;}
                        else if(Sel_op == '!'){return recValue != selValue;}
                        else if(Sel_op == '<'){return recValue < selValue;}
                        else if(Sel_op == '>'){return recValue > selValue;} 
                    }
                    else if (type == "Integer") {
                        int recValue = any_cast<int>(value);
                        int selValue = stoi(Sel_val); 
                        if(Sel_op == '='){return recValue == selValue;}
                        else if(Sel_op == '!'){return recValue != selValue;}
                        else if(Sel_op == '<'){return recValue < selValue;}
                        else if(Sel_op == '>'){return recValue > selValue;} 
                    }            
                    else {
                        cout << "BAD" << endl;
                    } 
                    return false;
                }
        };

    public:
        vector<Attribute> attributes;

        Record() {}

        Record(const vector<string>& names, const vector<string>& types, const vector<string>& vals) {
            for(size_t i=0; i < names.size(); i++) {
                addAttribute(names[i], types[i], vals[i]);
            }
        }

        void addAttribute(const string& name, const string& type, const string& value) {
            attributes.emplace_back(name, type, value);
        }

        void addAttribute(const Attribute& attr) {
            attributes.push_back(attr);
        }

        vector<string> getAttributenames(){
            vector<string> attrNames;
            for(const auto& attr : attributes){
                attrNames.push_back(attr.name);
            }
            return attrNames;
        }

        Attribute getAttribute(const string& name) const {
            size_t i;
            for(i=0; i < attributes.size(); i++) {
                if (name == attributes[i].name)
                    break;
            }

            return attributes[i];
        }

        vector<string> getAttributetypes(){
            vector<string> attrTypes;
            for(const auto& attr : attributes){
                attrTypes.push_back(attr.type);
            }
            return attrTypes;
        }

        friend ostream& operator<< (ostream& os, const Record& r) {
            bool first = true;
            for(Attribute attr : r.attributes) {
                if (first) first = false;
                else cout << " ";

                cout << attr;
            }
            return os;
        }

        bool evaluate_cond(const string& Sel_attr, const string& Sel_val, char Sel_op){
            for(int i = 0; i < attributes.size(); i++){
                if(attributes[i].name == Sel_attr){
                    return attributes[i].evaluate_cond(Sel_val, Sel_op); 
                }
            }
            return false;
        }

        Record concatonaterecs(const Record& r2){
            Record conc;
            for(const auto& attr : attributes){
                conc.addAttribute(attr);
            }
            for(const auto& attr : r2.attributes){
                conc.addAttribute(attr);
            }
            return conc;
        }

        bool attributes_match(const Record& other, const string& Attr1Name, const string& Attr2Name) {
            Attribute Attr1 = getAttribute(Attr1Name);
            Attribute Attr2 = other.getAttribute(Attr2Name);
            if (Attr1.type != Attr2.type) {
                return false;
            }

            if (Attr1.type == "String") {
                return any_cast<string>(Attr1.value) == any_cast<string>(Attr2.value);
            } 
            else if (Attr1.type == "Integer") {
                return any_cast<int>(Attr1.value) == any_cast<int>(Attr2.value);
            } 
            else if (Attr1.type == "Double") {
                return any_cast<double>(Attr1.value) == any_cast<double>(Attr2.value);
            }
            return false; 
        }

};

#endif
