//==================================================================================================
/*!
  @file

  @copyright 2012-2015 NumScale SAS
  @copyright 2015 J.T.Lapreste

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IDIVCEIL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IDIVCEIL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-arithmetic

    Computes the integer conversion of the ceil of the division of its parameters.

    @par semantic:
    For any given value @c x,  @c y of type @c T:

    @code
    T r = idivceil(x, y);
    @endcode

    The code is similar to:

    @code
    as_integer<T> r = toints(ceil(x/y));
    @endcode

    If y is null, it returns Valmax (resp. Valmin)
    if x is positive (resp. negative) and 0 if x is null.

    @see funcref{toints, funcref{ceil

    @return      a value of the integral type associated to the input.


**/
  template<typename T> auto idivceil(T const& x) {}

  namespace functional
  {
    /*!
      @ingroup group-arithmetic

      Function object tied to simd::idivceil

      @see simd::idivceil
    **/
    const boost::dispatch::functor<tag::idivceil_> idivceil = {};
  }
} }
#endif

#include <boost/simd/function/definition/idivceil.hpp>
#include <boost/simd/arch/common/generic/function/idivceil.hpp>
//#include <boost/simd/arch/common/function/simd/idivceil.hpp>

#endif