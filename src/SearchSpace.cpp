#include "SearchSpace.hpp"
#include <string>
#include <vector>
#include "Result.hpp"
#include "Dataset.hpp"
#include "Detector.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

SearchSpace::SearchSpace(int problemSize)
{
    fSearchSpace = new datatype[problemSize * 2];
    fProblemSize = problemSize;
}

void SearchSpace::init()
{
    for (int i = 0; i < fProblemSize; i++)
    {
        this->setSearchSpaceIndex(0.0, (2 * i));
        this->setSearchSpaceIndex(1.0, (2 * i + 1));
    }
}

datatype *SearchSpace::getSearchSpace()
{
    return fSearchSpace;
}

datatype SearchSpace::getSearchSpaceIndex(int index) const
{
    return fSearchSpace[index];
}

void SearchSpace::setSearchSpaceIndex(datatype value, int index)
{
    fSearchSpace[index] = value;
}
