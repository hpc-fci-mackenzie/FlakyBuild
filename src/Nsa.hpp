#ifndef NSA_H
#define NSA_H
#include <vector>
#include "ConfigFile.hpp"
#include "Result.hpp"
#include "SearchSpace.hpp"

class Nsa
{
private:
    ConfigFile fConfigFile;
    std::vector<result> fGeneralResults;
    SearchSpace fSearchSpace;
    void printResults();

public:
    Nsa(ConfigFile, std::vector<result>, SearchSpace);
    void run();
};

#endif