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
typedef struct MapPointer{
	bool has_zeros : 1;
	bool has_zero : 1;
	bool has_one : 1;
	void* zeros;
	MapPointer* zero;
	MapPointer* one;
} MapPointer;
inline MapPointer* new_MapPointer(){
	MapPointer* r=memory_new_type(MapPointer);
	r->has_zeros=false;r->has_zero=false;r->has_one=false;
	return r;
}
inline void delete_MapPointer(MapPointer* m){
	memory_delete(m);
}
extern void MapPointer_set_do(MapPointer* m, void* key, void* value);

extern void* orNull_MapPointer_ref(MapPointer* m, void* key);
extern void* MapPointer_ref(MapPointer* m, void* key, void* default_v);
extern void* assert_MapPointer_ref(MapPointer* m, void* key);
