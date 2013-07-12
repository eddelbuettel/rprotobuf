// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-
/* :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1: */
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
#include "fieldtypes.h"
#include "Rcppsupport.h"

namespace rprotobuf{
	
/**
 * extract a field from a message
 *
 * @param pointer external pointer to a message
 * @param name name of the field
 *
 * @return the field called "name" of the message if the 
 *         message has the field, otherwise an error is generated
 */
SEXP getMessageField( SEXP pointer, SEXP name ){
	
#ifdef RPB_DEBUG
Rprintf( "<getMessageField>\n" ) ;

PRINT_DEBUG_INFO( "pointer", pointer ) ;
PRINT_DEBUG_INFO( "name", name ) ;
#endif

	/* grab the Message pointer */
	Rcpp::XPtr<GPB::Message> message(pointer) ;

	GPB::FieldDescriptor* field_desc = getFieldDescriptor( message, name ) ;
	
#ifdef RPB_DEBUG
Rprintf( "</getMessageField>\n" ) ;
#endif

	return( extractFieldAsSEXP(message, field_desc) ) ;
	
}

SEXP extractFieldAsSEXP( const Rcpp::XPtr<GPB::Message>& message,
						 const GPB::FieldDescriptor*  fieldDesc ){

    const Reflection * ref = message->GetReflection() ;
       
    if( fieldDesc->is_repeated() ){
    	
    	switch( GPB::FieldDescriptor::TypeToCppType(fieldDesc->type()) ){

#undef HANDLE_REPEATED_FIELD
#define HANDLE_REPEATED_FIELD(TYPE,DATATYPE) \
		case TYPE :													\
			return Rcpp::wrap( RepeatedFieldImporter<DATATYPE>(ref, *message, fieldDesc) ) ; \

			HANDLE_REPEATED_FIELD(CPPTYPE_INT32, GPB::int32) ;
    		HANDLE_REPEATED_FIELD(CPPTYPE_UINT32, GPB::uint32) ;
#ifdef RCPP_HAS_LONG_LONG_TYPES
    		HANDLE_REPEATED_FIELD(CPPTYPE_INT64, GPB::int64) ;
    		HANDLE_REPEATED_FIELD(CPPTYPE_UINT64, GPB::uint64) ;
#endif
    		HANDLE_REPEATED_FIELD(CPPTYPE_DOUBLE, double) ;
    		HANDLE_REPEATED_FIELD(CPPTYPE_FLOAT, float) ;
    		HANDLE_REPEATED_FIELD(CPPTYPE_BOOL, bool) ;
    		HANDLE_REPEATED_FIELD(CPPTYPE_ENUM, enum_field ) ;
    		HANDLE_REPEATED_FIELD(CPPTYPE_MESSAGE, message_field ) ;
#undef HANDLE_REPEATED_FIELD

		case CPPTYPE_STRING:
			if (fieldDesc->type() == TYPE_STRING) {
				return Rcpp::wrap( RepeatedFieldImporter<std::string>(ref, *message, fieldDesc) ) ;
			} else if (fieldDesc->type() == TYPE_BYTES) {
				int field_size = ref->FieldSize( *message, fieldDesc ) ;
				Rcpp::List res(field_size);
				for (int i=0; i<field_size; i++) {
					std::string s = ref->GetRepeatedString(*message, fieldDesc, i);
					res[i] =  Rcpp::wrap(std::vector<Rbyte>(s.begin(), s.end()));
				}
				return res;
			} else {
				throwException( "unknown field type with CPP_TYPE STRING", "ConversionException" ) ;
			}
			
		default:
			throwException("Unsupported type", "ConversionException");
    	}
    	
    } else {
    	
    	switch( GPB::FieldDescriptor::TypeToCppType(fieldDesc->type()) ){

#undef HANDLE_SINGLE_FIELD
#define HANDLE_SINGLE_FIELD(CPPTYPE,SUFFIX) 					\
		case CPPTYPE: 									\
			return Rcpp::wrap( ref->Get##SUFFIX(*message, fieldDesc ) ) ;

		HANDLE_SINGLE_FIELD( CPPTYPE_INT32,  Int32 ); 
		HANDLE_SINGLE_FIELD( CPPTYPE_UINT32, UInt32 ); 
#ifdef RCPP_HAS_LONG_LONG_TYPES
		HANDLE_SINGLE_FIELD( CPPTYPE_INT64,  Int64 );
		HANDLE_SINGLE_FIELD( CPPTYPE_UINT64, UInt64 );
#endif
		HANDLE_SINGLE_FIELD( CPPTYPE_DOUBLE, Double );
		HANDLE_SINGLE_FIELD( CPPTYPE_FLOAT, Float );
		HANDLE_SINGLE_FIELD( CPPTYPE_BOOL, Bool );
#undef HANDLE_SINGLE_FIELD

		case CPPTYPE_STRING:
			if (fieldDesc->type() == TYPE_STRING) {
				return Rcpp::wrap( ref->GetString(*message, fieldDesc) );
			} else if (fieldDesc->type() == TYPE_BYTES) {
				std::string s = ref->GetString(*message, fieldDesc);
				return Rcpp::wrap(std::vector<Rbyte>(s.begin(), s.end()));
			} else {
				throwException( "unknown field type with CPP_TYPE STRING", "ConversionException" ) ;			   
			}
		case CPPTYPE_ENUM : 
			return Rcpp::wrap( ref->GetEnum( *message, fieldDesc )->number() ) ;
    		
   		case CPPTYPE_MESSAGE:
			return S4_Message( CLONE( &ref->GetMessage( *message, fieldDesc ) ) ) ;
			break ;

		default:
			throwException("Unsupported type", "ConversionException");
    	}

    }
    return R_NilValue ; /* -Wall */
}

} // namespace rprotobuf

