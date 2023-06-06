#ifndef PYSPARSE_MATRIX_HPP
#define PYSPARSE_MATRIX_HPP

#include "./SparseMatrixImpl.hpp"
#include <memory>

template<
        typename Index,
        typename Element,
        typename IndexComparator = std::less<Index>,
        typename Allocator = std::allocator<std::pair<Index, Element>>
>
class SparseMatrix {
private:
    typedef SparseMatrixImpl<Index, Element, IndexComparator, Allocator> _impl;

public:
    using index_type = typename _impl::index_type;
    using element_type = typename _impl::element_type;
    using index_compare = typename _impl::index_compare;
    using allocator_type = typename _impl::allocator_type;
    using element_view_type = typename _impl::element_view_type;
    using size_type = typename _impl::size_type;
    using value_type = typename _impl::value_type;
    using shape_type = typename _impl::shape_type;
    using iterator = typename _impl::iterator;
    using const_iterator = typename _impl::const_iterator;
    using reverse_iterator = typename _impl::reverse_iterator;
    using const_reverse_iterator = typename _impl::const_reverse_iterator;

public:
    using _sparse_matrix_vector_view_type = typename _impl::_sparse_matrix_vector_view_type;
    using _raw_matrix_on_vector_type = typename _impl::_raw_matrix_on_vector_type;
    using _raw_matrix_on_map_type = typename _impl::_raw_matrix_on_map_type;

private:
    typedef std::shared_ptr<_impl> _impl_ptr;

private:
    SparseMatrix(_impl_ptr base, _impl_ptr transposed) : _base(base), _transposed() {}

    SparseMatrix(_impl &&base);

public:
    SparseMatrix(const _raw_matrix_on_vector_type &raw);

    SparseMatrix(const _raw_matrix_on_map_type &raw);

    SparseMatrix(const SparseMatrix &other) = default;

    SparseMatrix(SparseMatrix &&other) noexcept = default;

    ~SparseMatrix() = default;

    SparseMatrix &operator=(const SparseMatrix &other) = default;

    SparseMatrix &operator=(SparseMatrix &&other) noexcept = default;

    SparseMatrix add(const SparseMatrix &other) const;

    SparseMatrix add(SparseMatrix &&other) const { return this->add(other); }

    SparseMatrix subtract(const SparseMatrix &other) const;

    SparseMatrix subtract(SparseMatrix &&other) const { return this->subtract(other); }

    SparseMatrix multiply(element_type value) const;

    SparseMatrix multiply(const SparseMatrix &other) const;

    SparseMatrix multiply(SparseMatrix &&other) const { return this->multiply(other); }

    SparseMatrix divide(element_type value) const;

    SparseMatrix divide(const SparseMatrix &other) const;

    SparseMatrix divide(SparseMatrix &&other) const { return this->divide(other); }

    SparseMatrix matmul(const SparseMatrix &other) const;

    SparseMatrix matmul(SparseMatrix &&other) const { return this->matmul(other); }

    SparseMatrix transpose() const;

    element_view_type at(size_type index) const { return this->_base->at(index); }

    const shape_type &shape() const { return this->_base->shape(); }

    _sparse_matrix_vector_view_type to_vector() const { return this->_base->to_vector(); }

    _raw_matrix_on_map_type to_map() const { return this->_base->to_map(); }

    iterator begin() { return this->_base->begin(); }

    iterator end() { return this->_base->end(); }

    const_iterator cbegin() const { return this->_base->cbegin(); }

    const_iterator cend() const { return this->_base->cend(); }

    reverse_iterator rbegin() { return this->_base->rbegin(); }

    reverse_iterator rend() { return this->_base->rend(); }

    const_reverse_iterator crbegin() const { return this->_base->crbegin(); }

    const_reverse_iterator crend() const { return this->_base->crend(); }

private:
    _impl_ptr _base, _transposed;
};

#include "./SparseMatrix.tcc"

#endif //PYSPARSE_MATRIX_HPP
