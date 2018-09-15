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
#include "memory.c"
#include ">require"
define_struct(List)(
    var(head __ void*);
    var(tail __ List*););
#define List_push(xs, x) { \
    List** List_push_hELPEr=&(xs); \
    List* List_push_hELPEr_new=memory_alloc_type(List); \
    List_push_hELPEr_new->head=(x); \
    List_push_hELPEr_new->tail=*List_push_hELPEr; \
    *List_push_hELPEr=List_push_hELPEr_new;}

#include ">module"
