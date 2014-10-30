/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#pragma once

#ifndef	cml_vector_writable_vector_h
#define	cml_vector_writable_vector_h

#include <initializer_list>
#include <cml/common/mpl/enable_if_array.h>
#include <cml/vector/readable_vector.h>

namespace cml {

/** Base class for writable vector types.  Writable vectors support
 * non-const read-write access to its elements, in addition to read-only
 * access via readable_vector.
 *
 * In addition to the requirements of readable_vector, DerivedT must
 * implement:
 *
 * - <X> get(int i), where <X> is the mutable_value types defined by
 * vector_traits<DerivedT>; and
 *
 * - DerivedT& set(int i, <Y>), where <Y> is the immutable_value type
 * defined by vector_traits<DerivedT>.
 *
 * Note that mutable_value and immutable_value need not be reference types.
 */
template<class DerivedT>
class writable_vector
: public readable_vector<DerivedT>
{
  public:

    typedef DerivedT					vector_type;
    typedef readable_vector<vector_type>		readable_type;
    typedef vector_traits<vector_type>			traits_type;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::mutable_value		mutable_value;
    typedef typename traits_type::immutable_value	immutable_value;


  public:

    /* Disambiguate readable_vector<> methods: */
    using readable_type::actual;
    using readable_type::get;
    using readable_type::operator[];


  public:

    /** Return a mutable reference to the vector cast as DerivedT. */
    DerivedT& actual();

    /** Return mutable element @c i. */
    mutable_value get(int i);

    /** Set element @c i. */
    DerivedT& set(int i, immutable_value v);

    /** Return a mutable reference to element @c i. */
    mutable_value operator[](int i);

    /** Assign from a readable_vector. */
    template<class OtherDerivedT>
      DerivedT& operator=(const readable_vector<OtherDerivedT>& other);

    /** Assign from an array type. */
    template<class Array, typename cml::enable_if_array_t<Array>* = nullptr>
	DerivedT& operator=(const Array& array);

    /** Assign from initializer list. */
    template<class Other>
      DerivedT& operator=(std::initializer_list<Other> l);

    /** Modify the vector by addition of another vector. */
    template<class OtherDerivedT>
      DerivedT& operator+=(const readable_vector<OtherDerivedT>& other);

    /** Modify the vector by subtraction of another vector. */
    template<class OtherDerivedT>
      DerivedT& operator-=(const readable_vector<OtherDerivedT>& other);

    /** Multiply the vector by a scalar. */
    DerivedT& operator*=(immutable_value v);

    /** Divide the vector by a scalar. */
    DerivedT& operator/=(immutable_value v);


  protected:

    /** Assign from a readable_vector. */
    template<class OtherDerivedT>
      DerivedT& assign(const readable_vector<OtherDerivedT>& other);

    /** Assign from an array type. */
    template<class Array,
      typename cml::enable_if_array_t<Array>* = nullptr>
	DerivedT& assign(const Array& array);

    /** Assign from an initializer_list. */
    template<class Other>
      DerivedT& assign(const std::initializer_list<Other>& l);


  protected:

    // Force assignment through operator=(readable_vector<>):
    writable_vector& operator=(writable_vector&) = delete;
};

} // namespace cml

#define __CML_VECTOR_WRITABLE_VECTOR_TPP
#include <cml/vector/writable_vector.tpp>
#undef __CML_VECTOR_WRITABLE_VECTOR_TPP

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2