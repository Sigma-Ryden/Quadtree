#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random> // rand, srand
#include <ctime> // time

#include <Detail/Meta.hpp>

class DefaultGenerator
{
public:
    using size_type = std::size_t;
    using Generator = int (*)();

public:
    DefaultGenerator() noexcept
    {
        std::srand(DefaultGenerator::seed());
    }

    DefaultGenerator(size_type seed) noexcept { std::srand(seed); }

    void seed(size_type seed) noexcept { std::srand(seed); }

    int operator() () noexcept { return std::rand(); }

    static std::size_t seed() noexcept
    {
        return static_cast<std::size_t>(std::time(nullptr));
    }

    static constexpr int min() noexcept { return 0; }
    static constexpr int max() noexcept { return RAND_MAX; }
};

template <class T, typename enable = void>
class Random;

template <class T>
class Random<T, meta::when<std::is_integral<T>::value>>
{
public:
    using integral_type = T;
    using size_type = std::size_t;

private:
    DefaultGenerator gen;

public:
    Random() noexcept : gen(DefaultGenerator::seed()) {}
    Random(size_type seed) noexcept : gen(seed) {}

    void seed(size_type seed) noexcept { gen.seed(seed); }

    integral_type operator() () noexcept
    {
        return static_cast<integral_type>(gen());
    }

    integral_type operator() (integral_type min, integral_type max) noexcept
    {
        return (*this)() % (max - min + 1) + min;
    }
};

template <class T>
class Random<T, meta::when<std::is_floating_point<T>::value>>
{
public:
    using floating_type = T;
    using size_type = std::size_t;

private:
    DefaultGenerator gen;

public:
    Random() noexcept : gen(DefaultGenerator::seed()) {}
    Random(size_type seed) noexcept : gen(seed) {}

    void seed(size_type seed) noexcept { gen.seed(seed); }

    floating_type operator() () noexcept
    {
        return static_cast<floating_type>(gen()) / static_cast<floating_type>(gen.max());
    }

    floating_type operator() (floating_type min, floating_type max) noexcept
    {
        return (max - min) * (*this)() + min;
    }
};

#endif // RANDOM_HPP
