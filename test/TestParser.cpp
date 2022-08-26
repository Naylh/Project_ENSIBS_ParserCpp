#include <iostream>
#include <dirent.h>
#include <vector>
#include <regex>

#include "TestParser.h"

// macros for the color in the console.
#define NC "\e[0m"
#define GRN "\e[0;32m"
#define RED "\e[0;31m"


using namespace std;

TestParser::TestParser() = default;

void TestParser::runTests() {
    this->_result += GRN "\nParser test : [";
    this->testCheckCSVExtension();
    this->testCalculateParsingAttributesGoodFile();
    this->testCalculateParsingAttributesBadFile();
    this->_result += ">]" NC;

    cout << this->_result << endl;
}

void TestParser::getFiles(const regex& badFileRegex, const char *dirPath) {
    DIR * rep = opendir(dirPath);
    this->_parserList = vector<Parser>();

    if (rep != nullptr) {
        struct dirent * ent;

        while ((ent = readdir(rep)) != nullptr) {
            if (regex_match(ent->d_name, badFileRegex)) {
                string filename = "./ressources/" + string(ent->d_name);
                this->_parserList.emplace_back(filename);
            }
        }

        closedir(rep);
    }
}


void TestParser::testCheckCSVExtension() {
    Parser parserTmp = Parser("./ressources/testWithoutCSVExt");
    this->_result += (parserTmp.getFilename().empty() ? "=" : RED "E" NC);

    parserTmp = Parser("./ressources/G2_PMRSimple.csv");
    this->_result += (parserTmp.getFilename().empty() ? RED "E" NC : "=");
}


void TestParser::testCalculateParsingAttributesGoodFile() {
    regex goodFileRegex("^G[0-9]+.*");
    this->getFiles(goodFileRegex, "./ressources/");

    for (Parser elt : this->_parserList)
        this->_result += (elt.calculateParsingAttributes() ? "=" : RED "E" NC);
}


void TestParser::testCalculateParsingAttributesBadFile() {
    regex badFileRegex("^FE[0-9]+.*$");
    this->getFiles(badFileRegex, "./ressources/");

    for (Parser elt: this->_parserList)
        this->_result += (elt.calculateParsingAttributes() ? RED "E" NC : "=");
}