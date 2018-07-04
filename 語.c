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
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "語.h"
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
			void* x;
			Value (*f)(void*);
		} delay;
	} value;
};
typedef struct ValueV ValueV;
void countInc(Value x){
	x->count++;
}
void countDec(Value x){
	x->count--;
	if(x->count==0){
		switch(x->type){
			case Cons:
				countDec(x->value.cons.head);
				countDec(x->value.cons.tail);
				break;
			case Null:
				break;
			case Symbol:
				free(x->value.symbol.value);
				break;
			case Data:
				countDec(x->value.data.name);
				countDec(x->value.data.list);
				break;
			case Set:
				countDec(x->value.set.value);
				break;
		}
		free(x);
	}
}
Value allocValueV(){
	Value r=malloc(sizeof(ValueV));
	r->count=0;
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
	return x->type==Cons;
}
ValueV nullV={
	.count=1,
	.type=Null
};
Value null(){return &nullV;}
bool null_p(Value x){
	return x->type==Null;
}
Value symbolCopy(size_t length, char* ValueV){
	char* new=malloc(length);
	memcpy(new, ValueV, length);
	Value r=allocValueV();
	r->type=Symbol;
	r->value.symbol.length=length;
	r->value.symbol.value=new;
	return r;
}
bool symbol_p(Value x){
	return x->type==Symbol;
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
	return x->type==Data;
}
Value set(Value ValueV){
	countInc(ValueV);
	Value r=allocValueV();
	r->type=Set;
	r->value.set.value=ValueV;
	return r;
}
bool set_p(Value x){
	return x->type==Set;
}
void assert_equal_optimize(Value x,Value y){
	countInc(x);
	y->type=Just;
	y->value.just.value=x;
}
