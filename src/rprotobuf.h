#ifndef RPROTOBUF_H
#define RPROTOBUF_H

/* should we check this is available */
#include <fcntl.h>
/* FIXME: need to include some header file instead of this define */
#define O_BINARY 0

#include <google/protobuf/descriptor.h>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/message.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>

#define R_NO_REMAP

/* we need to read and write to connections */
#define NEED_CONNECTION_PSTREAMS

#include <R.h>
#include <Rdefines.h>
#include <Rinternals.h>
#include <R_ext/Callbacks.h>

#include <Rcpp.h>

/* undefine this to quiet debug messages */
// #define RPB_DEBUG

#define PRINT_DEBUG_INFO(name,o) \
	Rprintf( "     %s [%d] =     ", name, TYPEOF(o) ) ; \
	Rf_PrintValue( o ) ; \

#define RPROTOBUF_LOOKUP 24
// #define LOOKUP_DEBUG

/* FIXME : quick hack because just using TRUE and FALSE did not work in lookup.cpp */
#define _TRUE_ (Rboolean)TRUE
#define _FALSE_ (Rboolean)FALSE

#define GET_MESSAGE_POINTER_FROM_XP(xp)  (Message*) EXTPTR_PTR( xp )
#define GET_MESSAGE_POINTER_FROM_S4(m)   (Message*) EXTPTR_PTR( GET_SLOT( m, Rf_install("pointer") ) )

#define GET_DESCRIPTOR_POINTER_FROM_XP(xp)  (Descriptor*) EXTPTR_PTR( xp )
#define GET_DESCRIPTOR_POINTER_FROM_S4(m)   (Descriptor*) EXTPTR_PTR( GET_SLOT( m, Rf_install("pointer") ) )


using namespace google::protobuf::compiler ;
using namespace google::protobuf ;

namespace rprotobuf{

/* in rprotobuf.cpp */
RcppExport SEXP do_dollar_Descriptor( SEXP, SEXP ) ;
RcppExport SEXP newProtoMessage( SEXP) ;
RcppExport SEXP getProtobufDescriptor( SEXP ) ;
RcppExport SEXP readProtoFiles( SEXP ); 
RcppExport Rboolean isMessage( SEXP, const char* ) ;
RcppExport FieldDescriptor* getFieldDescriptor(Message*, SEXP) ;
RcppExport SEXP check_libprotobuf_version( SEXP ) ;
RcppExport SEXP get_protobuf_library_version() ;

/* in constructors.cpp */
RcppExport SEXP new_RS4_Descriptor( const Descriptor * ); 
RcppExport SEXP new_RS4_FieldDescriptor( const FieldDescriptor *); 
RcppExport SEXP new_RS4_EnumDescriptor( const EnumDescriptor *); 
RcppExport SEXP new_RS4_Message( const Message *, SEXP ); 
RcppExport SEXP new_RS4_Message_( const Message* ); 

/* in extractors.cpp */
RcppExport SEXP getMessageField( SEXP, SEXP ); 
RcppExport SEXP extractFieldAsSEXP( const Message *, const Descriptor*, const FieldDescriptor *) ;
RcppExport SEXP get_message_descriptor( SEXP );
RcppExport int MESSAGE_GET_REPEATED_INT( Message*, FieldDescriptor*, int) ;
RcppExport double MESSAGE_GET_REPEATED_DOUBLE( Message*, FieldDescriptor*, int) ;


/* in completion.cpp */
RcppExport SEXP getMessageFieldNames( SEXP) ;
RcppExport SEXP getDescriptorMemberNames( SEXP) ;
RcppExport SEXP getEnumDescriptorConstantNames( SEXP ) ;

/* in exceptions.cpp */
RcppExport SEXP throwException( const char*, const char*) ;

/* in serialize.cpp */
RcppExport SEXP getMessagePayload( SEXP ) ;
RcppExport SEXP serializeMessageToFile( SEXP , SEXP ) ;
RcppExport SEXP serialize_to_connection( SEXP, SEXP ) ;

/* in lookup.cpp */
RcppExport SEXP newProtocolBufferLookup() ;

/* in mutators.cpp */
RcppExport SEXP setMessageField( SEXP, SEXP, SEXP ) ;
RcppExport int GET_int( SEXP, int ) ;
RcppExport double GET_double( SEXP, int ) ;
RcppExport float GET_float( SEXP, int ) ;
RcppExport int32 GET_int32( SEXP, int) ;
RcppExport int64 GET_int64( SEXP, int) ;
RcppExport uint32 GET_uint32( SEXP, int) ;
RcppExport uint64 GET_uint64( SEXP, int ) ;
RcppExport bool GET_bool( SEXP, int) ;
RcppExport std::string GET_stdstring( SEXP, int ) ;
RcppExport void CHECK_values_for_enum( FieldDescriptor*, SEXP) ;
RcppExport void CHECK_messages( FieldDescriptor*, SEXP) ;

/* in aslist.cpp */
RcppExport SEXP as_list_message( SEXP ) ;
RcppExport SEXP as_list_descriptor( SEXP ); 
RcppExport SEXP as_list_enum_descriptor( SEXP ); 

/* in ascharacter.cpp */
RcppExport SEXP as_character_message( SEXP );
RcppExport SEXP as_character_descriptor( SEXP ); 
RcppExport SEXP as_character_enum_descriptor( SEXP ); 
RcppExport SEXP as_character_field_descriptor(SEXP);
RcppExport SEXP get_value_of_enum( SEXP, SEXP); 

/* in update.cpp */
RcppExport SEXP update_message( SEXP, SEXP) ;

/* in has.cpp */
RcppExport SEXP message_has_field( SEXP, SEXP ); 

/* in clone.cpp */
RcppExport SEXP clone_message( SEXP ) ;

/* in merge.cpp */
RcppExport SEXP merge_message( SEXP, SEXP ); 

/* in read.cpp */
RcppExport SEXP readMessageFromFile( SEXP, SEXP ) ;
RcppExport SEXP readMessageFromConnection( SEXP, SEXP ) ; 

/* in size.cpp */
RcppExport SEXP get_message_bytesize( SEXP ) ;
RcppExport SEXP get_field_size(SEXP, SEXP);
RcppExport SEXP set_field_size(SEXP, SEXP, SEXP);

/* in length.cpp */
RcppExport SEXP get_message_length( SEXP ) ;

/* in initialized.cpp */
RcppExport SEXP is_message_initialized( SEXP ) ;

/* in clear.cpp */
RcppExport SEXP clear_message( SEXP ) ;
RcppExport SEXP clear_message_field( SEXP, SEXP ) ;

/* in swap.cpp */
RcppExport SEXP message_swap_fields(SEXP, SEXP, SEXP, SEXP) ;

/* in set.cpp */
RcppExport SEXP set_field_values( SEXP, SEXP, SEXP, SEXP ) ;
RcppExport SEXP get_field_values( SEXP, SEXP, SEXP) ;

/* in identical.cpp */
RcppExport SEXP identical_messages( SEXP, SEXP) ;

} // namespace rprotobuf


#endif
