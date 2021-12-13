#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP
#include <string>
#include <vector>
#include "Datatype.hpp"

class ConfigFile
{
private:
    std::string fConfigFile;
    int fProblemSize;
    int fMaxDetectors;
    datatype fMinDist;
    int fAmountOfProofs;
    std::string fTrainingDatasetCsvFile;
    std::string fTestingDatasetCsvFile;
    std::vector<int> fExpectedDetected;
    datatype *fSearchSpace;

public:
    ConfigFile(std::string &);
    ConfigFile() = default;
    void read();

    std::string getConfigFile() const;

    int getProblemSize() const;

    int getMaxDetectors() const;

    datatype getMinDist() const;

    int getAmountOfProofs() const;

    std::string getTrainingDatasetCsvFile() const;

    std::string getTestingDatasetCsvFile() const;

    std::vector<int> getExpectedDetected() const;

    void setSearchSpace();
    datatype getSearchSpaceIndex(int) const;
    void setSearchSpaceIndex(datatype, int);
};

#endif