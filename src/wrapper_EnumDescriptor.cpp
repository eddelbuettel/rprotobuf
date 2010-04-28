#include "rprotobuf.h"

namespace rprotobuf{

	RCPP_XP_METHOD_0(EnumDescriptor_length      ,GPB::EnumDescriptor,value_count)
	RCPP_XP_METHOD_0(EnumDescriptor__value_count,GPB::EnumDescriptor,value_count)
	
	RCPP_XP_METHOD_CAST_1(EnumDescriptor_getValueByIndex , GPB::EnumDescriptor , value            , S4_EnumValueDescriptor ) 
	RCPP_XP_METHOD_CAST_1(EnumDescriptor_getValueByNumber, GPB::EnumDescriptor , FindValueByNumber, S4_EnumValueDescriptor )
	RCPP_XP_METHOD_CAST_1(EnumDescriptor_getValueByName  , GPB::EnumDescriptor , FindValueByName  , S4_EnumValueDescriptor )
	
} // namespace rprotobuf
