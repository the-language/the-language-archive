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
#ifndef _HEAD_persistence_list_
#define _HEAD_persistence_list_


#include "define.h"
#include "c.h"
#include "eq.h"
#include "bool.h"
#include "memory.h"
struct PersistenceList;
typedef struct PersistenceList PersistenceList;
struct PersistenceList{
	size_t count;
	void* head;
	PersistenceList* tail;
};
#ifdef NULL
#define PersistenceList_null NULL
#else
PUBLIC PersistenceList PersistenceList_null_v;
#define PersistenceList_null (&PersistenceList_null_v)
#endif
INLINE bool PersistenceList_null_p(PersistenceList* xs){
	return eq_p(xs, PersistenceList_null);}
INLINE bool PersistenceList_cons_p(PersistenceList* xs){
	return !PersistenceList_null_p(xs);}
INLINE PersistenceList* PersistenceList_cons(void* x, PersistenceList* xs){
	assert(xs->count);
	xs->count++;
	PersistenceList* r=memory_new_type(PersistenceList);
	r->count=1;
	r->head=x;
	r->tail=xs;}
INLINE void* assert_PersistenceList_head(PersistenceList* xs){
	assert(PersistenceList_cons_p(xs));
	return xs->head;}
INLINE PersistenceList* assert_PersistenceList_tail(PersistenceList* xs){
	assert(PersistenceList_cons_p(xs));
	if(PersistenceList_cons_p(xs->tail)){
		xs->tail->count++;}
	return xs->tail;}
PUBLIC void remove_PersistenceList(PersistenceList* xs);

#endif
