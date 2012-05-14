// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 8 -*-
//
// wrapper_EnumDescriptor.cpp: R/C++ interface class library
//
// Copyright (C) 2010 - 2011  Dirk Eddelbuettel and Romain Francois
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

#include "rprotobuf.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(EnumDescriptor__,__NAME__)	

	RCPP_XP_METHOD_0(METHOD(as_character), GPB::EnumDescriptor      , DebugString) ;
	RCPP_XP_METHOD_0(METHOD(length)      ,GPB::EnumDescriptor,value_count)
	RCPP_XP_METHOD_0(METHOD(value_count) ,GPB::EnumDescriptor,value_count)
	
	RCPP_FUNCTION_1(S4_Descriptor, METHOD(containing_type), Rcpp::XPtr<GPB::EnumDescriptor> d ){
		return S4_Descriptor( d->containing_type() ) ;
	}

	RCPP_FUNCTION_2( S4_EnumValueDescriptor, METHOD(getValueByIndex) , Rcpp::XPtr<GPB::EnumDescriptor> d, int index){
		if ((index >= 0) && (index < d->value_count())) {
		return S4_EnumValueDescriptor( d->value(index) ) ;
		} else {
			return S4_EnumValueDescriptor(NULL);
		}
	}
	
	RCPP_FUNCTION_2( S4_EnumValueDescriptor, METHOD(getValueByNumber), Rcpp::XPtr<GPB::EnumDescriptor> d, int i ){
		return S4_EnumValueDescriptor( d->FindValueByNumber(i)  ) ;                  
	}
	RCPP_FUNCTION_2( S4_EnumValueDescriptor, METHOD(getValueByName)  ,  Rcpp::XPtr<GPB::EnumDescriptor> d , std::string name ){
		return S4_EnumValueDescriptor( d->FindValueByName(name) ) ;
	}

	RCPP_FUNCTION_1(S4_Message, METHOD(as_Message), Rcpp::XPtr<GPB::EnumDescriptor> d ){
		GPB::EnumDescriptorProto* message = new GPB::EnumDescriptorProto() ; 
		d->CopyTo( message ); 
		return S4_Message(message) ;
	}
	
/**
 * Get the value of the enum called name
 *
 * @param xp external pointer to an EnumDescriptor
 * @param name the name of the enum
 * 
 * @param the value associated with the name
 */
RCPP_FUNCTION_2(int,get_value_of_enum, 
	Rcpp::XPtr<GPB::EnumDescriptor> d, std::string name){
	
	const GPB::EnumValueDescriptor* evd = d->FindValueByName(name) ;
    if( !evd ){
    	/* or maybe it should just be NA */
    	throwException( "cannot get the value", "UnknownEnumValueException" ) ;
    }
	return evd->number(); 
}

/**
 * @param xp external pointer to a Descriptor
 * @return the descriptor as an R list
 */
RCPP_FUNCTION_1( Rcpp::IntegerVector, METHOD(as_list), Rcpp::XPtr<GPB::EnumDescriptor> d ){
	
	int n = d->value_count() ;
	Rcpp::IntegerVector values(n) ;
	Rcpp::CharacterVector names(n) ;
	
	for( int i=0; i<n; i++){
		const GPB::EnumValueDescriptor* value_d = d->value(i) ;
		values[i] = value_d->number() ;
		names[i]  = value_d->name() ;
	}
	values.names() = names ;
	return values; 
}

RCPP_FUNCTION_1( Rcpp::CharacterVector, METHOD(getConstantNames), Rcpp::XPtr<GPB::EnumDescriptor> d){
	int n = d->value_count() ;
	Rcpp::CharacterVector res( n) ;
	for( int i=0; i<n; i++){
		res[i] = d->value(i)->name() ;
	}
	return res ;
}

RCPP_FUNCTION_1( S4_FileDescriptor, METHOD(fileDescriptor), Rcpp::XPtr<GPB::EnumDescriptor> desc){
	return S4_FileDescriptor( desc->file() ); 
}

RCPP_FUNCTION_2( std::string, METHOD(name), Rcpp::XPtr<GPB::EnumDescriptor> d, bool full){
	return full ? d->full_name() : d->name() ;
}

#undef METHOD

} // namespace rprotobuf
