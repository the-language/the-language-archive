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
#include "語.h"
#include <string.h>
#include <assert.h>
#include "bool.h"
#include "eq.h"
#include "memory.h"

typedef struct ValueV ValueV;
enum Type{Cons, Null, Symbol, SymbolConst, Data, Set, Just, Delay};
struct ValueV{
	size_t count; //GC => ARC
	enum Type type;
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
			void* x;//f釋放x
			Value (*f)(void*);//不用free
		} delay;
	} value;
};
extern void hold(Value x){
	assert(x->count);
	x->count++;
}
void Value_sub_unhold(Value x){
	switch(x->type){
		case Cons:
			unhold(x->value.cons.head);
			unhold(x->value.cons.tail);
			break;
		case Null:
			break;
		case Symbol:
			memory_free(x->value.symbol.value);
			break;
		case SymbolConst:
			break;
		case Data:
			unhold(x->value.data.name);
			unhold(x->value.data.list);
			break;
		case Set:
			unhold(x->value.set.value);
			break;
	}
}
extern void unhold(Value x){
	x->count--;
	if(eq_p(x->count,0)){
		Value_sub_unhold(x);
		memory_free(x);
	}
}
#define Value_is_p(v, t) eq_p(unJustDelay(v)->type, t)

struct ValueList;
typedef struct ValueList ValueList;
struct ValueList {
	Value head;
	ValueList* tail;//NULL=>無
};
inline void ValueList_push_alloc(ValueList** l,Value x){
	ValueList* r=memory_alloc_type(ValueList);
	r->head=x;r->tail=*l;
	*l=r;
}
inline void ValueList_push_alloc_hold(ValueList** l,Value x){
	hold(x);
	return ValueList_push_alloc(l,x);
}
inline Value ValueList_pop_free(ValueList** l){
	ValueList* nl=(*l)->tail;Value r=(*l)->head;
	memory_free(*l);
	*l=nl;
	return r;
}
#define ValueList_for_free_m(xs,i,body) \
while(xs){ \
	Value i=ValueList_pop_free(&xs); \
	body \
}

Value unJustDelay(Value x){
	hold(x);
	ValueList* justs=NULL;
	ValueList* delays=NULL;
	while(true){
		switch(x->type){
			case Just:
				ValueList_push_alloc_hold(&justs,x);
				unhold(x);
				x=x->value.just.value;
				hold(x);
				break;
			case Delay:
				ValueList_push_alloc_hold(&justs,x);
				Value new=x->value.delay.f(x->value.delay.x);
				hold(new);
				x->type=Just;x->value.just.value=new;
				unhold(x);
				break;
			default:
				goto out;
		}
	}
	out:
	ValueList_for_free_m(justs,v,{
		unhold(v->value.just.value);hold(x);
		v->value.just.value=x;
		unhold(v);
	});
	unhold(x);
	return x;
}
inline Value allocValueV(){
	Value r=memory_alloc_type(ValueV);
	r->count=1;
	return r;
}
extern Value cons(Value head, Value tail){
	hold(head);
	hold(tail);
	Value r=allocValueV();
	r->type=Cons;
	r->value.cons.head=head;
	r->value.cons.tail=tail;
	return r;
}
extern Value cons_head(Value x){
	assert(cons_p(x));
	hold(x->value.cons.head);
	return x->value.cons.head;
}
extern Value cons_tail(Value x){
	assert(cons_p(x));
	hold(x->value.cons.tail);
	return x->value.cons.tail;
}
extern bool cons_p(Value x){
	return Value_is_p(x, Cons);
}
ValueV nullV={
	.count=1,
	.type=Null
};
extern Value null(){return &nullV;}
extern bool null_p(Value x){
	return Value_is_p(x, Null);
}
extern Value symbol_copy(size_t length, char* x){
	char* new=memory_alloc(length);
	memcpy(new, x, length);
	Value r=allocValueV();
	r->type=Symbol;
	r->value.symbol.length=length;
	r->value.symbol.value=new;
	return r;
}
//symbol_const("...")
extern Value symbol_const(char* x){
	Value r=allocValueV();
	r->type=SymbolConst;
	r->value.symbol.length=strlen(x);
	r->value.symbol.value=x;
	return r;
}
extern size_t symbol_length(Value x){
	assert(symbol_p(x));
	return x->value.symbol.length;
}
extern void symbol_value_copyTo(Value x, char* s){
	assert(symbol_p(x));
	memcpy(s, x->value.symbol.value, x->value.symbol.length);
}
extern bool symbol_p(Value x){
	return Value_is_p(x, Symbol) || Value_is_p(x, SymbolConst);
}
extern Value data(Value name, Value list){
	hold(name);
	hold(list);
	Value r=allocValueV();
	r->type=Data;
	r->value.data.name=name;
	r->value.data.list=list;
	return r;
}
extern Value data_name(Value x){
	assert(data_p(x));
	hold(x->value.data.name);
	return x->value.data.name;
}
extern Value data_list(Value x){
	assert(data_p(x));
	hold(x->value.data.list);
	return x->value.data.list;
}
extern bool data_p(Value x){
	return Value_is_p(x, Data);
}
extern Value set(Value x){
	hold(x);
	Value r=allocValueV();
	r->type=Set;
	r->value.set.value=x;
	return r;
}
extern Value unset(Value x){
	assert(set_p(x));
	hold(x->value.set.value);
	return x->value.set.value;
}
extern bool set_p(Value x){return Value_is_p(x, Set);}
extern void assert_equal_optimize(Value x,Value y){
	hold(x);Value_sub_unhold(y);
	y->type=Just;
	y->value.just.value=x;
}
