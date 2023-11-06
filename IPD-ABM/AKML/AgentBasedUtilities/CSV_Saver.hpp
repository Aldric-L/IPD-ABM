//
//  CSV-Saver.hpp
//  AKML Project
//
//  Created by Aldric Labarthe on 05/11/2023.
//

#ifndef CSV_Saver_hpp
#define CSV_Saver_hpp

#include <stdio.h>
#include <vector>
#include <fstream>
#include <iomanip>

#include "Save.hpp"

namespace akml {

    class CSV_Saver {
    protected:
        std::vector<std::pair<std::size_t, akml::Save*>> memory;
        
    public:
        void addSave(akml::Save** iteration);
        template <class Saveclass>
        void saveToCSV(const std::string filepathandname="data.csv") {
            std::ofstream file;
            file.open (filepathandname);
            file << "iteration," << Saveclass::printTitleAsCSV() <<"\n";
            for (int it(0); it < memory.size(); it++){
                file << it << "," << memory[it].second->printAsCSV() <<"\n";
            }
            file.close();
        }
    };

}

#endif /* CSV_Saver_hpp */
