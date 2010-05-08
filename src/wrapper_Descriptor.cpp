#include "rprotobuf.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(Descriptor__,__NAME__)	

RCPP_XP_METHOD_0( METHOD(as_character), GPB::Descriptor          , DebugString) ;

/**
 * @param xp external pointer to a Descriptor
 * @return the descriptor as an R list
 */
RCPP_FUNCTION_1( Rcpp::List, METHOD(as_lis), Rcpp::XPtr<GPB::Descriptor> desc ){
	
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

RCPP_FUNCTION_1(S4_Message, METHOD(as_Message) , Rcpp::XPtr<GPB::Descriptor> d ){
	GPB::DescriptorProto* message = new GPB::DescriptorProto() ; 
	d->CopyTo( message ); 
	return message  ;
}


#undef METHOD

} // namespace rprotobuf
