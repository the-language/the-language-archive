/*
    語: The Language
    Copyright (C) 2018  Zaoqi

    This program is memory_free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the memory_free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _HEAD_lang_
#define _HEAD_lang_


#include "define.h"
#include "byte.h"
#include "bool.h"
//WIP
record(Value);
PUBLIC Value Value_null_v;
#define Value_null (&Value_null_v)
PUBLIC Value* Value_symbol_dynamic_memcpy(size_t symbol_length, byte* old_symbol);
PUBLIC Value* Value_symbol_const(size_t symbol_length, byte* symbol);
PUBLIC void Value_hold(Value* x);
PUBLIC void Value_unhold(Value* x);
PUBLIC Value* Value_cons(Value* x, Value* y);
PUBLIC Value* Value_cons_head(Value* x);
PUBLIC Value* Value_cons_tail(Value* x);
PUBLIC bool Value_cons_p(Value* x);
PUBLIC Value* Value_data(Value* x, Value* y);
PUBLIC Value* Value_data_name(Value* x);
PUBLIC Value* Value_data_list(Value* x);
PUBLIC bool Value_data_p(Value* x);


#endif
