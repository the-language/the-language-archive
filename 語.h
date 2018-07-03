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
#include <stddef.h>
struct Value;
typedef struct Value Value;
struct Value {
	size_t count;
	enum {Cons, Null, Symbol, Data, Set} type;
	union {
		struct {
			Value* head;
			Value* tail;
		} cons;
		// null
		struct {
			size_t length;//byte
			char* value;
		} symbol;
		struct {
			Value* name;
			Value* list;
		} data;
		struct {
			Value* value;
		} set;
	} value;
};
void countInc(Value*);
void countDec(Value*);
Value* cons(Value* head, Value* tail);
Value* null();
Value* symbolCopy(size_t length, char* value);
Value* data(Value* name, Value* list);
Value* set(Value* value);
