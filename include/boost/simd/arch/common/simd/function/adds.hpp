//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS
  @copyright 2016 J.T. Lapreste

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ADDS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ADDS_HPP_INCLUDED

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/simd/bitwise_cast.hpp>
#include <boost/simd/function/simd/bitwise_or.hpp>
#include <boost/simd/function/simd/bitwise_xor.hpp>
#include <boost/simd/function/simd/bitwise_not.hpp>
#include <boost/simd/function/simd/complement.hpp>
#include <boost/simd/function/simd/genmask.hpp>
#include <boost/simd/function/simd/if_else.hpp>
#include <boost/simd/function/simd/is_greater_equal.hpp>
#include <boost/simd/function/simd/is_less.hpp>
#include <boost/simd/function/simd/is_gez.hpp>
#include <boost/simd/function/simd/plus.hpp>
#include <boost/simd/function/simd/shr.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD(adds_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return a0+a1;
      }
   };

   BOOST_DISPATCH_OVERLOAD(adds_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::uint_<A0>, X>
                          , bs::pack_<bd::uint_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        A0 a0pa1 = a0+a1;
        return a0pa1 | genmask(is_less(a0pa1, a0));
      }
   };

   BOOST_DISPATCH_OVERLOAD(adds_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::int_<A0>, X>
                          , bs::pack_<bd::int_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        using utype = bd::as_unsigned_t<A0>;
        using stype = bd::scalar_of_t<A0>;
        utype ux = bitwise_cast<utype>(a0);
        utype uy = bitwise_cast<utype>(a1);
        utype res = ux + uy;
        ux = shr(ux, sizeof(stype)*CHAR_BIT-1) + splat<utype>(Valmax<stype>()); //+ static_cast<bd::scalar_of_t<utype>>(Valmax<stype>());
        auto t = is_gez(bitwise_cast<A0>(ux ^ uy) | ~(uy ^ res));
        return bitwise_cast<A0>(if_else(t, ux, res));
      }
   };
} } }

#endif
