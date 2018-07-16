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


#include "bool.h"
#include "until.h"
#include "c.h"
struct lock;
typedef struct lock lock;
//單進程實現
struct lock{
	bool locked : 1;};
inline void lock_init(lock* x){
	x->locked=false;}
#define lock_init_m(x) lock_init(&x)
inline bool lock_lock_do(lock* x){
	if(x->locked)
		{return false;}
		else{x->locked=true;return true;}}
#define lock_lock_do_m(x) lock_lock_do(&x)
inline void must_lock_do(lock* x){
	until(lock_lock_do(x)){}}
#define must_lock_do_m(x) must_lock_do(&x)
inline bool lock_unlock_do(lock* x){
	if(x->locked)
		{x->locked=false;return true;}
		else{return false;}}
#define lock_unlock_do_m(x) lock_unlock_do(&x)
inline void assert_lock_unlock_do(lock* x){
	bool b=lock_unlock_do(x);
	assert(b);}
#define assert_lock_unlock_do_m(x) assert_lock_unlock_do(&x)


#endif
