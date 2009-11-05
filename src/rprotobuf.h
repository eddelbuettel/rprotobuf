#ifndef RPROTOBUF_H
#define RPROTOBUF_H

#include <google/protobuf/descriptor.h>
#include <google/protobuf/compiler/importer.h>
#include <google/protobuf/dynamic_message.h>

#define R_NO_REMAP

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

/* in constructors.cpp */
RcppExport SEXP new_RS4_Descriptor( const Descriptor * ); 
RcppExport SEXP new_RS4_FieldDescriptor( const FieldDescriptor *); 
RcppExport SEXP new_RS4_EnumDescriptor( const EnumDescriptor *); 
RcppExport SEXP new_RS4_Message( const Message *, SEXP ); 
RcppExport SEXP new_RS4_Message_( const Message* ); 

/* in extractors.cpp */
RcppExport SEXP getMessageField( SEXP, SEXP ); 
RcppExport SEXP extractFieldAsSEXP( const Message *, const Descriptor*, const FieldDescriptor *) ;

/* in completion.cpp */
RcppExport SEXP getMessageFieldNames( SEXP) ;
RcppExport SEXP getDescriptorMemberNames( SEXP) ;
RcppExport SEXP getEnumDescriptorConstantNames( SEXP ) ;

/* in exceptions.cpp */
RcppExport SEXP throwException( const char*, const char*) ;

/* in serialize.cpp */
RcppExport SEXP getMessagePayload( SEXP ) ;

/* in lookup.cpp */
RcppExport SEXP newProtocolBufferLookup() ;

/* in mutators.cpp */
RcppExport int GETINT( SEXP, int) ;                                                                        
RcppExport SEXP setMessageField( SEXP, SEXP, SEXP ) ;

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

} // namespace rprotobuf


#endif
