/*
    語: The Language
    Copyright (C) 2018  Zaoqi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#include "module<"

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L && !defined(__STDC_NO_ATOMICS__)) || (defined(__cplusplus) && __cplusplus >= 201103L)
#	if defined(__cplusplus)
#		include <atomic>
		using std::atomic_init;
		using std::atomic_fetch_add;
		using std::atomic_load;
		using std::atomic_compare_exchange_strong;
#		define atomic_hELPEr(x) std::atomic<x>
#	else
#		include <stdatomic.h>
#		define atomic_hELPEr(x) _Atomic(x)
#	endif
#	define HELPER_atomic_define1(T) \
	define_public_inline_withTypeOfBody_lambda(void atomic_##T##_init(volatile atomic_##T* a, T desired))( \
		atomic_init(a, desired);) \
	define_public_inline_withTypeOfBody_lambda(T atomic_##T##_read_add(volatile atomic_##T* a, T x))( \
		atomic_fetch_add(a, x);) \
	define_public_inline_withTypeOfBody_lambda(T atomic_##T##_read_sub(volatile atomic_##T* a, T x))( \
		atomic_fetch_sub(a, x);) \
	define_public_inline_withTypeOfBody_lambda(T atomic_##T##_read(volatile atomic_##T* a))( \
		atomic_load(a);) \
	define_public_inline_withTypeOfBody_lambda(bool atomic_##T##_compare_exchange(volatile atomic_##T* a, T expected, T desired))( \
		atomic_compare_exchange_strong(a, &expected, desired);) \
	define_public_inline_withTypeOfBody_lambda(bool atomic_##T##_compare_exchange_load(volatile atomic_##T* a, T expected, T desired, T* ret))( \
		if_then_else(atomic_compare_exchange_strong(a, &expected, desired))( \
			*ret=desired; \
			true; \
		)( \
			*ret=expected; \
			false;);)
#	define HELPER_atomic_define(T, M) \
	define_public_inline_withTypeOfBody_lambda(void atomic_##T##_init(volatile atomic_##T* a, T desired))( \
		atomic_init(a, desired);) \
	define_public_inline_withTypeOfBody_lambda(T atomic_##T##_read_add(volatile atomic_##T* a, T x))( \
		atomic_fetch_add(a, (M)x);) \
	define_public_inline_withTypeOfBody_lambda(T atomic_##T##_read_sub(volatile atomic_##T* a, T x))( \
		atomic_fetch_sub(a, (M)x);) \
	define_public_inline_withTypeOfBody_lambda(T atomic_##T##_read(volatile atomic_##T* a))( \
		atomic_load(a);) \
	define_public_inline_withTypeOfBody_lambda(bool atomic_##T##_compare_exchange(volatile atomic_##T* a, T expected, T desired))( \
		atomic_compare_exchange_strong(a, &expected, desired);) \
	define_public_inline_withTypeOfBody_lambda(bool atomic_##T##_compare_exchange_load(volatile atomic_##T* a, T expected, T desired, T* ret))( \
		if_then_else(atomic_compare_exchange_strong(a, &expected, desired))( \
			*ret=desired; \
			true; \
		)( \
			*ret=expected; \
			false;);)
#	define atomic_nat_pointer atomic_hELPEr(nat_pointer)
	HELPER_atomic_define(nat_pointer, ptrdiff_t)
	
#	define atomic_int_pointer atomic_hELPEr(int_pointer)
	HELPER_atomic_define(int_pointer, ptrdiff_t)
	
#	define atomic_bool atomic_hELPEr(bool)
	HELPER_atomic_define1(bool)
	
#	define atomic_size_t atomic_hELPEr(size_t)
	HELPER_atomic_define1(size_t)
	
#	define atomic_int8 atomic_hELPEr(int8)
	HELPER_atomic_define1(int8)
	
#	define atomic_int16 atomic_hELPEr(int16)
	HELPER_atomic_define1(int16)
	
#	define atomic_int32 atomic_hELPEr(int32)
	HELPER_atomic_define1(int32)
	
#	define atomic_int64 atomic_hELPEr(int64)
	HELPER_atomic_define1(int64)
	
#	define atomic_nat8 atomic_hELPEr(nat8)
	HELPER_atomic_define1(nat8)
	
#	define atomic_nat16 atomic_hELPEr(nat16)
	HELPER_atomic_define1(nat16)
	
#	define atomic_nat32 atomic_hELPEr(nat32)
	HELPER_atomic_define1(nat32)
	
#	define atomic_nat64 atomic_hELPEr(nat64)
	HELPER_atomic_define1(nat64)
#else
#error "WIP"
#endif

#include ">module"
