#ifndef PYSPARSE_SPARSEMATRIXIMPL_HPP
#define PYSPARSE_SPARSEMATRIXIMPL_HPP

#include "./SparseStructure.hpp"
#include "./Shape.hpp"
#include "./View.hpp"

#include <map>

template<
        typename Index,
        typename Element,
        typename IndexComparator = std::less<Index>,
        typename Allocator = std::allocator<std::pair<Index, Element>>
>
class SparseMatrixImpl {
public:
    typedef Index index_type;
    typedef Element element_type;
    typedef IndexComparator index_compare;
    typedef Allocator allocator_type;

private:
    typedef SparseStructure<index_type, element_type, index_compare, allocator_type> _vector;
    typedef typename std::allocator_traits<allocator_type>::template rebind_alloc<std::pair<index_type, _vector>>
            _impl_allocator;
    typedef SparseStructure<index_type, _vector, index_compare, _impl_allocator> _impl;

public:
    typedef View<typename _vector::iterator> element_view_type;
    typedef typename _vector::size_type size_type;
    typedef typename _vector::value_type value_type;
    typedef Shape<size_type> shape_type;

    typedef typename _impl::iterator iterator;
    typedef typename _impl::const_iterator const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef std::vector<std::pair<index_type, std::vector<std::pair<index_type, element_type>>>>
            _raw_matrix_on_vector_type;
    typedef std::map<index_type, std::map<index_type, element_type, index_compare>, index_compare>
            _raw_matrix_on_map_type;
    typedef std::vector<std::vector<element_type>> _sparse_matrix_vector_view_type;

private:
    SparseMatrixImpl(const _impl &implementation);

    SparseMatrixImpl(_impl &&implementation);

public:
    SparseMatrixImpl() = default;

    SparseMatrixImpl(const _raw_matrix_on_vector_type &raw);

    SparseMatrixImpl(const _raw_matrix_on_map_type &raw);

    SparseMatrixImpl(const SparseMatrixImpl &other) = default;

    SparseMatrixImpl(SparseMatrixImpl &&other) noexcept = default;

    ~SparseMatrixImpl() = default;

    SparseMatrixImpl &operator=(const SparseMatrixImpl &other) = default;

    SparseMatrixImpl &operator=(SparseMatrixImpl &&other) noexcept = default;

    SparseMatrixImpl add(const SparseMatrixImpl &other) const;

    SparseMatrixImpl subtract(const SparseMatrixImpl &other) const;

    SparseMatrixImpl multiply(element_type value) const;

    SparseMatrixImpl multiply(const SparseMatrixImpl &other) const;

    SparseMatrixImpl divide(element_type value) const;

    SparseMatrixImpl divide(const SparseMatrixImpl &other) const;

    SparseMatrixImpl matmul(const SparseMatrixImpl &other) const;

    SparseMatrixImpl transpose() const;

    element_view_type at(size_type index);

    const shape_type &shape() const { return this->_shape; }

    _sparse_matrix_vector_view_type to_vector() const;

    _raw_matrix_on_map_type to_map() const;

    iterator begin() { return this->_data.begin(); }

    iterator end() { return this->_data.end(); }

    const_iterator cbegin() const { return this->_data.cbegin(); }

    const_iterator cend() const { return this->_data.cend(); }

    reverse_iterator rbegin() { return this->_data.rbegin(); }

    reverse_iterator rend() { return this->_data.rend(); }

    const_reverse_iterator crbegin() const { return this->_data.crbegin(); }

    const_reverse_iterator crend() const { return this->_data.crend(); }

private:
    void _set_shape();

    void _check_shapes(const SparseMatrixImpl &other) const;

private:
    _impl _data;
    shape_type _shape;

private:
    static auto _add_elements(const element_type &a, const element_type &b) { return a + b; }

    static _vector _add_vectors(const _vector &a, const _vector &b) {
        return a.sparse_union(b, SparseMatrixImpl::_add_elements);
    }

    static auto _subtract_elements(const element_type &a, const element_type &b) { return a - b; }

    static _vector _subtract_vectors(const _vector &a, const _vector &b) {
        return a.sparse_union(b, SparseMatrixImpl::_subtract_elements);
    }

    static auto _multiply_elements(const element_type &a, const element_type &b) { return a * b; }

    static _vector _multiply_vectors(const _vector &a, const _vector &b) {
        return a.sparse_union(b, SparseMatrixImpl::_multiply_elements);
    }

    static auto _divide_elements(const element_type &a, const element_type &b);

    static _vector _divide_vectors(const _vector &a, const _vector &b) {
        return a.sparse_union(b, SparseMatrixImpl::_divide_elements);
    }
};

#include "./SparseMatrixImpl.tcc"

#endif //PYSPARSE_SPARSEMATRIXIMPL_HPP
