#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
    int max_detectors, min_dist, amount_of_proofs;

    if(argc == 4) {
        max_detectors = std::atoi(argv[1]);
        min_dist = std::atoi(argv[2]);;
        amount_of_proofs = std::atoi(argv[3]);;
    } else if(argc == 1) {
        max_detectors = 160000;
        min_dist = 4;
        amount_of_proofs = 1;
    } else {
        std::cout << "Usage: " << argv[0] << " [MAX-DETECTORS] [MIN-DISTANCE] [AMOUNT-OF-POOFS]" << std::endl << std::endl;
        return -1;
    }
    return 0;
}
