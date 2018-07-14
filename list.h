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
struct ListPointer;
typedef struct ListPointer ListPointer;
extern ListPointer* ListPointer_null();
extern void remove_ListPointer(ListPointer* xs);
extern ListPointer* ListPointer_cons(void* head, ListPointer* tail);
extern bool ListPointer_cons_p(ListPointer* xs);
extern bool ListPointer_null_p(ListPointer* xs);
extern void* assert_ListPointer_head(ListPointer* xs);
extern ListPointer* assert_ListPointer_tail(ListPointer* xs);
