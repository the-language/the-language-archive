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
#ifndef _HEAD_map_
#define _HEAD_map_


#include "c.h"
#include "memory.h"
#include "bool.h"
struct Map;typedef struct Map Map;struct Map{
	bool has_zeros : 1;
	bool has_zero : 1;
	bool has_one : 1;
	void* zeros;
	Map* zero;
	Map* one;};
inline Map* new_Map(){
	Map* r=memory_new_type(Map);
	r->has_zeros=false;r->has_zero=false;r->has_one=false;
	return r;}
extern void delete_Map(Map* m);
extern void Map_set_do(Map* m, void* key, void* value);

extern void* orNull_Map_ref(Map* m, void* key);
extern void* Map_ref(Map* m, void* key, void* default_v);
extern void* assert_Map_ref(Map* m, void* key);

inline bool Map_not_null_p(Map* m){
	return m->has_zeros||m->has_zero||m->has_one;}
inline bool Map_null_p(Map* c){
	return !Map_not_null_p(c);}


#endif
