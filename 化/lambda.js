//    The Language: the best programming language
//    Copyright (C) 2018  Zaoqi <zaomir@outlook.com>

//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as published
//    by the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.

//    You should have received a copy of the GNU Affero General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

var t_count=0;
var t_gen=function(){
	var r=t_count;
	t_count+=1;
	return r;
};
var t_just=t_gen();
var t_eval=t_gen();
var t_true=t_gen();
var t_false=t_gen();
var t_cons=t_gen();
var t_null=t_gen();
var t_sym=t_gen();
var t_sym_cons=t_gen();
var t_map=t_gen();
var t_func=t_gen();
var t_form=t_gen();
var t_data=t_gen();
var t_err=t_gen();

var d_make=function(t,x,y){
	return [t,x,y];
};
var d_t=function(d){
	return d[0];
};
var d_x=function(d){
	return d[1];
};
var d_y=function(d){
	return d[2];
};
var d_remake=function(d,t,x,y){
	d[0]=t;
	d[1]=x;
	d[2]=y;
};
var d_set=function(d1,d2){
	d1[0]=d2[0];
	d1[1]=d2[1];
	d1[2]=d2[2];
};
var d_is=function(t,d){
	return d[0]===t;
};
//WIP
