#include "Geometry.hpp"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <set>
#include <string>
#include "ConfigFile.hpp"

void Geometry::setProblemSize(int problemSize){
    fProblemSize = problemSize;
}

datatype Geometry::euclideanDistance(datatype *vector, datatype *points)
{
    double sum = 0;
    for (int i = 0; i < fProblemSize; i++)
    {
        double tmp = vector[i] - points[i];
        sum += (tmp * tmp);
    }
    return std::sqrt(sum);
}

bool Geometry::matches(datatype *vector, std::vector<datatype *> *dataset, datatype minDist)
{
    for (auto it = dataset->cbegin(); it != dataset->cend(); it++)
    {
        datatype dist = euclideanDistance(vector, *it);
        if (dist <= minDist)
        {
            return true;
        }
    }
    return false;
}
