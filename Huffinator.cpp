#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Huffinator.hpp"
#include "FreqTable.hpp"
#include "HuffTree.hpp"

Huffinator& Huffinator::operator =(const Huffinator &other) {
    tree = other.tree;
    table = other.table;

    return *this;
}

double Huffinator::compress(std::ifstream &in, std::ofstream &out) {
    std::string ogStr;
    std::string compressed;
    char sym;

    in.unsetf(std::ios_base::skipws);
    buildTable(in);
    buildTreeFromTable();
    tree.encode(table, std::vector<bool>());

    out.seekp(0);
    out << tree.toString();

    in.clear();
    in.seekg(0);
    while(in >> sym) {
        ogStr += sym;
    }

    double length = ogStr.size()*8L;
    double nuLength = 0;
    for(std::string::iterator it=ogStr.begin(); it!=ogStr.end(); ++it) {

        std::vector<bool> code = table.getSymCode(*it);
        for(std::vector<bool>::iterator vit=code.begin(); vit!=code.end(); ++vit) {
            compressed += *vit;
        }
        nuLength += code.size();
    }

    int len = compressed.size();
    out.write((char*) &len, sizeof(int));

    std::string::iterator it = compressed.begin();
    std::bitset<8> byte;

    while(it != compressed.end()) {
        for(int i=7; i>=0 && it!=compressed.end(); i--) {
            if(*it == 1) {
                byte.set(i);
            }
            ++it;
        }
        out.write((char*) &byte, sizeof(char));
        byte.reset();
    }

    return nuLength/length;
}

void Huffinator::decompress(std::ifstream &in, std::ofstream &out) {
    std::string treeOfTheHuffMan;
    std::string compressed;
    std::bitset<8> byte;
    int length;
    char sym;

    in.unsetf(std::ios_base::skipws);
    in.read(&sym, sizeof(char));
    if(sym != '(') {
        return;
    }

    treeOfTheHuffMan += sym;
    int brackClose = -1;
    while(brackClose != 0 && in >> sym) {
        if(sym == '(') {
            brackClose--;
        } else if(sym == ')') {
            brackClose++;
        }
        treeOfTheHuffMan += sym;
    }

    buildTree(treeOfTheHuffMan);
    HuffTree *curr = &tree;

    in.read((char*) &length, sizeof(int));

    while(!in.eof()) {
        in.read(&sym, sizeof(char));
        byte = std::bitset<8>(sym);
        compressed += byte.to_string();
    }

    for(int i=0; i<compressed.size() && i<length; i++) {
        if(compressed[i] == '0') {
            curr = curr->_left;
        } else if(compressed[i] == '1') {
            curr = curr->_right;
        }

        if(curr->_sym != 0) {
            out << curr->_sym;
            curr = &tree;
        }
    }
}

void Huffinator::buildTree(std::string str) {
    tree = HuffTree(str);
}

void Huffinator::buildTreeFromTable() {
    std::vector<HuffTree*> treez;

    for(int i=0; i<table.table.size(); ++i) {
        treez.push_back(new HuffTree(std::get<1>(table.table[i]), std::get<0>(table.table[i]), nullptr, nullptr));
    }

    sortDem(treez);

    if(treez.size() > 1) {
        HuffTree *temp = new HuffTree(treez[0]->_freq + treez[1]->_freq, 0, treez[0], treez[1]);

        for(int i=2; i<treez.size(); i++) {
            temp = new HuffTree(temp->_freq + treez[i]->_freq, 0, treez[i], temp);
        }

        tree = HuffTree(*temp);
        delete temp;
    } else {
        tree = HuffTree(*treez[0]);
    }
}

void Huffinator::buildTable(std::ifstream &in) {
    char sym;

    in.seekg(0);
    while(in >> sym) {
        table.setSymFreq(sym, table.getSymFreq(sym) + 1);
    }
}

void Huffinator::sortDem(std::vector<HuffTree*> &treez) const {
    ///CHANGE TO MERGE SORT
    int i=1;
    while(i<treez.size()) {
        int j=i;
        while(j>0 && treez[j-1]->_freq > treez[j]->_freq) {
            HuffTree *temp = treez[j-1];
            treez[j-1] = treez[j];
            treez[j] = temp;
            j--;
        }
        i++;
    }
}
