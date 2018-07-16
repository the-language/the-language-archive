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
#ifndef ListPointer_null


#include "eq.h"
#include "bool.h"
#include "memory.h"
struct ListPointer;
typedef struct ListPointer ListPointer;
struct ListPointer{
	void* head;
	ListPointer* tail;};
extern ListPointer ListPointer_null_v;
#define ListPointer_null (&ListPointer_null_v)
extern void remove_ListPointer(ListPointer* xs);
extern ListPointer* ListPointer_cons(void* head, ListPointer* tail);
inline bool ListPointer_null_p(ListPointer* xs){return eq_p(xs, ListPointer_null);}
inline bool ListPointer_cons_p(ListPointer* xs){return !ListPointer_null_p(xs);}
extern void* assert_ListPointer_head(ListPointer* xs);
extern ListPointer* assert_ListPointer_tail(ListPointer* xs);

inline void ListPointer_push(ListPointer** l, void* x){
	ListPointer* r=memory_new_type(ListPointer);
	r->head=x;r->tail=*l;
	*l=r;}
#define ListPointer_push_m(xs, x) ListPointer_push(&xs, x)
inline void* assert_ListPointer_pop(ListPointer** l){
	assert(ListPointer_cons_p(*l));
	ListPointer* nl=(*l)->tail;void* r=(*l)->head;
	memory_delete(*l);
	*l=nl;
	return r;}
#define assert_ListPointer_pop_m(xs) assert_ListPointer_pop(&xs)


#endif
