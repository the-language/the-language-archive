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
#include "fallthrough.h"
// PHP簡單實現
enumeration(ValueTypeType){Atom, Box, Pair};
enumeration(ValueType){A_T, B_T, C_T, D_T};
#define AtomSymbolDynamic A_T//WIP
#define AtomSymbolConst B_T//WIP
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
		size_t symbol_length;// 單位 byte//WIP
		Value* x;
	} x;
	union{
		byte* symbol;//WIP
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
PRIVATE lock value_xs_lock;
PRIVATE Value* value_xs=Value_null;
INLINE void addValue(Value* x){
	x->lock=lock_init;
	x->count=0;
	lock_with_m(value_xs_lock, {
		x->next=value_xs;
		value_xs=x;})}

INLINE bool safeValue_safeLang_Value_is_p(Value* x, ValueTypeType tt, ValueType t){lock_with_m(x->lock, {
	return eq_p(x->type_type, tt)&&eq_p(x->type, t);})}
PUBLIC void Value_hold(Value* x){lock_with_m(x->lock, {
	assert(x->count);
	x->count++;})}
INLINE void unsafeLang_unsafeValue_Value_delete_extra(Value* x){
	switch(x->type_type){
		case Atom:
			switch(x->type){
				case AtomSymbolDynamic:assert_must_memory_delete(x->y.symbol, x->x.symbol_length);break;
				case AtomSymbolConst:case AtomNull:break;
				case AtomHole:default:assert(false);}
			break;
		case Box:
			switch(x->type){
				case BoxDelay:case BoxJust:case BoxCollection:break;
				default:assert(false);}
			break;
		case Pair:
			switch(x->type){
				case PairCons:case PairData:break;
				default:assert(false);}
			break;
		default:assert(false);}}
INLINE void Value_unhold_helper_delete(Value* x){
	unsafeLang_unsafeValue_Value_delete_extra(x);
	memory_delete_type(x, Value);}
PRIVATE lock unsafeLang_safeValue_Value_unhold_lock;
PRIVATE List unsafeLang_safeValue_Value_unhold_end;
//不計算Stack，不會消耗更多的內存
PRIVATE void unsafeLang_safeValue_Value_unhold(Value* x){lock_with_m(unsafeLang_safeValue_Value_unhold_lock, {
	List(Value*)* xs=&unsafeLang_safeValue_Value_unhold_end;unsafeLang_safeValue_Value_unhold_end.tail=(void*)x;
	while(true){
		Value* x;
		bool is_end=eq_p(xs, &unsafeLang_safeValue_Value_unhold_end);
		if(is_end){
			x=(Value*)unsafeLang_safeValue_Value_unhold_end.tail;
		}else{
			x=assert_List_pop_m(xs);}

		assert_must_lock_do_m(x->lock);
		assert(x->count);
		x->count--;
		if(eq_p(x->count, 0)){
			//循環在這裏不會出現
			ValueTypeType temp_type_type=x->type_type;
			Value* temp_x=x->x.x;
			Value* temp_y=x->y.x;
			Value_unhold_helper_delete(x);
			//不計算Stack，不會消耗更多的內存
			switch(temp_type_type){
				case Atom:break;
				case Pair:
					List_push_m(xs, temp_y);
					fallthrough;
				case Box:
					List_push_m(xs, temp_x);
					break;
				default:assert(false);}
		}else{
			assert_lock_unlock_do_m(x);}
		
		if(is_end){return;}}})}
PUBLIC void Value_unhold(Value* x){unsafeLang_safeValue_Value_unhold(x);}
PUBLIC void gc_lang(){
	//WIP
}
INLINE void unsafeLang_unsafeValue_safeSubValue_Value_unhold_subValue(Value* x){
	assert(x->count);
	switch(x->type_type){
		case Atom:break;
		case Pair:
			unsafeLang_safeValue_Value_unhold(x->y.x);
			fallthrough;
		case Box:
			unsafeLang_safeValue_Value_unhold(x->x.x);
			break;
		default:assert(false);}}
PUBLIC void Value_assert_equal(Value* x, Value* y){
	Value_hold(y);
	lock_with_m(x->lock, {
		assert(x->count);
		unsafeLang_unsafeValue_Value_delete_extra(x);
		unsafeLang_unsafeValue_safeSubValue_Value_unhold_subValue(x);
		x->type_type=Box;x->type=BoxJust;x->x.x=y;})}
PUBLIC Value* Value_symbol_dynamic_memcpy(size_t symbol_length, byte* old_symbol){
	byte* new=memory_new(symbol_length);
	memcpy(new, old_symbol, symbol_length);
	Value* r=memory_new_type(Value);
	r->type_type=Atom;r->type=AtomSymbolDynamic;r->x.symbol_length=symbol_length;r->y.symbol=new;
	addValue(r);
	return r;}
PUBLIC Value* Value_symbol_const(size_t symbol_length, byte* symbol){
	Value* r=memory_new_type(Value);
	r->type_type=Atom;r->type=AtomSymbolConst;r->x.symbol_length=symbol_length;r->y.symbol=symbol;
	addValue(r);
	return r;}
PUBLIC bool Value_symbol_p(Value* x){lock_with_m(x->lock, {
	return and(eq_p(x->type_type, Atom), eq_p(x->type, AtomSymbolDynamic)||eq_p(x->type, AtomSymbolConst));})}
PUBLIC Value* Value_cons(Value* x, Value* y){
	Value_hold(x);Value_hold(y);
	Value* r=memory_new_type(Value);
	r->type_type=Pair;r->type=PairCons;r->x.x=x;r->y.x=y;
	addValue(r);
	return r;}
PUBLIC Value* Value_cons_head(Value* x){lock_with_m(x->lock, {
	assert(x->count);assert(Value_cons_p(x));
	Value_hold(x->x.x);
})}
PUBLIC Value* Value_cons_tail(Value* x){lock_with_m(x->lock, {
	assert(x->count);assert(Value_cons_p(x));
	Value_hold(x->y.x);
})}
PUBLIC bool Value_cons_p(Value* x){return safeValue_safeLang_Value_is_p(x, Pair, PairCons);}
PUBLIC Value* Value_data(Value* x, Value* y){
	Value_hold(x);Value_hold(y);
	Value* r=memory_new_type(Value);
	r->count=1;r->type_type=Pair;r->type=PairData;r->x.x=x;r->y.x=y;
	addValue(r);
	return r;}
PUBLIC Value* Value_data_name(Value* x){lock_with_m(x->lock, {
	assert(x->count);assert(Value_data_p(x));
	Value_hold(x->x.x);
})}
PUBLIC Value* Value_data_list(Value* x){lock_with_m(x->lock, {
	assert(x->count);assert(Value_data_p(x));
	Value_hold(x->y.x);
})}
PUBLIC bool Value_data_p(Value* x){return safeValue_safeLang_Value_is_p(x, Pair, PairData);}
//WIP
