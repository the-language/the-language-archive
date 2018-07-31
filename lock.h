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
#ifndef lock_init_m


#include "define.h"
#include "bool.h"
#include "until.h"
#include "c.h"
//單進程無中斷實現
typedef bool lock;
#define lock_in_record(name) bool name :1;
#define lock_init true
INLINE bool lock_lock_do(lock* x){
	if(*x)
		{return false;}
		else{*x=true;return true;}}
#define lock_lock_do_m(x) lock_lock_do(&x)
INLINE void assert_must_lock_do(lock* x){
	bool b=lock_lock_do(x);
	assert(b);}
#define assert_must_lock_do_m(x) assert_must_lock_do(&x)
INLINE bool lock_unlock_do(lock* x){
	if(*x)
		{*x=false;return true;}
		else{return false;}}
#define lock_unlock_do_m(x) lock_unlock_do(&x)
INLINE void assert_lock_unlock_do(lock* x){
	bool b=lock_unlock_do(x);
	assert(b);}
#define assert_lock_unlock_do_m(x) assert_lock_unlock_do(&x)
#define lock_with_m(lock, body) { \
	lock* _TEMP_lock_with_m_=&(lock); \
	assert_must_lock_do(_TEMP_lock_with_m_); \
	body \
	assert_lock_unlock_do(_TEMP_lock_with_m_);}
#define lock_with_2_m(x, y, body) lock_with_m(x, lock_with_m(y, body))
#define lock_with_if_m(lock, body, elseb) { \
	lock* _TEMP_lock_lock_with_if_m_=&(lock); \
	if(lock_lock_do(_TEMP_lock_lock_with_if_m_)){ \
		body \
		assert_lock_unlock_do_m(lock); \
	}else{ \
		elseb}}


#endif
