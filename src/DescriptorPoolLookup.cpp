#include "rprotobuf.h"
#include "DescriptorPoolLookup.h"

namespace rprotobuf{
	
	void DescriptorPoolLookup::add( const std::string& element){
		elements.insert( element ); 
	}
	
	bool DescriptorPoolLookup::contains( const std::string& element ){
		return elements.find( element ) != elements.end() ;
	}
	
	SEXP DescriptorPoolLookup::getElements(){
		/* return(RcppSexp(elements).asSexp()); */
		SEXP res = PROTECT( Rf_allocVector( STRSXP, elements.size() ) ) ;
		std::set<std::string>::iterator it = elements.begin() ;
		int i=0; 
		while( it != elements.end() ){
			SET_STRING_ELT( res, i, Rf_mkChar( it->c_str() ) ) ;
			it++ ;
			i++;
		}
		UNPROTECT(1) ; /* res */
		return res ;
	}
	
	std::set<std::string> DescriptorPoolLookup::elements ;
	RWarningErrorCollector DescriptorPoolLookup::error_collector ;
	RSourceTree DescriptorPoolLookup::source_tree ;
	GPB::compiler::Importer DescriptorPoolLookup::importer(&source_tree, &error_collector) ;
	GPB::DynamicMessageFactory DescriptorPoolLookup::message_factory(importer.pool()) ;
	
	void DescriptorPoolLookup::importProtoFiles(SEXP files, SEXP dirs ){
		source_tree.addDirectories( dirs ) ;
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
		// source_tree.removeDirectories( dirs ) ;
	}
	
	const GPB::DescriptorPool* DescriptorPoolLookup::pool(){
		return importer.pool() ;
	}
	
	const GPB::DynamicMessageFactory* DescriptorPoolLookup::factory(){
		return &message_factory ;
	}
	
	
} // namespace rprotobuf
