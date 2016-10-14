//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CAST_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/as.hpp>
#include <boost/simd/detail/dispatch/hierarchy.hpp>
#include <type_traits>

namespace boost { namespace simd { namespace ext
{
 namespace bd = boost::dispatch;
 namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( cast_
                          , (typename A0, typename A1, typename X)
                          , bd::cpu_
                          , bs::pack_< bd::unspecified_<A0>, X>
                          , bd::target_< bd::scalar_< bd::unspecified_<A1> > >
                          )
  {
    using s_t =  typename A1::type;
    using result_t = bs:: pack<s_t, A0::static_size>;

    BOOST_FORCEINLINE result_t operator()(A0 const& a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "NAIVE_CAST" << std::endl;
      result_t r;
//       for(size_t i=0; i < A0::static_size; ++i)
//       {
//         r[i] = static_cast<s_t>(a0[i]);
//       }
      return r;
    }
  };
} } }

#endif
