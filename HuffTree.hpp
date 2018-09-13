#ifndef HUFF_TREE_HPP
#define HUFF_TREE_HPP

#include <string>
#include <vector>
#include "FreqTable.hpp"

struct HuffTree {
    int _freq;
    char _sym;
    HuffTree *_left;
    HuffTree *_right;

public:
    HuffTree() : _freq(0), _sym(0), _left(nullptr), _right(nullptr) {}
    HuffTree(int freq, char sym, HuffTree *left, HuffTree *right) : _freq(freq), _sym(sym), _left(left), _right(right) {}
    HuffTree(const HuffTree&);
    HuffTree(std::string str);
    HuffTree& operator =(const HuffTree&);

    void encode(FreqTable &table, std::vector<bool> code) const;
    std::string toString() const;

    ~HuffTree() {destroy();}

private:
    void buildFrom(const HuffTree&);
    void destroy();
};

#endif // HUFF_TREE_H
