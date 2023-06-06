#ifndef PYSPARSE_EXCEPTIONS_HPP
#define PYSPARSE_EXCEPTIONS_HPP

#include <stdexcept>
#include <pybind11/pytypes.h>

struct ViewCastError : pybind11::value_error {
    ViewCastError() : pybind11::value_error("View object isn't value") {}
};



#endif //PYSPARSE_EXCEPTIONS_HPP
