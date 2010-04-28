#include "rprotobuf.h"

namespace rprotobuf{

/**
 * @param xp external pointer to a Descriptor
 * @return the descriptor as an R list
 */
RCPP_FUNCTION_1( Rcpp::List, as_list_descriptor, Rcpp::XPtr<GPB::Descriptor> desc ){
	
 	Rcpp::CharacterVector names = getDescriptorMemberNames(desc) ; 
	int n = names.size() ;
	int nfields = desc->field_count() ;
	int ntypes  = desc->nested_type_count() ;
	int nenums  = desc->enum_type_count() ;
	
	Rcpp::List res(n); 
	int i=0;
	int j=0; 
	for( i=0; i<nfields; j++, i++){
		res[j] = S4_FieldDescriptor( desc->field(i) ); 
	}
	for( i=0; i<ntypes; j++, i++){
		res[j] = S4_Descriptor( desc->nested_type(i) ); 
	}
	for( i=0; i<nenums; j++, i++){
		res[j] = S4_EnumDescriptor( desc->enum_type(i) ); 
	}
	res.names() = names ;
	
	return res; 
}


/**
 * @param xp external pointer to a Descriptor
 * @return the descriptor as an R list
 */
RCPP_FUNCTION_1( Rcpp::IntegerVector, as_list_enum_descriptor, Rcpp::XPtr<GPB::EnumDescriptor> d ){
	
	int n = d->value_count() ;
	Rcpp::IntegerVector values(n) ;
	Rcpp::CharacterVector names(n) ;
	
	for( int i=0; i<n; i++){
		const GPB::EnumValueDescriptor* value_d = d->value(i) ;
		values[i] = value_d->number() ;
		names[i]  = value_d->name() ;
	}
	values.names() = names ;
	return values; 
}


/**
 * @param xp (GPB::FileDescriptor*) external pointer
 * @return the descriptor as an R list
 */
RCPP_FUNCTION_1( Rcpp::List, as_list_file_descriptor, Rcpp::XPtr<GPB::FileDescriptor> desc ){

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

/**
 * @param xp (GPB::ServiceDescriptor*) external pointer
 * @return the descriptor as an R list
 */
RCPP_FUNCTION_1( Rcpp::List, as_list_service_descriptor, Rcpp::XPtr<GPB::ServiceDescriptor> desc ){
	
#ifdef RPB_DEBUG
Rprintf( "<as_list_service_descriptor>\n" ) ;
#endif

	Rcpp::CharacterVector names = getServiceDescriptorMethodNames(desc) ; 
	int n = names.size() ;
	
	Rcpp::List res(n); 
	for( int i=0; i<n; i++){
		res[i] = S4_MethodDescriptor( desc->method(i) ); 
	}
	res.names() = names ;
	
#ifdef RPB_DEBUG
Rprintf( "</as_list_service_descriptor>\n" ) ;
#endif
	return res; 
}



} // namespace rprotobuf

