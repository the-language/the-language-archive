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
PRIVATE lock lock_values;
#define with_lang_m(body) lock_with_m(lock_values, body)
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
INLINE bool safeValue_safeLang_Value_is_p(Value* x, ValueTypeType tt, ValueType t){with_lang_m({lock_with_m(x->lock, {
	return eq_p(x->type_type, tt)&&eq_p(x->type, t);})})}
PUBLIC Value Value_null_v;
Value Value_null_v={.count=1, .type_type=Atom, .type=AtomNull};
PUBLIC void Value_hold(Value* x){with_lang_m({lock_with_m(x->lock, {
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
				case Box:
					List_push_m(xs, temp_x);
					break;
				case Pair:
					List_push_m(xs, temp_x);
					List_push_m(xs, temp_y);
					break;
				default:assert(false);}
		}else{
			assert_lock_unlock_do_m(x);}
		
		if(is_end){return;}}})}
PUBLIC void Value_unhold(Value* x){with_lang_m({unsafeLang_safeValue_Value_unhold(x);})}
PUBLIC void gc_lang(){
	//WIP
}
PUBLIC Value* Value_cons(Value* x, Value* y){
	Value_hold(x);Value_hold(y);
	Value* r=memory_new_type(Value);
	r->count=1;r->type_type=Pair;r->type=PairCons;r->x.x=x;r->y.x=y;
	return r;}
PUBLIC bool Value_cons_p(Value* x){return safeValue_safeLang_Value_is_p(x, Pair, PairCons);}
PUBLIC Value* Value_data(Value* x, Value* y){
	Value_hold(x);Value_hold(y);
	Value* r=memory_new_type(Value);
	r->count=1;r->type_type=Pair;r->type=PairData;r->x.x=x;r->y.x=y;
	return r;}
PUBLIC bool Value_data_p(Value* x){return safeValue_safeLang_Value_is_p(x, Pair, PairData);}
