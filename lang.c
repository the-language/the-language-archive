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
List/*(Value)*/* xs_marked=List_null;
record(Value){
	lock lock;
	size_t count; // 自動引用計數
	bool is_marked : 1;//需要marksweep_lock
	anonymous_enumeration{
		ValueCons,
		ValueNull,
		ValueSymbol,
		ValueData,
		ValueCollection,
		ValueJust,
		ValueDelay,
		ValueHole
	} type : 3;
	union{
		anonymous_record{
			bool is_marksweep_head :1;
			bool is_marksweep_tail :1;
			Value* head;
			Value* tail;
		} ValueCons;
		anonymous_record{
		} ValueNull;
		anonymous_record{
			bool is_const :1;
			size_t length;// 單位 byte
			byte* value;
		} ValueSymbol;
		anonymous_record{
			bool is_marksweep_name :1;
			bool is_marksweep_list :1;
			Value* name;
			Value* list;
		} ValueData;
		anonymous_record{
			bool is_marksweep :1;
			Value* x;
		} ValueCollection;
		anonymous_record{
			bool is_marksweep :1;
			Value* x;
		} ValueJust;
		anonymous_record{
			bool is_marksweep :1;
			Value* x;
			Value* (*f)(Value*);
		} ValueDelay;
		anonymous_record{
		} ValueHole;
	} x;
};
INLINE void unsafe_delete_Value_self(Value* x){
	memory_delete_type(x, Value);
}
#define with_marksweep_m(body) lock_with_m(marksweep_lock, body)
#define with_value_m(x, body) lock_with_m(x->lock, body)
#define value_lock(x) assert_must_lock_do_m(x->lock)
#define value_unlock(x) assert_lock_unlock_do_m(x->lock)
INLINE bool unsafeValue_unsafeMarksweep_Value_exist_p(Value* x){
	return or(x->count, x->is_marked);}
INLINE bool unsafeValue_safeMarksweep_Value_exist_p(Value* x){with_marksweep_m({
	return unsafeValue_unsafeMarksweep_Value_exist_p(x);})}
PUBLIC void assert_Value_hold(Value* x){with_value_m(x, {
	assert(unsafeValue_safeMarksweep_Value_exist_p(x));
	x->count++;})}
PRIVATE void safeValue_unsafeMarksweep_assert_Value_unhold(Value* x);
PRIVATE void unsafeValue_unsafeMarksweep_delete_Value(Value* x){
	assert(not(unsafeValue_unsafeMarksweep_Value_exist_p(x)));
	switch(x->type){
		case ValueCons:
			if(not(x->x.ValueCons.is_marksweep_head)){
				safeValue_unsafeMarksweep_assert_Value_unhold(x->x.ValueCons.head);}
			if(not(x->x.ValueCons.is_marksweep_tail)){
				safeValue_unsafeMarksweep_assert_Value_unhold(x->x.ValueCons.tail);}
			break;
		case ValueNull:
			break;
		case ValueSymbol:
			if(not(x->x.ValueSymbol.is_const)){
				memory_delete(x->x.ValueSymbol.value, x->x.ValueSymbol.length);}
			break;
		case ValueData:
			if(not(x->x.ValueData.is_marksweep_name)){
				safeValue_unsafeMarksweep_assert_Value_unhold(x->x.ValueData.name);}
			if(not(x->x.ValueData.is_marksweep_list)){
				safeValue_unsafeMarksweep_assert_Value_unhold(x->x.ValueData.list);}
			break;
		case ValueCollection:
			if(not(x->x.ValueCollection.is_marksweep)){
				safeValue_unsafeMarksweep_assert_Value_unhold(x->x.ValueCollection.x);}
			break;
		case ValueJust:
			if(not(x->x.ValueJust.is_marksweep)){
				safeValue_unsafeMarksweep_assert_Value_unhold(x->x.ValueJust.x);}
			break;
		case ValueDelay:
			if(not(x->x.ValueDelay.is_marksweep)){
				safeValue_unsafeMarksweep_assert_Value_unhold(x->x.ValueDelay.x);}
			break;
		case ValueHole:default:assert(false);}
	unsafe_delete_Value_self(x);
}
PRIVATE void safeValue_unsafeMarksweep_assert_Value_unhold(Value* x){
	value_lock(x);
	assert(unsafeValue_safeMarksweep_Value_exist_p(x));
	assert(x->count);
	x->count--;
	if(unsafeValue_unsafeMarksweep_Value_exist_p(x)){
		value_unlock(x);
	}else{
		unsafeValue_unsafeMarksweep_delete_Value(x);}}
//WIP
PUBLIC void gcValue(){
}

