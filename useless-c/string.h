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
#ifndef _HEAD_string_
#define _HEAD_string_


#include "define.h"
#include "c.h"
#include "memory.h"
#include "byte.h"
record(String){
	size_t count;
	bool is_const;
	size_t length;
	const byte* x;
}
INLINE String* new_String_fromConst_endByZero(const char* const x){
	String* r=memory_new_type(String);
	r->count=1;r->is_const=true;r->length=strlen(x);r->x=x;
	return r;}
INLINE String* new_String_memcpy(char* old, size_t length){
	char* news=memory_new(length);
	memcpy(news, old, length);
	String* r=memory_new_type(String);
	r->count=1;r->is_const=false;r->length=length;r->x=news;
	return r;}
INLINE String* new_String_memcpy_endByZero(char* old){
	return new_String_memcpy(old, strlen(length));
}
INLINE void delete_String(String* x){
	assert(x->count);
	x->count--;
	if(eq_p(x->count, 0)){
		if(not(x->is_const)){memory_delete(x->x, x->length);}
		memory_delete_type(x, String);}}
INLINE String* String_copy(String* x){
	assert(x->count);
	x->count++;
	return x;}
INLINE size_t String_length(String* x){
	assert(x->count);
	return x->length;}
INLINE const char* unsafe_unString(String* x){
	assert(x->count);
	return x->x;}
INLINE char* unString_memcpy(String* x){
	assert(x->count);
	char* r=memory_new(x->length);
	memcpy(r, x->x, x->length);
	return r;}
INLINE char* unString_memcpy_endByZero(String* x){
	assert(x->count);
	char* r=memory_new(x->length+1);
	memcpy(r, x->x, x->length);
	r[x->length]='\0';
	return r;}

#endif
