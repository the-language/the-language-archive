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
#include "byte.h"
// PHP簡單實現
lock lock_values;
#define with_lang(body) lock_with_m(lock_values, body)
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
	union{
		size_t symbol_length;// 單位 byte
		Value* x;
	} x;
	union{
		byte* symbol_x;
		Value* x;
		Value* (*delay_f)(Value*);
	} y;
	lock_in_record(lock);
	ValueTypeType type_type :2;
	ValueType type :2;
	Value* next;//Value_null表示結束
};
PUBLIC Value Value_null_v;
Value Value_null_v={.count=1, .type_type=Atom, .type=AtomNull};
PUBLIC void Value_hold(Value* x){with_lang({lock_with_m(x->lock, {
	assert(x->count);
	x->count++;})})}
INLINE void Value_unhold_helper_delete(Value* x){
	switch(x->type_type){
		case Atom:
			switch(x->type){
				case AtomSymbolDynamic:assert_must_memory_delete(x->y.symbol_x, x->x.symbol_length);return;
				case AtomSymbolConst:case AtomNull:return;
				case AtomHole:default:assert(false);}
			assert(false);
		case Box:
			switch(x->type){
				case BoxDelay:case BoxJust:case BoxCollection:return;
				default:assert(false);}
			assert(false);
		case Pair:
			switch(x->type){
				case PairCons:case PairData:return;
				default:assert(false);}
			assert(false);
		default:assert(false);}
	assert(false);}
PRIVATE void unsafeLang_safeValue_Value_unhold(Value* x){
	assert_must_lock_do_m(x->lock);
	assert(x->count);
	x->count--;
	if(eq_p(x->count, 0)){
		//循環在這裏不會出現
		switch(x->type_type){
			case Atom:break;
			case Box:
				unsafeLang_safeValue_Value_unhold(x->x.x);
				break;
			case Pair:
				unsafeLang_safeValue_Value_unhold(x->x.x);
				unsafeLang_safeValue_Value_unhold(x->y.x);
				break;
			default:assert(false);}
		Value_unhold_helper_delete(x);
	}else{
		assert_lock_unlock_do_m(x);}}
PUBLIC void Value_unhold(Value* x){with_lang({unsafeLang_safeValue_Value_unhold(x);})}
PUBLIC void gc_lang(){
	//WIP
}
