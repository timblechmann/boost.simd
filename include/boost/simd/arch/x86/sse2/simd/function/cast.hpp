//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_CAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_CAST_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/repeat_upper_half.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

//   // float --> double
//   BOOST_DISPATCH_OVERLOAD ( cast_
//                           , (typename A0, typename A1)
//                           , bs::sse2_
//                           , bs::pack_<bd::single_<A0>, bs::sse_>
//                           , bd::target_< bd::scalar_< bd::double_<A1> > >
//                           )
//   {
//     using result = typename A0::template rebind<typename A1::type>;
//     BOOST_FORCEINLINE result operator() ( const A0 & a0) const BOOST_NOEXCEPT
//     {
//       return {_mm_cvtps_pd(a0), _mm_cvtps_pd(repeat_upper_half(a0))};
//     }
//   };

// //   // double_ --> float
// //   BOOST_DISPATCH_OVERLOAD ( cast_
// //                           , (typename A0, typename A1)
// //                           , bs::sse2_
// //                           , bs::pack_<bd::single_<A0>, bs::sse_>
// //                           , bd::target_< bd::scalar_< bd::double_<A1> > >
// //                          )
// //   {
// //     using result = typename A0::template rebind<typename A1::type>;
// //     BOOST_FORCEINLINE result operator() ( const A0 & a0) const BOOST_NOEXCEPT
// //     {
// //       return {_mm_cvtps_pd(a0), _mm_cvtps_pd(repeat_upper_half(a0))};
// //     }
// //   };


//   // float --> int32
//   BOOST_DISPATCH_OVERLOAD ( cast_
//                           , (typename A0, typename A1)
//                           , bs::sse2_
//                           , bs::pack_<bd::single_<A0>, bs::sse_>
//                           , bd::target_< bd::scalar_< bd::int32_<A1> > >
//                          )
//   {
//     using result = typename A0::template rebind<typename A1::type>;
//     BOOST_FORCEINLINE result operator() ( const A0 & a0) const BOOST_NOEXCEPT
//     {
//       return _mm_cvtepi32_ps(a0);
//     }
//   };




//   // double --> int64
//   BOOST_DISPATCH_OVERLOAD ( cast_
//                           , (typename A0, typename A1)
//                           , bs::sse2_
//                           , bs::pack_<bd::double_<A0>, bs::sse_>
//                           , bd::target_< bd::scalar_< bd::int64_<A1> > >
//                          )
//   {
//     using result = typename A0::template rebind<typename A1::type>;
//     BOOST_FORCEINLINE  bd::as_integer_t<A0>  operator() (const A0 & a0) const BOOST_NOEXCEPT
//     {
//       return { _mmcvtsd_si64(a0),  _mmcvtsd_si64(repeat_upper_half(a0))};

//  //      bd::downgrade_t<bd::as_integer_t<A0>> out = _mm_cvttpd_epi32(a0);
//  //       return bs::split_low(out);
//     }
//   };


} } }

#endif
