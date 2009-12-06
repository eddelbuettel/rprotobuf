#include "rprotobuf.h"

namespace rprotobuf{

/**
 * returns the field names of the message
 *
 * @param xp external pointer to a Message
 *
 * @return field names, as an R character vector (STRSXP)
 */
SEXP getMessageFieldNames( SEXP xp ){
	
	/* grab the Message pointer */
	GPB::Message* message = (GPB::Message*)EXTPTR_PTR(xp) ;
	
	/* the message descriptor */
	const GPB::Descriptor* desc = message->GetDescriptor() ;
	
	int nfields = desc->field_count() ; 
	SEXP res = PROTECT( Rf_allocVector(STRSXP, nfields) ) ;
	int i=0; 
	while( i<nfields){
		SET_STRING_ELT( res, i, Rf_mkChar( desc->field(i)->name().c_str() ) ) ;
		i++;
	}
	UNPROTECT(1); 
	return( res );
	
}

/**
 * returns the names of the members contained in the descriptor
 * (nested types, enums, fields)
 *
 * @param xp external pointer to a Descriptor
 *
 * @return member names, as an R character vector (STRSXP)
 */
SEXP getDescriptorMemberNames( SEXP xp ){
	
	/* the message descriptor */
	GPB::Descriptor* desc = (GPB::Descriptor*)EXTPTR_PTR(xp) ;
	
	int nfields = desc->field_count() ;
	int ntypes  = desc->nested_type_count() ;
	int nenums  = desc->enum_type_count() ;
	
	SEXP res = PROTECT( Rf_allocVector(STRSXP, nfields + ntypes + nenums ) ) ;
	int i=0;
	int j=0; 
	while( i<nfields){
		SET_STRING_ELT( res, j, Rf_mkChar( desc->field(i)->name().c_str() ) ) ;
		i++; 
		j++;
	}
	i=0; 
	while( i<ntypes){
		SET_STRING_ELT( res, j, Rf_mkChar( desc->nested_type(i)->name().c_str() ) ) ;
		i++; 
		j++;
	}
	i = 0; 
	while( i<nenums){
		SET_STRING_ELT( res, j, Rf_mkChar( desc->enum_type(i)->name().c_str() ) ) ;
		i++; 
		j++;
	}
	
	UNPROTECT(1); 
	return( res );
}



/**
 * returns the names of the "members" contained in the 
 * file descriptor (message types, enum types, fields)
 *
 * @param xp (GPB::FileDescriptor*) external pointer
 *
 * @return member names, as an R character vector (STRSXP)
 */
SEXP getFileDescriptorMemberNames( SEXP xp ){
	
	/* the message descriptor */
	GPB::FileDescriptor* desc = (GPB::FileDescriptor*)EXTPTR_PTR(xp) ;
	
	int ntypes  = desc->message_type_count() ;
	int nenums  = desc->enum_type_count() ;
	int nserv   = desc->service_count() ;
	
	SEXP res = PROTECT( Rf_allocVector(STRSXP, ntypes + nenums + nserv ) ) ;
	int i=0;
	int j=0; 
	while( i<ntypes){
		SET_STRING_ELT( res, j, Rf_mkChar( desc->message_type(i)->name().c_str() ) ) ;
		i++; 
		j++;
	}
	i=0; 
	while( i<nenums){
		SET_STRING_ELT( res, j, Rf_mkChar( desc->enum_type(i)->name().c_str() ) ) ;
		i++; 
		j++;
	}
	i = 0; 
	while( i<nserv){
		SET_STRING_ELT( res, j, Rf_mkChar( desc->service(i)->name().c_str() ) ) ;
		i++; 
		j++;
	}
	
	UNPROTECT(1); /* res */
	return( res );
}



/**
 * returns the names of the members contained in the descriptor
 * (nested types, enums, fields)
 *
 * @param xp external pointer to a Descriptor
 *
 * @return member names, as an R character vector (STRSXP)
 */
SEXP getEnumDescriptorConstantNames( SEXP xp){
	
	GPB::EnumDescriptor* d = (GPB::EnumDescriptor*)EXTPTR_PTR(xp) ;
	
	int n = d->value_count() ;
	SEXP names = PROTECT( Rf_allocVector( STRSXP, n ) );
	for( int i=0; i<n; i++){
		SET_STRING_ELT( names, i, Rf_mkChar(d->value(i)->name().c_str() ) ) ;
	}
	UNPROTECT(1) ; /* names */
	return names ;
	
}


/**
 * returns the names of the methods contained in the 
 * service descriptor
 *
 * @param xp (GPB::ServiceDescriptor*) external pointer
 *
 * @return method names, as an R character vector (STRSXP)
 */
SEXP getServiceDescriptorMethodNames( SEXP xp ){
	
	/* the message descriptor */
	GPB::ServiceDescriptor* desc = (GPB::ServiceDescriptor*)EXTPTR_PTR(xp) ;
	
	int nmeths  = desc->method_count() ;

	SEXP res = PROTECT( Rf_allocVector(STRSXP, nmeths ) ) ;
	int i=0;
	int j=0; 
	while( i<nmeths){
		SET_STRING_ELT( res, j, Rf_mkChar( desc->method(i)->name().c_str() ) ) ;
		i++; 
		j++;
	}
	
	UNPROTECT(1); /* res */
	return( res );
}


} // namespace rprotobuf

