// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-
//
// rprotobuf.h: R/C++ interface class library
//
// Copyright (C) 2009 - 2012  Dirk Eddelbuettel and Romain Francois
// Copyright (C) 2012 - 2013  Dirk Eddelbuettel, Romain Francois and Murray Stokely
//
// This file is part of RProtoBuf.
//
// RProtoBuf is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// RProtoBuf is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RProtoBuf.  If not, see <http://www.gnu.org/licenses/>.

#ifndef RPROTOBUF_H
#define RPROTOBUF_H

#include <unistd.h>	       // g++-4.7 wants this
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
#include <google/protobuf/service.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/text_format.h>
namespace GPB = google::protobuf;

#define R_NO_REMAP

/* we need to read and write to connections */
#define NEED_CONNECTION_PSTREAMS

#include <RcppCommon.h>

RCPP_ENUM_TRAITS(GPB::FieldDescriptor::Label)
RCPP_ENUM_TRAITS(GPB::FieldDescriptor::CppType)
RCPP_ENUM_TRAITS(GPB::FieldDescriptor::Type)

//RCPP_TRAITS(GPB::int64,REALSXP)
//RCPP_TRAITS(GPB::uint64,REALSXP)

#include <Rcpp.h>

#include <Rdefines.h>
#include <R_ext/Callbacks.h>


/* uncomment for debugging */
// #define RPB_DEBUG

#ifdef RPB_DEBUG
#define RPB_DEBUG_BEGIN(__WHAT__) Rprintf( "<" #__WHAT__ ">\n" ) ;
#define RPB_DEBUG_END(__WHAT__) Rprintf( "</" #__WHAT__ ">\n" ) ;
#else 
#define RPB_DEBUG_BEGIN(__WHAT__)
#define RPB_DEBUG_END(__WHAT__)

#endif

#define FIN_DBG(ptr, CLAZZ) 
// #define FIN_DBG(ptr, CLAZZ) Rprintf( "RProtoBuf finalizing %s (%p)\n", CLAZZ, ptr )

#define PRINT_DEBUG_INFO(name,o) \
	Rprintf( "     %s [%d] =     ", name, TYPEOF(o) ) ; \
	Rf_PrintValue( o ) ; \

#define RPROTOBUF_LOOKUP 24
// #define LOOKUP_DEBUG

/* FIXME : quick hack because just using TRUE and FALSE did not work in lookup.cpp */
#define _TRUE_ (Rboolean)TRUE
#define _FALSE_ (Rboolean)FALSE

#define GET_MESSAGE_POINTER_FROM_XP(xp)  (GPB::Message*) EXTPTR_PTR( xp )
#define GET_MESSAGE_POINTER_FROM_S4(m)   (GPB::Message*) EXTPTR_PTR( GET_SLOT( m, Rf_install("pointer") ) )

#define GET_DESCRIPTOR_POINTER_FROM_XP(xp)  (GPB::Descriptor*) EXTPTR_PTR( xp )
#define GET_DESCRIPTOR_POINTER_FROM_S4(m)   (GPB::Descriptor*) EXTPTR_PTR( GET_SLOT( m, Rf_install("pointer") ) )

#define GET_FIELD_DESCRIPTOR_POINTER_FROM_XP(xp)  (GPB::FieldDescriptor*) EXTPTR_PTR( xp )
#define GET_FIELD_DESCRIPTOR_POINTER_FROM_S4(m)   (GPB::FieldDescriptor*) EXTPTR_PTR( GET_SLOT( m, Rf_install("pointer") ) )

#define GET_ENUM_VALUE_DESCRIPTOR_POINTER_FROM_XP(xp)  (GPB::EnumValueDescriptor*) EXTPTR_PTR( xp )
#define GET_ENUM_VALUE_DESCRIPTOR_POINTER_FROM_S4(m)   (GPB::EnumValueDescriptor*) EXTPTR_PTR( GET_SLOT( m, Rf_install("pointer") ) )

#define GET_METHOD(xp)  (GPB::MethodDescriptor*) EXTPTR_PTR( xp )

#define COPYSTRING(s) s
#define THROW_SOCKET_ERROR(message) Rf_error( "%s : %s", message, strerror(sockerrno) )

