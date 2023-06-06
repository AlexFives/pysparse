#ifndef PYSPARSE_PYSHAPE_HPP
#define PYSPARSE_PYSHAPE_HPP

#include <memory>

#include "../source/Shape.hpp"
#include "./exceptions.hpp"

template<typename Iterator>
class PyShapeIterator {
public:
    using value_type = typename Iterator::value_type;

public:
    PyShapeIterator(Iterator begin, Iterator end) : _iter(begin), _end(end) {}

    PyShapeIterator(const PyShapeIterator &other) = default;

    PyShapeIterator(PyShapeIterator &&other) = default;

    ~PyShapeIterator() = default;

    PyShapeIterator &operator=(const PyShapeIterator &other) = default;

    PyShapeIterator &operator=(PyShapeIterator &&other) = default;

    const value_type &__next__() {
        if (this->_iter == this->_end)
            throw pybind11::stop_iteration();
        return *(this->_iter++);
    }

private:
    Iterator _iter, _end;
};

template<typename ShapeType>
class PyShape {
private:
    typedef Shape<typename ShapeType::value_type> _impl;
    typedef const _impl *_impl_ptr;

public:
    using value_type = typename _impl::value_type;
    using size_type = typename _impl::size_type;

    typedef PyShapeIterator<typename _impl::const_iterator> iterator;

public:
    PyShape(const _impl &implementation) : _ptr(&implementation) {}

    PyShape(const PyShape &other) = default;

    PyShape(PyShape &&other) = default;

    ~PyShape() = default;

    PyShape &operator=(const PyShape &other) = default;

    PyShape &operator=(PyShape &&other) = default;

    bool __eq__(const PyShape &other) const { return this->_ptr->operator==(*other._ptr); }

    bool __ne__(const PyShape &other) const { return not this->__eq__(other); }

    value_type __getitem__(size_type index) const {
        try {
            return this->_ptr->at(index);
        } catch (std::out_of_range &err) {
            throw pybind11::index_error("Index out of range");
        }
    }

    size_type __len__() const { return this->_ptr->size(); }

    iterator __iter__() const { return {this->_ptr->cbegin(), this->_ptr->cend()}; }


private:
    _impl_ptr _ptr;
};

#endif //PYSPARSE_PYSHAPE_HPP
