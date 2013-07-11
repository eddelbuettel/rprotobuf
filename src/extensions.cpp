/*
 * Copyright 2012 Google Inc. All Rights Reserved.
 * Author: Murray Stokely
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#include "rprotobuf.h"
#include "fieldtypes.h"
#include "Rcppsupport.h"

namespace rprotobuf {

// TODO add num_extensions to wrapper_Message.cpp and show this also
// in show().


/**
 * set a non-repeated extension field to a new value
 *
 * @param pointer external pointer to a message
 * @param sfielddesc S4 field descriptor class
 * @param value new value for the field
 *
 * @return always NULL, the message is modified by reference
 */
RcppExport SEXP setExtensionField( SEXP pointer, SEXP sfielddesc, SEXP value ){
        GPB::Message* message = GET_MESSAGE_POINTER_FROM_XP(pointer) ;
        const Reflection * ref = message->GetReflection() ;
        GPB::FieldDescriptor* field_desc = GET_FIELD_DESCRIPTOR_POINTER_FROM_S4(sfielddesc);

	if (!field_desc->is_extension()) {
		Rprintf("Field is not an extension! tag = %d type = %s\n",
			field_desc->number(), field_desc->type_name());
		return R_NilValue;
	}

	switch (field_desc->type()) {
		// All floating-point and 64-bit types as R numerics.
		case TYPE_DOUBLE:
			ref->SetDouble(message, field_desc, REAL(value)[0]);
			break;
		case TYPE_FLOAT:
			ref->SetFloat(message, field_desc, REAL(value)[0]);
			break;
		case TYPE_INT64:
			ref->SetInt64(message, field_desc, REAL(value)[0]);
			break;
		case TYPE_UINT64:
			ref->SetUInt64(message, field_desc, REAL(value)[0]);
			break;
		case TYPE_INT32:
			ref->SetInt32(message, field_desc, INTEGER(value)[0]);
			break;
		case TYPE_UINT32:
			ref->SetUInt32(message, field_desc, INTEGER(value)[0]);
			break;
		case TYPE_BOOL:
			ref->SetBool(message, field_desc, LOGICAL(value)[0]);
			break;
		case TYPE_STRING:
			ref->SetString(message, field_desc,
				       CHAR(STRING_ELT(value, 0)));
			break;

// TODO(mstokely): support enums and messages.
// Check value is an EnumValueDescriptor first.
//		case TYPE_ENUM:
//			ref->SetEnum(message, field_desc, value);
//			break;
		default:
			printf("Not implemented yet");
	}

	return R_NilValue;
}

/**
 * set a repeated extension field to a new value
 *
 * @param pointer external pointer to a message
 * @param sfielddesc S4 field descriptor class
 * @param value new value for the field
 *
 * @return always NULL, the message is modified by reference
 */
RcppExport SEXP setExtensionRepeatedField( SEXP pointer,
					   SEXP sfielddesc, SEXP value ){
        GPB::Message* message = GET_MESSAGE_POINTER_FROM_XP(pointer) ;
        const Reflection * ref = message->GetReflection() ;
        GPB::FieldDescriptor* field_desc = GET_FIELD_DESCRIPTOR_POINTER_FROM_S4(sfielddesc);

	if (!field_desc->is_extension()) {
		Rprintf("Field is not an extension! tag = %d type = %s\n",
			field_desc->number(), field_desc->type_name());
		return R_NilValue;
	}

	ref->ClearField(message, field_desc);
	Rprintf("in set repeated extension: length: %d\n", LENGTH(value));
	switch (field_desc->type()) {		// All floating-point and 64-bit types as R numerics.
		case TYPE_DOUBLE:
			for (int i = 0; i < LENGTH(value); i++) {
				ref->AddDouble(message, field_desc,
					       REAL(value)[i]);
			}
			break;
		case TYPE_FLOAT:
			for (int i = 0; i < LENGTH(value); i++) {
				ref->AddFloat(message, field_desc,
						      REAL(value)[i]);
			}
			break;
		case TYPE_INT64:
			for (int i = 0; i < LENGTH(value); i++) {
				ref->AddInt64(message, field_desc,
					      REAL(value)[i]);
			}
			break;
		case TYPE_UINT64:
			for (int i = 0; i < LENGTH(value); i++) {
				  ref->AddUInt64(message, field_desc,
						 REAL(value)[i]);
			}
			break;
		case TYPE_INT32:
			for (int i = 0; i < LENGTH(value); i++) {
				ref->AddInt32(message, field_desc,
					      INTEGER(value)[i]);
			}
			break;
		case TYPE_UINT32:
			for (int i = 0; i < LENGTH(value); i++) {
				ref->AddUInt32(message, field_desc,
					       INTEGER(value)[i]);
			}
			break;
		case TYPE_BOOL:
			for (int i = 0; i < LENGTH(value); i++) {
				ref->AddBool(message, field_desc,
					     LOGICAL(value)[i]);
			}
			break;
		case TYPE_STRING:
			for (int i = 0; i < LENGTH(value); i++) {
				ref->AddString(message, field_desc,
					       CHAR(STRING_ELT(value, i)));
			}
			break;
// TODO(mstokely): support enums, messages.
// Check value is an EnumValueDescriptor first.
//		case TYPE_ENUM:
//			ref->SetEnum(message, field_desc, value);
//			break;
		default:
			printf("Not implemented yet");
	}

	return R_NilValue;
}

