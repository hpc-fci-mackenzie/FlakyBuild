#include <cmath>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "csv.hpp"
#include "ConfigFile.hpp"
#include "Dataset.hpp"
#include "Datatype.hpp"
#include "Detector.hpp"
#include "Result.hpp"



void initSearchSpace(ConfigFile &configFile)
{
    configFile.setSearchSpace();
    for (int i = 0; i < configFile.getProblemSize(); i++)
    {
        configFile.setSearchSpaceIndex(0.0, (2 * i));
        configFile.setSearchSpaceIndex(1.0, (2 * i + 1));
    }
}

void run(ConfigFile &configFile)
{
    std::vector<result> generalResults;
    initSearchSpace(configFile);
    Dataset trainingDataset(configFile.getTrainingDatasetCsvFile(), configFile.getProblemSize());
    Dataset testingDataset(configFile.getTestingDatasetCsvFile(), configFile.getProblemSize());
    std::vector<datatype *> *selfDatasetForTraining = trainingDataset.readDataset();
    std::vector<datatype *> *generateSelfDatasetForTesting = testingDataset.readDataset();
    Detector trainingDetectors(configFile, selfDatasetForTraining);
    Detector testingDetectors(configFile, generateSelfDatasetForTesting);
    for (int proof = 0; proof < configFile.getAmountOfProofs(); proof++)
    {
        std::vector<datatype *> *detectors = trainingDetectors.generateDetectors();
        generalResults.push_back(testingDetectors.applyDetectors(detectors));
    }
    
    std::cout << "Detectors: " << configFile.getMaxDetectors() << std::endl;
    std::cout << "Min. distance: " << configFile.getMinDist() << std::endl;
    std::cout << "Runs: " << configFile.getAmountOfProofs() << std::endl;
    datatype sumDR = 0;
    datatype sumFAR = 0;
    for (result &r : generalResults)
    {
        std::cout << r.DR << ", " << r.FAR << std::endl;
        sumDR += r.DR;
        sumFAR += r.FAR;
    }
    std::cout << "Average: " << sumDR / configFile.getAmountOfProofs() << ", " << sumFAR / configFile.getAmountOfProofs() << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        std::string configFileName = argv[1];
        ConfigFile configFile(configFileName);
        configFile.read();
        run(configFile);
    }
    else
    {
        std::cout << "Usage: " << argv[0] << " <CONFIG-FILE>" << std::endl
                  << std::endl;
        return -1;
    }

    return 0;
}
