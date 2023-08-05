//
// Created by R M on 8/4/23.
//

#ifndef PROTEIN_SORT_PARSER_H
#define PROTEIN_SORT_PARSER_H
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "Protein.h"


class Parser {
public:
    Parser();
    int ParseFile(std::string filepath, std::unordered_map<std::string, Protein>& proteinHashMap, std::vector<std::string>& proteinIDs);


};


#endif //PROTEIN_SORT_PARSER_H
