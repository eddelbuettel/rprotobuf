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
#define LOOKUP_DEBUG

/* FIXME : quick hack because just using TRUE and FALSE did not work in lookup.cpp */
#define _TRUE_ (Rboolean)TRUE
#define _FALSE_ (Rboolean)FALSE

using namespace google::protobuf::compiler ;
using namespace google::protobuf ;

namespace org{
namespace rproject{
namespace rprotobuf{
namespace{

/* in rprotobuf.cpp */
RcppExport SEXP get_message_debug_string( SEXP ); 
RcppExport SEXP get_descriptor_debug_string( SEXP ); 
RcppExport SEXP do_dollar_Descriptor( SEXP, SEXP ) ;
RcppExport SEXP setMessageField( SEXP, SEXP, SEXP ) ;
RcppExport SEXP newProtoMessage( SEXP) ;
RcppExport SEXP getProtobufDescriptor( SEXP ) ;
RcppExport SEXP readProtoFiles( SEXP ); 

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

/* in exceptions.cpp */
RcppExport SEXP throwException( const char*, const char*) ;

/* in serialize.cpp */
RcppExport SEXP getMessagePayload( SEXP ) ;


} // namespace
} // namespace rprotobuf
} // namespace rproject
} // namespace org


#endif
