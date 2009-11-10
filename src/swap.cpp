#include "rprotobuf.h"

namespace rprotobuf{

	SEXP message_swap_fields(SEXP xp, SEXP field, SEXP left, SEXP right ){
		
		Message* m = GET_MESSAGE_POINTER_FROM_XP( xp ) ; 
		FieldDescriptor* field_desc = getFieldDescriptor( m, field ) ;
		const Reflection* ref = m->GetReflection(); 
		if( ! field_desc->is_repeated() ){
			Rf_error( "swap can only be used with repeated fields" ) ; 
		}
		int n = LENGTH(left); /* we know that length(left) == length(right) */ 
		for( int i=0; i<n; i++){
			ref->SwapElements(m, field_desc, GET_int(left, i) , GET_int(right,i) ) ;
		}
		return( R_NilValue ); 
	}

} // namespace rprotobuf
