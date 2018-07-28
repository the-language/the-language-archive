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
#include "define.h"
#include "c.h"
#include "memory.h"
#include "map.h"
#include "bool.h"
#include "list.h"
#include "eq.h"
PUBLIC void delete_Map(Map* m){
	List* ms=List_null;
	List_push_m(ms, m);
	while(List_cons_p(ms)){
		Map* m=assert_List_pop_m(ms);
		if(m->has_zero){List_push_m(ms, m->zero);}
		if(m->has_one){List_push_m(ms, m->one);}
		memory_delete_type(m, Map);}}
PUBLIC void Map_set_do(Map* m, void* key, void* value){
	size_t k=(size_t)key;
	Map* i=m;
	while(k){
		bool b=k&1;
		k=k>>1;
		
		if(b){
			if(!i->has_one){
				i->has_one=true;i->one=new_Map();}
			i=i->one;
		}else{
			if(!i->has_zero){
				i->has_zero=true;i->zero=new_Map();}
			i=i->zero;}}
	i->has_zeros=true;
	i->zeros=value;}
PUBLIC void* orNull_Map_ref(Map* m, void* key){
	size_t k=(size_t)key;
	Map* i=m;
	while(k){
		bool b=k&1;
		k=k>>1;
		
		if(b){
			if(!i->has_one){
				return NULL;}
			i=i->one;
		}else{
			if(!i->has_zero){
				return NULL;}
			i=i->zero;}}
	return i->has_zeros?i->zeros:NULL;}
PUBLIC void* Map_ref(Map* m, void* key, void* default_v){
	size_t k=(size_t)key;
	Map* i=m;
	while(k){
		bool b=k&1;
		k=k>>1;
		
		if(b){
			if(!i->has_one){
				return default_v;}
			i=i->one;
		}else{
			if(!i->has_zero){
				return default_v;}
			i=i->zero;}}
	return i->has_zeros?i->zeros:default_v;}
PUBLIC void* assert_Map_ref(Map* m, void* key){
	size_t k=(size_t)key;
	Map* i=m;
	while(k){
		bool b=k&1;
		k=k>>1;
		
		if(b){
			assert(i->has_one);
			i=i->one;
		}else{
			assert(i->has_zero);
			i=i->zero;}}
	assert(i->has_zeros);
	return i->zeros;}
