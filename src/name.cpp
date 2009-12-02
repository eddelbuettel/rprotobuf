#include "rprotobuf.h"

namespace rprotobuf{

	/** 
	 * Retrieves the name, or the full name of a message descriptor
	 *
	 * @param xp (Descriptor*) external pointer
	 * @param full if TRUE the full name is returned, including the scope
	 */
	SEXP name_descriptor( SEXP xp, SEXP full ){
#ifdef RPB_DEBUG
Rprintf( "<name_descriptor>\n" ) ;
#endif
	
	Descriptor* d = (Descriptor*)EXTPTR_PTR(xp) ;
	SEXP res = PROTECT( Rf_mkString( 
		LOGICAL(full)[0] ? d->full_name().c_str() : d->name().c_str() ) );
	UNPROTECT(1); /* res */
	
#ifdef RPB_DEBUG
Rprintf( "</name_descriptor>\n" ) ;
#endif
	
	return res ;
}

	/** 
	 * Retrieves the name, or the full name of a field descriptor
	 *
	 * @param xp (FieldDescriptor*) external pointer
	 * @param full if TRUE the full name is returned, including the scope
	 */
	SEXP name_field_descriptor( SEXP xp, SEXP full ){
#ifdef RPB_DEBUG
Rprintf( "<name_field_descriptor>\n" ) ;
#endif
	
	FieldDescriptor* d = (FieldDescriptor*)EXTPTR_PTR(xp) ;
	SEXP res = PROTECT( Rf_mkString( 
		LOGICAL(full)[0] ? d->full_name().c_str() : d->name().c_str() ) );
	UNPROTECT(1); /* res */
	
#ifdef RPB_DEBUG
Rprintf( "</name_field_descriptor>\n" ) ;
#endif
	
	return res ;
}



} // namespace rprotobuf

