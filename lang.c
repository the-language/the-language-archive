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
lock marksweep_lock=lock_init;
List(Value*)* marksweep_xs=List_null;

lock just_xs_lock=lock_init;
List(Value*)* just_xs_a=List_null;
List(Value*)* just_xs_b=List_null;

lock unhold_xs_lock=lock_init;
List(Value*)* unhold_xs=List_null;

enumeration ValueTypeType{Atom, Box, Pair};
enumeration ValueType{A_T, B_T, C_T, D_T};
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
	bool is_marked :1;//需要marksweep_lock
	anonymous_enumeration{ValueGCingNotMarked, ValueGCingMarked, ValueGCingARC} gc_state :2;
	ValueTypeType type_type :2;
	ValueType type :2;
	bool is_marksweep_x :1;
	bool is_marksweep_y :1;
	union{
		size_t symbol_length;// 單位 byte
		Value* x;
	} x;
	union{
		byte* symbol_x;
		Value* x;
		Value*(*delay_f)(Value*);
	} y;};
INLINE bool unsafeValue_Value_is(Value x, ValueTypeType tt, ValueType t){
	return eq_p(x->type_type, tt)&&eq_p(x->type, t);}
INLINE void unsafeUnholdXs_Value_unhold(Value x){List_push_m(unhold_xs, x);}
PUBLIC void Value_unhold(Value x){lock_with_m(unhold_xs_lock, {unsafeUnholdXs_unsafeValue_Value_unhold(x);})}
INLINE void safeMarksweep_unsafeValueJust_safeValue_Just_set_do(Value just, Value x){
	assert(unsafeValue_Value_is(just, Box, BoxJust));
	//WIP
	if(not(just->is_marksweep_x)){Value_unhold(just->x->x);}
	lock_with_m(x->lock, {
		if(x->
	})
//WIP
PUBLIC void gc_step_lang_value_just(){lock_with_m(just_xs_lock, {
	if(List_null_p(just_xs_a)){
		if(List_null_p(just_xs_b)){return;}
		just_xs_a=just_xs_b;
	}
	assert(List_cons_p(just_xs_a));
	Value* x=assert_List_pop_m(just_xs_a);
	lock_with_m(x->lock,{
		assert(unsafeValue_Value_is(x, Box, BoxJust));
		Value* y=x->x->x;
		assert_must_lock_do_m(y->lock);
		if(unsafeValue_Value_is(y, Box, BoxJust)){
			Value* z=y->x->x;
			Value_hold(z);
			assert_lock_unlock_do_m(y->lock);
			unsafeValueJust_safeValue_Just_set_do(x, z);
			Value_unhold(z);
		}else{
			assert_lock_unlock_do_m(y->lock);
		}})
		
}
