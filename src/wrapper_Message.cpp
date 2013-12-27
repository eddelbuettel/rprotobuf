#include "rprotobuf.h"
#include "fieldtypes.h"
#include "RcppMacros.h"

#define SAME(x,y,tol) ( (tol==0.0 && x == y ) ||  ( ( (x-y)*(x-y) < tol*tol ) ? 1 : 0 ) ) 

namespace rprotobuf{

/* helpers */

/* this is only to be called for repeated fields */
int MESSAGE_GET_REPEATED_INT(GPB::Message* message,
			     GPB::FieldDescriptor* field_desc, int index ){
	BEGIN_RCPP
	const GPB::Reflection* ref = message->GetReflection() ; 
		
	switch( field_desc->type() ){
	case TYPE_INT32:
	case TYPE_SINT32:
	case TYPE_SFIXED32:
		return (int) ref->GetRepeatedInt32( *message, field_desc, index ) ;
	case TYPE_INT64:
	case TYPE_SINT64:
	case TYPE_SFIXED64:
		return (int) ref->GetRepeatedInt64( *message, field_desc, index ) ;
	case TYPE_UINT32:
	case TYPE_FIXED32:
		return (int) ref->GetRepeatedUInt32( *message, field_desc, index ) ;
	case TYPE_UINT64:
	case TYPE_FIXED64:
		return (int) ref->GetRepeatedUInt64( *message, field_desc, index ) ;
	case TYPE_ENUM:
		return ref->GetRepeatedEnum( *message, field_desc, index )->number() ;
	default:
		Rcpp_error("cannot cast to int");
	}
	VOID_END_RCPP
	return 0 ; // -Wall
}
	
/* this is only to be called for repeated fields */
double MESSAGE_GET_REPEATED_DOUBLE(GPB::Message* message,
				   GPB::FieldDescriptor* field_desc,
				   int index ){
	BEGIN_RCPP
	const GPB::Reflection* ref = message->GetReflection() ; 
		
	switch( field_desc->type() ){
	case TYPE_FLOAT:
		return (double) ref->GetRepeatedFloat( *message, field_desc, index ) ;
	case TYPE_DOUBLE:
		return (double) ref->GetRepeatedDouble( *message, field_desc, index ) ;
	default:
		Rcpp_error("cannot cast to double");
	}
	VOID_END_RCPP
	return 0; // -Wall
}

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(Message__,__NAME__)

/**
 * clone a message
 *
 * @param xp external pointer to a message
 * @return a new message, clone of the input message
 */
RPB_FUNCTION_1( S4_Message, METHOD(clone) , Rcpp::XPtr<GPB::Message> message ){
	/* cloning message as sheep */
	GPB::Message* sheep = message->New() ;
	sheep->CopyFrom( *message );
	
	return S4_Message( sheep ) ;
}

/**
 * TRUE if the message has the specified field name.
 * FALSE otherwise.
 *
 *
 * @param xp external pointer to the Message
 * @param name name of the field
 */
RPB_FUNCTION_2(bool, METHOD(field_exists), Rcpp::XPtr<GPB::Message> message, std::string name ){
	const GPB::Descriptor* desc = message->GetDescriptor(); 
	const GPB::FieldDescriptor* field_desc = desc->FindFieldByName( name ) ;
	return (field_desc != NULL);
}

/**
 * TRUE if the message has the field name and it is populated.
 * FALSE otherwise.
 *
 * @param xp external pointer to the Message
 * @param name name of the field
 */
RPB_FUNCTION_2(bool, METHOD(has_field), Rcpp::XPtr<GPB::Message> message, std::string name ){

	const GPB::Descriptor* desc = message->GetDescriptor(); 
	const GPB::FieldDescriptor* field_desc = desc->FindFieldByName( name ) ;
	
	bool res = false ;
	if( field_desc ){
		const GPB::Reflection * ref = message->GetReflection() ;
		if( field_desc->is_repeated() ){
			res = ref->FieldSize( *message, field_desc ) > 0 ;
		} else{
			res = ref->HasField( *message, field_desc ) ;
		}
	}
	return res ;
}


/**
 * Check if all required fields are set
 *
 * @param xp external pointer to the Message
 */
RPB_FUNCTION_1( bool, METHOD(is_initialized), Rcpp::XPtr<GPB::Message> message){
	return message->IsInitialized() ;
}


/** 
 * serialize a message to a file
 *
 * @param xp external pointer to a GPB::Message*
 * @param filename file name where to serialize
 */
RPB_FUNCTION_VOID_2( METHOD(serialize_to_file) , Rcpp::XPtr<GPB::Message> message, const char* filename){
	
	/* open the file in binary mode to write */
	/* we make sure in the R side that filename is the full path of the file */
	int file = open( filename, 
		O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0666); 
	
	/* using partial to allow partially filled messages */
	message->SerializePartialToFileDescriptor( file ) ;
	
	close( file ) ; 
}

/**
 * create a raw vector that contains the content of the serialized 
 * message
 *
 * @param xp xternal pointer to the message
 */
RPB_FUNCTION_1( Rcpp::RawVector, METHOD(get_payload), Rcpp::XPtr<GPB::Message> message ){

	/* create a raw vector of the appropriate size */
	int size = message->ByteSize() ;
	Rcpp::RawVector payload( size ) ;
	
	/* fill the array */
	message->SerializePartialToArray( payload.begin(), size ); 
	
	return( payload ) ;
}

RPB_XP_METHOD_VOID_0(METHOD(clear), GPB::Message, Clear )

/**
 * Clear a field of a message
 *
 * @param xp (GPB::Message*) external pointer
 * @param field name or tag of the field
 */
RPB_FUNCTION_VOID_2(METHOD(clear_field), Rcpp::XPtr<GPB::Message> m, SEXP field ){
	const GPB::FieldDescriptor* field_desc = getFieldDescriptor( m, field ) ;
	const GPB::Reflection* ref = m->GetReflection(); 
	ref->ClearField( m, field_desc ) ;
}


/**
 * @param xp external pointer to a Message
 * @return the message as an R list
 */
RPB_FUNCTION_1( Rcpp::List, METHOD(as_list), Rcpp::XPtr<GPB::Message> message ){
    
	const GPB::Descriptor* desc = message->GetDescriptor() ;
	int nf = desc->field_count() ;
	
	Rcpp::CharacterVector fieldNames(nf) ;
	Rcpp::List val( nf ) ;
	/* TODO: not use getMessageField */
	for( int i=0; i<nf; i++){
		const GPB::FieldDescriptor* fd = desc->field(i) ;
		val[i] = 
			getMessageField( message, Rcpp::CharacterVector::create( fd->name() ) ) ;
		fieldNames[i] = fd->name() ;
	}
	val.names() = fieldNames ;
	return val ;
}

/**
 * The number of fields the message has. A field counts in these two situations :
 * - it is repeated and the array size is greater than 0
 * - it is not repeated and the message has it
 *
 * @param xp external pointer to the Message
 */
RPB_FUNCTION_1(int, METHOD(length), Rcpp::XPtr<GPB::Message> message){
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
	return res ;
}

/**
 * The number of extensions the message has.
 *
 * @param xp external pointer to the Message
 */
RPB_FUNCTION_1(int, METHOD(num_extensions), Rcpp::XPtr<GPB::Message> message){
	const GPB::Reflection * ref = message->GetReflection() ;
	int nexts = 0;
	vector<const FieldDescriptor*> fields;
	ref->ListFields(*message, &fields);
	for (int i = 0; i < fields.size(); i++) {
	  if (fields[i]->is_extension()) {
	    nexts++;
	  }
	}
	return nexts ;
}

/**
 * Get the message descriptor of a Message
 * 
 * @param xp (GPB::Message*) external pointer
 * @return the descriptor, as a Descriptor R S4 object
 */
RPB_FUNCTION_1(S4_Descriptor, METHOD(descriptor), Rcpp::XPtr<GPB::Message> message ){
	return( message->GetDescriptor() ) ;
}

RPB_XP_METHOD_0( METHOD(as_character) , GPB::Message, DebugString) 
RPB_XP_METHOD_0( METHOD(bytesize), GPB::Message, ByteSize )

RPB_FUNCTION_2( int, METHOD(field_size), Rcpp::XPtr<GPB::Message> message, SEXP field  ){
	
	const GPB::FieldDescriptor* field_desc = getFieldDescriptor( message, field ) ;
	
	int res = 0 ;
	if( field_desc->is_repeated() ){
		res = message->GetReflection()->FieldSize(*message, field_desc ) ;
	} else{
		res = message->GetReflection()->HasField(*message, field_desc) ? 1: 0 ;
	}
	return res ;
}

RPB_FUNCTION_1( S4_FileDescriptor, METHOD(fileDescriptor), Rcpp::XPtr<GPB::Message> message ){
	return S4_FileDescriptor( message->GetDescriptor()->file() ) ; 
}


RPB_FUNCTION_VOID_3( METHOD(set_field_size), Rcpp::XPtr<GPB::Message> message, SEXP field, int target){
	
	const GPB::FieldDescriptor* field_desc = getFieldDescriptor( message, field ) ;
	const GPB::Reflection* ref = message->GetReflection() ;
	
	if( field_desc->is_repeated() ){
		int current = ref->FieldSize(*message, field_desc ) ;
		
		if( target == 0){
			ref->ClearField( message, field_desc );
		} else if( current > target ){
			while( current != target ){
				ref->RemoveLast( message, field_desc ) ;
				current-- ;
			}
		} else if( current == target ) {
			/* nothing to do */
		} else { /* current < target */
			
			while( current != target ){
			
				switch( field_desc->type() ){
						case TYPE_INT32:
    					case TYPE_SINT32:
    					case TYPE_SFIXED32:
    				        {
    				        	ref->AddInt32(message, field_desc, (int32)0 ) ;
    				        	break ;
    				        }
    					case TYPE_INT64:
						case TYPE_SINT64:
						case TYPE_SFIXED64:
    				        {
    				        	ref->AddInt64(message, field_desc, (int64)0 ) ;
    				        	break ;
    				        }
		    			case TYPE_UINT32:
    					case TYPE_FIXED32:
    						{
    							ref->AddUInt32(message, field_desc, (uint32)0 ) ;
    				        	break ;
    				        }
    					case TYPE_UINT64:
    					case TYPE_FIXED64:
    						{
    							ref->AddUInt32(message, field_desc, (uint64)0 ) ;
    				        	break ;
    						}
    				    case TYPE_DOUBLE:
    				    	{
    				    		ref->AddDouble(message, field_desc, (double)0.0 ) ;
    				    		break ;
    				    	}
    				    case TYPE_FLOAT:
    				    	{
    				    		ref->AddFloat(message, field_desc, (float)0.0 ) ;
    				    		break ;
    				    	}
    				    case TYPE_BOOL:
    				    	{
    				    		ref->AddBool(message, field_desc, (bool)0 ) ;
    				    		break ;
    				    	}
    				    case TYPE_STRING:
    				    case TYPE_BYTES:
    				    	{
    				    		ref->AddString(message, field_desc, "" ) ;
    							break ;
    				    	}
    				    case TYPE_MESSAGE:
    				    case TYPE_GROUP:
    				    	{
    				    		/* fill with the prototype for that message type */
    				    		Rf_error( "growing repeated messages not implemented yet, patches welcome" ) ;
    				    		break ;
    				    	}
    				    case TYPE_ENUM:
    				    	{ 
    				    		/* fill with the prototype for that message type */
    				    		Rf_error( "growing repeated enum not implemented yet, patches welcome" ) ;
    				    		break ;
    				    	}
    				} /* switch */
    			
    			current++ ;
    		} /* while */
			
			
		}
		
	} else{
		if( target == 0 ){
			if( ref->HasField( *message, field_desc ) ){
				ref->ClearField( message, field_desc );
			}
		} else {
			if( !ref->HasField( *message, field_desc ) ){
				switch( field_desc->type() ){
					case TYPE_INT32:
    				case TYPE_SINT32:
    				case TYPE_SFIXED32:
    			        {
    			        	ref->SetInt32(message, field_desc, (int32)0 ) ;
    			        	break ;
    			        }
    				case TYPE_INT64:
					case TYPE_SINT64:
					case TYPE_SFIXED64:
    			        {
    			        	ref->SetInt64(message, field_desc, (int64)0 ) ;
    			        	break ;
    			        }
		    		case TYPE_UINT32:
    				case TYPE_FIXED32:
    					{
    						ref->SetUInt32(message, field_desc, (uint32)0 ) ;
    			        	break ;
    			        }
    				case TYPE_UINT64:
    				case TYPE_FIXED64:
    					{
    						ref->SetUInt32(message, field_desc, (uint64)0 ) ;
    			        	break ;
    					}
    			    case TYPE_DOUBLE:
    			    	{
    			    		ref->SetDouble(message, field_desc, (double)0.0 ) ;
    			    		break ;
    			    	}
    			    case TYPE_FLOAT:
    			    	{
    			    		ref->SetFloat(message, field_desc, (float)0.0 ) ;
    			    		break ;
    			    	}
    			    case TYPE_BOOL:
    			    	{
    			    		ref->SetBool(message, field_desc, (bool)0 ) ;
    			    		break ;
    			    	}
    			    case TYPE_STRING:
    			    case TYPE_BYTES:
    			    	{
    			    		ref->SetString(message, field_desc, "" ) ;
    						break ;
    			    	}
    			    case TYPE_MESSAGE:
    			    case TYPE_GROUP:
    			    	{
    			    		/* fill with the prototype for that message type */
    			    		Rf_error( "not implemented yet, patches welcome" ) ;
    			    		break ;
    			    	}
    			    case TYPE_ENUM:
    			    	{ 
    			    		/* fill with the prototype for that message type */
    			    		Rf_error( "not implemented yet, patches welcome" ) ;
    			    		break ;
    			    	}
    				}
    			}
		}
	}
}

/**
 * returns the field names of the message
 *
 * @param xp external pointer to a Message
 *
 * @return field names, as an R character vector (STRSXP)
 */
RPB_FUNCTION_1( Rcpp::CharacterVector, METHOD(fieldNames), Rcpp::XPtr<GPB::Message> message){
	const GPB::Descriptor* desc = message->GetDescriptor() ;
	
	int nfields = desc->field_count() ; 
	Rcpp::CharacterVector res(nfields) ;
	for(int i=0; i<nfields; i++){
		res[i] = desc->field(i)->name() ;
	}
	return( res );
}

bool identical_messages_( GPB::Message* m1,  GPB::Message* m2, double tol ){
  BEGIN_RCPP
	const GPB::Descriptor* d1 = m1->GetDescriptor() ;
	const GPB::Descriptor* d2 = m2->GetDescriptor() ;
	
	/* first of all, check if this is the same message type */
	if( d1 != d2 ){
		return false ;
	}
	
	const GPB::Reflection* ref = m2->GetReflection() ;
	
	/* iterate field descriptors */
	int nf = d1->field_count() ;
	for( int i=0; i<nf; i++){
		const GPB::FieldDescriptor* field_desc = d1->field( i ) ;
		
		if( field_desc->is_repeated() ){
			
			/* test if the size differs */
			int fs = ref->FieldSize( *m1, field_desc) ;
			if( fs != ref->FieldSize( *m2, field_desc) ) return false ;
			
			/* test all items */
			switch( field_desc->type() ){
				case TYPE_INT32:
				case TYPE_SINT32:
				case TYPE_SFIXED32:
					{
						for( int j=0; j<fs; j++){
							if( ref->GetRepeatedInt32( *m1, field_desc, j ) != ref->GetRepeatedInt32( *m2, field_desc, j ) ) return false ; 
						}
						break ;
					}
				case TYPE_INT64:
				case TYPE_SINT64:
				case TYPE_SFIXED64:
					{
						for( int j=0; j<fs; j++){
							if( ref->GetRepeatedInt64( *m1, field_desc, j ) != ref->GetRepeatedInt64( *m2, field_desc, j ) ) return false ; 
						}
						break ;
					}
    			case TYPE_UINT32:
    			case TYPE_FIXED32:
    				{
    					for( int j=0; j<fs; j++){
							if( ref->GetRepeatedUInt32( *m1, field_desc, j ) != ref->GetRepeatedUInt32( *m2, field_desc, j ) ) return false ; 
						}
						break ;
    				}
    			case TYPE_UINT64:
    			case TYPE_FIXED64:
    				{
    					for( int j=0; j<fs; j++){
							if( ref->GetRepeatedUInt64( *m1, field_desc, j ) != ref->GetRepeatedUInt64( *m2, field_desc, j ) ) return false ; 
						}
						break ;	    					
    				}
    			case TYPE_DOUBLE:
    				{
    					for( int j=0; j<fs; j++){
							if( !SAME( ref->GetRepeatedDouble( *m1, field_desc, j ), ref->GetRepeatedDouble( *m2, field_desc, j ), tol) ) return false ; 
						}
						break ;	    					
    				}
    			case TYPE_FLOAT:
    				{
    					for( int j=0; j<fs; j++){
							if( !SAME( ref->GetRepeatedFloat( *m1, field_desc, j ), ref->GetRepeatedFloat( *m2, field_desc, j ), tol) ) return false ; 
						}
						break ;	    					
    				}
    			case TYPE_BOOL:
    				{
    					for( int j=0; j<fs; j++){
							if( ref->GetRepeatedBool( *m1, field_desc, j ) != ref->GetRepeatedBool( *m2, field_desc, j ) ) return false ; 
						}
						break ;	    					
    				}
				case TYPE_STRING:
    			case TYPE_BYTES:
    				{
    					for( int j=0; j<fs; j++){
							if( ref->GetRepeatedString( *m1, field_desc, j ) != ref->GetRepeatedString( *m2, field_desc, j ) ) return false ; 
						}
						break ;	    					
    				}
    			case TYPE_ENUM :
    				{
    					for( int j=0; j<fs; j++){
							if( ref->GetRepeatedEnum( *m1, field_desc, j ) != ref->GetRepeatedEnum( *m2, field_desc, j ) ) return false ; 
						}
						break ;
    				}
    			case TYPE_MESSAGE:
    			case TYPE_GROUP:
    				{
    					for( int j=0; j<fs; j++){
							const GPB::Message* mm1 = &ref->GetRepeatedMessage( *m1, field_desc, j ) ;
							const GPB::Message* mm2 = &ref->GetRepeatedMessage( *m2, field_desc, j ) ;
    						if( !identical_messages_( (GPB::Message*)mm1, (GPB::Message*)mm2, tol ) ){
    							return false ;
    						}
						}
						break ;
    				}
    			default:
				Rcpp_error("unknown type");
			}
			
		} else {
			
			switch( field_desc->type() ){
				case TYPE_INT32:
				case TYPE_SINT32:
				case TYPE_SFIXED32:
					{
						if( ref->GetInt32( *m1, field_desc) != ref->GetInt32( *m2, field_desc ) ) return false ; 
						break ;
					}
				case TYPE_INT64:
				case TYPE_SINT64:
				case TYPE_SFIXED64:
					{
						if( ref->GetInt64( *m1, field_desc) != ref->GetInt64( *m2, field_desc) ) return false ; 
						break ;
					}
    			case TYPE_UINT32:
    			case TYPE_FIXED32:
    				{
    					if( ref->GetUInt32( *m1, field_desc ) != ref->GetUInt32( *m2, field_desc ) ) return false ; 
						break ;
    				}
    			case TYPE_UINT64:
    			case TYPE_FIXED64:
    				{
    					if( ref->GetUInt64( *m1, field_desc ) != ref->GetUInt64( *m2, field_desc ) ) return false ; 
						break ;	    					
    				}
    			case TYPE_DOUBLE:
    				{
    					if( ref->GetDouble( *m1, field_desc ) != ref->GetDouble( *m2, field_desc ) ) return false ; 
						break ;	    					
    				}
    			case TYPE_FLOAT:
    				{
    					if( ref->GetFloat( *m1, field_desc ) != ref->GetFloat( *m2, field_desc ) ) return false ; 
						break ;	    					
    				}
    			case TYPE_BOOL:
    				{
    					if( ref->GetBool( *m1, field_desc ) != ref->GetBool( *m2, field_desc ) ) return false ; 
						break ;	    					
    				}
				case TYPE_STRING:
    			case TYPE_BYTES:
    				{
    					if( ref->GetString( *m1, field_desc ) != ref->GetString( *m2, field_desc ) ) return false ; 
						break ;	    					
    				}
    			case TYPE_ENUM :
    				{
    					if( ref->GetEnum( *m1, field_desc) != ref->GetEnum( *m2, field_desc ) ) return false ; 
						break ;
    				}
    			case TYPE_MESSAGE:
    			case TYPE_GROUP:
    				{
    					const GPB::Message* mm1 = &ref->GetMessage( *m1, field_desc ) ;
						const GPB::Message* mm2 = &ref->GetMessage( *m2, field_desc ) ;
    					if( !identical_messages_( (GPB::Message*)mm1, (GPB::Message*)mm2, tol ) ){
    						return false ;
    					}
						break ;
    				}
    			default:
				Rcpp_error("unknown type");
			}
			
		}
	}
  VOID_END_RCPP
  /* finally */
  return true ;
}

RPB_FUNCTION_2( bool, identical_messages, Rcpp::XPtr<GPB::Message> m1, Rcpp::XPtr<GPB::Message> m2){
	return identical_messages_( m1, m2, 0.0 ) ;
}

RPB_FUNCTION_3( bool, all_equal_messages, Rcpp::XPtr<GPB::Message> m1, Rcpp::XPtr<GPB::Message> m2, double tol){
	return identical_messages_( m1, m2, tol ) ;
}

RPB_FUNCTION_VOID_4( METHOD(swap), Rcpp::XPtr<GPB::Message> message, SEXP field, Rcpp::IntegerVector left, Rcpp::IntegerVector right){
	GPB::FieldDescriptor* field_desc = getFieldDescriptor( message, field ) ;
	const GPB::Reflection* ref = message->GetReflection(); 
	if( ! field_desc->is_repeated() ){
		throw std::range_error( "swap can only be used with repeated fields" ) ; 
	}
	int n = LENGTH(left); /* we know that length(left) == length(right) */ 
	for( int i=0; i<n; i++){
		ref->SwapElements(message, field_desc, left[i] , right[i] ) ;
	}
}

/**
 * creates a new message by merging two messages of the same type
 *
 * @param xp1 external pointer to a GPB::Message*
 * @param xp2 external pointer to a GPB::Message*
 *
 * @return a new message, as an R object of "Message" S4 class
 */
RPB_FUNCTION_2( S4_Message, METHOD(merge), Rcpp::XPtr<GPB::Message> m1, Rcpp::XPtr<GPB::Message> m2){
	GPB::Message* merged = m1->New() ; 
	merged->MergeFrom( *m1 ) ; 
	merged->MergeFrom( *m2 ); 
	return S4_Message( merged ) ;
}


/**
 * Add values to a repeated field
 *
 * @param xp (GPB::Message*) external pointer
 * @param field field tag number or name
 * @param values values to append
 */ 
RPB_FUNCTION_VOID_3( METHOD(add_values), Rcpp::XPtr<GPB::Message> message,
		     SEXP field, SEXP values){
	const Reflection * ref = message->GetReflection() ;
	const GPB::FieldDescriptor* field_desc = getFieldDescriptor( message, field );
		
	if( values == R_NilValue || LENGTH(values) == 0 ){
		return ; 
	}
		
	if( field_desc->is_repeated() ){
		/* first check */
		switch( field_desc->type() ){
		case TYPE_ENUM:
			{
				CHECK_values_for_enum( field_desc, values) ; 
				break ;
			}
		case TYPE_MESSAGE:
		case TYPE_GROUP:
			{
				CHECK_messages( field_desc, values ) ;
				break ;
			}
		default:
			{// nothing
			}
		}

		int value_size = LENGTH( values ) ;
		/* then add the values */
		switch( field_desc->type() ){
		// {{{ int32
		case TYPE_INT32:
		case TYPE_SINT32:
		case TYPE_SFIXED32:
			{
				switch( TYPEOF( values ) ){
				case INTSXP:
				case REALSXP:
				case LGLSXP:
				case RAWSXP:	
					{
					for( int i=0; i<value_size; i++){
						ref->AddInt32( message, field_desc, GET_int32(values,i) ) ;
					}
					break ;
					}
				default: 
					{
						Rcpp::stop("Cannot convert to int32");
					}
				}
				break ;   
			}
		// }}}
    			
		// {{{ int64
		case TYPE_INT64:
		case TYPE_SINT64:
		case TYPE_SFIXED64:
			{
				switch( TYPEOF( values ) ){
				case INTSXP:
				case REALSXP:
				case LGLSXP:
				case RAWSXP:	
					for( int i=0; i<value_size; i++){
						ref->AddInt64( message, field_desc, GET_int64(values,i) ) ;
					}
				default: 
					Rcpp::stop("Cannot convert to int64");
				}
				break ;
			}
		// }}}	
    				
    		// {{{ uint32
		case TYPE_UINT32:
		case TYPE_FIXED32:
			{
			switch( TYPEOF( values ) ){
			case INTSXP:
			case REALSXP:
			case LGLSXP:
			case RAWSXP:	
				{
				for( int i=0; i<value_size; i++){
					ref->AddUInt32( message, field_desc, GET_int32(values,i) ) ;
				}
				break ;
				}
			default: 
				Rcpp::stop("Cannot convert to uint32");
    			}
			break ;   
			}
		// }}}
     			
		// {{{ uint64
		case TYPE_UINT64:
		case TYPE_FIXED64:
		{
			switch( TYPEOF( values ) ){
			case INTSXP:
			case REALSXP:
			case LGLSXP:
			case RAWSXP:	
			{
				for( int i=0; i<value_size; i++){
					ref->AddUInt64( message, field_desc, GET_uint64(values,i) ) ;
				}
				break ;
			}
			default: 
				Rcpp::stop("Cannot convert to int64");
			}
			break ;   
		}
		// }}}
        	
		// {{{ double
		case TYPE_DOUBLE:
		{
			switch( TYPEOF( values ) ){
			case INTSXP:
			case REALSXP:
			case LGLSXP:
			case RAWSXP:	
			{
				for( int i=0; i<value_size; i++){
					ref->AddDouble( message, field_desc, GET_double(values,i) ) ;
				}
				break ;
			}
			default: 
				Rcpp::stop("Cannot convert to double");
			}
			break ;   
		}
		// }}}	
    				
		// {{{ float
		case TYPE_FLOAT:
		{
			switch( TYPEOF( values ) ){
			case INTSXP:
			case REALSXP:
			case LGLSXP:
			case RAWSXP:	
				{
					for( int i=0; i<value_size; i++){
						ref->AddFloat( message, field_desc, GET_float(values,i) ) ;
					}
					break ;
				}
			default: 
				Rcpp::stop("Cannot convert to float");
			}
			break ;   
		}
		// }}}	
    			
		// {{{ bool
		case TYPE_BOOL:
		{
			switch( TYPEOF( values ) ){
			case INTSXP:
			case REALSXP:
			case LGLSXP:
			case RAWSXP:	
			{
				for( int i=0; i<value_size; i++){
					ref->AddBool( message, field_desc, GET_bool(values,i) ) ;
				}
				break ;
			}
			default: 
				Rcpp::stop("Cannot convert to bool");
			}
			break ;   
		}
		// }}}

		// {{{ string
		case TYPE_STRING:
		{
			if( TYPEOF(values) == STRSXP ){ 
				for( int i=0 ; i<value_size; i++){
					ref->AddString( message, field_desc, COPYSTRING( CHAR(STRING_ELT(values,i )) ) ) ;
				}
			} else{
				Rcpp::stop("Cannot convert to string");
			}
			break ; 
		}
		// }}}

		// {{{ bytes
		case TYPE_BYTES:
		{
			if( TYPEOF(values) == RAWSXP ){
				ref->AddString( message, field_desc, GET_bytes(values,0 )) ;
			} else if( TYPEOF(values) == VECSXP ){ 
				for( int i=0 ; i<value_size; i++) {
					ref->AddString( message, field_desc, GET_bytes(values,i )) ;
				}
			} else{
				Rcpp::stop("Cannot convert to bytes");
			}
			break ; 
		}
		// }}}
    			
		// {{{ message
		case TYPE_MESSAGE:
		case TYPE_GROUP: 
		{    
			if( TYPEOF(values) == VECSXP )  {
				for( int i=0; i<value_size; i++){
					GPB::Message* mess = GET_MESSAGE_POINTER_FROM_S4( VECTOR_ELT( values, i) ) ; 
					/* we already know it is of the correct
					   type because of premptive check above */

					ref->AddMessage(message, field_desc)->CopyFrom( *mess ) ; 
				}
			} else{
				Rcpp::stop("type mismatch, expecting a list of 'Message' objects");
			}
			break ;
		}
		// }}}
    			
		// {{{ enum
		case TYPE_ENUM : 
		{
			const GPB::EnumDescriptor* enum_desc = field_desc->enum_type() ;
			switch( TYPEOF( values ) ){
			// {{{ numbers 
			case INTSXP:
			case REALSXP:
			case LGLSXP:
			case RAWSXP:
			{
				for( int i=0; i<value_size; i++){
					int val = GET_int(values, i ); 
					ref->AddEnum( message, field_desc, enum_desc->FindValueByNumber(val) ) ;
				}
				break ;
			}
			// }}}

			// {{{ STRSXP
			case STRSXP:
			{
				for( int i=0; i<value_size; i++){
					std::string val = CHAR( STRING_ELT( values, i) ) ;
					const GPB::EnumValueDescriptor* evd = enum_desc->FindValueByName(val) ;
					ref->AddEnum( message, field_desc, evd ) ; 
				}
				break ;
			}
			// }}}

			// {{{ default
			default:
			{
				Rcpp::stop("cannot set enum value");
			}
			// }}}
			}
			break; 
		}
		// }}}
		default:
		{
			// nothing
		}
    		}
	} else{
	  Rcpp::stop("add can only be used on repeated fields");
	}
}


/**
 * fetch a subset of the values of a field
 *
 * @param (GPB::Message*) external pointer
 * @param field name or tag number of the field
 * @param index 
 */
RPB_FUNCTION_3( SEXP, METHOD(get_field_values), Rcpp::XPtr<GPB::Message> message, SEXP field, Rcpp::IntegerVector index ){
	GPB::FieldDescriptor* field_desc = getFieldDescriptor( message, field ) ;
	if( !field_desc->is_repeated() ){
		Rf_error( "fetch can only be used on repeated fields" ) ;
	}
		
	int n = index.size() ; 
	switch( field_desc->type() ){
			
	case TYPE_INT32:
	case TYPE_SINT32:
	case TYPE_SFIXED32:
	case TYPE_INT64:
	case TYPE_SINT64:
	case TYPE_SFIXED64:
	case TYPE_UINT32:
	case TYPE_FIXED32:
	case TYPE_UINT64:
	case TYPE_FIXED64:
	case TYPE_ENUM:
		{
		Rcpp::IntegerVector res(n) ;
		for( int i=0; i<n; i++){
			res[i] = MESSAGE_GET_REPEATED_INT(message, field_desc,
							  index[i]) ;
		}
		return res; 
		}
	case TYPE_DOUBLE:
	case TYPE_FLOAT:
		{
		Rcpp::NumericVector res(n) ;
		for( int i=0; i<n; i++){
			res[i] = MESSAGE_GET_REPEATED_DOUBLE(message,
							     field_desc,
							     index[i]) ;
		}
		return res; 
		}
	case TYPE_BOOL:
		{
		Rcpp::LogicalVector res(n) ;
		for( int i=0; i<n; i++){
			res[i] = MESSAGE_GET_REPEATED_DOUBLE( 
							     message, field_desc, index[i] ) ;
		}
		return res; 
		}
	case TYPE_STRING:
		{
		const GPB::Reflection* ref = message->GetReflection() ; 
		Rcpp::CharacterVector res(n) ;
		for( int i=0; i<n; i++){
			res[i] = ref->GetRepeatedString( *message, field_desc, index[i] ) ;
		}
		return res ;
		}
	case TYPE_BYTES:
		{
		const GPB::Reflection* ref = message->GetReflection() ; 
		Rcpp::List res(n) ;
		for( int i=0; i<n; i++){
			std::string s = ref->GetRepeatedString( *message, field_desc, index[i] );
			res[i] = std::vector<Rbyte>(s.begin(), s.end());
		}
		return res ;
		}
	case TYPE_MESSAGE:
	case TYPE_GROUP:
		{
		const GPB::Reflection* ref = message->GetReflection() ; 
		Rcpp::List res(n) ;
		for( int i=0; i<n; i++){
			res[i] = S4_Message( CLONE( &ref->GetRepeatedMessage( *message, field_desc, i ) ) ) ;
		} 
		return res ;
		}
	default: 
		throw std::range_error( "unknown type" ) ;
	}
	return R_NilValue ; // -Wall 
}


