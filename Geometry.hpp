#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
#include <vector>
#include "Datatype.hpp"
#include "Dataset.hpp"

class Geometry
{
private:
    int fProblemSize;
public:
    void setProblemSize(int);
    datatype euclideanDistance(datatype *, datatype *);
    bool matches(datatype *, std::vector<datatype *> *, datatype);
};

#endif