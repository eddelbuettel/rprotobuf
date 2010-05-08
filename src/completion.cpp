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
	Rcpp::XPtr<GPB::Message> message(xp); 
	return getMessageFieldNames(message);
}	

SEXP getMessageFieldNames_( const Rcpp::XPtr<GPB::Message>& message ){
	
	/* the message descriptor */
	const GPB::Descriptor* desc = message->GetDescriptor() ;
	
	int nfields = desc->field_count() ; 
	Rcpp::CharacterVector res(nfields) ;
	for(int i=0; i<nfields; i++){
		res[i] = desc->field(i)->name() ;
	}
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


} // namespace rprotobuf

