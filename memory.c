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
#include <stdlib.h>
define_public_inline_lambda_withTypeOfBody(orNull_memory_alloc_bytes(nat_pointer size) __ void*)(
    malloc(size););
define_public_inline_lambda_withTypeOfBody(memory_alloc_bytes(nat_pointer size) __ void*)(
    var(r, void*)=(void*)0;
    while(!r)r=orNull_memory_alloc_bytes(size);
    r;);
define_public_inline_lambda_withTypeOfBody(memory_free_bytes(var(size , nat_pointer), var(pointer , void*)) __ void)(
    free(pointer);
    make_void(););
#include ">module"
