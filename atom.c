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

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
//  atomic_size_t
//  atomic_bool
#  define atomic_size_t_fetch_add atomic_fetch_add
#  define atomic_bool_fetch_add atomic_fetch_add
#  define atomic_size_t_fetch_sub atomic_fetch_sub
#  define atomic_bool_init atomic_init
#  define atomic_size_t_init atomic_init
#  define atomic_bool_compare_exchange(obj, expected, desired) \
	({_Bool _TEMP_atom_atomic_bool_compare_exchange_=expected;atomic_compare_exchange_strong(obj, &_TEMP_atom_atomic_bool_compare_exchange_, desired);})
#  define atomic_size_t_compare_exchange(obj, expected, desired) \
	({size_t _TEMP_atom_atomic_bool_compare_exchange_=expected;atomic_compare_exchange_strong(obj, &_TEMP_atom_atomic_bool_compare_exchange_, desired);})
//WIP
#else
#endif

#include ">module"
