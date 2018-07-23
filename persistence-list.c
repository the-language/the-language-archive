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
#include "persistence-list.h"
#include "eq.h"
#include "memory.h"
#include "c.h"
#ifdef NULL
#else
PUBLIC PersistenceList PersistenceList_null_v;
PersistenceList PersistenceList_null_v={};
#endif
PUBLIC void remove_PersistenceList(PersistenceList* xs){
	assert(xs->count);
	xs->count--;
	if(eq_p(xs->count, 0)){
		memory_delete(xs->head);
		remove_PersistenceList(xs->tail);}}

