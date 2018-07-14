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
#include "c.h"
#include "bool.h"
#include "eq.h"
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
			Value x;
			Value (*f)(Value);// f不被remove
		} delay;
	} value;
};
inline bool Value_exist_p(Value x){
	return x->count||x->mark;
}
struct ValueList;
typedef struct ValueList ValueList;
struct ValueList {
	Value head;
	ValueList* tail;//NULL=>無
}
inline void ValueList_push(ValueList** l,Value x){
	ValueList* r=memory_alloc_type(ValueList);
	r->head=x;r->tail=*l;
	*l=r;
}
inline Value ValueList_pop(ValueList** l){
	ValueList* nl=(*l)->tail;Value r=(*l)->head;
	memory_free(*l);
	*l=nl;
	return r;
}
extern void Value_hold(Value x){
	assert(Value_exist_p(x));
	x->count++;
}
void do_Value_unhold(ValueList* xs){
	while(xs){
		Value x=ValueList_pop(&xs);
		assert(x->count);
		x->count--;
		if(!Value_exist_p(x)){Value_ValueList_push_sub(x, &xs);}
	}
}
void Value_ValueList_push_sub(Value x, ValueList** xs){
	switch(x->type){
		case Cons:
			ValueList_push(xs, x->value.cons.head);
			ValueList_push(xs, x->value.cons.tail);
			break;
		case Null:break;
		case Symbol:break;
		case SymbolConst:break;
		case Data:
			ValueList_push(xs, x->value.data.name);
			ValueList_push(xs, x->value.data.list);
			break;
		case Collection:
			ValueList_push(xs, x->value.collection);
			break;
		case Just:
			ValueList_push(xs, x->value.just);
			break;
		case Delay:
			ValueList_push(xs, x->value.delay.x);
			break;
		default:assert(false);
	}
}
extern void Value_unhold(Value x){
	ValueList* xs=NULL;
	ValueList_push(&xs, x);
	do_Value_unhold(xs);
}

