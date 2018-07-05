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
#include "bool.h"
#include <stddef.h>
struct ValueV;
typedef struct ValueV* Value;
extern void hold(Value x);
extern void unhold(Value x);
extern Value cons(Value head, Value tail);
extern Value cons_head(Value x);
extern Value cons_tail(Value x);
extern bool cons_p(Value x);
extern Value null();
extern bool null_p(Value x);
extern Value symbol_copy(size_t length, char* x);
//symbol_const("...")
extern Value symbol_const(char* x);
extern size_t symbol_length(Value x);
extern void symbol_value_copyTo(Value x, char* s);
extern bool symbol_p(Value x);
extern Value data(Value name, Value list);
extern bool data_p(Value x);
extern Value data_name(Value x);
extern Value data_list(Value x);
extern Value collection(Value x);
extern Value uncollection(Value x);
extern bool collection_p(Value x);
extern void assert_equal_optimize(Value x,Value y);
