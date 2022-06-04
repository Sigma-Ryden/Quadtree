#ifndef DETAIL_META_HPP
#define DETAIL_META_HPP

#include <type_traits> // enable_if, true_type, false_type

namespace meta
{

template <bool condition, typename T = void>
using when = typename std::enable_if<condition, T>::type;

template <bool condition>
using require = when<condition, int>;

template <class F, typename... Args>
struct is_callable
{
private:
    template <class> static std::false_type check(...);

    template <class U> static auto check(U* p) ->
    decltype((*p)(std::declval<Args>()...), std::true_type{});

public:
    static constexpr bool value = decltype(check<F>(nullptr))::value;
};

}

#endif // DETAIL_META_HPP
