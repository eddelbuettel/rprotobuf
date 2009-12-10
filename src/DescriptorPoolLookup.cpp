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
		for( std::vector<std::string>::const_iterator iter = elements.begin(); iter != elements.end(); ++iter ) {
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
		for( std::vector<std::string>::const_iterator iter = elements.begin(); iter != elements.end(); ++iter, ++i ) {
			SET_STRING_ELT( res, i, Rf_mkChar( iter->c_str() ) ) ;
		}
		
		UNPROTECT(1) ; /* size */
		return res ;
	}
	
	std::vector<std::string> DescriptorPoolLookup::elements ;
	
	RWarningErrorCollector DescriptorPoolLookup::error_collector ;
	RSourceTree DescriptorPoolLookup::source_tree ;
	GPB::compiler::Importer DescriptorPoolLookup::importer(&source_tree, &error_collector) ;
	GPB::DynamicMessageFactory DescriptorPoolLookup::message_factory(importer.pool()) ;
	
	void DescriptorPoolLookup::importProtoFiles(SEXP files){
		int n = LENGTH(files) ;
		for( int j=0; j < n; j++ ){
			const GPB::FileDescriptor* file_desc = importer.Import( CHAR(STRING_ELT(files, j)) );
		    int ntypes = file_desc->message_type_count() ;
		    for( int i=0; i<ntypes; i++){
		    	const GPB::Descriptor* desc = file_desc->message_type( i ) ;
		    	add( desc->full_name() ); 
		    	/* should we bother recursing ? */
		    	/* TODO: also add top level services */
		    }
		}
	}
	
	const GPB::DescriptorPool* DescriptorPoolLookup::pool(){
		return importer.pool() ;
	}
	
	const GPB::DynamicMessageFactory* DescriptorPoolLookup::factory(){
		return &message_factory ;
	}
	
	
} // namespace rprotobuf
