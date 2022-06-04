#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <cstddef> // size_t, ptrdiff_t
#include <vector> // vector

template <typename T>
class Container
{
public:
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;
    using value_type        = T;

    using reference         = T&;
    using const_reference   = const T&;

    using pointer           = T*;
    using const_pointer     = const T*;

    using iterator          = typename std::vector<T>::iterator;
    using const_iterator    = typename std::vector<T>::const_iterator;

private:
    std::vector<T> storage_;

public:
    Container() noexcept;
    Container(size_type size);

    void remove(size_type i);

    void add(const Container<T>& container);

    template <class InIt>
    void add(InIt first, InIt last);

    void add(const T& value);

    void resize(size_type size) { storage_.resize(size); }
    void reserve(size_type capacity) { storage_.reserve(capacity); }

    void clear() noexcept;

    bool empty() const noexcept { return storage_.empty(); }

    size_type size() const noexcept { return storage_.size(); }
    size_type capacity() const noexcept { return storage_.capacity(); }

    reference operator[] (size_type i) noexcept
    { return storage_[i]; }

    const_reference operator[] (size_type i) const noexcept
    { return storage_[i]; }

    iterator begin() noexcept { return storage_.begin(); }
    iterator end() noexcept { return storage_.end(); }

    const_iterator begin() const noexcept { return storage_.begin(); }
    const_iterator end() const noexcept { return storage_.end(); }

    reference front() noexcept { return storage_.front(); }
    reference back() noexcept { return storage_.back(); }

    const_reference front() const noexcept { return storage_.front(); }
    const_reference back() const noexcept { return storage_.back(); }

    pointer data() noexcept { return storage_.data(); }
    const_pointer data() const noexcept { return storage_.data(); }
};

template <typename T>
Container<T>::Container() noexcept
    : storage_()
{
}

template <typename T>
Container<T>::Container(size_type size)
    : storage_(size)
{
}

template <typename T>
void Container<T>::remove(size_type i)
{
    storage_.erase(storage_.begin() + i);
}

template <typename T>
template <class InIt>
void Container<T>::add(InIt first, InIt last)
{
    storage_.reserve(storage_.size() + (last - first));

    while (first != last)
        storage_.push_back(*first++);
}

template <typename T>
void Container<T>::add(const Container<T>& container)
{
    add(container.begin(), container.end());
}

template <typename T>
void Container<T>::add(const T& value)
{
    storage_.push_back(value);
}

template <typename T>
void Container<T>::clear() noexcept
{
    storage_.clear();
}

#endif // CONTAINER_HPP
