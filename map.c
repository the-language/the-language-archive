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
#include <stdio.h>
#include "memory.h"
#include "map.h"
#include "bool.h"
#include <assert.h>
struct MutableMapPointer{
	void* zeros;
	MutableMapPointer* aZero;
	MutableMapPointer* aOne;
};
extern MutableMapPointer* make_MutableMapPointer(){
	MutableMapPointer* r=memory_new_type(MutableMapPointer);
	r->zeros=NULL;
	r->aZero=NULL;
	r->aOne=NULL;
	return r;
}
extern void delete_MutableMapPointer(MutableMapPointer* m){
	memory_remove(m);
}
extern void MutableMapPointer_set(MutableMapPointer* m, void* key, void* value){
	assert(key);assert(value);
	size_t k=(size_t)key;
	MutableMapPointer* point=m;
	while(k){
		bool b=k&1;
		k=k>>1;
		
		MutableMapPointer** r=b?&(point->aOne):&(point->aZero);
		if(!r){*r=make_MutableMapPointer();}
		point=*r;
	}
	point->zeros=value;
}
extern void* orNull_MutableMapPointer_ref(MutableMapPointer* m, void* key){
	assert(key);
	size_t k=(size_t)key;
	MutableMapPointer* point=m;
	while(k){
		bool b=k&1;
		k=k>>1;
		
		point=b?point->aOne:point->aZero;
		if(!point){return NULL;}
	}
	return point->zeros;
}
extern void* assert_MutableMapPointer_ref(MutableMapPointer* m, void* key){
	assert(key);
	size_t k=(size_t)key;
	MutableMapPointer* point=m;
	while(k){
		bool b=k&1;
		k=k>>1;
		
		point=b?point->aOne:point->aZero;
		assert(point);
	}
	assert(point->zeros);
	return point->zeros;
}
