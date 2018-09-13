#ifndef HUFFINATOR_HPP
#define HUFFINATOR_HPP

#include <fstream>
#include <string>
#include "FreqTable.hpp"
#include "HuffTree.hpp"

class Huffinator {

    HuffTree tree;
    FreqTable table;

public:
    Huffinator() {}
    Huffinator(const Huffinator& other) : tree(other.tree), table(other.table) {}
    Huffinator& operator =(const Huffinator& other);

    double compress(std::ifstream&, std::ofstream&);
    void decompress(std::ifstream&, std::ofstream&);

    ~Huffinator() {}

private:
    void buildTree(std::string);
    void buildTreeFromTable();
    void buildTable(std::ifstream&);

    void sortDem(std::vector<HuffTree*>&) const;
};

#endif // HUFFINATOR_HPP
