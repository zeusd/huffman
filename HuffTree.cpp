#include "HuffTree.hpp"
#include "FreqTable.hpp"
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

HuffTree::HuffTree(const HuffTree &other) : _freq(0), _sym(0), _left(nullptr), _right(nullptr) {
    buildFrom(other);
}

HuffTree::HuffTree(std::string str) : _freq(0), _sym(0), _left(nullptr), _right(nullptr)  {
    std::string::iterator it = str.begin();
    std::stringstream ss;
    std::string ls;
    std::string rs;

    if(*it != '(') {
        destroy();
    } else {
        ++it;
    }

    while(it != str.end() && *it != '(' && *it != ' ') {
        ss << *it;
        ++it;
    }

    _freq = std::atoi(ss.str().c_str());

    if(it != str.end() && *it == ' ') {
        ++it;
        _sym = *it;

        return;
    } else if (it != str.end() && *it == '(') {
        ls += *it;
        int endofnode = -1;

        while (endofnode != 0) {
            ++it;
            ls += *it;

            if(*it == '(') {
                --endofnode;
            } else if(*it == ')') {
                ++endofnode;
            }
        }

        _left = new HuffTree(ls);
        ++it;

        if(*it != '(') {
            destroy();
        }
        rs += *it;
        endofnode = -1;

        while (endofnode != 0) {
            ++it;
            rs += *it;

            if(*it == '(') {
                --endofnode;
            } else if(*it == ')') {
                ++endofnode;
            }
        }

        _right = new HuffTree(rs);
        ++it;
    } else {
        destroy();
    }

    if(*it != ')') {
        destroy();
    }
}

HuffTree& HuffTree::operator =(const HuffTree &other) {
    destroy();
    buildFrom(other);

    return *this;
}

void HuffTree::encode(FreqTable &table, std::vector<bool> code) const {
    if(!_left && !_right) {
        table.setSymCode(_sym, code);
    } else if(_left && _right) {
        std::vector<bool> nuCode = code;
        nuCode.push_back(0);
        _left->encode(table, nuCode);
        nuCode = code;
        nuCode.push_back(1);
        _right->encode(table, nuCode);
    }
}

std::string HuffTree::toString() const {
    std::stringstream ss;
    ss << '(';
    ss << _freq;

    if(_left && _right) {
        ss << _left->toString();
        ss << _right->toString();
    } else {
        ss << " " <<_sym;
    }

    ss << ')';

    return ss.str();
}

void HuffTree::buildFrom(const HuffTree &other) {
    _freq = other._freq;
    _sym = other._sym;

    if(other._left) {
        _left = new HuffTree(*other._left);
    }

    if(other._right) {
        _right = new HuffTree(*other._right);
    }
}

void HuffTree::destroy() {
    _freq = 0;
    _sym = 0;

    if(_left) {
        delete _left;
        _left = nullptr;
    }

    if(_right) {
        delete _right;
        _right = nullptr;
    }
}
