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
struct Letrec;
typedef struct Letrec Letrec;
typedef enum {Cons, Null, Symbol, SymbolConst, Data, Collection, Just, Delay, Letrec} ValueVType;
struct ValueV{
	size_t count; //GC => ARC
	ValueVType type;
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
		Value collection;
		Value just;
		struct {
			Value (*f)(Value);//f不用free
			Value x;
		} delay;
		struct {
			Letrec* rec;
			size_t id;
		} letrec;
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
		case Collection:
			unhold(x->value.collection);
			break;
		case Just:
			unhold(x->value.just);
			break;
		case Delay:
			unhold(x->value.delay.x);
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
#define Value_set(x,y) {unhold(x);hold(y);x=y;}


struct LetrecValue;
typedef struct LetrecValue LetrecValue;
struct Letrec{
	size_t count;
	
	size_t size;
	LetrecValue* list;
};
inline void holdLetrec(Letrec* rec){
	assert(rec->count);
	rec->count++
}
struct LetrecValue{
	enum {RecCons, RecData, RecCollection, RecDelay, RecValue} type;
	union {
		struct {
			size_t head;
			size_t tail;
		} cons;
		struct {
			size_t name;
			size_t list;
		} data;
		size_t collection;
		struct {
			Value (*f)(Value);
			size_t x;
		} delay;
		Value value;
	} value;
};
Value makeValueLetrec(Letrec* rec, size_t id){
	holdLetrec(rec);
	Value r=allocValueV();
	r->type=Letrec;
	r->value.letrec.rec=rec;r->value.letrec.id=id;
	//[r]
	return r;
};
void unLetrec(Letrec* rec, size_t id){
	assert(id<rec->size);
	LetrecValue* v=&(rec->list[id]);
	switch(v->type){
		case RecCons:
			Value head=makeValueLetrec(rec, v->value.cons.head);Value tail=makeValueLetrec(rec, v->value.cons.tail);
			Value r=cons(head, tail);
			unhold(head);unhold(tail);
			return r;
		case RecData:
			Value name=makeValueLetrec(rec, v->value.data.name);Value list=makeValueLetrec(rec, v->value.data.list);
			Value r=data(name, list);
			unhold(name);unhold(list);
			return r;
		case RecCollection:
			return makeValueLetrec(rec, v->value.collection);
		case RecValue:
			Value x=makeValueLetrec(rec, v->value.delay.x);
			//WIP
			
		
}
void LetrecValue_unDelay(Letrec* rec, size_t id){
	assert(id<rec->size);
	LetrecValue* v=rec->list[id];
	//WIP
}

Value unJustDelay(Value x){//不增加hold
	hold(x);
	//[x] //部分hold列表
	ValueList* justs=NULL;
	ValueList* delays=NULL;
	while(true){
		switch(x->type){
			case Just:
				ValueList_push_alloc_hold(&justs,x);
				//[x]
				Value_set(x,x->value.just);//[x->value.just]
				//[x]
				break;
			case Delay:
				ValueList_push_alloc_hold(&justs,x);
				Value new=x->value.delay.f(x->value.delay.x);
				//[new,x]
				unhold(x->value.delay.x);x->type=Just;hold(new);x->value.just=new;
				//[new,x]
				unhold(x);
				//[new]
				x=new;
				//[x]
				break;
			default:
				goto out;
		}
		//[x]
	}
	//[x]
	out:
	ValueList_for_free_m(justs,v,{
		//[v,v->value.just,x]
		Value_set(v->value.just,x);//[v,x]
		unhold(v);
		//[x]
	});
	//[x]
	unhold(x);
	//[]
	return x;
}
inline Value allocValueV(){
	Value r=memory_alloc_type(ValueV);
	r->count=1;
	//[r]
	return r;
}
extern Value cons(Value head, Value tail){
	hold(head);hold(tail);
	Value r=allocValueV();
	r->type=Cons;
	r->value.cons.head=head;
	r->value.cons.tail=tail;
	//[r]
	return r;
}
extern Value cons_head(Value x){
	assert(cons_p(x));
	//BUGS
	hold(x->value.cons.head);
	//[x->value.cons.head]
	return x->value.cons.head;
}
extern Value cons_tail(Value x){
	assert(cons_p(x));
	hold(x->value.cons.tail);
	//[x->value.cons.head]
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
	//[r]
	return r;
}
//symbol_const("...")
extern Value symbol_const(char* x){
	Value r=allocValueV();
	r->type=SymbolConst;
	r->value.symbol.length=strlen(x);
	r->value.symbol.value=x;
	//[r]
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
	hold(name);hold(list);
	Value r=allocValueV();
	r->type=Data;
	r->value.data.name=name;
	r->value.data.list=list;
	//[r]
	return r;
}
extern Value data_name(Value x){
	assert(data_p(x));
	hold(x->value.data.name);
	//[x->value.data.name]
	return x->value.data.name;
}
extern Value data_list(Value x){
	assert(data_p(x));
	hold(x->value.data.list);
	//[x->value.data.list]
	return x->value.data.list;
}
extern bool data_p(Value x){
	return Value_is_p(x, Data);
}
extern Value collection(Value x){
	hold(x);
	Value r=allocValueV();
	r->type=Collection;
	r->value.collection=x;
	//[r]
	return r;
}
extern Value uncollection(Value x){
	assert(collection_p(x));
	hold(x->value.collection);
	//[x->value.collection]
	return x->value.collection;
}
extern bool collection_p(Value x){return Value_is_p(x, Collection);}
extern void assert_equal_optimize(Value x,Value y){
	hold(x);Value_sub_unhold(y);
	y->type=Just;
	y->value.just=x;
	//[]
}
extern Value delay(Value (*f)(Value), Value x){
	hold(x);
	Value r=allocValueV();
	r->type=Delay;
	r->value.delay.f=f;r->value.delay.x=x;
	//[r]
	return r;
}
	
