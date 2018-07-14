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
#include <stddef.h>
#include "bool.h"
#include "語.h"
typedef struct ValueV ValueV;
typedef enum {Cons, Null, Symbol, SymbolConst, Data, Collection, Just, Delay} ValueVType;
struct ValueV{
	size_t count; // 自動引用計數
	ValueVType type : 3;
	unsigned long mark : 5;
		// 0 => 非 mark-sweep
		// 其他 => 由GC確定
	union {
		struct {
			Value head;
			Value tail;
		} cons;
		// null
		struct {
			size_t length;// 單位 byte
			char* value;
		} symbol;
		struct {
			Value name;
			Value list;
		} data;
		Value collection;
		Value just;
		struct {
			Value (*f)(Value);// f不被remove
			Value x;
		} delay;
	} value;
};
