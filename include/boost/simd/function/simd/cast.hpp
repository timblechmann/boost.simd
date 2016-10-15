//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================

#ifndef BOOST_SIMD_FUNCTION_SIMD_CAST_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SIMD_CAST_HPP_INCLUDED

#include <boost/simd/function/scalar/cast.hpp>
#include <boost/simd/arch/common/generic/function/autodispatcher.hpp>
#include <boost/simd/arch/common/simd/function/cast.hpp>

#if defined(BOOST_HW_SIMD_X86_OR_AMD_AVAILABLE)
#  if BOOST_HW_SIMD_X86_OR_AMD >= BOOST_HW_SIMD_X86_SSE2_VERSION
#    include <boost/simd/arch/x86/sse2/simd/function/cast.hpp>
#  endif
// #  if BOOST_HW_SIMD_X86_OR_AMD >= BOOST_HW_SIMD_X86_AVX_VERSION
// #    include <boost/simd/arch/x86/avx/simd/function/cast.hpp>
// #  endif
#endif

// #if defined(BOOST_HW_SIMD_PPC_AVAILABLE)
// #  if BOOST_HW_SIMD_PPC >= BOOST_HW_SIMD_PPC_VMX_VERSION
// #    include <boost/simd/arch/ppc/vmx/simd/function/cast.hpp>
// #  endif
// #endif

#endif
