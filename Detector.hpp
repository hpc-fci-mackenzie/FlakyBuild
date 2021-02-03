#ifndef DETECTOR_HPP
#define DETECTOR_HPP
#include <vector>
#include "Datatype.hpp"
#include "Dataset.hpp"
#include "Result.hpp"
#include "ConfigFile.hpp"
#include "Geometry.hpp"

class Detector
{
private:
    std::vector<datatype *> *fSelfDataset;
    int fGeneration;
    std::vector<datatype *> *fDetectors;
    ConfigFile fConfigFile;
    Geometry geometry;

public:
    Detector(ConfigFile, std::vector<datatype *>*);
    void randomVector(datatype *);
    std::vector<datatype *> *generateDetectors();
    result applyDetectors(std::vector<datatype*> *);
};

#endif