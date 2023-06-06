#ifndef PYSPARSE_SHAPE_HPP
#define PYSPARSE_SHAPE_HPP

#include <vector>

template<
        typename ShapeType
>
class Shape {
public:
    typedef ShapeType value_type;
    typedef std::size_t size_type;

private:
    typedef std::vector<value_type> _impl;

public:
    using iterator = typename _impl::iterator;
    using const_iterator = typename _impl::const_iterator;
    using reverse_iterator = typename _impl::reverse_iterator;
    using const_reverse_iterator = typename _impl::const_reverse_iterator;

public:
    Shape() = default;

    Shape(const _impl &shapes) : _shapes(shapes) {}

    Shape(_impl &&shapes) : _shapes(std::move(shapes)) {}

    Shape(const Shape &other) = default;

    Shape(Shape &&other) = default;

    Shape &operator=(const Shape &other) = default;

    Shape &operator=(Shape &&other) = default;

    value_type at(const size_type &index) const { return this->_shapes.at(index); }

    value_type at(size_type &&index) const { return this->_shapes.at(index); }

    bool operator==(const Shape &other) const { return this->_shapes == other._shapes; }

    bool operator==(Shape &&other) const { return this->_shapes == other._shapes; }

    bool operator!=(const Shape &other) const { return this->_shapes != other._shapes; }

    bool operator!=(Shape &&other) const { return this->_shapes != other._shapes; }

    void transpose(size_type a = 0, size_type b = 1);

    size_type size() const { return this->_shapes.size(); }

    bool is_null() const { return this->_shapes.empty(); }

    iterator begin() { return this->_shapes.begin(); }

    iterator end() { return this->_shapes.end(); }

    const_iterator cbegin() const { return this->_shapes.cbegin(); }

    const_iterator cend() const { return this->_shapes.cend(); }

    reverse_iterator rbegin() { return this->_shapes.rbegin(); }

    reverse_iterator rend() { return this->_shapes.rend(); }

    const_reverse_iterator crbegin() { return this->_shapes.crbegin(); }

    const_reverse_iterator crend() { return this->_shapes.crend(); }

private:
    _impl _shapes;
};

#endif //PYSPARSE_SHAPE_HPP
