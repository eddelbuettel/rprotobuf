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
RcppExport SEXP readProtoFiles( SEXP file ){
	
#ifdef RPB_DEBUG
Rprintf( "<readProtoFiles>\n" ) ;
PrintValue( file ) ;
#endif
	
	if( TYPEOF( file) != STRSXP ){
		error( "'file must be a character vector"  );
	}
	
	// TODO : read all the files, not just the first one
	const char * filename = CHAR( STRING_ELT( file, 0 ) ); 

#ifdef RPB_DEBUG
Rprintf( "   importer.Import( '%s' ) \n", filename ) ;
#endif
	
	MockErrorCollector error_collector ;
	DiskSourceTree source_tree;
	source_tree.MapPath("/", "/");
	Importer importer(&source_tree, &error_collector);
	const FileDescriptor* proto_file =
    	importer.Import( "/tmp/person.proto" );
    
Rprintf( "  name    = %s \n", proto_file->name().c_str()  ) ;
Rprintf( "  package = %s \n", proto_file->package().c_str()  ) ;
int nmessages = proto_file->message_type_count() ;
Rprintf( "  number of top level message types = %d \n", nmessages ) ;
int i=0;
while( i<nmessages ){
	const Descriptor* descriptor = proto_file->message_type(i); 
	Rprintf( "       %d  : %s \n", i, descriptor->full_name().c_str() ) ;
	i++ ;
}

int nenum = proto_file->enum_type_count() ;
Rprintf( "  number of top level enum types = %d \n", nenum ) ;
i=0;
while( i<nenum ){
	const EnumDescriptor* descriptor = proto_file->enum_type(i); 
	Rprintf( "       %d  : %s \n", i, descriptor->full_name().c_str() ) ;
	i++ ;
}

// look into the descriptor pool
Rprintf( "  Retrieve the 'tutorial.Person' descriptor from the pool\n" ) ;
const DescriptorPool * pool = DescriptorPool::generated_pool() ;
const Descriptor * desc = pool->FindMessageTypeByName( "tutorial.Person" ) ; 
int nfields = desc->field_count() ;
Rprintf( "  %d fields\n", nfields ) ;
i=0; 
while( i<nfields){
	const FieldDescriptor * f = desc->field( i ) ; 
	Rprintf( "       [%d] : %s (tag number=%d, type=%d)\n", 
		i, f->name().c_str(), f->number(), f->type() ) ; 
	i++; 
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
 */
RcppExport SEXP getProtobufDescriptor( SEXP type ){

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
	
	SEXP ptr ; 
	// TODO: should we implement the finalizer for this external pointer
	PROTECT(ptr = R_MakeExternalPtr( (void*)desc, R_NilValue, R_NilValue));
	UNPROTECT(1); 

#ifdef RPB_DEBUG
Rprintf( "</getProtobufDescriptor>\n" ) ;
#endif
	
	return ptr ;
}


/**
 * make a new protobuf message
 *
 * @param descriptor a "protobufDescriptor" R object
 */
RcppExport SEXP newProtoMessage( SEXP descriptor ){

#ifdef RPB_DEBUG
Rprintf( "<newProtoMessage>\n" ) ;
#endif

	/* the message type */
	SEXP type = GET_SLOT( descriptor, install("type") ) ;
	
	/* the pointer to the c++ descriptor object */
	SEXP desc_ptr  = GET_SLOT( descriptor, install("pointer") ) ;

#ifdef RPB_DEBUG
PRINT_DEBUG_INFO( "type", type ) ;
PRINT_DEBUG_INFO( "desc_ptr", desc_ptr ) ;
#endif
	
	/* create the a prototype for this message and create an external pointer to it */
	SEXP p ; 
	// TODO: replace 0 with some C++ pointer
	// TODO: implement the finalizer for this external pointer
	PROTECT(p = R_MakeExternalPtr(0, R_NilValue, R_NilValue));
	UNPROTECT(1); 
	
#ifdef RPB_DEBUG
Rprintf( "</newProtoMessage>\n" ) ;
#endif

	return p ;
}


/**
 * extract a field from a message
 *
 * @param pointer external pointer to a message
 * @param name name of the field
 *
 * @return the field called "name" of the message if the 
 *         message has the field, otherwise an error is generated
 */
RcppExport SEXP getMessageField( SEXP pointer, SEXP name ){
	
#ifdef RPB_DEBUG
Rprintf( "<getMessageField>\n" ) ;

PRINT_DEBUG_INFO( "pointer", pointer ) ;
PRINT_DEBUG_INFO( "name", name ) ;
#endif

	/* TODO: do something */
	

#ifdef RPB_DEBUG
Rprintf( "</getMessageField>\n" ) ;
#endif
	
	return R_NilValue ;
	
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
RcppExport SEXP setMessageField( SEXP pointer, SEXP name, SEXP value ){
	
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
RcppExport SEXP do_dollar_Descriptor( SEXP pointer, SEXP name ){
	
	const char * what = CHAR( STRING_ELT( name, 0 ) ) ;
	Descriptor * desc = (Descriptor*) EXTPTR_PTR(pointer) ;
	
}


} // namespace

} // namespace rprotobuf
} // namespace rproject
} // namespace org

