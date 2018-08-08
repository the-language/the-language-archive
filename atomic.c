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

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L && !defined(__STDC_NO_ATOMICS__)
#	include <stdatomic.h>
	/* atomic_size_t */
	define_public_inline_function(void atomic_size_t_init(volatile atomic_size_t* a, size_t desired))({
		atomic_init(a, desired);})
	define_public_inline_function(size_t atomic_size_t_fetch_add(volatile atomic_size_t* a, size_t x))({
		atomic_fetch_add(a, x);})
	define_public_inline_function(size_t atomic_size_t_fetch_sub(volatile atomic_size_t* a, size_t x))({
		atomic_fetch_sub(a, x);})
	define_public_inline_function(size_t atomic_size_t_read(volatile atomic_size_t* a))({
		atomic_load(a);})
	define_public_inline_function(bool atomic_size_t_compare_exchange(volatile atomic_size_t* a, size_t expected, size_t desired))({
		atomic_compare_exchange_strong(a, &expected, desired);})
	define_public_inline_function(bool atomic_size_t_compare_exchange_load(volatile atomic_size_t* a, size_t expected, size_t desired, size_t* ret))({
		if_then_else(atomic_compare_exchange_strong(a, &expected, desired))({
			*ret=desired;
			true;
		})({
			*ret=expected;
			false;});})
	
#	define atomic_ptr_t atomic_uintptr_t
	define_public_inline_function(void atomic_ptr_t_init(volatile atomic_ptr_t* a, ptr_t desired))({
		atomic_init(a, desired);})
	define_public_inline_function(ptr_t atomic_ptr_t_fetch_add(volatile atomic_ptr_t* a, ptr_t x))({
		atomic_fetch_add(a, (ptrdiff_t)x);})
	define_public_inline_function(ptr_t atomic_ptr_t_fetch_sub(volatile atomic_ptr_t* a, ptr_t x))({
		atomic_fetch_sub(a, (ptrdiff_t)x);})
	define_public_inline_function(ptr_t atomic_ptr_t_read(volatile atomic_ptr_t* a))({
		atomic_load(a);})
	define_public_inline_function(bool atomic_ptr_t_compare_exchange(volatile atomic_ptr_t* a, ptr_t expected, ptr_t desired))({
		atomic_compare_exchange_strong(a, &expected, desired);})
	define_public_inline_function(bool atomic_ptr_t_compare_exchange_load(volatile atomic_ptr_t* a, ptr_t expected, ptr_t desired, ptr_t* ret))({
		if_then_else(atomic_compare_exchange_strong(a, &expected, desired))({
			*ret=desired;
			true;
		})({
			*ret=expected;
			false;});})
	
	/* atomic_bool */
	define_public_inline_function(void atomic_bool_init(volatile atomic_bool* a, bool desired))({
		atomic_init(a, desired);})
	define_public_inline_function(bool atomic_bool_read(volatile atomic_bool* a))({
		atomic_load(a);})
	define_public_inline_function(bool atomic_bool_compare_exchange(volatile atomic_bool* a, bool expected, bool desired))({
		atomic_compare_exchange_strong(a, &expected, desired);})
	define_public_inline_function(bool atomic_bool_compare_exchange_load(volatile atomic_bool* a, bool expected, bool desired, bool* ret))({
		if_then_else(atomic_compare_exchange_strong(a, &expected, desired))({
			*ret=desired;
			true;
		})({
			*ret=expected;
			false;});})
#else
#error "WIP"
#endif

#define lock atomic_bool
define_public_inline_function(void lock_init(volatile lock* l))({
	atomic_bool_init(l, false);})
define_public_inline_function(bool lock_lock(volatile lock* l))({
	atomic_bool_compare_exchange(l, false, true);})
//#error "WIP"

#include ">module"
