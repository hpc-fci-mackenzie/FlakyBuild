#ifndef DATASET_H
#define DATASET_H
#include <string>
#include <vector>
#include "Datatype.hpp"

class Dataset
{
private:
    std::string fFilename;
    int fProblemSize;

public:
    Dataset(std::string, int);
    std::vector<datatype *> *readDataset();
};

#endif