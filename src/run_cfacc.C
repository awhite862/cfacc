#include "run_cfacc.h"
#include "cfrac.h"

namespace cfacc {

namespace {

void print_start_banner(std::ostream &os) {

    os << " ======================================================= " << std::endl;
    os << "|          Regularized analytic continuation            |" << std::endl;
    os << "|                  calculation manager                  |" << std::endl;
    os << "|                                                       |" << std::endl;
    os << "|                written by Alec White                  |" << std::endl;
    os << " ======================================================= " << std::endl << std::endl;
}

void print_end_banner(std::ostream &os) {

    os << " ======================================================= " << std::endl;
    os << "|          Regularized analytic continuation            |" << std::endl;
    os << "|                calculation completed                  |" << std::endl;
    os << " ======================================================= " << std::endl << std::endl;
}

} // unnamed namespace

void run_cfacc(jobinfo &ji, std::ostream &os) {
    print_start_banner(os);
    ji.print(os);
    std::vector<std::complex<double> > l, k;
    for (size_t i = 0; i < ji.kappa.n_elem; i++) {
        l.push_back(ji.lambda(i));
        k.push_back(ji.kappa(i));
    }
    cfrac cf(l, k);
    os << "Reproduce input data: " << std::endl;
    for (size_t i = 0; i < l.size(); i++) {
        os << "  " << k[i] << "   " << cf.compute_value(l[i]) << std::endl;
    }

    print_end_banner(os);
}

} // namespace cfacc
