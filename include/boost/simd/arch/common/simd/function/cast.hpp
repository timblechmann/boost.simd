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
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/detail/type_id.hpp>
#include <type_traits>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/slice_low.hpp>
#include <boost/simd/function/if_allbits_else_zero.hpp>
#include <boost/simd/function/interleave.hpp>
#include <boost/simd/function/interleave_first.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/constant/zero.hpp>

// TODO improve the "take all" NAIVE part

// this file already take care of the trivial (NO_CAST) part
// and the semi-trivial cast from signed < -> unsigned of same size

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
   using result = typename A0::template rebind<typename A1::type>;

    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const& ) const BOOST_NOEXCEPT
    {
      return do_(a0, typename std::is_same<A0, result>::type());
    }

    BOOST_FORCEINLINE result do_(A0 const& a0, std::false_type ) const BOOST_NOEXCEPT
    {
      using s_t =  typename A1::type;
      std::cout << "target: " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in NAIVE_CAST" <<  std::endl;
      result r;
      for(size_t i=0; i < A0::static_size; ++i)
      {
        r[i] = static_cast<s_t>(a0[i]);
      }
      return r;
    }

    BOOST_FORCEINLINE result do_(A0 const& a0, std::true_type const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in NO_CAST" << std::endl;
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                             , (typename A0,typename A1, typename X)
                             , (detail::same_sizeof<typename A0::value_type,typename A1::type>)
                             , bd::cpu_
                             , bs::pack_< bd::int_<A0>, X>
                             , bd::target_< bd::scalar_< bd::uint_<A1> > >
                             )
  {
    using result = typename A0::template rebind<typename A1::type>;

    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in SIGNED->UNSIGNED" << std::endl;
      return a0.storage();
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                             , (typename A0,typename A1, typename X)
                             , (detail::same_sizeof<typename A0::value_type, typename A1::type>)
                             , bd::cpu_
                             , bs::pack_< bd::uint_<A0>, X>
                             , bd::target_< bd::scalar_< bd::int_<A1> > >
                             )
  {
    using result = typename A0::template rebind<typename A1::type>;

    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in UNSIGNED->SIGNED" << std::endl;
      return a0.storage();
    }
  };

 //////////////////////////////////////////////////////////////////////////////////////////////////
 // double to something
 //////////////////////////////////////////////////////////////////////////////////////////////////
 // double --> uint64
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::double_<A0>, X>
                          , bd::target_< bd::scalar_< bd::uint64_<A1> > >
                         )
  {
    using result = typename A0::template rebind<typename A1::type>;
    using siA1 = bd::as_integer_t<typename A1::type, signed>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 00" << std::endl;
      return cast<siA1>(a0).storage();
    }
  };

 //////////////////////////////////////////////////////////////////////////////////////////////////
 // float to something
 //////////////////////////////////////////////////////////////////////////////////////////////////
 // float --> uint32
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::single_<A0>, X>
                          , bd::target_< bd::scalar_< bd::uint32_<A1> > >
                         )
  {
    using result = typename A0::template rebind<typename A1::type>;
    using siA1 = bd::as_integer_t<typename A1::type, signed>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 9" << std::endl;
      return cast<siA1>(a0).storage();
    }
  };


 //////////////////////////////////////////////////////////////////////////////////////////////////
 // (u)int64 to something
 //////////////////////////////////////////////////////////////////////////////////////////////////

  // (u)int64 --> int32
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints64_<A0>, X>
                          , bd::target_< bd::scalar_< bd::int32_<A1> > >
                         )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 1" << std::endl;
      using p32 = pack<typename A1::type, A0::static_size*2>;
      return slice_low( deinterleave_first(p32(a0.storage()), Zero<p32>()));
    }
  };

  // (u)int64 --> uint32
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints64_<A0>, X>
                          , bd::target_< bd::scalar_< bd::uint32_<A1> > >
                         )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 2" << std::endl;
      using pu32 = pack<typename A1::type, A0::static_size*2>;
      return slice_low( deinterleave_first(pu32(a0.storage()), Zero<pu32>()));
    }
  };

