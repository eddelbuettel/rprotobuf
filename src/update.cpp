#include "rprotobuf.h"

namespace rprotobuf{

SEXP update_message( SEXP xp, SEXP list ){
	
#ifdef RPB_DEBUG
Rprintf( "<update_message>\n" ) ;
#endif
	
	SEXP names = Rf_getAttrib(list, Rf_install("names") ) ;
	
	int n = LENGTH(list);
	//char* what ;
	for( int i=0; i<n; i++){
		setMessageField( xp, 
			Rf_mkString( CHAR( STRING_ELT( names, i) ) ), 
			VECTOR_ELT(list, i) ); 
	}
	

#ifdef RPB_DEBUG
Rprintf( "</update_message>\n" ) ;
#endif
	
	return( R_NilValue ); 
}

} // namespace rprotobuf

