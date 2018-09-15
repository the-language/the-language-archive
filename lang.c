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
#pragma once
#include "module<"
#include "require<"
#include "lock.c"
#include "memory.c"
#include "list.c"
#include ">require"
define_enumeration(ValueTypeType)(Atom, Box, Pair);
define_enumeration(ValueType)(A_T, B_T, C_T, D_T);
define_private(var(AtomSymbolDynamic __ const ValueType) __ A_T);
define_private(var(AtomSymbolConst __ const ValueType) __ B_T);
define_private(var(AtomNull __ const ValueType) __ C_T);
define_private(var(AtomHole __ const ValueType) __ D_T);
define_private(var(BoxDelay __ const ValueType) __ A_T);
define_private(var(BoxJust __ const ValueType) __ B_T);
define_private(var(BoxCollection __ const ValueType) __ C_T);
define_private(var(PairCons __ const ValueType) __ A_T);
define_private(var(PairData __ const ValueType) __ B_T);
define_struct(Value)(
    nat_pointer count;
    union{
	nat_pointer symbol_length;// 單位 byte
	Value* x;
    } x;
    union{
	byte* symbol;
	Value* x;
	Value* (*delay_f)(Value*);
    } y;
    lock lock;
    bool enable_marksweep :1;
    ValueTypeType type_type :2;
    ValueType type :2;);
define_private(var(marksweeps __ List/*(Value*)*/*) __ (List*)0);
define_private(var(marksweeps_lock_raw __ lock*) __ (lock*)0);
define_private_inline_lambda_withTypeOfBody(marksweeps_lock() __ lock*)(
    if(!marksweeps_lock_raw){
	marksweeps_lock_raw=memory_alloc_type(lock);
	lock_init(marksweeps_lock_raw);
    }
    marksweeps_lock_raw;);
define_public_lambda_withTypeOfBody(newValueHole() __ Value*)(
    var(r __ Value*)=memory_alloc_type(Value);
    r->count=1;
    r->lock=lock_init;
    r->type_type=Atom;
    r->type=AtomHole;
    lock_with(marksweeps_lock() , Value*)(
	List_push(marksweeps, r);
	r;););
#include ">module"
