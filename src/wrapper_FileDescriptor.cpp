#include "rprotobuf.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(FileDescriptor__,__NAME__)

RCPP_XP_METHOD_0( METHOD(as_character)       , GPB::FileDescriptor      , DebugString) ;

RCPP_FUNCTION_1(S4_Message, METHOD(as_Message), Rcpp::XPtr<GPB::FileDescriptor> d ){
	GPB::FileDescriptorProto* message = new GPB::FileDescriptorProto() ; 
	d->CopyTo( message ); 
	return S4_Message( message ) ;
}


RCPP_FUNCTION_1( Rcpp::CharacterVector, METHOD(getMemberNames), Rcpp::XPtr<GPB::FileDescriptor> desc ){
	int ntypes  = desc->message_type_count() ;
	int nenums  = desc->enum_type_count() ;
	int nserv   = desc->service_count() ;
	
	Rcpp::CharacterVector res( ntypes + nenums + nserv ) ;
	int i=0;
	int j=0; 
	while( i<ntypes){
		res[j] = desc->message_type(i)->name() ;
		i++; 
		j++;
	}
	i=0; 
	while( i<nenums){
		res[j] = desc->enum_type(i)->name() ;
		i++; 
		j++;
	}
	i = 0; 
	while( i<nserv){
		res[j] = desc->service(i)->name() ;
		i++; 
		j++;
	}
	return res ;
	
}

/**
 * @param xp (GPB::FileDescriptor*) external pointer
 * @return the descriptor as an R list
 */
RCPP_FUNCTION_1( Rcpp::List, METHOD(as_list), Rcpp::XPtr<GPB::FileDescriptor> desc ){
	int ntypes    = desc->message_type_count() ;
	int nenums    = desc->enum_type_count() ;
	int nserv     = desc->service_count() ;
	int n = ntypes + nenums + nserv ;
	
	Rcpp::CharacterVector names(n) ; 
	Rcpp::List res( n ); 
	int i=0;
	int j=0; 
	for( i=0; i<ntypes; j++, i++){
		res[j] = S4_Descriptor( desc->message_type(i) ) ;
		names[j] = desc->message_type(i)->name() ;
	}
	for( i=0; i<nenums; j++, i++){
		res[j] = S4_EnumDescriptor( desc->enum_type(i) ); 
		names[j] = desc->enum_type(i)->name() ;
	}
	for( i=0; i<nserv; j++, i++){
		res[j] = S4_ServiceDescriptor( desc->service(i) );
		names[j] = desc->service(i)->name() ;
	}
	res.names() = names ;
	return res; 
}

RCPP_FUNCTION_1( std::string, METHOD(name), Rcpp::XPtr<GPB::EnumDescriptor> d ){
	return d->full_name() ;
}

#undef METHOD

} // namespace rprotobuf
