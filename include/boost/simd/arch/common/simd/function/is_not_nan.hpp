//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS
  @copyright 2016 J.T. Lapreste

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_NOT_NAN_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_NOT_NAN_HPP_INCLUDED

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/sdk/as_logical.hpp>
#include <boost/simd/constant/true.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/simd/is_ord.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD(is_not_nan_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          )
   {
     using result =  bs::as_logical_t<A0>;
     BOOST_FORCEINLINE result operator()(const A0&) const BOOST_NOEXCEPT
     {
       return bs::True<result>();
     }
   };

  BOOST_DISPATCH_OVERLOAD(is_not_nan_
                         , (typename A0, typename X)
                         , bd::cpu_
                         , bs::pack_<bd::floating_<A0>, X>
                         )
  {
    BOOST_FORCEINLINE bs::as_logical_t<A0> operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      return is_ord(a0, a0);
    }
  };

} } }

#endif

