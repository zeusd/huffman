#include <vector>
#include <tuple>
#include "FreqTable.hpp"


FreqTable::FreqTable(const FreqTable &other) {
    for(int i=0; i<other.table.size(); i++) {
        table.push_back(other.table[i]);
    }
}

FreqTable& FreqTable::operator =(const FreqTable &other) {
    table.clear();
    for(int i=0; i<other.table.size(); i++) {
        table.push_back(other.table[i]);
    }

    return *this;
}

int FreqTable::getSymFreq(char sym) const {
    for(int i=0; i<table.size(); i++) {
        if(std::get<0>(table[i]) == sym) {
            return std::get<1>(table[i]);
        }
    }
    return 0;
}

void FreqTable::setSymFreq(char sym, int freq) {
    std::tuple<char, int, std::vector<bool>> symRow = make_tuple(sym, freq, std::vector<bool>());
    bool found = false;

    for(int i=0; i<table.size(); i++) {
        if(std::get<0>(table[i]) == sym) {
            table[i] = symRow;
            found = true;
        }
    }
    if(!found) {
        table.push_back(symRow);
    }
}

std::vector<bool> FreqTable::getSymCode(char sym) const {
   for(int i=0; i<table.size(); i++) {
        if(std::get<0>(table[i]) == sym) {
            return std::get<2>(table[i]);
        }
    }
    return std::vector<bool>();
}

void FreqTable::setSymCode(char sym, std::vector<bool> code) {
    std::tuple<char, int, std::vector<bool>> symRow = make_tuple(sym, getSymFreq(sym), code);
    bool found = false;

    for(int i=0; i<table.size(); i++) {
        if(std::get<0>(table[i]) == sym) {
            table[i] = symRow;
            found = true;
        }
    }
    if(!found) {
        table.push_back(symRow);
    }
}
