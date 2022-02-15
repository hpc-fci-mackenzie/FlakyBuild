#ifndef DETECTOR_HPP
#define DETECTOR_HPP
#include <vector>
#include "ConfigFile.hpp"
#include "Datatype.hpp"
#include "Geometry.hpp"
#include "Result.hpp"
#include "SearchSpace.hpp"

class Detector
{
private:
    std::vector<datatype *> *fSelfDataset;
    std::vector<datatype *> *fDetectors;
    SearchSpace fSearchSpace;
    ConfigFile fConfigFile;
    Geometry geometry;

public:
    Detector(ConfigFile, std::vector<datatype *> *, SearchSpace);
    void randomVector(datatype *);
    std::vector<datatype *> *generateDetectors();
    result applyDetectors(std::vector<datatype *> *);
};

#endif