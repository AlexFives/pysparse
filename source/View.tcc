//#include "./View.hpp"

template<typename Iterator>
View<Iterator> View<Iterator>::at(size_type index) const {
    if (index >= this->_size)
        return {this->_end, this->_end};
    auto first = std::next(this->_begin, index);
    auto last = std::next(first);
    return {first, last};
}

template<typename Iterator>
typename View<Iterator>::value_type View<Iterator>::value() const {
    if (not this->is_value())
        throw std::runtime_error("This View instance can't be casted to value_type");
    if (this->_size == 0)
        return View::_SENTINEL;
    return *this->_begin;
}
