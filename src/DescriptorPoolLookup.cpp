#include "rprotobuf.h"
#include "DescriptorPoolLookup.h"

namespace rprotobuf{
	
	void DescriptorPoolLookup::add( std::string element){
		if( !contains( element ) ){
			elements.push_back( element ) ;
		}
	}
	
	bool DescriptorPoolLookup::contains( std::string element ){
		/* should use binary_search */
		for( vector<string>::const_iterator iter = elements.begin(); iter != elements.end(); ++iter ) {
			if( iter->compare( element ) == 0){
				return 1 ;
			}
		}
		return 0; 
	}
	
	/* this should really be in Rcpp somewhere */
	SEXP DescriptorPoolLookup::getElements(){
		
		int size = elements.size() ;
		
		SEXP res = PROTECT( Rf_allocVector( STRSXP, size ) ) ;
		
		int i =0; 
		for( vector<string>::const_iterator iter = elements.begin(); iter != elements.end(); ++iter, ++i ) {
			SET_STRING_ELT( res, i, Rf_mkChar( iter->c_str() ) ) ;
		}
		
		UNPROTECT(1) ; /* size */
		return res ;
	}
	
	std::vector<std::string> DescriptorPoolLookup::elements ;
	
} // namespace rprotobuf
