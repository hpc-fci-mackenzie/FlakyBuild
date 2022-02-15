#ifndef SEARCHSPACE_H
#define SEARCHSPACE_H
#include <vector>
#include "ConfigFile.hpp"
#include "Datatype.hpp"
#include "Result.hpp"

class SearchSpace
{
private:
    datatype *fSearchSpace;
    datatype getSearchSpaceIndex(int) const;
    void setSearchSpaceIndex(datatype, int);
    int fProblemSize;
    friend class Detector;

public:
    SearchSpace() = default;
    SearchSpace(int);
    void init();
    void setSearchSpace();
    datatype *getSearchSpace();
};

#endif