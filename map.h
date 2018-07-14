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
#include "bool.h"
typedef struct MutableMapPointer{
	bool has_zeros : 1;
	bool has_zero : 1;
	bool has_one : 1;
	void* zeros;
	MutableMapPointer* zero;
	MutableMapPointer* one;
} MutableMapPointer;
inline MutableMapPointer* new_MutableMapPointer(){
	MutableMapPointer* r=memory_new_type(MutableMapPointer);
	r->has_zeros=false;r->has_zero=false;r->has_one=false;
	return r;
}
inline void delete_MutableMapPointer(MutableMapPointer* m){
	memory_remove(m);
}
extern void MutableMapPointer_set(MutableMapPointer* m, void* key, void* value);

extern void* orNull_MutableMapPointer_ref(MutableMapPointer* m, void* key);
extern void* MutableMapPointer_ref(MutableMapPointer* m, void* key, void* default_v);
extern void* assert_MutableMapPointer_ref(MutableMapPointer* m, void* key);
