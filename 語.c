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
#include <string.h>
#include "bool.h"
#include "eq.h"
#include "語.h"
#include "memory.h"

struct ValueV {
	size_t count;
	enum {Cons, Null, Symbol, Data, Set, Just, Delay} type;
	union {
		struct {
			Value head;
			Value tail;
		} cons;
		// null
		struct {
			size_t length;//byte
			char* value;
		} symbol;
		struct {
			Value name;
			Value list;
		} data;
		struct {
			Value value;
		} set;
		struct {
			Value value;
		} just;
		struct {
			void* x;//f釋放它
			Value (*f)(void*);
		} delay;
	} value;
};
typedef struct ValueV ValueV;
struct ValueList;
typedef struct ValueList ValueList;
struct ValueList {
	Value head;
	ValueList* tail;//NULL=>無
};
void countInc(Value x){
	x->count++;
}
void countDec(Value x){
	x->count--;
	if(eq_p(x->count,0)){
		switch(x->type){
			case Cons:
				countDec(x->value.cons.head);
				countDec(x->value.cons.tail);
				break;
			case Null:
				break;
			case Symbol:
				memory_free(x->value.symbol.value);
				break;
			case Data:
				countDec(x->value.data.name);
				countDec(x->value.data.list);
				break;
			case Set:
				countDec(x->value.set.value);
				break;
		}
		memory_free(x);
	}
}
Value unJust(Value x){
	ValueList* list=NULL;
	while(eq_p(x->type,Just)){
		ValueList* n=memory_allocType(ValueList);
		n->head=x;n->tail=list;
		
		x=x->value.just.value;list=n;
	}
	while(list){
		ValueList* n=list;list->head->value.just.value=x;
		list=list->tail;
		memory_free(n);
	}
	return x;
}
Value unDelay(Value x){
	ValueList* list=NULL;
	while(eq_p(x->type, Delay)){//WIP-Just
		ValueList* n=memory_allocType(ValueList);
		n->head=x;n->tail=list;
		
		x=x->value.delay.f(x->value.delay.x);list=n;
	}
	while(list){
		ValueList* n=list;list->head->type=Just;list->head->value.just.value=x;
		list=list->tail;countDec(n->head);
		memory_free(n);
	}
}
Value allocValueV(){
	Value r=memory_allocType(ValueV);
	r->count=1;
	return r;
}
Value cons(Value head, Value tail){
	countInc(head);
	countInc(tail);
	Value r=allocValueV();
	r->type=Cons;
	r->value.cons.head=head;
	r->value.cons.tail=tail;
	return r;
}
bool cons_p(Value x){
	return eq_p(unJust(x)->type,Cons);
}
ValueV nullV={
	.count=1,
	.type=Null
};
Value null(){return &nullV;}
bool null_p(Value x){
	return eq_p(unJust(x)->type,Null);
}
Value symbolCopy(size_t length, char* ValueV){
	char* new=memory_alloc(length);
	memcpy(new, ValueV, length);
	Value r=allocValueV();
	r->type=Symbol;
	r->value.symbol.length=length;
	r->value.symbol.value=new;
	return r;
}
bool symbol_p(Value x){
	return eq_p(unJust(x)->type,Symbol);
}
Value data(Value name, Value list){
	countInc(name);
	countInc(list);
	Value r=allocValueV();
	r->type=Data;
	r->value.data.name=name;
	r->value.data.list=list;
	return r;
}
bool data_p(Value x){
	return eq_p(unJust(x)->type,Data);
}
Value set(Value ValueV){
	countInc(ValueV);
	Value r=allocValueV();
	r->type=Set;
	r->value.set.value=ValueV;
	return r;
}
bool set_p(Value x){
	return eq_p(unJust(x)->type,Set);
}
void assert_equal_optimize(Value x,Value y){
	countInc(x);
	y->type=Just;
	y->value.just.value=x;
}
