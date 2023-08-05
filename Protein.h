//
// Created by R M on 8/4/23.
//

#ifndef PROTEIN_SORT_PROTEIN_H
#define PROTEIN_SORT_PROTEIN_H


struct Protein {
    std::string _id;
    std::string _sequence;
    Protein(std::string id, std::string seq){
        _sequence = seq;
        _id = id;
    }
};


#endif //PROTEIN_SORT_PROTEIN_H
