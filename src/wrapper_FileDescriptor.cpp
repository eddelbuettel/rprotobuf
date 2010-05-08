#include "rprotobuf.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(FileDescriptor__,__NAME__)

RCPP_XP_METHOD_0( METHOD(as_character)       , GPB::FileDescriptor      , DebugString) ;

RCPP_FUNCTION_1(S4_FileDescriptor, METHOD(as_Message), Rcpp::XPtr<GPB::FileDescriptor> d ){
	GPB::FileDescriptorProto* message = new GPB::FileDescriptorProto() ; 
	d->CopyTo( message ); 
	return message ;
}

/**
 * @param xp (GPB::FileDescriptor*) external pointer
 * @return the descriptor as an R list
 */
RCPP_FUNCTION_1( Rcpp::List, METHOD(as_list), Rcpp::XPtr<GPB::FileDescriptor> desc ){

#ifdef RPB_DEBUG
Rprintf( "<as_list_file_descriptor>\n" ) ;
#endif
	
	Rcpp::CharacterVector names = getFileDescriptorMemberNames(desc) ; 
	int n = names.size() ;
	int ntypes    = desc->message_type_count() ;
	int nenums    = desc->enum_type_count() ;
	int nserv     = desc->service_count() ;
	
	Rcpp::List res( n ); 
	int i=0;
	int j=0; 
	for( i=0; i<ntypes; j++, i++){
		res[j] = S4_Descriptor( desc->message_type(i) ) ; 
	}
	for( i=0; i<nenums; j++, i++){
		res[j] = S4_EnumDescriptor( desc->enum_type(i) ); 
	}
	for( i=0; i<nserv; j++, i++){
		res[j] = S4_ServiceDescriptor( desc->service(i) ); 
	}
	res.names() = names ;
	
#ifdef RPB_DEBUG
Rprintf( "</as_list_file_descriptor>\n" ) ;
#endif
	return res; 
}

#undef METHOD

} // namespace rprotobuf
