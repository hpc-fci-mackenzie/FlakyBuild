#include "Dataset.hpp"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#include "csv.hpp"
#include "Datatype.hpp"

Dataset::Dataset(std::string filename, int problemSize)
{
    fFilename = filename;
    fProblemSize = problemSize;
}

std::vector<datatype *> *Dataset::readDataset()
{
    std::vector<datatype *> *data = new std::vector<datatype *>();
    std::vector<std::string> none(fProblemSize, "none");
    csv::CSVFormat format;
    format.trim({' ', '\t'});
    format.column_names(none);
    std::cout << "esse eh o filename:" << fFilename << "\n" << fProblemSize
              << std::endl;
    csv::CSVReader reader(fFilename.c_str(), format);
    for (csv::CSVRow &row : reader)
    {
        datatype *row_data = new datatype[fProblemSize];
        int row_count = 0;
        for (csv::CSVField &field : row)
        {
            row_data[row_count] = field.get<datatype>();
            row_count++;
        }
        data->push_back(row_data);
    }
    return data;
};
