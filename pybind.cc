#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "./python_objects/header.hpp"

namespace py = pybind11;

typedef std::size_t index_type;
typedef PySparseMatrix<index_type, int32_t> SpM_int32;
typedef PySparseMatrix<index_type, int64_t> SpM_int64;
typedef PySparseMatrix<index_type, float> SpM_float;
typedef PySparseMatrix<index_type, double> SpM_double;
typedef PySparseMatrix<index_type, long double> SpM_long_double;

template<typename IteratorT>
void make_shape_iterator(py::module_ &handle, const char *name) {
    std::string class_name = std::string(name) + "ShapeIterator";
    py::class_<IteratorT>(handle, class_name.c_str())
            .def("__next__", &IteratorT::__next__);
}

template<typename ShapeT>
void make_shape(py::module_ &handle, const char *name) {
    std::string class_name = std::string(name) + "Shape";
    py::class_<ShapeT>(handle, class_name.c_str())
            .def("__eq__", &ShapeT::__eq__, py::arg("other"))
            .def("__ne__", &ShapeT::__ne__, py::arg("other"))
            .def("__len__", &ShapeT::__len__)
            .def("__getitem__", &ShapeT::__getitem__, py::arg("index"))
            .def("__iter__", &ShapeT::__iter__);
}

template<typename ViewT>
void make_view(py::module_ &handle, const char *name) {
    std::string class_name = std::string(name) + "View";
    py::class_<ViewT>(handle, class_name.c_str())
            .def("is_value", &ViewT::is_value)
            .def("value", &ViewT::value)
            .def("__len__", &ViewT::__len__)
            .def("__getitem__", &ViewT::__getitem__, py::arg("index"));
}

template<typename IteratorT>
void make_sparse_matrix_iterator(py::module_ &handle, const char *name) {
    std::string class_name = std::string(name) + "Iterator";
    py::class_<IteratorT>(handle, class_name.c_str())
            .def("__next__", &IteratorT::__next__);
}

template<typename SpM>
void make_sparse_matrix(py::module_ &handle, const char *name) {
    py::class_<SpM>(handle, name)
            .def(py::init<typename SpM::_raw_matrix_on_vector_type>(), py::arg("data"))
            .def(py::init<typename SpM::_raw_matrix_on_map_type>(), py::arg("data"))
            .def("to_list", &SpM::to_list)
            .def("to_dict", &SpM::to_dict)
            .def("__add__", &SpM::__add__, py::arg("other"))
            .def("__sub__", &SpM::__sub__, py::arg("other"))
            .def("__mul__", &SpM::__mul__element, py::arg("value"))
            .def("__mul__", &SpM::__mul__matrix, py::arg("other"))
            .def("__truediv__", &SpM::__div__element, py::arg("value"))
            .def("__truediv__", &SpM::__div__matrix, py::arg("other"))
            .def("__matmul__", &SpM::__matmul__, py::arg("other"))
            .def("transpose", &SpM::transpose)
            .def("shape", &SpM::shape)
            .def("__getitem__", &SpM::__getitem__, py::arg("index"))
            .def("__iter__", &SpM::__iter__);
}

template<typename SpM>
void make_type(py::module_ &handle, const char *name) {
    using iterator = typename SpM::iterator;
    using shape = typename SpM::shape_type;
    using view = typename SpM::view_type;
    using shape_iterator = typename shape::iterator;

    make_shape_iterator<shape_iterator>(handle, name);
    make_shape<shape>(handle, name);
    make_view<view>(handle, name);
    make_sparse_matrix_iterator<iterator>(handle, name);
    make_sparse_matrix<SpM>(handle, name);
}

PYBIND11_MODULE(pysparse, handle) {
    py::register_exception<ViewCastError>(handle, "ViewCastError");

//    make_type<SpM_int32>(handle, "Int32SparseMatrix");
    make_type<SpM_int64>(handle, "Int64SparseMatrix");
//    make_type<SpM_float>(handle, "FloatSparseMatrix");
//    make_type<SpM_double>(handle, "DoubleSparseMatrix");
//    make_type<SpM_long_double>(handle, "LongDoubleSparseMatrix");
}