#define XPP EXTPTR_PTR

#define NEW_S4_OBJECT(CLAZZ) SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS(CLAZZ)) ); \
  		if (!Rf_inherits(oo, CLAZZ)) throwException(CLAZZ, "CannotCreateObjectException" );
  		
namespace rprotobuf{

typedef GPB::int32  int32  ;
typedef GPB::uint32 uint32 ;
typedef GPB::int64  int64  ;
typedef GPB::uint64 uint64 ;
	
/* in rprotobuf.cpp */
GPB::Message* PROTOTYPE( const GPB::Descriptor*) ;
GPB::Message* CLONE(const GPB::Message*) ;
RcppExport SEXP do_dollar_Descriptor( SEXP, SEXP ) ;
RcppExport SEXP newProtoMessage( SEXP) ;
RcppExport SEXP getProtobufDescriptor( SEXP ) ;
RcppExport SEXP getExtensionDescriptor( SEXP ) ;
RcppExport SEXP readProtoFiles( SEXP, SEXP ); 
RcppExport Rboolean isMessage( SEXP, const char* ) ;
RcppExport GPB::FieldDescriptor* getFieldDescriptor(GPB::Message*, SEXP) ;

/* in extractors.cpp */
RcppExport SEXP getMessageField( SEXP, SEXP ); 
RcppExport SEXP extractFieldAsSEXP( const Rcpp::XPtr<GPB::Message>& , const GPB::FieldDescriptor* ) ;

/* in exceptions.cpp */
RcppExport SEXP throwException( const char*, const char*) ;

/* in lookup.cpp */
RcppExport SEXP newProtocolBufferLookup(SEXP) ;

/* in mutators.cpp */
RcppExport SEXP setMessageField( SEXP, SEXP, SEXP ) ;
int GET_int( SEXP, int ) ;
double GET_double( SEXP, int ) ;
float GET_float( SEXP, int ) ;
int32 GET_int32( SEXP, int) ;
int64 GET_int64( SEXP, int) ;
uint32 GET_uint32( SEXP, int) ;
uint64 GET_uint64( SEXP, int ) ;
bool GET_bool( SEXP, int) ;
std::string GET_stdstring( SEXP, int ) ;
std::string GET_bytes( SEXP, int ) ;
void CHECK_values_for_enum( const GPB::FieldDescriptor*, SEXP) ;
void CHECK_messages( const GPB::FieldDescriptor*, SEXP) ;

/* in wrapper_ServiceDescriptor.cpp */
RcppExport SEXP ServiceDescriptor_length(SEXP);
RcppExport SEXP ServiceDescriptor_method_count(SEXP) ;
RcppExport SEXP ServiceDescriptor_getMethodByIndex(SEXP, SEXP) ;
RcppExport SEXP ServiceDescriptor_getMethodByName(SEXP, SEXP) ;

/* in streams.cpp */
void ZeroCopyInputStreamWrapper_finalizer( SEXP ); 
void ZeroCopyOutputStreamWrapper_finalizer( SEXP ); 

RcppExport SEXP ZeroCopyInputStream_Next(SEXP) ;
RcppExport SEXP ZeroCopyInputStream_BackUp(SEXP, SEXP) ;
RcppExport SEXP ZeroCopyInputStream_ByteCount(SEXP) ;
RcppExport SEXP ZeroCopyInputStream_Skip(SEXP, SEXP) ;
RcppExport SEXP ZeroCopyInputStream_ReadRaw( SEXP, SEXP) ;
RcppExport SEXP ZeroCopyInputStream_ReadString( SEXP, SEXP) ;
RcppExport SEXP ZeroCopyInputStream_ReadVarint32( SEXP ) ;
RcppExport SEXP ZeroCopyInputStream_ReadVarint64( SEXP ) ;
RcppExport SEXP ZeroCopyInputStream_ReadLittleEndian32( SEXP ) ;
RcppExport SEXP ZeroCopyInputStream_ReadLittleEndian64( SEXP ) ;

RcppExport SEXP ZeroCopyOutputStream_Next(SEXP, SEXP) ;
RcppExport SEXP ZeroCopyOutputStream_BackUp(SEXP, SEXP) ;
RcppExport SEXP ZeroCopyOutputStream_ByteCount(SEXP) ;
RcppExport SEXP ZeroCopyOutputStream_WriteRaw( SEXP, SEXP);
RcppExport SEXP ZeroCopyOutputStream_WriteString( SEXP, SEXP);
RcppExport SEXP ZeroCopyOutputStream_WriteLittleEndian32( SEXP, SEXP );
RcppExport SEXP ZeroCopyOutputStream_WriteLittleEndian64( SEXP, SEXP );
RcppExport SEXP ZeroCopyOutputStream_WriteVarint32( SEXP, SEXP );
RcppExport SEXP ZeroCopyOutputStream_WriteVarint64( SEXP, SEXP );


RcppExport SEXP FileOutputStream_new( SEXP, SEXP, SEXP) ;
RcppExport SEXP FileOutputStream_Close( SEXP) ;
RcppExport SEXP FileOutputStream_Flush( SEXP) ;
RcppExport SEXP FileOutputStream_GetErrno( SEXP) ;
RcppExport SEXP FileOutputStream_SetCloseOnDelete( SEXP, SEXP ) ;

RcppExport SEXP FileInputStream_new( SEXP, SEXP, SEXP) ;
RcppExport SEXP FileInputStream_Close( SEXP) ;
RcppExport SEXP FileInputStream_GetErrno( SEXP) ;
RcppExport SEXP FileInputStream_SetCloseOnDelete( SEXP, SEXP ) ;

RcppExport SEXP ConnectionInputStream_new( SEXP , SEXP) ;

RcppExport SEXP ConnectionOutputStream_new( SEXP , SEXP) ;

