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
	enum {Cons, Null, Symbol, Data, Set} type;
	union {
		struct {
			Value head;
			Value tail;
		} cons;
		// null
		struct {
			size_t length;//byte
			char* ValueV;
		} symbol;
		struct {
			Value name;
			Value list;
		} data;
		struct {
			Value ValueV;
		} set;
	} ValueV;
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
				countDec(x->ValueV.cons.head);
				countDec(x->ValueV.cons.tail);
				break;
			case Null:
				break;
			case Symbol:
				free(x->ValueV.symbol.ValueV);
				break;
			case Data:
				countDec(x->ValueV.data.name);
				countDec(x->ValueV.data.list);
				break;
			case Set:
				countDec(x->ValueV.set.ValueV);
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
	r->ValueV.cons.head=head;
	r->ValueV.cons.tail=tail;
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
	r->ValueV.symbol.length=length;
	r->ValueV.symbol.ValueV=new;
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
	r->ValueV.data.name=name;
	r->ValueV.data.list=list;
	return r;
}
bool data_p(Value x){
	return x->type==Data;
}
Value set(Value ValueV){
	countInc(ValueV);
	Value r=allocValueV();
	r->type=Set;
	r->ValueV.set.ValueV=ValueV;
	return r;
}
bool set_p(Value x){
	return x->type==Set;
}
