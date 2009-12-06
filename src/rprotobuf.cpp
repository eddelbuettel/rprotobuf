#include "rprotobuf.h"
#include "RSourceTree.h"
#include "DescriptorPoolLookup.h" 
#include "RWarningErrorCollector.h"

namespace rprotobuf{

/**
 * read a proto file and cache the message definitions it contains
 *
 * @param file proto file name
 */
SEXP readProtoFiles( SEXP file ){
	
#ifdef RPB_DEBUG
Rprintf( "<readProtoFiles>\n" ) ;
PrintValue( file ) ;
Rprintf( "   importer.Import( '%s' ) \n", filename ) ;
#endif
	
	RWarningErrorCollector error_collector ;
	RSourceTree source_tree;
	Importer importer(&source_tree, &error_collector);
	
	int n = LENGTH(file) ;
	for( int j=0; j < n; j++ ){
		const FileDescriptor* file_desc = importer.Import( CHAR(STRING_ELT(file, j)) );
	    int ntypes = file_desc->message_type_count() ;
	    for( int i=0; i<ntypes; i++){
	    	const Descriptor* desc = file_desc->message_type( i ) ;
	    	DescriptorPoolLookup::add( desc->full_name() ); 
	    	/* should we bother recursing ? */
	    }
	}
	
#ifdef RPB_DEBUG
Rprintf( "</readProtoFiles>\n" ) ;
#endif

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
PrintValue( type ) ;
#endif
	
	const char * typeName = CHAR( STRING_ELT(type, 0 ) ) ;
	const DescriptorPool * pool = DescriptorPool::generated_pool() ;
	const Descriptor * desc = pool->FindMessageTypeByName( typeName ) ; 
	if( !desc ){
		return R_NilValue ;
	}
	
	return( new_RS4_Descriptor( desc ) ) ;
}

/**
 * make a new protobuf message
 *
 * @param descriptor a "Descriptor" R object
 */
SEXP newProtoMessage( SEXP descriptor ){

#ifdef RPB_DEBUG
Rprintf( "<newProtoMessage>\n" ) ;
#endif

	/* the message type */
	SEXP type = GET_SLOT( descriptor, Rf_install("type") ) ;
	
	/* the pointer to the c++ descriptor object */
	Descriptor* desc = GET_DESCRIPTOR_POINTER_FROM_S4( descriptor ); 
	
#ifdef RPB_DEBUG
PRINT_DEBUG_INFO( "type", type ) ;
PRINT_DEBUG_INFO( "desc_ptr", desc_ptr ) ;
#endif
	
	/* grab the Message from the factory */
	const Message * message = MessageFactory::generated_factory()->GetPrototype( desc )->New(); 
	if( !message ){
		throwException( "could not call factory->GetPrototype(desc)->New()", "MessageCreationException" ) ; 
	}
#ifdef RPB_DEBUG
Rprintf( "</newProtoMessage>\n" ) ;
#endif
	
	return( new_RS4_Message( message, type )  ) ;
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
	Descriptor * desc = (Descriptor*) EXTPTR_PTR(pointer) ;
	
	// trying fields first :
	
	if( desc->field_count() ){
		const FieldDescriptor * fd = desc->FindFieldByName(what) ;
		if( fd ){
			return( new_RS4_FieldDescriptor(fd ) ) ;
		}
	}
	
	// now trying nested types
	if( desc->nested_type_count() ){
		const Descriptor* d = desc->FindNestedTypeByName(what) ;
		if( d ){
			return( new_RS4_Descriptor( d ) ) ;
		}
	}
	
	// now for enum types
	if( desc->enum_type_count() ){
		const EnumDescriptor * ed = desc->FindEnumTypeByName(what) ;
		if( ed ){
			return( new_RS4_EnumDescriptor( ed ) ) ;
		}
	}
	
	
	// TODO: extensions, services, ... (later)
	
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
	
	Message* message = (Message*) EXTPTR_PTR( GET_SLOT( m, Rf_install("pointer") ) );
	
	const char* type = message->GetDescriptor()->full_name().c_str() ;
	if( strcmp( type, target) ){
		return _FALSE_ ;
	}

	return _TRUE_ ; 
}


FieldDescriptor* getFieldDescriptor(Message* message, SEXP name){
	FieldDescriptor* field_desc = (FieldDescriptor*)0;
	const Descriptor* desc = message->GetDescriptor() ;
	switch( TYPEOF(name) ){
		case STRSXP:
			{
				const char * what = CHAR( STRING_ELT(name, 0 ) ) ;
				field_desc = (FieldDescriptor*)desc->FindFieldByName( what ) ;
				break ;
			}
		case REALSXP: 
			{
				field_desc = (FieldDescriptor*)desc->FindFieldByNumber( (int)REAL(name)[0] ) ;
				break ;
			}
		case INTSXP:
			{
				field_desc = (FieldDescriptor*)desc->FindFieldByNumber( INTEGER(name)[0] ) ;
				break ;
			}
	}
	
	if( !field_desc ){
		throwException( "could not get FieldDescriptor for field", "NoSuchFieldException" ) ;
	}
	
	return field_desc ;
}

SEXP check_libprotobuf_version( SEXP minversion ){

	if( GOOGLE_PROTOBUF_VERSION < INTEGER(minversion)[0] ){
		Rf_error( "The protobuf library you are using is too old for this package, please upgrade" ) ;
	}
	return( R_NilValue ) ;
}

SEXP get_protobuf_library_version(){
	return( Rf_ScalarInteger( GOOGLE_PROTOBUF_VERSION ) );
}

} // namespace rprotobuf

