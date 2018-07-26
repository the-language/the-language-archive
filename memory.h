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
#ifndef memory_new_type


#include "define.h"
#include "c.h"
INLINE void* maybe_memory_new(size_t size){
	return malloc(size);}
PUBLIC void* assert_must_memory_new(size_t size);
#define memory_new assert_must_memory_new
#define memory_new_type(t) memory_new(sizeof(t))

INLINE void* maybe_memory_resize(void* pointer, size_t size){	
	return realloc(pointer, size);}
PUBLIC void* assert_must_memory_resize(void* pointer, size_t size);
#define memory_resize assert_must_memory_resize

INLINE void memory_delete(void* ptr){
	free(ptr);}


#endif
