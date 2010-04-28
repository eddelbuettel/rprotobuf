#include "rprotobuf.h"

namespace rprotobuf{

/**
 * The number of fields the message has. A field counts in these two situations :
 * - it is repeated and the array size is greater than 0
 * - it is not repeated and the message has it
 *
 * @param xp external pointer to the Message
 */
RCPP_FUNCTION_1(int, get_message_length, Rcpp::XPtr<GPB::Message> message){

RPB_DEBUG_BEGIN(get_message_length)

	const GPB::Descriptor* desc = message->GetDescriptor(); 
	const GPB::Reflection * ref = message->GetReflection() ;
	
	int nfields = desc->field_count() ;
	
	int res = 0; 
	
	for( int i=0; i<nfields; i++){
		const GPB::FieldDescriptor* field_desc = desc->field( i ) ;
		if( field_desc->is_repeated() ){
			if( ref->FieldSize( *message, field_desc ) > 0 ){
				res++ ;
			}
		} else{
			if( ref->HasField( *message, field_desc ) ){
				res++ ;
			}
		}
	}
	
RPB_DEBUG_END(get_message_length)
	
	return res ;

}

} // namespace rprotobuf

