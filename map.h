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
struct MutableMapPointer;
typedef struct MutableMapPointer MutableMapPointer;
extern MutableMapPointer* make_MutableMapPointer();
extern void delete_MutableMapPointer(MutableMapPointer* m);
// key value 非 NULL
extern void MutableMapPointer_set(MutableMapPointer* m, void* key, void* value);
extern void* orNull_MutableMapPointer_ref(MutableMapPointer* m, void* key);
inline void* maybe_MutableMapPointer_ref(MutableMapPointer* m, void* key, void* default_v){
	void* value=orNull_MutableMapPointer_ref(m, key);
	return value?value:default_v;
}
extern void* assert_MutableMapPointer_ref(MutableMapPointer* m, void* key);
