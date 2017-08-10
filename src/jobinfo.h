/**
 * Copyright (C) 2017, Alec F. White
 *
 * Licensed under the 2-Clause BSD License. See the LICENSE.txt 
 * file released with this work for additional information.
 **/
#ifndef RACC_JOBINFO_H
#define RACC_JOBINFO_H

#include <vector>
#include <armadillo>

namespace cfacc {

struct jobinfo {

    size_t n; //!< number of data points
    arma::vec lambda; //!< lambda (coupling constant) values
    arma::vec EA; //!< electron affinity values
    arma::vec kappa; //!< kappa (sqrt(EA)) values

    size_t method; //!< method specifier
    std::complex<double> guess; //!< guess energy

    void print(std::ostream &os) {
        os << "Job-info: " << std::endl;
        lambda.print(os, "Coupling constants:");
        kappa.print(os, "Electron affinities:");
    }
};

} // namespace racc

#endif  //  RACC_JOBINFO_H
