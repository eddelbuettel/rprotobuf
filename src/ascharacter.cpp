#include "rprotobuf.h"

namespace rprotobuf{

RCPP_XP_METHOD_0(as_character_enum_descriptor       , GPB::EnumDescriptor      , DebugString) ;
RCPP_XP_METHOD_0(as_character_field_descriptor      , GPB::FieldDescriptor     , DebugString) ;
RCPP_XP_METHOD_0(as_character_file_descriptor       , GPB::FileDescriptor      , DebugString) ;
RCPP_XP_METHOD_0(as_character_enum_value_descriptor , GPB::EnumValueDescriptor , DebugString) ;
RCPP_XP_METHOD_0(as_character_message               , GPB::Message             , DebugString) ;
RCPP_XP_METHOD_0(as_character_descriptor            , GPB::Descriptor          , DebugString) ;
RCPP_XP_METHOD_0(as_character_service_descriptor    , GPB::ServiceDescriptor   , DebugString) ;
RCPP_XP_METHOD_0(as_character_method_descriptor     , GPB::MethodDescriptor    , DebugString) ;


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

} // namespace rprotobuf

