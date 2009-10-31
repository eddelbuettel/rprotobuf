#include "rprotobuf.h"

namespace org{
namespace rproject{
namespace rprotobuf{
namespace{

/**
 * create a raw vector that contains the content of the serialized 
 * message
 *
 * @param xp xternal pointer to the message
 */
SEXP getMessagePayload( SEXP xp ){
	           
	SEXP payload = PROTECT( Rf_allocVector( RAWSXP, 0) ); 
	/* TODO: implement */
	Rf_warning( "serialization not implemented yet" ) ;
	
	UNPROTECT(1); /* payload */ 
	return( payload ) ;
	
}
	
	
} // namespace
} // namespace rprotobuf
} // namespace rproject
} // namespace org

