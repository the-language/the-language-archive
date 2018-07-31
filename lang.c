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
//WIP
#include "define.h"
#include "c.h"
#include "bool.h"
#include "eq.h"
#include "lang.h"
#include "list.h"
#include "lock.h"
#include "collection.h"
#include "byte.h"
// PHP簡單實現
enumeration(ValueTypeType){Atom, Box, Pair};
enumeration(ValueType){A_T, B_T, C_T, D_T};
#define AtomSymbolDynamic A_T
#define AtomSymbolConst B_T
#define AtomNull C_T
#define AtomHole D_T

#define BoxDelay A_T
#define BoxJust B_T
#define BoxCollection C_T

#define PairCons A_T
#define PairData B_T
record(Value){
	size_t count; // 自動引用計數
	lock_in_record(lock);
	ValueTypeType type_type :2;
	ValueType type :2;
	union{
		size_t symbol_length;// 單位 byte
		Value* x;
	} x;
	union{
		byte* symbol_x;
		Value* x;
		Value*(*delay_f)(Value*);
	} y;};
PUBLIC void Value_hold(Value* x){
	lock_with_m(x->lock, {
		//WIP
	});
}

