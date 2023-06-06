#ifndef NUM_SPARSE_SPARSE_SPARSESTRUCTURE_HPP
#define NUM_SPARSE_SPARSE_SPARSESTRUCTURE_HPP

#include <map>

template<
        typename Key,
        typename Element,
        typename KeyComparator = std::less<Key>,
        typename Allocator = std::allocator<std::pair<Key, Element>>
>
class SparseStructure {
private:
    typedef typename std::map<Key, Element, KeyComparator, Allocator> _impl;

public:
    using key_type = typename _impl::key_type;
    using element_type = typename _impl::mapped_type;
    using key_compare_type = typename _impl::key_compare;
    using allocator_type = typename _impl::allocator_type;

    using value_type = typename _impl::value_type;
    using reference = typename _impl::reference;
    using const_reference = typename _impl::const_reference;
    using pointer = typename _impl::pointer;
    using const_pointer = typename _impl::const_pointer;

    using size_type = typename _impl::size_type;
    using difference_type = typename _impl::difference_type;

    using iterator = typename _impl::iterator;
    using reverse_iterator = typename _impl::reverse_iterator;
    using const_iterator = typename _impl::const_iterator;
    using const_reverse_iterator = typename _impl::const_reverse_iterator;

public:
    explicit SparseStructure(const Allocator &allocator = Allocator(),
                             KeyComparator key_comparator = KeyComparator());

    SparseStructure(const SparseStructure &other);

    SparseStructure(SparseStructure &&other) noexcept;

    SparseStructure(const std::initializer_list<value_type> &data,
                    const Allocator &allocator = Allocator(),
                    KeyComparator key_comparator = KeyComparator());

    SparseStructure(std::initializer_list<value_type> &&data,
                    const Allocator &allocator = Allocator(),
                    KeyComparator key_comparator = KeyComparator());

    template<typename ForwardIterator>
    SparseStructure(ForwardIterator begin, ForwardIterator end,
                    const Allocator &allocator = Allocator(),
                    KeyComparator key_comparator = KeyComparator());

    ~SparseStructure() = default;

    SparseStructure &operator=(const SparseStructure &other) = default;

    SparseStructure &operator=(SparseStructure &&other) noexcept = default;

    [[nodiscard]] bool empty() const noexcept { return this->_data.empty(); }

    [[nodiscard]] size_type size() const noexcept { return this->_data.size(); }

    [[nodiscard]] key_type dims() const noexcept;

    [[nodiscard]] size_type num_zeros() const noexcept { return {this->dims() - this->size()}; }

    void add(const key_type &key, const element_type &element);

    void add(key_type &&key, element_type &&element) { this->add(key, element); }

    void add(const value_type &value) { this->add(value.first, value.second); }

    void add(value_type &&value) { this->add(value); }

    void remove(const key_type &key);

    void remove(key_type &&key) { this->remove(key); }

    iterator find(const key_type &key);

    iterator find(key_type &&key) { return this->at(key); }

    void clear();

    iterator begin() { return this->_data.begin(); }

    iterator end() { return this->_data.end(); }

    reverse_iterator rbegin() { return this->begin(); }

    reverse_iterator rend() { return this->end(); }

    const_iterator cbegin() const { return this->_data.begin(); }

    const_iterator cend() const { return this->_data.end(); }

    const_reverse_iterator crbegin() const { return this->cbegin(); }

    const_reverse_iterator crend() const { return this->cend(); }

    allocator_type allocator() const { return this->_data.get_allocator(); }

    key_compare_type key_compare() const { return this->_data.key_comp(); }

    element_type sum() const;

    bool operator==(const SparseStructure &other) const { return this->_data == other._data; }

    bool operator==(const SparseStructure &&other) const { return this->_data == other._data; }

    bool operator!=(const SparseStructure &other) const { return this->_data != other._data; }

    bool operator!=(const SparseStructure &&other) const { return this->_data != other._data; }

    template<typename Function>
    void apply(Function function);

    template<typename Function>
    SparseStructure sparse_intersection(const SparseStructure &other, Function function) const;

    template<typename Function>
    SparseStructure sparse_union(const SparseStructure &other, Function function) const;

    template<typename Function>
    SparseStructure sparse_difference(const SparseStructure &other, Function function) const;

    template<typename Function>
    SparseStructure sparse_symmetric_difference(const SparseStructure &other, Function function) const;

    template<typename Function>
    element_type apply_sum(Function function) const;

    template<typename Function>
    element_type sparse_intersection_sum(const SparseStructure &other, Function function) const;

    template<typename Function>
    element_type sparse_union_sum(const SparseStructure &other, Function function) const;

    template<typename Function>
    element_type sparse_difference_sum(const SparseStructure &other, Function function) const;

    template<typename Function>
    element_type sparse_symmetric_difference_sum(const SparseStructure &other, Function function) const;

private:
    _impl _data;
};

#include "./SparseStructure.tcc"

#endif //NUM_SPARSE_SPARSE_SPARSESTRUCTURE_HPP
