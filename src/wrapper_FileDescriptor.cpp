#include "rprotobuf.h"
#include "RcppMacros.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(FileDescriptor__,__NAME__)

RPB_XP_METHOD_0( METHOD(as_character)       , GPB::FileDescriptor      , DebugString) ;

RPB_FUNCTION_1(S4_Message, METHOD(as_Message), Rcpp::XPtr<GPB::FileDescriptor> d ){
	GPB::FileDescriptorProto* message = new GPB::FileDescriptorProto() ; 
	d->CopyTo( message ); 
	return S4_Message( message ) ;
}


RPB_FUNCTION_1( Rcpp::CharacterVector, METHOD(getMemberNames), Rcpp::XPtr<GPB::FileDescriptor> desc ){
	int ntypes  = desc->message_type_count() ;
	int nenums  = desc->enum_type_count() ;
	int nserv   = desc->service_count() ;
	int nexts   = desc->extension_count() ;
	
	Rcpp::CharacterVector res( ntypes + nenums + nserv + nexts ) ;
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
	i = 0; 
	while( i<nexts){
		res[j] = desc->extension(i)->name() ;
		i++;
		j++;
	}
	return res ;
	
}

/**
 * @param xp (GPB::FileDescriptor*) external pointer
 * @return the descriptor as an R list
 */
RPB_FUNCTION_1( Rcpp::List, METHOD(as_list), Rcpp::XPtr<GPB::FileDescriptor> desc ){
	int ntypes    = desc->message_type_count() ;
	int nenums    = desc->enum_type_count() ;
	int nserv     = desc->service_count() ;
	int nexts     = desc->extension_count() ;
	int n = ntypes + nenums + nserv + nexts;
	
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
	for( i=0; i<nexts; j++, i++){
		res[j] = S4_FieldDescriptor( desc->extension(i) );
		// always use full names for extensions
		names[j] = desc->extension(i)->full_name() ;
	}
	res.names() = names ;
	return res; 
}

RPB_FUNCTION_1( std::string, METHOD(name), Rcpp::XPtr<GPB::FileDescriptor> desc ){
	return desc->name() ;
}

#undef METHOD

} // namespace rprotobuf
