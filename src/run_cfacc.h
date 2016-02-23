#ifndef RUN_CFACC_H
#define RUN_CFACC_H

#include "jobinfo.h"

namespace cfacc {

/** \brief run a continued fraction analytic continuation calculation.
    \param[in] jobinfo parameters for current job
    \param[in] os output stream
 **/
void run_cfacc(jobinfo &ji, std::ostream &os);

} // namespace cfacc

#endif  //  RUN_CFACC_H
