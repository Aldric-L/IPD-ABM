//
//  CSV-Saver.cpp
//  AKML Project
//
//  Created by Aldric Labarthe on 05/11/2023.
//

#include "CSV_Saver.hpp"

namespace akml {
    void CSV_Saver::addSave(akml::Save** iteration){
        if (memory.size() == 0)
            memory.push_back(std::make_pair(1, *iteration));
        else
            memory.push_back(std::make_pair(memory.back().first+1, *iteration));
    }

    /*void CSV_Saver::saveToCSV(const std::string filepathandname){
        std::ofstream file;
        file.open (filepathandname);
        for (int it(0); it < memory.size(); it++){
            file << it << "," << memory[it].second->printAsCSV() <<"\n";
        }
        file.close();
    }*/
}
