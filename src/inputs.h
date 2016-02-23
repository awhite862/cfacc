#ifndef CFACC_INPUTS_H
#define CFACC_INPUTS_H

#include <src/jobinfo.h>

namespace cfacc {

/** \brief Get raw input data, couplings and EAs, from file.
    \param filename file where inputs are located
    \param ji jobinfo object
 **/
void get_input_data(const char * filename, jobinfo &ji);


} // namespace cfacc

#endif  //  CFACC_INPUTS_H
