#include "Detector.hpp"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <set>
#include <string>
#include "Debug.hpp"

Detector::Detector(ConfigFile configFile, std::vector<datatype *> *selfDataset, SearchSpace searchSpace)
{
    fConfigFile = configFile;
    geometry.setProblemSize(configFile.getProblemSize());
    fSelfDataset = selfDataset;
    fSearchSpace = searchSpace;
}

void Detector::randomVector(datatype *vector)
{
    for (int i = 0; i < fConfigFile.getProblemSize(); i++)
    {
#ifdef DEBUG
        vector[i] = fSearchSpace.getSearchSpaceIndex(2 * i) + ((fSearchSpace.getSearchSpaceIndex(2 * i + 1) - fSearchSpace.getSearchSpaceIndex(2 * i)) * Random());
#else
        vector[i] = fSearchSpace.getSearchSpaceIndex(2 * i) + ((fSearchSpace.getSearchSpaceIndex(2 * i + 1) - fSearchSpace.getSearchSpaceIndex(2 * i)) * uniform(engine));
#endif
    }
}

std::vector<datatype *> *Detector::generateDetectors()
{
    std::vector<datatype *> *detectors = new std::vector<datatype *>();
    std::cout << "Generating detectors..." << std::endl;
    size_t size = 0;
#pragma omp parallel
    {
        do
        {
            bool found = false;
            datatype *detector = new datatype[fConfigFile.getProblemSize()];
            randomVector(detector);
            if (!geometry.matches(detector, fSelfDataset, fConfigFile.getMinDist()))
            {
                std::vector<datatype *> *copy;
#pragma omp critical
                {
                    copy = new std::vector<datatype *>(detectors->begin(), detectors->end());
                }
                if (!geometry.matches(detector, copy, 0.0))
                {
#pragma omp critical
                    {
                        detectors->push_back(detector);
                    }
                    found = true;
                    std::cout << detectors->size() << "/" << fConfigFile.getMaxDetectors() << std::endl;
                }
            }
            if (!found)
            {
                delete[] detector;
            }
#pragma omp critical
            {
                size = detectors->size();
            }
        } while (size < fConfigFile.getMaxDetectors());
    }

    detectors->resize(fConfigFile.getMaxDetectors());
    return detectors;
}
result Detector::applyDetectors(std::vector<datatype *> *detectors)
{
    std::set<int> *detected = new std::set<int>();
    int trial = 1;
    for (auto it = fSelfDataset->cbegin(); it != fSelfDataset->cend(); it++)
    {
        bool actual = geometry.matches(*it, detectors, fConfigFile.getMinDist());
        bool expected = geometry.matches(*it, fSelfDataset, fConfigFile.getMinDist());
        if (actual == expected)
        {
            detected->insert(trial);
        }
        trial++;
    }

    std::cout << "Expected to be detected: ";
    std::vector<int> configExpectedDetected = fConfigFile.getExpectedDetected();
    for (auto it = configExpectedDetected.cbegin(); it != configExpectedDetected.cend();)
    {
        std::cout << *it;
        if (++it != configExpectedDetected.cend())
            std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << "Found: ";
    for (auto it = detected->cbegin(); it != detected->cend();)
    {
        std::cout << *it;
        if (++it != detected->cend())
            std::cout << ", ";
    }
    std::cout << std::endl;

    std::set<int> expectedDetected(configExpectedDetected.begin(), configExpectedDetected.end());
    datatype expectedDetectedSize = expectedDetected.size();
    for (auto it = detected->cbegin(); it != detected->cend(); it++)
    {
        auto found = expectedDetected.find(*it);
        if (found != expectedDetected.end())
        {
            expectedDetected.erase(*it);
        }
    }
    datatype new_expectedDetectedSize = expectedDetected.size();

    result result;
    result.DR = (-(new_expectedDetectedSize - expectedDetectedSize) / expectedDetectedSize);

    expectedDetected.clear();
    expectedDetected.insert(configExpectedDetected.begin(), configExpectedDetected.end());
    for (auto it = expectedDetected.cbegin(); it != expectedDetected.cend(); it++)
    {
        auto found = detected->find(*it);
        if (found != detected->end())
        {
            detected->erase(*it);
        }
    }
    datatype newDetectedSize = detected->size();
    result.FAR = (newDetectedSize / expectedDetectedSize);

    return result;
}
