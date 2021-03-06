//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MINMOD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MINMOD_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/if_else_zero.hpp>
#include <boost/simd/function/is_gez.hpp>
#include <boost/simd/function/is_nltz.hpp>
#include <boost/simd/function/min.hpp>
#include <boost/simd/function/multiplies.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(minmod_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::int_<A0>, X>
                          , bs::pack_<bd::int_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return if_else_zero(is_gez(bitwise_xor(a0, a1)),bs::min(a0, a1));
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(minmod_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::uint_<A0>, X>
                          , bs::pack_<bd::uint_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return  bs::min(a0,a1);
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(minmod_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return if_else_zero(is_nltz((a0*a1)),bs::conformant_(bs::min)(a0, a1));
      }
   };

} } }


#endif

