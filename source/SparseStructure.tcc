//#include "./SparseStructure.hpp"

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
SparseStructure<Key, Element, KeyComparator, Allocator>::
SparseStructure(const Allocator &allocator, KeyComparator key_comparator) :
        _data(key_comparator, allocator) {}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
SparseStructure<Key, Element, KeyComparator, Allocator>::
SparseStructure(const SparseStructure &other) : _data(other._data) {}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
SparseStructure<Key, Element, KeyComparator, Allocator>::
SparseStructure(SparseStructure &&other) noexcept : _data(std::move(other._data)) {}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
SparseStructure<Key, Element, KeyComparator, Allocator>::
SparseStructure(const std::initializer_list<value_type> &data, const Allocator &allocator,
                KeyComparator key_comparator) : SparseStructure(allocator, key_comparator) {
    for (const auto &[key, value] : data) {
        if (value != element_type())
            this->_data.insert({key, value});
    }
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
SparseStructure<Key, Element, KeyComparator, Allocator>::
SparseStructure(std::initializer_list<value_type> &&data, const Allocator &allocator,
                KeyComparator key_comparator) : SparseStructure(data, allocator, key_comparator) {}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
template<typename ForwardIterator>
SparseStructure<Key, Element, KeyComparator, Allocator>::
SparseStructure(ForwardIterator begin, ForwardIterator end, const Allocator &allocator,
                KeyComparator key_comparator) : SparseStructure(allocator, key_comparator) {
    for (auto iter = begin; iter != end; ++iter) {
        if (iter->second != element_type())
            this->_data.insert({iter->first, iter->second});
    }
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
typename SparseStructure<Key, Element, KeyComparator, Allocator>::key_type
SparseStructure<Key, Element, KeyComparator, Allocator>::dims() const noexcept {
    if (this->empty())
        return 0;
    return this->_data.rbegin()->first + 1;
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
void
SparseStructure<Key, Element, KeyComparator, Allocator>::
add(const key_type &key, const element_type &element) {
    if (element != element_type())
        this->_data.insert({key, element});
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
void
SparseStructure<Key, Element, KeyComparator, Allocator>::
remove(const key_type &key) {
    this->_data.erase(key);
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
typename SparseStructure<Key, Element, KeyComparator, Allocator>::iterator
SparseStructure<Key, Element, KeyComparator, Allocator>::
find(const key_type &key) {
    return iterator(this->_data.find(key));
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
void
SparseStructure<Key, Element, KeyComparator, Allocator>::
clear() {
    this->_data.clear();
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
typename SparseStructure<Key, Element, KeyComparator, Allocator>::element_type
SparseStructure<Key, Element, KeyComparator, Allocator>::sum() const {
    auto result = element_type();
    for (auto &[key, value]: *this)
        result += value;
    return result;
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
template<typename Function>
void SparseStructure<Key, Element, KeyComparator, Allocator>::apply(Function function) {
    for (auto &[key, value]: *this)
        value = function(value);
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
template<typename Function>
SparseStructure<Key, Element, KeyComparator, Allocator>
SparseStructure<Key, Element, KeyComparator, Allocator>::
sparse_intersection(const SparseStructure &other, Function function) const {
    auto this_iter = this->cbegin();
    auto other_iter = other.cbegin();
    auto key_comparator = this->key_compare();
    SparseStructure result;

    while (this_iter != this->cend() and other_iter != other.cend()) {
        if (key_comparator(this_iter->first, other_iter->first))
            ++this_iter;
        else if (key_comparator(other_iter->first, this_iter->first))
            ++other_iter;
        else {
            result.add(this_iter->first, function(this_iter++->second, other_iter++->second));
        }
    }
    return result;
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
template<typename Function>
SparseStructure<Key, Element, KeyComparator, Allocator>
SparseStructure<Key, Element, KeyComparator, Allocator>::
sparse_union(const SparseStructure &other, Function function) const {
    auto this_iter = this->cbegin();
    auto other_iter = other.cbegin();
    auto key_comparator = this->key_compare();
    auto null = element_type();
    SparseStructure result;

    while (this_iter != this->cend() and other_iter != other.cend()) {
        if (key_comparator(this_iter->first, other_iter->first))
            result.add(this_iter->first, function(this_iter++->second, null));
        else if (key_comparator(other_iter->first, this_iter->first))
            result.add(other_iter->first, function(null, other_iter++->second));
        else
            result.add(this_iter->first, function(this_iter++->second, other_iter++->second));
    }

    while (this_iter != this->cend())
        result.add(this_iter->first, function(this_iter++->second, null));

    while (other_iter != other.cend())
        result.add(other_iter->first, function(null, other_iter++->second));

    return result;
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
template<typename Function>
SparseStructure<Key, Element, KeyComparator, Allocator>
SparseStructure<Key, Element, KeyComparator, Allocator>::
sparse_difference(const SparseStructure &other, Function function) const {
    auto this_iter = this->cbegin();
    auto other_iter = other.cbegin();
    auto key_comparator = this->key_compare();
    auto null = element_type();
    SparseStructure result;

    while (this_iter != this->cend() and other_iter != other.cend()) {
        if (key_comparator(this_iter->first, other_iter->first))
            result.add(this_iter->first, function(this_iter++->second, null));
        else if (key_comparator(other_iter->first, this_iter->first))
            ++other_iter;
        else {
            ++this_iter;
            ++other_iter;
        }
    }

    while (this_iter != this->cend())
        result.add(this_iter->first, function(this_iter++->second, null));

    return result;
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
template<typename Function>
SparseStructure<Key, Element, KeyComparator, Allocator>
SparseStructure<Key, Element, KeyComparator, Allocator>::
sparse_symmetric_difference(const SparseStructure &other, Function function) const {
    auto this_iter = this->cbegin();
    auto other_iter = other.cbegin();
    auto key_comparator = this->key_compare();
    auto null = element_type();
    SparseStructure result;

    while (this_iter != this->cend() and other_iter != other.cend()) {
        if (key_comparator(this_iter->first, other_iter->first))
            result.add(this_iter->first, function(this_iter++->second, null));
        else if (key_comparator(other_iter->first, this_iter->first))
            result.add(other_iter->first, function(null, other_iter++->second));
        else {
            ++this_iter;
            ++other_iter;
        }
    }

    while (this_iter != this->cend())
        result.add(this_iter->first, function(this_iter++->second, null));

    while (other_iter != other.cend())
        result.add(other_iter->first, function(null, other_iter++->second));

    return result;
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
template<typename Function>
typename SparseStructure<Key, Element, KeyComparator, Allocator>::element_type
SparseStructure<Key, Element, KeyComparator, Allocator>::apply_sum(Function function) const {
    auto result = element_type();
    for (const auto &[key, value]: *this)
        result += function(value);
    return result;
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
template<typename Function>
typename SparseStructure<Key, Element, KeyComparator, Allocator>::element_type
SparseStructure<Key, Element, KeyComparator, Allocator>::
sparse_intersection_sum(const SparseStructure &other, Function function) const {
    auto this_iter = this->cbegin();
    auto other_iter = other.cbegin();
    auto key_comparator = this->key_compare();
    auto result = element_type();

    while (this_iter != this->cend() and other_iter != other.cend()) {
        if (key_comparator(this_iter->first, other_iter->first))
            ++this_iter;
        else if (key_comparator(other_iter->first, this_iter->first))
            ++other_iter;
        else
            result += function(this_iter++->second, other_iter++->second);
    }
    return result;
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
template<typename Function>
typename SparseStructure<Key, Element, KeyComparator, Allocator>::element_type
SparseStructure<Key, Element, KeyComparator, Allocator>::
sparse_union_sum(const SparseStructure &other, Function function) const {
    auto this_iter = this->cbegin();
    auto other_iter = other.cbegin();
    auto key_comparator = this->key_compare();
    auto null = element_type();
    auto result = element_type();

    while (this_iter != this->cend() and other_iter != other.cend()) {
        if (key_comparator(this_iter->first, other_iter->first))
            result += function(this_iter++->second, null);
        else if (key_comparator(other_iter->first, this_iter->first))
            result += function(null, other_iter++->second);
        else
            result += function(this_iter++->second, other_iter++->second);
    }

    while (this_iter != this->cend())
        result += function(this_iter++->second, null);

    while (other_iter != other.cend())
        result += function(null, other_iter++->second);

    return result;
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
template<typename Function>
typename SparseStructure<Key, Element, KeyComparator, Allocator>::element_type
SparseStructure<Key, Element, KeyComparator, Allocator>::
sparse_difference_sum(const SparseStructure &other, Function function) const {
    auto this_iter = this->cbegin();
    auto other_iter = other.cbegin();
    auto key_comparator = this->key_compare();
    auto null = element_type();
    auto result = element_type();

    while (this_iter != this->cend() and other_iter != other.cend()) {
        if (key_comparator(this_iter->first, other_iter->first))
            result += function(this_iter++->second, null);
        else if (key_comparator(other_iter->first, this_iter->first))
            ++other_iter;
        else {
            ++this_iter;
            ++other_iter;
        }
    }

    while (this_iter != this->cend())
        result += function(this_iter++->second, null);

    return result;
}

template<
        typename Key,
        typename Element,
        typename KeyComparator,
        typename Allocator
>
template<typename Function>
typename SparseStructure<Key, Element, KeyComparator, Allocator>::element_type
SparseStructure<Key, Element, KeyComparator, Allocator>::
sparse_symmetric_difference_sum(const SparseStructure &other, Function function) const {
    auto this_iter = this->cbegin();
    auto other_iter = other.cbegin();
    auto key_comparator = this->key_compare();
    auto null = element_type();
    auto result = element_type();

    while (this_iter != this->cend() and other_iter != other.cend()) {
        if (key_comparator(this_iter->first, other_iter->first))
            result += function(this_iter++->second, null);
        else if (key_comparator(other_iter->first, this_iter->first))
            result += function(null, other_iter++->second);
        else {
            ++this_iter;
            ++other_iter;
        }
    }

    while (this_iter != this->cend())
        result += function(this_iter++->second, null);

    while (other_iter != other.cend())
        result += function(null, other_iter++->second);

    return result;
}