//
// Created by R M on 8/4/23.
//

#include "Parser.h"

Parser::Parser(){

}

int Parser::ParseFile(std::string filepath, std::unordered_map<std::string, Protein>& proteinHashMap, std::vector<std::string>& proteinIDs) {
    std::string line;
    std::string currentID = "NOT_AN_ID_DO_NOT_ADD";
    std::string currentSequence = "";
    int duplicateCt = 0;



    std::ifstream fastaFile ( filepath );
    while(getline(fastaFile, line)){

        if(line[0] == '>'){
            if(currentID != "NOT_AN_ID_DO_NOT_ADD") {
                if (proteinHashMap.emplace(currentID, Protein(currentID, currentSequence)).second)
                    duplicateCt++;
                proteinIDs.push_back(currentID);
            }
            currentID = line.substr(4, line.find("|", 4) - 4);
            currentSequence = "";
        }
        else{
            currentSequence += line;
        }
    }

    return duplicateCt;
}