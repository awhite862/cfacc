#ifndef CFRAC_H
#define CFRAC_H

#include <cassert>
#include <complex>
#include <vector>
#include <iostream>

namespace cfacc {

/**  \brief a class for creating a continued fraction interpolant of some data
 **/
class cfrac {

    public:
        cfrac(
            std::vector<std::complex<double> > &d,
            std::vector<std::complex<double> > &cd);

        void print(std::ostream &os);

        std::complex<double> compute_value(
            std::complex<double> in);

        std::complex<double> compute_fd_derivative(
            std::complex<double> in, double stepsize = 1e-6);

        std::complex<double> compute_analytic_derivative(
            std::complex<double> in);

    private:
        size_t n;
        std::vector<std::complex<double> > coeffs;
        std::vector<std::complex<double> > domain;

};

} // namespace cfrac

#endif  //  CFRAC_H
