#include <bits/stdc++.h>
#include <pybind11/pybind11.h>

#include "./python_objects/PySparseMatrix.hpp"

typedef PySparseMatrix<std::size_t, long double> SpM;

int main() {
    typename SpM::_raw_matrix_on_map_type data = {
            {0, {{0, 1}, {1, 2}}},
            {1, {{0, 3}, {1, 4}}}
    };

    SpM a(data);
    SpM b(data);


    auto result = a.__matmul__(b);
    auto transposed = result.transpose();
    auto add = a.__add__(b);
    auto subtract = a.__sub__(b);
    auto mult_element = a.__mul__element(1);
    auto mult_matrix = a.__mul__matrix(b);
    auto div_element = a.__div__element(2);
    auto div_matrix = a.__div__matrix(b);
    auto result_shape = result.shape();
    auto result_view = result.__getitem__(0);
    auto result_view_is_value = result_view.is_value();
    auto result_view_item = result_view.__getitem__(0);
    auto result_view_item_value = result_view_item.value();
    auto result_vector = result.to_list();
    auto result_map = result.to_dict();
    auto result_iter = result.__iter__();

    auto shape_iter = result_shape.__iter__();

    while (true) {
        auto value = result_iter.__next__();
    }

    return 0;
}