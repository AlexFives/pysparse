//#include "./SparseMatrix.hpp"

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrix<Index, Element, IndexComparator, Allocator>::
SparseMatrix(_impl &&base) : _base(new _impl(std::move(base))) {
    this->_transposed = _impl_ptr(new _impl(this->_base->transpose()));
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrix<Index, Element, IndexComparator, Allocator>::
SparseMatrix(const _raw_matrix_on_vector_type &raw) : _base(new _impl(raw)) {
    this->_transposed = _impl_ptr(new _impl(this->_base->transpose()));
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrix<Index, Element, IndexComparator, Allocator>::
SparseMatrix(const _raw_matrix_on_map_type &raw) : _base(new _impl(raw)) {
    this->_transposed = _impl_ptr(new _impl(this->_base->transpose()));
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrix<Index, Element, IndexComparator, Allocator>
SparseMatrix<Index, Element, IndexComparator, Allocator>::
add(const SparseMatrix &other) const {
    return {this->_base->add(*other._base)};
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrix<Index, Element, IndexComparator, Allocator>
SparseMatrix<Index, Element, IndexComparator, Allocator>::
subtract(const SparseMatrix &other) const {
    return {this->_base->subtract(*other._base)};
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrix<Index, Element, IndexComparator, Allocator>
SparseMatrix<Index, Element, IndexComparator, Allocator>::
multiply(element_type value) const {
    return {this->_base->multiply(value)};
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrix<Index, Element, IndexComparator, Allocator>
SparseMatrix<Index, Element, IndexComparator, Allocator>::
multiply(const SparseMatrix &other) const {
    return {this->_base->multiply(*other._base)};
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrix<Index, Element, IndexComparator, Allocator>
SparseMatrix<Index, Element, IndexComparator, Allocator>::
divide(element_type value) const {
    return {this->_base->divide(value)};
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrix<Index, Element, IndexComparator, Allocator>
SparseMatrix<Index, Element, IndexComparator, Allocator>::
divide(const SparseMatrix &other) const {
    return {this->_base->divide(*other._base)};
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrix<Index, Element, IndexComparator, Allocator>
SparseMatrix<Index, Element, IndexComparator, Allocator>::
matmul(const SparseMatrix &other) const {
    return {this->_base->matmul(*other._transposed)};
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrix<Index, Element, IndexComparator, Allocator>
SparseMatrix<Index, Element, IndexComparator, Allocator>::
transpose() const {
    return {this->_transposed, this->_base};
}