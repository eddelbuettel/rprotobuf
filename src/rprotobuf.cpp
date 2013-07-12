#include "rprotobuf.h"
#include "DescriptorPoolLookup.h" 

namespace rprotobuf{

	GPB::Message* PROTOTYPE( const GPB::Descriptor* desc){
#ifdef RPB_DEBUG
	Rprintf( "<PROTOTYPE>\n" ) ;
	Rprintf( "desc = %d\n", desc ) ;
#endif
	/* first try the runtime factory */
	GPB::Message* m = (GPB::Message*)((GPB::DynamicMessageFactory*)DescriptorPoolLookup::factory())->GetPrototype( desc )->New() ;
		
#ifdef RPB_DEBUG
		Rprintf( "generated factory = %d\n", m ) ;
#endif		
		if( !m ){
			/* then the dynamic runtime factory */
			m = (GPB::Message*)GPB::MessageFactory::generated_factory()->GetPrototype( desc )->New() ;
#ifdef RPB_DEBUG
		Rprintf( "runtime  factory = %d\n", m ) ;
#endif		
		}
		return m ;
	}
	
	
	GPB::Message* CLONE(const GPB::Message* origin){
#ifdef RPB_DEBUG
		Rprintf( "<CLONE>" ) ;
#endif		
		
		const GPB::Descriptor* desc = origin->GetDescriptor() ;
		GPB::Message* sheep = PROTOTYPE( desc ) ;
		sheep->CopyFrom(*origin) ;

#ifdef RPB_DEBUG
		Rprintf( "</CLONE>" ) ;
#endif		
		return sheep ;
	}
	
/**
 * read a proto file and cache the message definitions it contains
 *
 * @param file proto file name
 */
SEXP readProtoFiles( SEXP file, SEXP dirs ){
	DescriptorPoolLookup::importProtoFiles( file, dirs ) ;
	return R_NilValue ;
}

/**
 * get the descriptor associated with a message type
 *
 * @param type message type
 *
 * @return an S4 object of class Descriptor, or NULL if the type 
 *  is unknown
 */
SEXP getProtobufDescriptor( SEXP type ){

#ifdef RPB_DEBUG
Rprintf( "<getProtobufDescriptor>\n      type = " ) ;
Rf_PrintValue( type ) ;
#endif
	
	const char * typeName = CHAR( STRING_ELT(type, 0 ) ) ;
	
	/* first try the generated pool */
	const GPB::DescriptorPool*  pool = GPB::DescriptorPool::generated_pool() ;
	const GPB::Descriptor*  desc = pool->FindMessageTypeByName( typeName ) ; 
	if( !desc ){
		/* then try the "runtime" pool" */
		pool = DescriptorPoolLookup::pool() ;
		desc = pool->FindMessageTypeByName( typeName ) ;
		if( !desc ){
			/* unlucky */
			return R_NilValue ;
		}
	}
	
	return( S4_Descriptor( desc ) ) ;
}

/**
 * make a new protobuf message
 *
 * @param descriptor a "Descriptor" R object
 */
SEXP newProtoMessage( SEXP descriptor ){

#ifdef RPB_DEBUG
Rprintf( "<newProtoMessage>\n" ) ;
	/* FIXME: the message type, we don't really need that*/
	SEXP type = GET_SLOT( descriptor, Rf_install("type") ) ;
#endif
	
	/* the pointer to the c++ descriptor object */
	GPB::Descriptor* desc = GET_DESCRIPTOR_POINTER_FROM_S4( descriptor ); 
	
#ifdef RPB_DEBUG
Rprintf( "desc = %d\n", desc ) ;
PRINT_DEBUG_INFO( "type", type ) ;
#endif
	
	/* grab the Message from the factory */
	const GPB::Message* message = PROTOTYPE( desc ) ; 
	if( !message ){
		throwException( "could not call factory->GetPrototype(desc)->New()", "MessageCreationException" ) ; 
	}
#ifdef RPB_DEBUG
Rprintf( "</newProtoMessage>\n" ) ;
#endif
	
	return( S4_Message( message )  ) ;
}

/**
 * dollar extractor for Descriptor objects
 * it may return a Field descriptor or a nested type descriptor
 *
 * @param pointer external pointer to a google::protobuf::Descriptor object
 * @param name name of the thing to extract
 */
SEXP do_dollar_Descriptor( SEXP pointer, SEXP name ){
	
	const char * what = CHAR( STRING_ELT( name, 0 ) ) ;
	GPB::Descriptor * desc = (GPB::Descriptor*) EXTPTR_PTR(pointer) ;
	
	// trying fields first :
	
	if( desc->field_count() ){
		const GPB::FieldDescriptor*  fd = desc->FindFieldByName(what) ;
		if( fd ){
			return( S4_FieldDescriptor(fd ) ) ;
		}
	}
	
	// now trying nested types
	if( desc->nested_type_count() ){
		const GPB::Descriptor* d = desc->FindNestedTypeByName(what) ;
		if( d ){
			return( S4_Descriptor( d ) ) ;
		}
	}
	
	// now for enum types
	if( desc->enum_type_count() ){
		const GPB::EnumDescriptor* ed = desc->FindEnumTypeByName(what) ;
		if( ed ){
			return( S4_EnumDescriptor( ed ) ) ;
		}
	}
	
	
	// TODO: extensions (later)
	
	// give up
	// TODO: should this be unbound instead
	return( R_NilValue ); 
}

/** 
 *
 * @param m potentially a message 
 * @param target the exxpected type
 *
 * @return TRUE if m is a a message of the given type
 */ 
Rboolean isMessage( SEXP m, const char* target ){
#ifdef RPB_DEBUG
Rprintf( "<isMessage>\n" ) ;
#endif

	if( TYPEOF(m) != S4SXP || !Rf_inherits( m, "Message") ) return _FALSE_ ;
	
	GPB::Message* message = (GPB::Message*) EXTPTR_PTR( GET_SLOT( m, Rf_install("pointer") ) );
	
	const char* type = message->GetDescriptor()->full_name().c_str() ;
	if( strcmp( type, target) ){
		return _FALSE_ ;
	}

	return _TRUE_ ; 
}


GPB::FieldDescriptor* getFieldDescriptor(GPB::Message* message, SEXP name){
	GPB::FieldDescriptor* field_desc = (GPB::FieldDescriptor*)0;
	const GPB::Descriptor* desc = message->GetDescriptor() ;
	switch( TYPEOF(name) ){
		case S4SXP:
		  {
		    if (Rf_inherits( name, "FieldDescriptor") ){
		      field_desc = GET_FIELD_DESCRIPTOR_POINTER_FROM_S4(name);
		    } else {
		      throwException( "S4 class is not a FieldDescriptor", "NoSuchFieldException" ) ;
		    }
		    break ;
		  }
		case CHARSXP:
			{
				field_desc = (GPB::FieldDescriptor*)desc->FindFieldByName( CHAR(name) ) ;
				break ;	
			}
		case STRSXP:
			{
				field_desc = (GPB::FieldDescriptor*)desc->FindFieldByName( CHAR( STRING_ELT(name, 0 ) ) ) ;
				break ;
			}
		case REALSXP:
		case INTSXP:
			{
				field_desc = (GPB::FieldDescriptor*)desc->FindFieldByNumber( Rcpp::as<int>( name ) ) ;
				break ;
			}
	}
	if( !field_desc ){
		throwException( "could not get FieldDescriptor for field", "NoSuchFieldException" ) ;
	}
	return field_desc ;
}

RCPP_FUNCTION_VOID_1( check_libprotobuf_version, int minversion ){
	if( GOOGLE_PROTOBUF_VERSION < minversion ){
		throw std::range_error( "The protobuf library you are using is too old for this package, please upgrade" ) ;
	}
}

RCPP_FUNCTION_0(int, get_protobuf_library_version){
	return GOOGLE_PROTOBUF_VERSION;
}

} // namespace rprotobuf

