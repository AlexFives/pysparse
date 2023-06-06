#include "./SparseMatrixImpl.hpp"

#include <cmath>

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::
SparseMatrixImpl(const _impl &implementation) : _data(implementation) {
    this->_set_shape();
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::
SparseMatrixImpl(_impl &&implementation) : _data(std::move(implementation)) {
    this->_set_shape();
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::
SparseMatrixImpl(const _raw_matrix_on_vector_type &raw) {
    size_type n_columns = size_type();

    for (auto &data_pair: raw) {
        auto &vec_index = data_pair.first;
        auto &vec = data_pair.second;
        _vector data_vector(vec.begin(), vec.end());
        n_columns = std::max(n_columns, data_vector.dims());
        this->_data.add(vec_index, data_vector);
    }

    this->_shape = {{this->_data.dims(), n_columns}};
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::
SparseMatrixImpl(const _raw_matrix_on_map_type &raw) {
    size_type n_columns = size_type();

    for (auto &[vec_index, vec]: raw) {
        _vector data_vector(vec.begin(), vec.end());
        n_columns = std::max(n_columns, data_vector.dims());
        this->_data.add(vec_index, data_vector);
    }

    this->_shape = {{this->_data.dims(), n_columns}};
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::add(const SparseMatrixImpl &other) const {
    this->_check_shapes(other);
    return {this->_data.sparse_union(other._data, SparseMatrixImpl::_add_vectors)};
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::subtract(const SparseMatrixImpl &other) const {
    this->_check_shapes(other);
    return {this->_data.sparse_union(other._data, SparseMatrixImpl::_subtract_vectors)};
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::multiply(element_type value) const {
    if (value == element_type())
        return {};
    auto element_func = [&value](const element_type &element) {
        return value * element;
    };
    auto vector_func = [&element_func](_vector &vec) {
        vec.apply(element_func);
        return vec;
    };
    auto copy = *const_cast<SparseMatrixImpl *>(this);
    copy._data.apply(vector_func);
    return copy;
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::multiply(const SparseMatrixImpl &other) const {
    this->_check_shapes(other);
    return {this->_data.sparse_union(other._data, SparseMatrixImpl::_multiply_vectors)};
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::divide(element_type value) const {
    auto element_func = [&value](const element_type &element) {
        return SparseMatrixImpl::_divide_elements(element, value);
    };
    auto vector_func = [&element_func](_vector &vec) {
        vec.apply(element_func);
        return vec;
    };
    auto copy = *const_cast<SparseMatrixImpl *>(this);
    copy._data.apply(vector_func);
    return copy;
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::divide(const SparseMatrixImpl &other) const {
    this->_check_shapes(other);
    return {this->_data.sparse_union(other._data, SparseMatrixImpl::_divide_vectors)};
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::matmul(const SparseMatrixImpl &other) const {
    _impl result;
    for (auto this_iter = this->cbegin(); this_iter != this->cend(); ++this_iter) {
        auto &this_idx = this_iter->first;
        auto &this_vec = this_iter->second;
        _vector result_vector;
        for (auto other_iter = other.cbegin(); other_iter != other.cend(); ++other_iter) {
            auto &other_idx = other_iter->first;
            auto &other_vec = other_iter->second;
            element_type value = this_vec.sparse_union_sum(other_vec, SparseMatrixImpl::_multiply_elements);
            result_vector.add(other_idx, value);
        }
        result.add(this_idx, result_vector);
    }
    return {std::move(result)};
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::transpose() const {
    _raw_matrix_on_map_type raw_storage;
    for (auto vec_iter = this->cbegin(); vec_iter != this->cend(); ++vec_iter) {
        const auto &vec_idx = vec_iter->first;
        const auto &vec = vec_iter->second;
        for (auto element_iter = vec.cbegin(); element_iter != vec.cend(); ++element_iter) {
            const auto &element_idx = element_iter->first;
            const auto &element = element_iter->second;
            raw_storage[element_idx][vec_idx] = element;
        }
    }
    return SparseMatrixImpl(raw_storage);
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
typename SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::element_view_type
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::at(size_type index) {
    if (index >= this->_shape.at(0)) {
        auto end = this->end();
        return {end->second.end(), end->second.end()};
    }
    auto ptr = this->_data.find(index);
    return element_view_type(ptr->second.begin(), ptr->second.end());
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
typename SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::_sparse_matrix_vector_view_type
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::to_vector() const {
    auto dim_0 = this->_shape.at(0);
    auto dim_1 = this->_shape.at(1);
    _sparse_matrix_vector_view_type result(dim_0, std::vector<element_type>(dim_1, element_type()));
    for (auto iter = this->cbegin(); iter != this->cend(); ++iter) {
        std::vector<element_type> vector_(dim_1, element_type());
        auto &vec = iter->second;
        for (auto vec_iter = vec.cbegin(); vec_iter != vec.cend(); ++vec_iter) {
            vector_[vec_iter->first] = vec_iter->second;
        }
        result[iter->first] = vector_;
    }
    return result;
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
typename SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::_raw_matrix_on_map_type
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::to_map() const {
    _raw_matrix_on_map_type result;
    for (auto iter = this->cbegin(); iter != this->cend(); ++iter) {
        std::map<index_type, element_type> vector_;
        auto &vec = iter->second;
        for (auto vec_iter = vec.cbegin(); vec_iter != vec.cend(); ++vec_iter)
            vector_[vec_iter->first] = vec_iter->second;
        result[iter->first] = vector_;
    }
    return result;
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
void SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::_set_shape() {
    auto n_columns = size_type();
    for (auto &[index, vec]: this->_data)
        n_columns = std::max(n_columns, vec.dims());
    this->_shape = shape_type({this->_data.dims(), n_columns});
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
void
SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::
_check_shapes(const SparseMatrixImpl &other) const {
    if (this->_shape != this->_shape)
        throw std::length_error("Shapes don't match");
}

template<
        typename Index,
        typename Element,
        typename IndexComparator,
        typename Allocator
>
auto SparseMatrixImpl<Index, Element, IndexComparator, Allocator>::
_divide_elements(const element_type &a, const element_type &b) {
    if (b == element_type())
        return element_type(std::nan("nan"));
    return a / b;
}