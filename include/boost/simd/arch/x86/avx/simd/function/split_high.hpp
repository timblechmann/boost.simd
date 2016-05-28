//==================================================================================================
/**
  Copyright 2016 NumScale SAS
  Copyright 2016 J.T. Lapreste

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SPLIT_HIGH_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SPLIT_HIGH_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/slice_high.hpp>
#include <boost/simd/detail/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( split_high_, (typename A0), bs::avx_
                          , bs::pack_<bd::single_<A0>, bs::avx_>
                          )
  {
    BOOST_FORCEINLINE bd::upgrade_t<A0> operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return _mm256_cvtps_pd(slice_high(a0));
    }
  };
} } }

#endif