	/**
	 * set the values of a repeated field
	 *
	 * @param xp (GPB::Message*) external pointer
	 * @param field field tag number or name
	 * @param index positions (0-based) 
	 * @param values new values
	 */
	RPB_FUNCTION_VOID_4( METHOD(set_field_values), Rcpp::XPtr<GPB::Message> message, SEXP field, Rcpp::IntegerVector index, SEXP values ){
		
		const GPB::FieldDescriptor* field_desc = getFieldDescriptor( message, field ) ;
		if( !field_desc->is_repeated() ){
			throw std::range_error( "set can only be used on repeated fields" ) ;
		}
		
		const GPB::Reflection* ref = message->GetReflection(); 
		
		/* we know here that LENGTH(index) == LENGTH(values) */
		int n = index.size() ;
		switch( field_desc->type() ){
			
    			case TYPE_INT32:
    			case TYPE_SINT32:
    			case TYPE_SFIXED32:
					{	
						for( int i=0; i<n; i++){
							ref->SetRepeatedInt32( message, field_desc, 
								index[i], 
								GET_int32( values, i ) ) ;
						}
						break ;
					}
				case TYPE_INT64:
    			case TYPE_SINT64:
    			case TYPE_SFIXED64:
					{	
						for( int i=0; i<n; i++){
							ref->SetRepeatedInt64( message, field_desc, 
								index[i], 
								GET_int64( values, i ) ) ;
						}
						break ;
					}
	    		case TYPE_UINT32:
	    		case TYPE_FIXED32:
	    			{
						for( int i=0; i<n; i++){
							ref->SetRepeatedUInt32( message, field_desc, 
								GET_int( index, i ), 
								GET_uint32( values, i ) ) ;
						}
						break ;
	    			}
	    		case TYPE_UINT64:
	    		case TYPE_FIXED64:
	    			{
						for( int i=0; i<n; i++){
							ref->SetRepeatedUInt64( message, field_desc, 
								index[i], 
								GET_uint64( values, i ) ) ;
						}
						break ;
					}
				case TYPE_DOUBLE:
		    		{
		    			for( int i=0; i<n; i++){
							ref->SetRepeatedDouble( message, field_desc, 
								index[i], 
								GET_double( values, i ) ) ;
						}
						break ;

					}
				case TYPE_FLOAT:
					{
						for( int i=0; i<n; i++){
							ref->SetRepeatedFloat( message, field_desc, 
								index[i], 
								GET_float( values, i ) ) ;
						}
						break ;
					}
				case TYPE_BOOL:
					{
						for( int i=0; i<n; i++){
							ref->SetRepeatedBool( message, field_desc, 
								index[i], 
								GET_bool( values, i ) ) ;
						}
						break ;
					}
				case TYPE_STRING:
	    			{
	    				
	    				for( int i=0; i<n; i++){
							ref->SetRepeatedString( message, field_desc, 
								index[i], 
								GET_stdstring( values, i ) ) ;
						}
						break ;
	    			}
	    		case TYPE_BYTES:
	    			{
	    				
	    				for( int i=0; i<n; i++){
							ref->SetRepeatedString( message, field_desc, 
								index[i], 
								GET_bytes( values, i ) ) ;
						}
						break ;
	    			}
	    		case TYPE_ENUM :
	    			{
	    				CHECK_values_for_enum( field_desc, values ) ;
	    				
	    				const GPB::EnumDescriptor* enum_desc = field_desc->enum_type() ;
	    				
	    				switch( TYPEOF( values ) ){
    						case INTSXP:
    						case REALSXP:
    						case LGLSXP:
    						case RAWSXP:
    							{
    								for( int i=0; i<n; i++){
	    								int val = GET_int(values, i ); 
	    								ref->SetRepeatedEnum( message, field_desc, i, 
	    									enum_desc->FindValueByNumber(val) ) ;
	    							}
	    							
    								break ;
    							}
    						case STRSXP:
    							{
    								Rcpp::CharacterVector vals( values );
    								std::string val ;
    								for( int i=0; i<n; i++){
	   									val = vals[i] ;
	    								const GPB::EnumValueDescriptor* evd = enum_desc->FindValueByName(val) ;
	    								ref->SetRepeatedEnum( message, field_desc, i, evd ) ; 
	    							}
	    							
    								
    								break ;
    							}
    						default:
    							throw std::range_error( "impossible to convert to a enum" ) ; 
	    				}
	    				
	    				
	    			}
    			case TYPE_MESSAGE:
    			case TYPE_GROUP:
    				{
    					CHECK_messages( field_desc, values ) ; 
    					Rcpp::List vals( values ) ;
    					for( int i=0; i<n; i++){
			    			GPB::Message* mess = GET_MESSAGE_POINTER_FROM_S4( vals[i] ) ; 
			    			ref->MutableRepeatedMessage(message, field_desc, i )->CopyFrom( *mess ) ; ; 
			    		}
			    		break ;  
    				}
    			default: 
    				throw std::range_error( "unknown type" ) ;
		}
	}
	

	#undef METHOD

}
