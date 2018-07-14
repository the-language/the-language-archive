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
#include <stddef.h>
#include "memory.h"
#include "map.h"
#include "bool.h"
#include <assert.h>
struct MutableMapPointer{
	void* zeros;
	MutableMapPointer* aZero;
	MutableMapPointer* aOne;
};
extern MutableMapPointer* new_MutableMapPointer(){
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
	size_t k=(size_t)key;
	MutableMapPointer* i=m;
	while(k){
		bool b=k&1;
		k=k>>1;
		
		if(b){
			if(!i->has_one){
				i->has_one=true;i->one=new_MutableMapPointer();
			}
			i=i->one;
		}else{
			if(!i->has_zero){
				i->has_zero=true;i->zero=new_MutableMapPointer();
			}
			i=i->zero;
		}
	}
	i->has_zeros=true;
	i->zeros=value;
}
extern void* orNull_MutableMapPointer_ref(MutableMapPointer* m, void* key){
	size_t k=(size_t)key;
	MutableMapPointer* i=m;
	while(k){
		bool b=k&1;
		k=k>>1;
		
		if(b){
			if(!i->has_one){
				return NULL;
			}
			i=i->one;
		}else{
			if(!i->has_zero){
				return NULL;
			}
			i=i->zero;
		}
	}
	return i->has_zeros?i->zeros:NULL;
}
extern void* MutableMapPointer_ref(MutableMapPointer* m, void* key, void* default_v){
	size_t k=(size_t)key;
	MutableMapPointer* i=m;
	while(k){
		bool b=k&1;
		k=k>>1;
		
		if(b){
			if(!i->has_one){
				return default_v;
			}
			i=i->one;
		}else{
			if(!i->has_zero){
				return default_v;
			}
			i=i->zero;
		}
	}
	return i->has_zeros?i->zeros:default_v;
}
extern void* assert_MutableMapPointer_ref(MutableMapPointer* m, void* key){
	size_t k=(size_t)key;
	MutableMapPointer* i=m;
	while(k){
		bool b=k&1;
		k=k>>1;
		
		if(b){
			assert(i->has_one);
			i=i->one;
		}else{
			assert(i->has_zero);
			i=i->zero;
		}
	}
	assert(i->has_zeros);
	return i->zeros;
}
