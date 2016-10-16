//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_TYPE_ID_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_TYPE_ID_HPP_INCLUDED

#include <boost/core/demangle.hpp>
#include <type_traits>

namespace boost { namespace simd { namespace detail
{
  template<typename T> inline std::string type_id()
  {
    typedef std::is_const<typename std::remove_reference<T>::type>  const_t;
    typedef std::is_lvalue_reference<T>                             lref_t;
    typedef std::is_rvalue_reference<T>                             rref_t;
    std::string s = boost::core::demangle(typeid(T).name());
    s += const_t::value ? " const"  : "";
    s += lref_t::value   ? "&"      : "";
    s += rref_t::value   ? "&&"     : "";
    return s;
  }
  template<typename T> inline std::string type_id( const T& )
  {
    return type_id<T>();
  }

} } }

#endif
