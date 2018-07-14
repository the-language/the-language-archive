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
#include <stddef.h>
#include <stdlib.h>
inline void* maybe_memory_alloc(size_t size){
	return malloc(size);
}
extern void* memory_alloc(size_t);
inline void* must_memory_alloc(size_t size){
	return memory_alloc(size);
}
#define memory_alloc_type(t) memory_alloc(sizeof(t))
inline void memory_free(void* ptr){
	free(ptr);
}
