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
#include "memory.h"
#include "bool.h"
#include "c.h"
#include "eq.h"
#include "list.h"
extern ListPointer ListPointer_null_v;
ListPointer ListPointer_null_v={NULL,NULL};
extern void remove_ListPointer(ListPointer* xs){
	while(ListPointer_cons_p(xs)){
		ListPointer* temp=xs->tail;memory_delete(xs);
		xs=temp;}}
extern ListPointer* ListPointer_cons(void* head, ListPointer* tail){
	ListPointer* r=memory_new_type(ListPointer);
	r->head=head;r->tail=tail;
	return r;}
extern void* assert_ListPointer_head(ListPointer* xs){
	assert(ListPointer_cons_p(xs));
	return xs->head;}
extern ListPointer* assert_ListPointer_tail(ListPointer* xs){
	assert(ListPointer_cons_p(xs));
	return xs->tail;}