	/**
	 * simple class that wraps together a ZeroCopyOutputStream 
	 * and its associated CodedOutputStream. Since we don't expose
	 * CodedOutputStream at the R level, this allows to keep only one such 
	 * object with each ZeroCopyOutputStream
	 */
	class ZeroCopyOutputStreamWrapper {
		public:	                                    
			ZeroCopyOutputStreamWrapper( GPB::io::ZeroCopyOutputStream* stream );
			~ZeroCopyOutputStreamWrapper() ;
			
			GPB::io::ZeroCopyOutputStream* get_stream(); 
			GPB::io::CodedOutputStream* get_coded_stream() ; 
			
		private: 
			GPB::io::ZeroCopyOutputStream* stream ;
			GPB::io::CodedOutputStream* coded_stream ;
} ;

	/**
	 * simple class that wraps together a ZeroCopyInputStream 
	 * and its associated CodedInputStream. Since we don't expose
	 * CodedInputStream at the R level, this allows to keep only one such 
	 * object with each zero copy input stream
	 */
	class ZeroCopyInputStreamWrapper {
		public:	
			ZeroCopyInputStreamWrapper( GPB::io::ZeroCopyInputStream* stream );
			~ZeroCopyInputStreamWrapper() ;
			
			GPB::io::ZeroCopyInputStream* get_stream(); 
			GPB::io::CodedInputStream* get_coded_stream() ; 
			
		private: 
			GPB::io::ZeroCopyInputStream* stream ;
			GPB::io::CodedInputStream* coded_stream ;
	} ;


} // namespace rprotobuf

#include "S4_classes.h"
#include "RconnectionCopyingInputStream.h"

#define GET_ZCIS(xp) ( (ZeroCopyInputStreamWrapper*)XPP(xp) )->get_stream() 
#define GET_CIS(xp) ( (ZeroCopyInputStreamWrapper*)XPP(xp) )->get_coded_stream()
#define GET_FIS(xp) (GPB::io::FileInputStream*)( (ZeroCopyInputStreamWrapper*)XPP(xp) )->get_stream() 

#define GET_ZCOS(xp) ( (ZeroCopyOutputStreamWrapper*)XPP(xp) )->get_stream() 
#define GET_COS(xp) ( (ZeroCopyOutputStreamWrapper*)XPP(xp) )->get_coded_stream() 
#define GET_FOS(xp) (GPB::io::FileOutputStream*)( (ZeroCopyOutputStreamWrapper*)XPP(xp) )->get_stream() 

#endif
