// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 8 -*-
//
// rprotobuf.h: support for using Rcpp
//
// Copyright (C) 2010 Dirk Eddelbuettel and Romain Francois
//
// This file is part of RProtoBuf.
//
// RProtoBuf is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// RProtoBuf is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RProtoBuf.  If not, see <http://www.gnu.org/licenses/>.

#ifndef RPROTOBUF__RCPPSUPPORT__H
#define RPROTOBUF__RCPPSUPPORT__H

#include "rprotobuf.h"

namespace rprotobuf{

/* support for Rcpp::wrap protobuf repeated fields, this essentially uses
   the same macro trick as in protobuf, but reversed */

struct enum_field{} ;
struct message_field{} ;

template <typename T> class RepeatedFieldImporter{} ;

#undef GENERATE__FIELD__IMPORTER__DECL
#define GENERATE__FIELD__IMPORTER__DECL(__TYPE__,__CAMEL__)			\
template<> class RepeatedFieldImporter<__TYPE__>{ 				\
public:										\
	typedef __TYPE__ r_import_type ;					\
	RepeatedFieldImporter(							\
		const GPB::Reflection* ref_ ,					\
		const GPB::Message& message_,					\
		const GPB::FieldDescriptor* field_):				\
	 	ref(ref_), message(message_), field(field_){}			\
	inline int size() const {						\
		return ref->FieldSize( message, field ) ;			\
	}									\
	inline __TYPE__ get(int i) const {					\
		return ref->GetRepeated##__CAMEL__(message, field, i) ; 	\
	}									\
private:									\
	const GPB::Reflection* ref ;						\
	const GPB::Message& message ;						\
	const GPB::FieldDescriptor* field ;					\
}  ;										\

GENERATE__FIELD__IMPORTER__DECL(GPB::int32 ,Int32) ;
GENERATE__FIELD__IMPORTER__DECL(GPB::uint32,UInt32) ;
GENERATE__FIELD__IMPORTER__DECL(GPB::int64,Int64) ;
GENERATE__FIELD__IMPORTER__DECL(GPB::uint64,UInt64) ;
GENERATE__FIELD__IMPORTER__DECL(float,Float) ;
GENERATE__FIELD__IMPORTER__DECL(double,Double) ;
GENERATE__FIELD__IMPORTER__DECL(bool,Bool) ;
GENERATE__FIELD__IMPORTER__DECL(std::string,String) ;
#undef GENERATE__FIELD__IMPORTER__DECL

template<> class RepeatedFieldImporter<enum_field>{
public:
	typedef int r_import_type ;
	RepeatedFieldImporter( 
	 	const GPB::Reflection* ref_ ,		
		const GPB::Message& message_,		
		const GPB::FieldDescriptor* field_):	
		ref(ref_), message(message_), field(field_){} ;
	inline int size() const {
		return ref->FieldSize( message, field ) ;
	}
	inline int get(int i) const {
		return ref->GetRepeatedEnum(message, field, i)->number() ;
	}
private:
	const GPB::Reflection* ref ;
	const GPB::Message& message ;
	const GPB::FieldDescriptor* field ;	
} ;

template<> class RepeatedFieldImporter<message_field>{
public:
	typedef message_field r_import_type ;
	RepeatedFieldImporter( 
	 	const GPB::Reflection* ref_ ,		
		const GPB::Message& message_,		
		const GPB::FieldDescriptor* field_):	
		ref(ref_), message(message_), field(field_){} ;
	inline int size() const {
		return ref->FieldSize( message, field ) ;
	}
	inline SEXP wrap(int i) const {
		return S4_Message( CLONE( &ref->GetRepeatedMessage( message, field, i ) ) ) ;
	}
private:
	const GPB::Reflection* ref ;
	const GPB::Message& message ;
	const GPB::FieldDescriptor* field ;	
} ;

} // namespace rprotobuf

#endif
