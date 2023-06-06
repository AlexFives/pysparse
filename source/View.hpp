#ifndef PYSPARSE_VIEW_HPP
#define PYSPARSE_VIEW_HPP

#include <iterator>

template<typename Iterator>
class View {
private:
    typedef typename std::iterator_traits<Iterator> _traits_type;

public:

    typedef typename _traits_type::value_type value_type;
    typedef typename _traits_type::difference_type size_type;
    typedef Iterator iterator;

public:
    View(Iterator begin = nullptr, Iterator end = nullptr) :
            _begin(begin), _end(end), _size(std::distance(begin, end)) {}

    View(const View &other) = default;

    View(View &&other) = default;

    View &operator=(const View &other) = default;

    View &operator=(View &&other) = default;

    View at(size_type index) const;

    value_type value() const;

    operator value_type() const { return this->value(); }

    size_type size() const { return this->_size; }

    bool is_value() const { return this->_size <= 1; }

private:
    Iterator _begin, _end;
    size_type _size;

    static constexpr value_type _SENTINEL = value_type();
};

#include "./View.tcc"

#endif //PYSPARSE_VIEW_HPP
