#include "inputs.h"

namespace cfacc {

static const int max_input_size = 100;

void get_input_data(const char * filename, jobinfo &ji) {

    std::ifstream fs(filename, std::ifstream::in);
    if (!fs.good()){
        fs.exceptions(std::ifstream::badbit);
    }
    
    double rtemp, itemp;
    fs >> rtemp;
    fs >> itemp;
    ji.guess = std::complex<double>(rtemp, -itemp / 2.0);

    arma::vec ltemp(max_input_size);
    arma::vec ktemp(max_input_size);
    size_t i = 0;
    while(fs >> ltemp(i) && i < max_input_size) {
        fs >> ktemp(i);
        i++;
    }
    
    ltemp.resize(i);
    ktemp.resize(i);
    ji.lambda = ltemp;
    ji.EA = ktemp;
    ji.kappa = arma::sqrt(ktemp);
    ji.n = i;
}

} // namespace cfacc
