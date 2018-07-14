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
#include "c.h"
#include "collection.h"
extern void MutableCollectionPointer_add(MutableCollectionPointer* c, void* x){
	size_t k=(size_t)x;
	MutableCollectionPointer* i=c;
	while(k){
		bool b=k&1;
		k=k>>1;
		
		if(b){
			if(!i->has_one){
				i->has_one=true;i->one=make_MutableCollectionPointer();
			}
			i=i->one;
		}else{
			if(!i->has_zero){
				i->has_zero=true;i->zero=make_MutableCollectionPointer();
			}
			i=i->zero;
		}
	}
	i->has_zeros=true;
}
extern bool MutableCollectionPointer_has(MutableCollectionPointer* c, void* x){
	size_t k=(size_t)x;
	MutableCollectionPointer* i=c;
	while(k){
		bool b=k&1;
		k=k>>1;
		
		if(b){
			if(!i->has_one){
				return false;
			}
			i=i->one;
		}else{
			if(!i->has_zero){
				return false;
			}
			i=i->zero;
		}
	}
	return i->has_zeros;
}
