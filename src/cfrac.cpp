/**
 * Copyright (C) 2017, Alec F. White
 *
 * Licensed under the 2-Clause BSD License. See the LICENSE.txt 
 * file released with this work for additional information.
 **/
#include "cfrac.h"

namespace cfacc {

cfrac::cfrac(
    std::vector<std::complex<double> > &d,
    std::vector<std::complex<double> > &cd) :
    domain(d), n(d.size()) {

    assert(n == cd.size());

    coeffs.resize(n,0.0);
    coeffs[0] = (cd[0] / cd[1] - 1.0) / (d[1] - d[0]);

    for (size_t i = 1; i < n - 1; i++) {
        std::complex<double> t = coeffs[0] * (d[i + 1] - d[0]) *
            cd[i + 1] / (cd[i + 1] - cd[0]);
        for (size_t j = 2; j <= i; j++) {
            std::complex<double> t2 = coeffs[j - 1] * (d[i + 1] - d[j - 1])
                / (1.0 + t);
            t = t2;
        }
        coeffs[i] = (1.0 + t) / (d[i] - d[i + 1]);
    }
    coeffs[n - 1] = cd[0];
}
        
void cfrac::print(std::ostream &os) {
    os << "The coefficients are: " << std::endl;
    for (size_t i = 0; i < n; i++) {
        os << "\t " << coeffs[i] << std::endl;
    }
}
        
std::complex<double> cfrac::compute_value(std::complex<double> in) {
           
    std::complex<double> t = coeffs[n - 2] * (in - domain[n - 2]);
    std::complex<double> f1 = 1.0 / (1.0 + t);
    std::complex<double> f2 = 1.0;

    for (size_t i = 0; i < n - 2; i++) {
        std::complex<double> tempc = coeffs[n - 3 - i];
        std::complex<double> tempx = domain[n - 3 - i];
        t = tempc * (in - tempx) * f1;
        f2 = 1.0 / (1.0 + t);
        f1 = f2;
    }

    return coeffs[n - 1] * f2;
}

std::complex<double> cfrac::compute_analytic_derivative(
    std::complex<double> in) {

    std::complex<double> term = coeffs[n - 2] * (in - domain[n - 2]);
    std::complex<double> toim1 = 1.0 / (1.0 + term);
    std::complex<double> cprime = -coeffs[n - 2] * toim1 * toim1;
    for (int i = n - 3; i >= 0; i--) {
        term = coeffs[i] * (in - domain[i]) * toim1;
        std::complex<double> toim2 = 1.0 / (1.0 + term);
        cprime = -toim2 * toim2 * coeffs[i] * (toim1 + (in - domain[i]) * cprime); 
        toim1 = toim2; 
    }
    return coeffs[n - 1] * cprime; 
}
        
std::complex<double> cfrac::compute_fd_derivative(
    std::complex<double> in, double stepsize) {

    std::complex<double> plus = in + stepsize / 2.0;
    std::complex<double> minus = in - stepsize / 2.0;

    std::complex<double> forward = compute_value(plus);
    std::complex<double> back = compute_value(minus);

    return (forward - back) / stepsize;
}

} // namespace cfrac
