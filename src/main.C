#include <iostream>
#include <fstream>

#include "inputs.h"
#include "run_cfacc.h"

int main(int argc, char * argv[]) {

    cfacc::jobinfo ji;

    if (argc < 2) std::cout << "insufficient input parameters" << std::endl;
    else if (argc == 2) {
        try {
            get_input_data(argv[1],ji);
            run_cfacc(ji, std::cout);
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "unrecognized exception" << std::endl;
        }
    }
    else if (argc == 3) {
        try {
            get_input_data(argv[1],ji);
            std::ofstream fout;
            fout.open(argv[2]);
            run_cfacc(ji, fout);
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "unrecognized exception" << std::endl;
        }
    }
    else {
        std::cout << "too many input parameters" << std::endl;
    }
}
