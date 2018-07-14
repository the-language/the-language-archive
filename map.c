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
#include "c.h"
#include "memory.h"
#include "map.h"
#include "bool.h"
#include "list.h"
#include "eq.h"
extern void delete_MapPointer(MapPointer* m){
	ListPointer* ms=ListPointer_null;
	ListPointer_push_m(ms, m);
	while(ListPointer_cons_p(ms)){
		MapPointer* m=assert_ListPointer_pop_m(ms);
		if(m->has_zeros){memory_delete(m->zeros);}
		if(m->has_zero){ListPointer_push_m(ms, m->zero);}
		if(m->has_one){ListPointer_push_m(ms, m->one);}
	}
}
extern void MapPointer_set_do(MapPointer* m, void* key, void* value){
	size_t k=(size_t)key;
	MapPointer* i=m;
	while(k){
		bool b=k&1;
		k=k>>1;
		
		if(b){
			if(!i->has_one){
				i->has_one=true;i->one=new_MapPointer();
			}
			i=i->one;
		}else{
			if(!i->has_zero){
				i->has_zero=true;i->zero=new_MapPointer();
			}
			i=i->zero;
		}
	}
	i->has_zeros=true;
	i->zeros=value;
}
extern void* orNull_MapPointer_ref(MapPointer* m, void* key){
	size_t k=(size_t)key;
	MapPointer* i=m;
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
extern void* MapPointer_ref(MapPointer* m, void* key, void* default_v){
	size_t k=(size_t)key;
	MapPointer* i=m;
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
extern void* assert_MapPointer_ref(MapPointer* m, void* key){
	size_t k=(size_t)key;
	MapPointer* i=m;
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