RcppExport SEXP getExtension( SEXP pointer, SEXP sfielddesc){
        /* grab the Message pointer */
        const GPB::Message* message = GET_MESSAGE_POINTER_FROM_XP(pointer) ;
        const Reflection * ref = message->GetReflection() ;
        GPB::FieldDescriptor* field_desc =
		GET_FIELD_DESCRIPTOR_POINTER_FROM_S4(sfielddesc);

        if (!field_desc->is_extension()) {
		Rprintf("Field is not an extension! tag = %d type = %s\n",
			field_desc->number(), field_desc->type_name());
		return R_NilValue;
        }
	if (!ref->HasField(*message, field_desc)) {
		return R_NilValue;
        }

	switch (field_desc->type()) {
          case TYPE_DOUBLE:
		return(Rcpp::wrap( ref->GetDouble(*message, field_desc) ));
          case TYPE_FLOAT:
		return(Rcpp::wrap( ref->GetFloat(*message, field_desc) ));
          case TYPE_INT64:
		return(Rcpp::wrap( ref->GetInt64(*message, field_desc) ));
          case TYPE_UINT64:
		return(Rcpp::wrap( ref->GetUInt64(*message, field_desc) ));
          case TYPE_INT32:
		return(Rcpp::wrap( ref->GetInt32(*message, field_desc) ));
          case TYPE_UINT32:
		return(Rcpp::wrap( ref->GetUInt32(*message, field_desc) ));
          case TYPE_BOOL:
		return(Rcpp::wrap( ref->GetBool(*message, field_desc) ));
          case TYPE_STRING:
		return(Rcpp::wrap( ref->GetString(*message, field_desc) ));
          default:
		printf("Not implemented yet");
        }
        return R_NilValue;
}

RcppExport SEXP getExtensionRepeated( SEXP pointer, SEXP sfielddesc){
        /* grab the Message pointer */
        const GPB::Message* message = GET_MESSAGE_POINTER_FROM_XP(pointer) ;
        const Reflection * ref = message->GetReflection() ;
        GPB::FieldDescriptor* field_desc =
		GET_FIELD_DESCRIPTOR_POINTER_FROM_S4(sfielddesc);

        if (!field_desc->is_extension()) {
		Rprintf("Field is not an extension! tag = %d type = %s\n",
			field_desc->number(), field_desc->type_name());
		return R_NilValue;
        }
	if (ref->FieldSize(*message, field_desc) < 1) {
		return R_NilValue;
        }

    	switch( GPB::FieldDescriptor::TypeToCppType(field_desc->type()) ){
	  case CPPTYPE_DOUBLE:
			return Rcpp::wrap( RepeatedFieldImporter<double>(ref,
								 *message,
								 field_desc));
	  case CPPTYPE_FLOAT:
			return Rcpp::wrap( RepeatedFieldImporter<float>(ref,
								 *message,
								 field_desc));
  	  case CPPTYPE_INT32:
		return Rcpp::wrap( RepeatedFieldImporter<int32>(ref,
								*message,
								field_desc));
	  case CPPTYPE_UINT32:
		return Rcpp::wrap( RepeatedFieldImporter<uint32>(ref,
								*message,
								field_desc));
	  case CPPTYPE_INT64:
		return Rcpp::wrap( RepeatedFieldImporter<int64>(ref,
								*message,
								field_desc));
	  case CPPTYPE_UINT64:
		return Rcpp::wrap( RepeatedFieldImporter<uint64>(ref,
								*message,
								field_desc));
	  case CPPTYPE_BOOL:
		return Rcpp::wrap( RepeatedFieldImporter<bool>(ref,
							       *message,
							       field_desc));
          default:
		printf("Not implemented yet");
        }
        return R_NilValue;
}

}  // namespace rprotobuf
