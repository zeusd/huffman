#include <iostream>
#include <iomanip>
#include <fstream>
#include "HuffTree.hpp"
#include "Huffinator.hpp"

int main(int argc, char *argv[]) {

    std::string c = "-c";
    std::string d = "-d";
    std::string inf = "-i";
    std::string outf = "-o";
    std::string inname;
    std::string outname;
    std::ifstream in;
    std::ofstream out;
    bool compress = false;
    bool decompress = false;

    if(argc!=6) {
        std::cout << "Wrong number of arguments :/";
        return 0;
    }

    for(int i=1; i<argc; i++) {
        if(c == argv[i]) {
            compress = true;
        }
        if(d == argv[i]) {
            decompress = true;
        }

        if(inf == argv[i] && i<argc-1) {
            ++i;
            inname = argv[i];

        }

        if(outf == argv[i] && i<argc-1) {
            ++i;
            outname = argv[i];
        }
    }

    if(compress && decompress) {
        std::cout << "Must either compress or decompress :/";
    } else if(compress) {
        in.open(inname, std::ios::in);
        out.open(outname, std::ios::out | std::ios::binary | std::ios::trunc);

        Huffinator mrHuff;

        double compRate = mrHuff.compress(in, out);

        in.close();
        out.close();

        std::cout << "Compression rate is " << compRate*100 << "%\n";
    } else if (decompress) {
        in.open(inname, std::ios::in | std::ios::binary);
        out.open(outname, std::ios::out | std::ios::trunc);

        Huffinator msHuff;
        msHuff.decompress(in, out);

        in.close();
        out.close();
    } else {
        std::cout << "You want me to do nothing? Okay...";
    }

    return 0;
}
