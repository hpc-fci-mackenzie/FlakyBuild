#include "ConfigFile.hpp"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <set>
#include "csv.hpp"

ConfigFile::ConfigFile(std::string &name)
{
    fConfigFile = name;
}

void ConfigFile::read()
{
    csv::CSVFormat format;
    format.trim({' ', '\t'});
    format.variable_columns(csv::VariableColumnPolicy::KEEP);
    csv::CSVReader reader(fConfigFile, format);
    csv::CSVRow row;
    // 1st row
    reader.read_row(row);
    fProblemSize = row[0].get<int>();
    fMaxDetectors = row[1].get<int>();
    fMinDist = row[2].get<int>();
    fAmountOfProofs = row[3].get<int>();
    fTrainingDatasetCsvFile = row[4].get();
    fTestingDatasetCsvFile = row[5].get();
    // 2nd row
    reader.read_row(row);
    for (csv::CSVField &field : row)
        fExpectedDetected.push_back(field.get<int>());
}

std::string ConfigFile::getConfigFile() const
{
    return fConfigFile;
}
int ConfigFile::getMaxDetectors() const
{
    return fMaxDetectors;
}

datatype ConfigFile::getMinDist() const
{
    return fMinDist;
}

int ConfigFile::getAmountOfProofs() const
{
    return fAmountOfProofs;
}

std::string ConfigFile::getTrainingDatasetCsvFile() const
{
    return fTrainingDatasetCsvFile;
}

std::string ConfigFile::getTestingDatasetCsvFile() const
{
    return fTestingDatasetCsvFile;
}

std::vector<int> ConfigFile::getExpectedDetected() const
{
    return fExpectedDetected;
}

int ConfigFile::getProblemSize() const
{
    return fProblemSize;
}
