#include <iomanip>
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
    cfrac cf(k, l);
    os << "Reproduce input data: " << std::endl;
    for (size_t i = 0; i < l.size(); i++) {
        os << "  " << l[i] << "   " << cf.compute_value(k[i]) << std::endl;
    }

    os << "Guess: " << std::real(ji.guess) << " -  i * " << -std::imag(ji.guess) << std::endl;

    os << " Performing Newton's method to find zeros " << std::endl;
    os << " ++++++++++++++++++++++++++++++++++++++++ " << std::endl;
    os << " Iteration #         function value       " << std::endl;
    os << " ---------------------------------------- " << std::endl;

    size_t max_iter = 100;
    double conv = 1e-6;

    std::complex<double> x = std::complex<double>(0.0,-1.0) * std::sqrt(ji.guess);
    os << " x: " << x << std::endl;
    size_t i = 0;
    for (i = 0; i < max_iter; i++) {
        std::complex<double> f = cf.compute_value(x);
        std::complex<double> fprime = cf.compute_analytic_derivative(x);
        std::complex<double> step = - f / fprime;
        std::complex<double> xnew = x + step;
        std::complex<double> newf = cf.compute_value(xnew);
        //if (std::abs(newf) > std::abs(f)) {
        //    xnew = x + step / 2.0;
        //    newf = cf.compute_value(xnew);
        //    os << "Warning: stepsize halved!" << std::endl;
        //}
        x = xnew;
        os << "  " << i + 1 << "      " << newf << "    " << std::abs(newf) << "   " << x << std::endl;
        if (std::abs(newf) < conv) break;
    }
    if (i == max_iter) {
        os << "  Newton's method failed to converge" << std::endl;
    }
    else {
        os << "  Newton's method converged" << std::endl;
    }

    double a2 = -1.0 * std::real(x);
    double b = -1.0 * std::imag(x);
    double pos = b*b - a2*a2;
    double wid = 4.0 * a2 * b;
    
    os << x << std::endl;
    os << " Resonance position:  " << std::fixed << std::setprecision(14) << pos << std::endl;
    os << " Resonance width:     " << wid << std::endl;
    print_end_banner(os);
}

} // namespace cfacc
