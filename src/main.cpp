#include <cmath>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "csv.hpp"
#include "Nsa.hpp"
#include "Result.hpp"
#include "SearchSpace.hpp"

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        std::string configFileName = argv[1];
        std::vector<result> generalResults;
        ConfigFile configFile(configFileName);
        configFile.read();
        SearchSpace searchSpace = SearchSpace(configFile.getProblemSize());
        Nsa nsa = Nsa(configFile, generalResults, searchSpace);
        nsa.run();
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " <CONFIG-FILE>" << std::endl
                  << std::endl;
        return -1;
    }

    return 0;
}
