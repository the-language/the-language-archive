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

var d_eq;
var d_lt;
var d_gt;
var d_cp=function(x,y,lt,eq,gt){
	if(d_eq(x,y)){
		return eq();
	}else if(d_lt(x,y)){
		return lt();
	}else{
		return gt();
	}
};

//m [l,k,v,r]
//0 l
//1 k
//2 v
//3 r
var m_get;
m_get=function(m,k,no){
	if(null===m){
		return no();
	}else{
		return d_cp(k,m[1],function(){return m_get(m[0],k,no);},
			function(){return m[2];},
			function(){return m_get(m[3],k,no);});
	}
};
var m_set;
m_set=function(m,k,v){
	if(null===m){
		return [null,k,v,null];
	}else{
		return d_cp(k,m[1],function(){return [m_set(m[0],k,v),m[1],m[2],m[3]];},
			function(){return [m[0],k,v,m[3]];},
			function(){return [m[0],m[1],m[2],m_set(m[3],k,v)];});
	}
};

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

var unjust=function(x){
	var d=x;
	var ds=[];
	while(d_is(t_just,d)){
		ds.push(d);
		d=d_x(d);
	}
	for(var i=0;i<ds.length;i++){
		d_remake(ds[i],t_just,d);
	}
	return d;
};
//WIP