//  //////////////////////////////////////////////////////////////////////////////////////////////////
//  // int32 to something
//  //////////////////////////////////////////////////////////////////////////////////////////////////

  // (u)int32 --> int64
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints32_<A0>, X>
                          , bd::target_< bd::scalar_< bd::int64_<A1> > >
                         )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 3" << std::endl;
       using p64 = pack<typename A1::type, A0::static_size/2>;
       auto x = interleave(a0, if_allbits_else_zero(is_ltz(a0)));
       return combine(p64(x[0].storage()), p64(x[1].storage()));
    }
  };

  // (u)int32 --> uint64
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints32_<A0>, X>
                          , bd::target_< bd::scalar_< bd::uint64_<A1> > >
                         )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 4" << std::endl;
       using pu64 = pack<typename A1::type, A0::static_size/2>;
       auto x = interleave(a0, if_allbits_else_zero(is_ltz(a0)));
       return combine(pu64(x[0].storage()), pu64(x[1].storage()));
    }
  };

  // (u)int32 --> int16
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints32_<A0>, X>
                          , bd::target_< bd::scalar_< bd::int16_<A1> > >
                         )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 5" << std::endl;
      using p16 = pack<typename A1::type, A0::static_size*2>;
      return slice_low( deinterleave_first(p16(a0.storage()), Zero<p16>()));
    }
  };

  // (u)int32 --> uint16
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints32_<A0>, X>
                          , bd::target_< bd::scalar_< bd::uint16_<A1> > >
                         )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 6" << std::endl;
      using pu16 = pack<typename A1::type, A0::static_size*2>;
      return slice_low( deinterleave_first(pu16(a0.storage()), Zero<pu16>()));
    }
  };

 //////////////////////////////////////////////////////////////////////////////////////////////////
 // (u)int16 to something
 //////////////////////////////////////////////////////////////////////////////////////////////////

  // (u)int16 --> int32
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints16_<A0>, X>
                          , bd::target_< bd::scalar_< bd::int32_<A1> > >
                         )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 7" << std::endl;
       using p32 = pack<typename A1::type, A0::static_size/2>;
       auto x = interleave(a0, if_allbits_else_zero(is_ltz(a0)));
       return combine(p32(x[0].storage()), p32(x[1].storage()));
    }
  };
  // (u)int16 --> uint32
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints16_<A0>, X>
                          , bd::target_< bd::scalar_< bd::uint32_<A1> > >
                         )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 8" << std::endl;
       using pu32 = pack<typename A1::type, A0::static_size/2>;
       auto x = interleave(a0, if_allbits_else_zero(is_ltz(a0)));
       return combine(pu32(x[0].storage()), pu32(x[1].storage()));
    }
  };

  // (u)int16 --> int8
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints16_<A0>, X>
                          , bd::target_< bd::scalar_< bd::int8_<A1> > >
                         )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 9" << std::endl;
      using p8 = pack<typename A1::type, A0::static_size*2>;
      return slice_low( deinterleave_first(p8(a0.storage()), Zero<p8>()));
    }
  };

  // (u)int16 --> uint8
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints16_<A0>, X>
                          , bd::target_< bd::scalar_< bd::uint8_<A1> > >
                         )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 10" << std::endl;
      using pu8 = pack<typename A1::type, A0::static_size*2>;
      return slice_low( deinterleave_first(pu8(a0.storage()), Zero<pu8>()));
    }
  };

 //////////////////////////////////////////////////////////////////////////////////////////////////
 // (u)int8 to something
 //////////////////////////////////////////////////////////////////////////////////////////////////


  // (u)int8 --> int16
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints8_<A0>, X>
                          , bd::target_< bd::scalar_< bd::int16_<A1> > >
                         )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 11" << std::endl;
       using p16 = pack<typename A1::type, A0::static_size/2>;
       auto x = interleave(a0, if_allbits_else_zero(is_ltz(a0)));
       return combine(p16(x[0].storage()), p16(x[1].storage()));
    }
  };

  // (u)int8 --> uint16
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                          , (typename A0, typename A1, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints8_<A0>, X>
                          , bd::target_< bd::scalar_< bd::uint16_<A1> > >
                         )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 12" << std::endl;
      using pu16 = pack<typename A1::type, A0::static_size/2>;
      auto x = interleave(a0, if_allbits_else_zero(is_ltz(a0)));
      return combine(pu16(x[0].storage()), pu16(x[1].storage()));
    }
  };

  // type8 --> type32  and type16 -> type64
  BOOST_DISPATCH_OVERLOAD_IF ( cast_
                             , (typename A0, typename A1, typename X)
                             , (detail::sizeof_ratio_is_greater<typename A1::type, typename A0::value_type, 2>)
                             , bd::cpu_
                             , bs::pack_<bd::integer_<A0>, X>
                             , bd::target_< bd::scalar_< bd::integer_<A1> > >
                             )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      std::cout << "target " << detail::type_id<typename A1::type>() <<  " from " << detail::type_id<typename A0::value_type>() <<  " in 13" << std::endl;
      using sA1 = typename A1::type;
      using sdA1 = bd::as_integer_t< bd::downgrade_t<sA1>, signed>;
      return cast<sA1>(cast<sdA1>(a0));
    }
  };


} } }

#endif
