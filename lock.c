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
#include "require<"
#include "atomic.c"
#include ">require"
#define lock atomic_bool
define_public_inline_withTypeOfBody_lambda(void lock_init(volatile lock* l))({
	atomic_bool_init(l, false);})
define_public_inline_withTypeOfBody_lambda(bool lock_lock(volatile lock* l))({
	atomic_bool_compare_exchange(l, false, true);})
define_public_inline_withTypeOfBody_lambda(bool lock_unlock(volatile lock* l))({
	atomic_bool_compare_exchange(l, true, false);})
#include ">module"
