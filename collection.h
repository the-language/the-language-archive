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
#include "bool.h"
#include "memory.h"
typedef struct MutableCollectionPointer{
	bool has_zeros : 1;
	bool has_zero : 1;
	bool has_one : 1;
	MutableCollectionPointer* zero;
	MutableCollectionPointer* one;
} MutableCollectionPointer;
inline MutableCollectionPointer* new_MutableCollectionPointer(){
	MutableCollectionPointer* r=memory_new_type(MutableCollectionPointer);
	r->has_zeros=false;r->has_zero=false;r->has_one=false;
	return r;
};
inline void delete_MutableMapPointer(MutableCollectionPointer* c){
	memory_remove(c);
}
extern void MutableCollectionPointer_add(MutableCollectionPointer* c, void* x);
extern bool MutableCollectionPointer_has(MutableCollectionPointer* c, void* x);
