//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS
  @copyright 2016 J.T. Lapreste

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_NEXT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_NEXT_HPP_INCLUDED

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/simd/bitfloating.hpp>
#include <boost/simd/function/simd/bitinteger.hpp>
#include <boost/simd/function/simd/if_else.hpp>
#include <boost/simd/function/simd/inc.hpp>
#include <boost/simd/function/simd/is_equal.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD(next_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return inc(a0);
      }
   };

   BOOST_DISPATCH_OVERLOAD(next_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return if_else(eq(a0, Inf<A0>()), a0,  bitfloating(inc(bitinteger(a0))));
      }
   };

} } }
#endif

