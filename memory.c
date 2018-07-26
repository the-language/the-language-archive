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
#include "define.h"
#include "memory.h"
#include "gc.h"
#include "c.h"
#include "eq.h"
PUBLIC void* must_memory_new(size_t size){
	void* r=maybe_memory_new(size);
	if(eq_p(r, NULL)){gc();r=maybe_memory_new(size);}
	assert(r);
	return r;}
PUBLIC void* must_memory_resize(void* pointer, size_t size){
	void* r=maybe_memory_resize(pointer, size);
	if(eq_p(r, NULL)){gc();r=maybe_memory_resize(pointer, size);}
	assert(r);
	return r;}
