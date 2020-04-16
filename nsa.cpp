#include <cstdlib>
#include <iostream>
#include <cmath>
#include <set>
#include <string>
#include <vector>
#include "csv.hpp"

typedef double datatype;

struct {
    int problem_size;
    int max_detectors;
    datatype min_dist;
    int amount_of_proofs;
    char trainning_dataset_csv_file[100] = {0};
    char testing_dataset_csv_file[100] = {0};
    std::vector<int> expected_detected;
    datatype *search_space;
} config;

void read_config_file(const char* config_file)
{
    csv::CSVFormat format;
    format.trim({ ' ', '\t'  });
    format.variable_columns(csv::VariableColumnPolicy::KEEP);
    csv::CSVReader reader(config_file, format);
    csv::CSVRow row;
    // 1st row
    reader.read_row(row);
    config.problem_size = row[0].get<int>();
    config.max_detectors = row[1].get<int>();
    config.min_dist = row[2].get<datatype>();
    config.amount_of_proofs = row[3].get<int>();
    row[4].get().copy(config.trainning_dataset_csv_file, 100);
    row[5].get().copy(config.testing_dataset_csv_file, 100);
    // 2nd row
    reader.read_row(row);
    for (csv::CSVField& field: row) {
        config.expected_detected.push_back(field.get<int>());
    }
}

void init_search_space(void)
{
    config.search_space = new datatype[config.problem_size * 2];
    for (int i = 0; i < config.problem_size; i++) {
        config.search_space[2 * i] = 0.0;
        config.search_space[2 * i + 1] = 1.0;
    }
}

std::vector<datatype *> *read_dataset(const char *filename)
{
    std::vector<datatype *> *data = new std::vector<datatype *>();
    std::vector<std::string> none(config.problem_size, "none");
    csv::CSVFormat format;
    format.trim({ ' ', '\t'  });
    format.column_names(none);
    csv::CSVReader reader(filename, format);
    for (csv::CSVRow &row : reader) {
        datatype *row_data = new datatype[config.problem_size];
        int row_count = 0;
        for (csv::CSVField &field : row) {
            row_data[row_count] = field.get<datatype>();
            row_count++;
        }
        data->push_back(row_data);
    }
    return data;
}

/****
/* pRNG based on http://www.cs.wm.edu/~va/software/park/park.html
*****/

#define MODULUS    2147483647
#define MULTIPLIER 48271
#define DEFAULT    123456789

static long seed = DEFAULT;

double Random(void)
/* ----------------------------------------------------------------
 * Random returns a pseudo-random real number uniformly distributed
 * between 0.0 and 1.0.
 * ----------------------------------------------------------------
 */
{
    const long Q = MODULUS / MULTIPLIER;
    const long R = MODULUS % MULTIPLIER;
    long t;

    t = MULTIPLIER * (seed % Q) - R * (seed / Q);
    if (t > 0) {
        seed = t;
    } else {
        seed = t + MODULUS;
    }
    return ((double) seed / MODULUS);
}

void random_vector(datatype *vector)
{
    for (int i = 0; i < config.problem_size; i++) {
        vector[i] = config.search_space[2 * i] + ((config.search_space[2 * i + 1] - config.search_space[2 * i]) * Random());
    }
}

datatype euclidean_distance(datatype *vector, datatype *points) {
    double sum = 0;
    for (int i = 0; i < config.problem_size; i++) {
        double tmp = vector[i] - points[i];
        sum += (tmp * tmp);
    }
    return std::sqrt(sum);
}

bool matches(datatype *vector, std::vector<datatype *> *dataset, datatype min_dist)
{
    for (auto it = dataset->cbegin(); it != dataset->cend(); it++) {
        datatype dist = euclidean_distance(vector, *it);
        if(dist <= min_dist) {
            return true;
        }
    }
    return false;
}

std::vector<datatype*> *generate_detectors(std::vector<datatype *> *self_dataset, int generation)
{
    std::vector<datatype *> *detectors = new std::vector<datatype *>();
    std::cout << "Generating detectors..." << std::endl;
    datatype *detector = new datatype[config.problem_size];
    int count = 1;
    do {
        random_vector(detector);
        if (!matches(detector, self_dataset, config.min_dist)) {
            if (!matches(detector, detectors, 0.0)) {
                detectors->push_back(detector);
                detector = new datatype[config.problem_size];
            }
            std::cout << count++ << "/" << config.max_detectors << std::endl;
        }
    } while (detectors->size() < config.max_detectors);
    if (detector != *detectors->cend()) {
        delete[] detector;
    }
    return detectors;
}

std::string apply_detectors(std::vector<datatype*> *detectors, std::vector<datatype *> *self_dataset)
{
    std::set<int> *detected = new std::set<int>();
    int trial = 1;
    for (auto it = self_dataset->cbegin(); it != self_dataset->cend(); it++) {
        bool actual = matches(*it, detectors, config.min_dist);
        bool expected = matches(*it, self_dataset, config.min_dist);
        if (actual == expected) {
            detected->insert(trial);
        }
        trial++;
    }
    std::set<int> expected_detected(config.expected_detected.begin(), config.expected_detected.end());
    datatype expected_detected_size = expected_detected.size();
    for (auto it = detected->cbegin(); it != detected->cend(); it++) {
        auto found = expected_detected.find(*it);
        if (found != expected_detected.end()) {
            expected_detected.erase(*it);
        }
    }
    datatype new_expected_detected_size = expected_detected.size();
    std::string results = std::to_string(-(new_expected_detected_size - expected_detected_size) / expected_detected_size);

    expected_detected.clear();
    expected_detected.insert(config.expected_detected.begin(), config.expected_detected.end());
    for (auto it = expected_detected.cbegin(); it != expected_detected.cend(); it++) {
        auto found = detected->find(*it);
        if (found != detected->end()) {
            detected->erase(*it);
        }
    }
    datatype new_detected_size = detected->size();
    results += ", " + std::to_string(new_detected_size / expected_detected_size);

    return results + "\n";
}

void run()
{
    std::string general_results("");

    init_search_space();

    std::vector<datatype*>* self_dataset_for_training = read_dataset(config.trainning_dataset_csv_file);
    std::vector<datatype*>* generate_self_dataset_for_testing = read_dataset(config.testing_dataset_csv_file);

    for (int proof = 0; proof < config.amount_of_proofs; proof++) {
        std::vector<datatype*> *detectors = generate_detectors(self_dataset_for_training, proof + 1);
        general_results.append(apply_detectors(detectors, generate_self_dataset_for_testing));
    }

    std::cout << "Detectors: " << config.max_detectors << std::endl;
    std::cout << "Min. distance: " << config.min_dist << std::endl;
    std::cout << "Runs: " << config.amount_of_proofs << std::endl;
    std::cout << general_results << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc == 2) {
        read_config_file(argv[1]);
    } else {
        std::cout << "Usage: " << argv[0] << " <CONFIG-FILE>" << std::endl
                  << std::endl;
        return -1;
    }

    run();

    return 0;
}
