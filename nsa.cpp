#include <iostream>
#include <cstdlib>
#include <vector>
#include "csv.hpp"

constexpr int problem_size = 20;
double search_space[problem_size][problem_size];

void init_search_spaces(void)
{
    for (int i = 0; i < problem_size; i++) {
        search_space[i][0] = 0.0;
        search_space[i][1] = 1.0;
    }
}

std::vector<float *> *read_dataset(const char *filename)
{
    std::vector<float *> *data = new std::vector<float *>();
    csv::CSVReader reader(filename);
    for (csv::CSVRow &row : reader) {
        float *row_data = new float[problem_size];
        int row_count = 0;
        for (csv::CSVField &field : row) {
            row_data[row_count] = field.get<float>();
            row_count++;
        }
        data->push_back(row_data);
    }
    return data;
}

std::vector<float> *generate_detectors(int max_detectors, std::vector<float *> *self_dataset, int min_dist, int generation)
{
    return nullptr;
}

std::string apply_detectors(std::vector<float> *detectors, std::vector<float *> *self_dataset, int min_dist)
{
    std::string results = "";
    return results;
}

void run(int max_detectors, int min_dist, int amount_of_proofs)
{
    std::string general_results = "";

    init_search_spaces();

    for (int proof = 0; proof < amount_of_proofs; proof++) {
        std::vector<float*>* self_dataset_for_training = read_dataset("cortex_testing.csv");
        std::vector<float*>* generate_self_dataset_for_testing = read_dataset("cortex_testing.csv");
        std::vector<float> *detectors = generate_detectors(max_detectors, self_dataset_for_training, min_dist, proof + 1);
        general_results.append(apply_detectors(detectors, generate_self_dataset_for_testing, min_dist));
    }

    std::cout << general_results << std::endl << std::endl;
}

int main(int argc, char *argv[])
{
    int max_detectors, min_dist, amount_of_proofs;

    if (argc == 4) {
        max_detectors = std::atoi(argv[1]);
        min_dist = std::atoi(argv[2]);
        amount_of_proofs = std::atoi(argv[3]);
    } else if (argc == 1) {
        max_detectors = 160000;
        min_dist = 4;
        amount_of_proofs = 1;
    } else {
        std::cout << "Usage: " << argv[0] << " [MAX-DETECTORS] [MIN-DISTANCE] [AMOUNT-OF-POOFS]" << std::endl
                  << std::endl;
        return -1;
    }

    run(max_detectors, min_dist, amount_of_proofs);

    return 0;
}
