#ifndef DETAIL_META_HPP
#define DETAIL_META_HPP

#include <type_traits> // enable_if

namespace meta
{

template <bool condition>
using when = typename std::enable_if<condition>::type;

}

#endif // DETAIL_META_HPP
