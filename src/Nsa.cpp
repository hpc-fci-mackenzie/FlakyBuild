#include "Nsa.hpp"
#include <string>
#include <vector>
#include "ConfigFile.hpp"
#include "Result.hpp"
#include "Dataset.hpp"
#include "Detector.hpp"
#include "Datatype.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

Nsa::Nsa(ConfigFile configFile, std::vector<result> generalResults, SearchSpace searchSpace)
{
    fConfigFile = configFile;
    fGeneralResults = generalResults;
    fSearchSpace = searchSpace;
}

void Nsa::printResults()
{
    datatype sumDR = 0;
    datatype sumFAR = 0;
    for (result &r : fGeneralResults)
    {
        std::cout << r.DR << ", " << r.FAR << std::endl;
        sumDR += r.DR;
        sumFAR += r.FAR;
    }
    std::cout << "Average: " << sumDR / fConfigFile.getAmountOfProofs() << ", " << sumFAR / fConfigFile.getAmountOfProofs() << std::endl;
}

void Nsa::run()
{
    Dataset trainingDataset(fConfigFile.getTrainingDatasetCsvFile(), fConfigFile.getProblemSize());
    Dataset testingDataset(fConfigFile.getTestingDatasetCsvFile(), fConfigFile.getProblemSize());
    std::vector<datatype *> *selfDatasetForTraining = trainingDataset.readDataset();
    std::vector<datatype *> *generateSelfDatasetForTesting = testingDataset.readDataset();
    Detector trainingDetectors(fConfigFile, selfDatasetForTraining, fSearchSpace);
    Detector testingDetectors(fConfigFile, generateSelfDatasetForTesting, fSearchSpace);
    std::vector<datatype *> *detectors;
    for (int proof = 0; proof < fConfigFile.getAmountOfProofs(); proof++)
    {
        detectors = trainingDetectors.generateDetectors();
        fGeneralResults.push_back(testingDetectors.applyDetectors(detectors));
    }

    std::cout << "Detectors: " << fConfigFile.getMaxDetectors() << "/" << detectors->size() << std::endl;
    std::cout << "Min. distance: " << fConfigFile.getMinDist() << std::endl;
    std::cout << "Runs: " << fConfigFile.getAmountOfProofs() << std::endl;

    this->printResults();
}