#include "rprotobuf.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(Descriptor__,__NAME__)	

	RCPP_XP_METHOD_0(METHOD(as_character), GPB::EnumDescriptor      , DebugString) ;
	RCPP_XP_METHOD_0(METHOD(length)      ,GPB::EnumDescriptor,value_count)
	RCPP_XP_METHOD_0(METHOD(value_count) ,GPB::EnumDescriptor,value_count)
	
	RCPP_XP_METHOD_CAST_1(METHOD(getValueByIndex) , GPB::EnumDescriptor , value            , S4_EnumValueDescriptor ) 
	RCPP_XP_METHOD_CAST_1(METHOD(getValueByNumber), GPB::EnumDescriptor , FindValueByNumber, S4_EnumValueDescriptor )
	RCPP_XP_METHOD_CAST_1(METHOD(getValueByName)  , GPB::EnumDescriptor , FindValueByName  , S4_EnumValueDescriptor )

	RCPP_FUNCTION_1(S4_EnumDescriptor, METHOD(as_Message), Rcpp::XPtr<GPB::EnumDescriptor> d ){
		GPB::EnumDescriptorProto* message = new GPB::EnumDescriptorProto() ; 
		d->CopyTo( message ); 
		return message ;
	}
	
/**
 * Get the value of the enum called name
 *
 * @param xp external pointer to an EnumDescriptor
 * @param name the name of the enum
 * 
 * @param the value associated with the name
 */
RCPP_FUNCTION_2(int,get_value_of_enum, 
	Rcpp::XPtr<GPB::EnumDescriptor> d, std::string name){
	
	const GPB::EnumValueDescriptor* evd = d->FindValueByName(name) ;
    if( !evd ){
    	/* or maybe it should just be NA */
    	throwException( "cannot get the value", "UnknownEnumValueException" ) ;
    }
	return evd->number(); 
}



#undef METHOD

} // namespace rprotobuf
