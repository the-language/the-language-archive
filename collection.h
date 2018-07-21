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
#ifndef _HEAD_collection_
#define _HEAD_collection_


#include "bool.h"
#include "memory.h"
struct Collection;typedef struct Collection Collection;struct Collection{
	bool has_zeros : 1;
	bool has_zero : 1;
	bool has_one : 1;
	Collection* zero;
	Collection* one;};
inline Collection* new_Collection(){
	Collection* r=memory_new_type(Collection);
	r->has_zeros=false;r->has_zero=false;r->has_one=false;
	return r;}
extern void delete_Collection(Collection* c);
extern void Collection_add_do(Collection* c, void* x);
extern bool Collection_has(Collection* c, void* x);

inline bool Collection_not_null_p(Collection* c){
	return c->has_zeros||c->has_zero||c->has_one;}
inline bool Collection_null_p(Collection* c){
	return !Collection_not_null_p(c);}


#endif
