#ifndef FREQ_TABLE_HPP
#define FREQ_TABLE_HPP

#include <vector>
#include <tuple>

struct FreqTable {
    std::vector<std::tuple<char, int, std::vector<bool>>> table;

public:
    FreqTable() {table.clear();}
    FreqTable(const FreqTable&);
    FreqTable& operator =(const FreqTable&);

    int getSymFreq(char) const;
    void setSymFreq(char, int);
    std::vector<bool> getSymCode(char) const;
    void setSymCode(char, std::vector<bool>);

    ~FreqTable() {}
};

#endif // FREQ_TABLE_HPP
