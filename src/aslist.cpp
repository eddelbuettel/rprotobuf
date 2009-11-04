#include "rprotobuf.h"

namespace rprotobuf{

/**
 * @param xp external pointer to a Message
 * @return the message as an R list
 */
SEXP as_list_message( SEXP xp){
	
#ifdef RPB_DEBUG
Rprintf( "<as_list_message>\n" ) ;
#endif

	/* grab the Message pointer */
    //Message* message = (Message*)EXTPTR_PTR(xp) ;
	
	SEXP fieldNames = PROTECT( getMessageFieldNames(xp) ) ;
	int nf = LENGTH( fieldNames ); 
	SEXP val = PROTECT( Rf_allocVector(VECSXP, LENGTH(fieldNames) ) ) ; 
	for( int i=0; i<nf; i++){
		/* TODO: do not do mkString(char(string_elt))) */
		SET_VECTOR_ELT( val, i, getMessageField( xp, Rf_mkString(CHAR(STRING_ELT(fieldNames, i)) )) ) ; 
	}
	Rf_setAttrib( val, Rf_install("names"), fieldNames) ;
	UNPROTECT(2); /* val, fieldNames */
	
#ifdef RPB_DEBUG
Rprintf( "</as_list_message>\n" ) ;
#endif

	return val ;
}

/**
 * @param xp external pointer to a Descriptor
 * @return the descriptor as an R list
 */
SEXP as_list_descriptor( SEXP xp){
	
#ifdef RPB_DEBUG
Rprintf( "<as_list_descriptor>\n" ) ;
#endif
	
	Descriptor* desc = (Descriptor*) EXTPTR_PTR(xp) ;
	
	SEXP names = PROTECT( getDescriptorMemberNames(xp) ) ; 
	int n = LENGTH(names) ;
	int nfields = desc->field_count() ;
	int ntypes  = desc->nested_type_count() ;
	int nenums  = desc->enum_type_count() ;
	
	SEXP res = PROTECT( Rf_allocVector( VECSXP, n ) ); 
	int i=0;
	int j=0; 
	for( i=0; i<nfields; j++, i++){
		SET_VECTOR_ELT( res, j, new_RS4_FieldDescriptor( desc->field(i) ) ); 
	}
	for( i=0; i<ntypes; j++, i++){
		SET_VECTOR_ELT( res, j, new_RS4_Descriptor( desc->nested_type(i) ) ); 
	}
	for( i=0; i<nenums; j++, i++){
		SET_VECTOR_ELT( res, j, new_RS4_EnumDescriptor( desc->enum_type(i) ) ); 
	}
	Rf_setAttrib( res, Rf_install("names"), names) ;
	UNPROTECT(2); /* res, names */
	
#ifdef RPB_DEBUG
Rprintf( "</as_list_descriptor>\n" ) ;
#endif
	return res; 
}


/**
 * @param xp external pointer to a Descriptor
 * @return the descriptor as an R list
 */
SEXP as_list_enum_descriptor( SEXP xp){
#ifdef RPB_DEBUG
Rprintf( "<as_list_enum_descriptor>\n" ) ;
#endif

	EnumDescriptor* d = (EnumDescriptor*)EXTPTR_PTR(xp) ;
	
	int n = d->value_count() ;
	SEXP values = PROTECT( Rf_allocVector( INTSXP, n ) ) ;
	SEXP names  = PROTECT( Rf_allocVector( STRSXP, n ) ) ;
	
	for( int i=0; i<n; i++){
		const EnumValueDescriptor* value_d = d->value(i) ;
		INTEGER(values)[i] = value_d->number() ;
		/* FIXME: should we copy the string */
		SET_STRING_ELT( names, i, Rf_mkChar(value_d->name().c_str()) ) ;
	}
	
	Rf_setAttrib( values, Rf_install("names"), names ) ;
	UNPROTECT(2); /* names, values */
#ifdef RPB_DEBUG
Rprintf( "</as_list_enum_descriptor>\n" ) ;
#endif
	return values; 
	
}

} // namespace rprotobuf

