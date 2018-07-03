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
#include <stdlib.h>
#include "語.h"
void countInc(Value* x){
	x->count++;
}
void countDec(Value* x){
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
Value* allocValue(){
	Value* r=malloc(sizeof(Value));
	r->count=0;
	return r;
}
Value* cons(Value* head, Value* tail){
	head->count++;
	Value* r=allocValue();
	r->type=Cons;
	r->value.cons.head=head;
	r->value.cons.tail=tail;
	return r;
}
Value nullV={
	.count=1,
	.type=Null
};
Value* null(){return &nullV;}
