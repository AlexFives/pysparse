#ifndef PYSPARSE_PYVIEW_HPP
#define PYSPARSE_PYVIEW_HPP

#include <memory>

#include "../source/View.hpp"
#include "./exceptions.hpp"


template<typename Iterator>
class PyView {
private:
    typedef View<Iterator> _impl;
    typedef std::shared_ptr<_impl> _impl_ptr;

public:
    using value_type = typename _impl::value_type;
    using size_type = typename _impl::size_type;

public:
    PyView(_impl &&view) : _ptr(new _impl(view)) {}

    PyView(const PyView &other) = default;

    PyView(PyView &&other) = default;

    ~PyView() = default;

    PyView &operator=(const PyView &other) = default;

    PyView &operator=(PyView &&other) = default;

    bool is_value() const { return this->_ptr->is_value(); }

    value_type value() const {
        try {
            return this->_ptr->value();
        } catch (std::runtime_error &err) {
            throw ViewCastError();
        }
    }

    size_type __len__() const { return this->_ptr->size(); }

    PyView __getitem__(size_type index) const {
        return {this->_ptr->at(index)};
    }

private:
    _impl_ptr _ptr;
};

#endif //PYSPARSE_PYVIEW_HPP
