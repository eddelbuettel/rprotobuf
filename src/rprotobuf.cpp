#include "rprotobuf.h"

namespace org{
namespace rproject{
namespace rprotobuf{

class MockErrorCollector : public MultiFileErrorCollector {
 public:
  MockErrorCollector() {}
  ~MockErrorCollector() {}
  // implements ErrorCollector ---------------------------------------
  void AddError(const string& filename, int line, int column,
                const string& message) {
  	
  	/* we should send this as a warning in R */
  	cerr << filename ;
  	cerr << ":" << (line + 1) << ":" << (column + 1);
  	cerr << ": " << message << endl;
  
  }
};


namespace{
	
/**
 * read a proto file and cache the message definitions it contains
 *
 * @param file proto file name
 */
SEXP readProtoFiles( SEXP file ){
	
#ifdef RPB_DEBUG
Rprintf( "<readProtoFiles>\n" ) ;
PrintValue( file ) ;
#endif
	
	if( TYPEOF( file) != STRSXP ){
		Rf_error( "'file must be a character vector"  );
	}
	
#ifdef RPB_DEBUG
Rprintf( "   importer.Import( '%s' ) \n", filename ) ;
#endif
	
	MockErrorCollector error_collector ;
	DiskSourceTree source_tree;
	// FIXME : this works only on linux I suppose
	source_tree.MapPath("/", "/");
	Importer importer(&source_tree, &error_collector);
	
	int j = 0 ;
	int n = LENGTH(file) ;
	while( j < n ){
		importer.Import( CHAR(STRING_ELT(file, j)) );
	    j++; 
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
 * @return an S4 object of class protobufDescriptor, or NULL if the type 
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
 * @param descriptor a "protobufDescriptor" R object
 */
SEXP newProtoMessage( SEXP descriptor ){

#ifdef RPB_DEBUG
Rprintf( "<newProtoMessage>\n" ) ;
#endif

	/* the message type */
	SEXP type = GET_SLOT( descriptor, Rf_install("type") ) ;
	
	/* the pointer to the c++ descriptor object */
	Descriptor* desc = (Descriptor*)EXTPTR_PTR( GET_SLOT( descriptor, Rf_install("pointer") ) );

#ifdef RPB_DEBUG
PRINT_DEBUG_INFO( "type", type ) ;
PRINT_DEBUG_INFO( "desc_ptr", desc_ptr ) ;
#endif
	
	/* grab the Message from the factory */
	const Message * message = MessageFactory::generated_factory()->GetPrototype( desc )->New(); 
	if( !message ){
		Rf_error( "could not call factory->GetPrototype(desc)->New()" ) ; 
	}
#ifdef RPB_DEBUG
Rprintf( "</newProtoMessage>\n" ) ;
#endif
	
	return( new_RS4_Message( message, type )  ) ;
}

/**
 * set a message field to a new value
 *
 * @param pointer external pointer to a message
 * @param name name of the field
 * @param value new value for the field
 *
 * @return allways NULL, the message is modified by reference
 */
SEXP setMessageField( SEXP pointer, SEXP name, SEXP value ){
	
#ifdef RPB_DEBUG
Rprintf( "<setMessageField>\n" ) ;

PRINT_DEBUG_INFO( "pointer", pointer ) ;
PRINT_DEBUG_INFO( "name", name ) ;
PRINT_DEBUG_INFO( "value", value ) ;
#endif

	/* TODO: do something */
	

#ifdef RPB_DEBUG
Rprintf( "</setMessageField>\n" ) ;
#endif
	
	return R_NilValue ;
	
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
 * Get the debug string of a message
 *
 * @param xp external pointer to a Message pointer
 */
SEXP get_message_debug_string( SEXP xp ){
	
	/* grab the Message pointer */
	Message* message = (Message*)EXTPTR_PTR(xp) ;
	
	SEXP res = PROTECT( Rf_mkString(message->DebugString().c_str() ) ) ; 
	UNPROTECT(1); /* res */
	return res ;
}


/**
 * Get the debug string of a message
 *
 * @param xp external pointer to a Descriptor pointer
 */
SEXP get_descriptor_debug_string( SEXP xp ){
	
	/* grab the Message pointer */
	Descriptor* desc = (Descriptor*)EXTPTR_PTR(xp) ;
	
	SEXP res = PROTECT( Rf_mkString(desc->DebugString().c_str() ) ) ; 
	UNPROTECT(1); /* res */
	return res ;
}

} // namespace
} // namespace rprotobuf
} // namespace rproject
} // namespace org

