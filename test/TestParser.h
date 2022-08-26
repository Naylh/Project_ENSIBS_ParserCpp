#ifndef PROJET_RESEAU_CPP_TESTPARSER_H
#define PROJET_RESEAU_CPP_TESTPARSER_H

#include "../sources/parsing/Parser.h"

/**
 * class that test the Node class.
 *
 * @author COUTAND Bastien
 * @version 1.1
 * @date 23.04.2022
 */
class TestParser {
    private:
        /**
         * Vector containing a list of parsers.
         */
        std::vector<Parser> _parserList;

        /**
         * Result in form of [=E=E==>].
         * E : Error
         * = : OK
         */
        std::string _result;

        /**
         * Function that allows to load the files of the dirPath folder according to a regex pattern.
         *
         * @param regex   : the pattern.
         * @param dirPath : the folder path.
         */
        void getFiles(const std::regex& regex, const char *dirPath);

        /**
         * Function to test the CSVExtension function.
         */
        void testCheckCSVExtension();

        /**
         * Function that tests the calculateParsingAttributes function for the correct files.
         */
        void testCalculateParsingAttributesGoodFile();

        /**
         * Function to test the calculateParsingAttributes function for incorrect files.
         */
        void testCalculateParsingAttributesBadFile();
    public:
        TestParser();

        /**
         * Function to run all tests.
         */
        void runTests();
};


#endif //PROJET_RESEAU_CPP_TESTPARSER_H