#ifndef PYSPARSE_PYSPARSEMATRIX_HPP
#define PYSPARSE_PYSPARSEMATRIX_HPP

#include "../source/SparseMatrix.hpp"
#include "./PyShape.hpp"
#include "./PyView.hpp"

#include <memory>

template<typename Iterator>
class PySparseMatrixIterator {
private:
    using value_type = typename Iterator::value_type;

public:
    PySparseMatrixIterator(Iterator begin, Iterator end) : _iter(begin), _end(end) {}

    PySparseMatrixIterator(const PySparseMatrixIterator &other) = default;

    PySparseMatrixIterator(PySparseMatrixIterator &&other) = default;

    ~PySparseMatrixIterator() = default;

    PySparseMatrixIterator &operator=(const PySparseMatrixIterator &other) = default;

    PySparseMatrixIterator &operator=(PySparseMatrixIterator &&other) = default;

    value_type &__next__() {
        if (this->_iter == this->_end)
            throw pybind11::stop_iteration();
        return *(this->_iter++);
    }

private:
    Iterator _iter, _end;
};

template<
        typename Index,
        typename Element,
        typename IndexComparator = std::less<Index>,
        typename Allocator = std::allocator<std::pair<Index, Element>>
>
class PySparseMatrix {
private:
    typedef SparseMatrix<Index, Element, IndexComparator, Allocator> _impl;
    typedef std::shared_ptr<_impl> _impl_ptr;

public:
    using shape_type = PyShape<typename _impl::shape_type>;
    using view_type = PyView<typename _impl::element_view_type::iterator>;

public:
    using _sparse_matrix_vector_view_type = typename _impl::_sparse_matrix_vector_view_type;
    using _raw_matrix_on_vector_type = typename _impl::_raw_matrix_on_vector_type;
    using _raw_matrix_on_map_type = typename _impl::_raw_matrix_on_map_type;
    using element_type = typename _impl::element_type;
    using size_type = typename _impl::size_type;

    typedef PySparseMatrixIterator<typename _impl::iterator> iterator;

private:
    PySparseMatrix(_impl &&implementation) : _ptr(new _impl(std::move(implementation))) {}

public:
    PySparseMatrix(const _raw_matrix_on_vector_type &data) : _ptr(new _impl(data)) {}

    PySparseMatrix(const _raw_matrix_on_map_type &data) : _ptr(new _impl(data)) {}

    PySparseMatrix(const PySparseMatrix &other) = default;

    PySparseMatrix(PySparseMatrix &&other) = default;

    ~PySparseMatrix() = default;

    PySparseMatrix &operator=(const PySparseMatrix &other) = default;

    PySparseMatrix &operator=(PySparseMatrix &&other) = default;

    _sparse_matrix_vector_view_type to_list() const {
        return this->_ptr->to_vector();
    }

    _raw_matrix_on_map_type to_dict() const {
        return this->_ptr->to_map();
    }

    PySparseMatrix __add__(const PySparseMatrix &other) const {
        return {this->_ptr->add(*other._ptr)};
    }

    PySparseMatrix __sub__(const PySparseMatrix &other) const {
        return {this->_ptr->subtract(*other._ptr)};
    }

    PySparseMatrix __mul__element(const element_type &element) const {
        return {this->_ptr->multiply(element)};
    }

    PySparseMatrix __mul__matrix(const PySparseMatrix &other) const {
        return {this->_ptr->multiply(*other._ptr)};
    }

    PySparseMatrix __div__element(const element_type &element) const {
        return {this->_ptr->divide(element)};
    }

    PySparseMatrix __div__matrix(const PySparseMatrix &other) const {
        return {this->_ptr->divide(*other._ptr)};
    }

    PySparseMatrix __matmul__(const PySparseMatrix &other) const {
        return {this->_ptr->matmul(*other._ptr)};
    }

    PySparseMatrix transpose() const {
        return {this->_ptr->transpose()};
    }

    shape_type shape() const { return shape_type(this->_ptr->shape()); }

    view_type __getitem__(size_type index) const {
        return {this->_ptr->at(index)};
    }

    iterator __iter__() {
        return {this->_ptr->begin(), this->_ptr->end()};
    }

private:
    _impl_ptr _ptr;
};


#endif //PYSPARSE_PYSPARSEMATRIX_HPP
