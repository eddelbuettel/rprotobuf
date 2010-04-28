// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 8 -*-
//
// rprotobuf.h: R/C++ interface class library
//
// Copyright (C) 2009 - 2010 Dirk Eddelbuettel and Romain Francois
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
namespace GPB = google::protobuf;

#define R_NO_REMAP

/* we need to read and write to connections */
#define NEED_CONNECTION_PSTREAMS

#include <RcppCommon.h>

RCPP_ENUM_TRAITS(GPB::FieldDescriptor::Label)
RCPP_ENUM_TRAITS(GPB::FieldDescriptor::CppType)
RCPP_ENUM_TRAITS(GPB::FieldDescriptor::Type)

RCPP_TRAITS(GPB::int64,REALSXP)
RCPP_TRAITS(GPB::uint64,REALSXP)

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

} // namespace rprotobuf

namespace rprotobuf {

	class S4_EnumValueDescriptor : public Rcpp::S4 {
	public:
		S4_EnumValueDescriptor( const GPB::EnumValueDescriptor* d) : S4("EnumValueDescriptor"){
		
			if( d ){
				slot( "pointer" ) = Rcpp::XPtr<GPB::EnumValueDescriptor>( 
					const_cast<GPB::EnumValueDescriptor*>(d), false) ;
			} else{
				setSEXP( R_NilValue ); 
			}
		}
		
		S4_EnumValueDescriptor( const S4_EnumValueDescriptor& other) : S4(){
			setSEXP( other.asSexp() );
		}
		S4_EnumValueDescriptor& operator=( const S4_EnumValueDescriptor& other){
			setSEXP( other.asSexp() );
			return *this ;
		}
		
	} ;
	
	
	class S4_Descriptor : public Rcpp::S4 {
	public:
		S4_Descriptor( const GPB::Descriptor* d) : S4( "Descriptor" ){
			slot( "pointer" ) = Rcpp::XPtr<GPB::Descriptor>( 
				const_cast<GPB::Descriptor*>(d), false) ;
			slot( "type" )    = d->full_name() ;
		}
		
		S4_Descriptor( const S4_Descriptor& other) : S4(){
			setSEXP( other.asSexp() );
		}
		S4_Descriptor& operator=( const S4_Descriptor& other){
			setSEXP( other.asSexp() );
			return *this ;
		}
	} ;
	
	class S4_FieldDescriptor : public Rcpp::S4 {
	public:
		S4_FieldDescriptor( const GPB::FieldDescriptor* d) : S4( "FieldDescriptor" ){
			slot( "pointer" ) = Rcpp::XPtr<GPB::FieldDescriptor>( 
				const_cast<GPB::FieldDescriptor*>(d), false) ;
			slot( "name" )      = d->name() ;
			slot( "full_name" ) = d->full_name() ;
			slot( "type" )      = d->containing_type()->full_name() ;
		}
		
		S4_FieldDescriptor( const S4_FieldDescriptor& other) : S4(){
			setSEXP( other.asSexp() );
		}
		S4_FieldDescriptor& operator=( const S4_FieldDescriptor& other){
			setSEXP( other.asSexp() );
			return *this ;
		}
	} ;
	

	class S4_ServiceDescriptor : public Rcpp::S4 {
	public:
		S4_ServiceDescriptor( const GPB::ServiceDescriptor* d) : S4( "ServiceDescriptor" ){
			slot( "pointer" ) = Rcpp::XPtr<GPB::ServiceDescriptor>( 
				const_cast<GPB::ServiceDescriptor*>(d), false) ;
		}
		
		S4_ServiceDescriptor( const S4_ServiceDescriptor& other) : S4(){
			setSEXP( other.asSexp() );
		}
		S4_ServiceDescriptor& operator=( const S4_ServiceDescriptor& other){
			setSEXP( other.asSexp() );
			return *this ;
		}
	} ;
	
	class S4_MethodDescriptor : public Rcpp::S4 {
	public:
		S4_MethodDescriptor( const GPB::MethodDescriptor* d) : S4( "MethodDescriptor" ){
			slot( "pointer" ) = Rcpp::XPtr<GPB::MethodDescriptor>( 
				const_cast<GPB::MethodDescriptor*>(d), false) ;
		}
		
		S4_MethodDescriptor( const S4_MethodDescriptor& other) : S4(){
			setSEXP( other.asSexp() );
		}
		S4_MethodDescriptor& operator=( const S4_MethodDescriptor& other){
			setSEXP( other.asSexp() );
			return *this ;
		}
	} ;
	
	class S4_EnumDescriptor : public Rcpp::S4 {
	public:
		S4_EnumDescriptor( const GPB::EnumDescriptor* d) : S4( "EnumDescriptor" ){
			slot( "pointer" ) = Rcpp::XPtr<GPB::EnumDescriptor>( 
				const_cast<GPB::EnumDescriptor*>(d), false) ;
			slot( "name" )     = d->name() ;
			slot( "full_name") = d->full_name() ;
			const GPB::Descriptor *type_desc = d->containing_type() ;
			if( type_desc ){
				slot( "type" ) = type_desc->full_name()  ;
			} else{
				slot( "type" ) = Rcpp::StringVector( (size_t)0) ;
			}
			
		}
		
		S4_EnumDescriptor( const S4_EnumDescriptor& other) : S4(){
			setSEXP( other.asSexp() );
		}
		S4_EnumDescriptor& operator=( const S4_EnumDescriptor& other){
			setSEXP( other.asSexp() );
			return *this ;
		}
	} ;

	class S4_Message : public Rcpp::S4 {
	public:
		S4_Message( const GPB::Message* d) : S4( "Message" ){
			slot( "pointer" ) = Rcpp::XPtr<GPB::Message>( 
				const_cast<GPB::Message*>(d), true) ;
			slot( "type" ) = d->GetDescriptor()->full_name() ;
		}
		
		S4_Message( const S4_Message& other) : S4(){
			setSEXP( other.asSexp() );
		}
		S4_Message& operator=( const S4_Message& other){
			setSEXP( other.asSexp() );
			return *this ;
		}
	} ;
	
/* in rprotobuf.cpp */
GPB::Message* PROTOTYPE( const GPB::Descriptor*) ;
GPB::Message* CLONE(const GPB::Message*) ;
RcppExport SEXP do_dollar_Descriptor( SEXP, SEXP ) ;
RcppExport SEXP newProtoMessage( SEXP) ;
RcppExport SEXP getProtobufDescriptor( SEXP ) ;
RcppExport SEXP readProtoFiles( SEXP, SEXP ); 
RcppExport Rboolean isMessage( SEXP, const char* ) ;
RcppExport GPB::FieldDescriptor* getFieldDescriptor(GPB::Message*, SEXP) ;
RcppExport SEXP check_libprotobuf_version( SEXP ) ;
RcppExport SEXP get_protobuf_library_version() ;
                                                                                    
/* in constructors.cpp */
void Message_finalizer( SEXP ) ;
RcppExport SEXP new_RS4_Descriptor( const GPB::Descriptor*  ); 
RcppExport SEXP new_RS4_FieldDescriptor( const GPB::FieldDescriptor* ); 
RcppExport SEXP new_RS4_EnumDescriptor( const GPB::EnumDescriptor*); 
RcppExport SEXP new_RS4_Message_( const GPB::Message* );
RcppExport SEXP new_RS4_ServiceDescriptor( const GPB::ServiceDescriptor* ) ;
RcppExport SEXP new_RS4_MethodDescriptor( const GPB::MethodDescriptor* ) ;
RcppExport SEXP new_RS4_FileDescriptor( const GPB::FileDescriptor* ) ;
RcppExport SEXP new_RS4_EnumValueDescriptor( const GPB::EnumValueDescriptor* ) ;

/* in extractors.cpp */
RcppExport SEXP getMessageField( SEXP, SEXP ); 
RcppExport SEXP extractFieldAsSEXP( const Rcpp::XPtr<GPB::Message>& , const GPB::Descriptor*, const GPB::FieldDescriptor* ) ;
RcppExport SEXP get_message_descriptor( SEXP );
RcppExport int MESSAGE_GET_REPEATED_INT( GPB::Message*, GPB::FieldDescriptor*, int) ;
RcppExport double MESSAGE_GET_REPEATED_DOUBLE( GPB::Message*, GPB::FieldDescriptor*, int) ;
RcppExport SEXP get_service_method( SEXP, SEXP) ; 

/* in completion.cpp */
RcppExport SEXP getMessageFieldNames( SEXP) ;
RcppExport SEXP getMessageFieldNames_(const Rcpp::XPtr<GPB::Message>& message) ;
RcppExport SEXP getDescriptorMemberNames( SEXP) ;
RcppExport SEXP getFileDescriptorMemberNames( SEXP) ;
RcppExport SEXP getEnumDescriptorConstantNames( SEXP ) ;
RcppExport SEXP getServiceDescriptorMethodNames( SEXP ) ;

/* in exceptions.cpp */
RcppExport SEXP throwException( const char*, const char*) ;

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
RcppExport void CHECK_values_for_enum( GPB::FieldDescriptor*, SEXP) ;
RcppExport void CHECK_messages( GPB::FieldDescriptor*, SEXP) ;

/* in aslist.cpp */
RcppExport SEXP as_list_descriptor( SEXP ); 
RcppExport SEXP as_list_enum_descriptor( SEXP );
RcppExport SEXP as_list_file_descriptor( SEXP ) ;
RcppExport SEXP as_list_service_descriptor( SEXP ); 

/* in merge.cpp */
RcppExport SEXP merge_message( SEXP, SEXP ); 

/* in read.cpp */
RcppExport SEXP readMessageFromFile( SEXP, SEXP ) ;
RcppExport SEXP readMessageFromConnection( SEXP, SEXP ) ;
RcppExport SEXP readMessageFromRawVector( SEXP, SEXP );

/* in size.cpp */
RcppExport SEXP get_message_bytesize( SEXP ) ;
RcppExport SEXP get_field_size(SEXP, SEXP);
RcppExport SEXP set_field_size(SEXP, SEXP, SEXP);

/* in swap.cpp */
RcppExport SEXP message_swap_fields(SEXP, SEXP, SEXP, SEXP) ;

/* in set.cpp */
RcppExport SEXP set_field_values( SEXP, SEXP, SEXP, SEXP ) ;
RcppExport SEXP get_field_values( SEXP, SEXP, SEXP) ;

/* in identical.cpp */
RcppExport SEXP identical_messages( SEXP, SEXP) ;
RcppExport SEXP all_equal_messages( SEXP, SEXP, SEXP) ;

/* in add.cpp */
RcppExport SEXP message_add_values( SEXP, SEXP, SEXP);

/* in fileDescriptor.cpp */
RcppExport SEXP get_message_file_descriptor( SEXP) ;
RcppExport SEXP get_descriptor_file_descriptor(SEXP) ;
RcppExport SEXP get_enum_file_descriptor(SEXP) ;
RcppExport SEXP get_field_file_descriptor(SEXP) ;
RcppExport SEXP get_service_file_descriptor(SEXP) ;
RcppExport SEXP get_method_file_descriptor(SEXP) ;

/* in name.cpp */
RcppExport SEXP name_descriptor( SEXP, SEXP ) ;
RcppExport SEXP name_field_descriptor( SEXP, SEXP ) ;
RcppExport SEXP name_enum_descriptor( SEXP, SEXP ) ;
RcppExport SEXP name_service_descriptor( SEXP, SEXP ) ;
RcppExport SEXP name_method_descriptor( SEXP, SEXP ) ;
RcppExport SEXP name_file_descriptor( SEXP ) ;

/* in containing_type.cpp */
RcppExport SEXP containing_type__Descriptor( SEXP ); 
RcppExport SEXP containing_type__EnumDescriptor( SEXP ); 
RcppExport SEXP containing_type__FieldDescriptor( SEXP ); 
RcppExport SEXP containing_type__ServiceDescriptor( SEXP ); 
RcppExport SEXP containing_type__MethodDescriptor( SEXP ); 

/* in field_count.cpp */
RcppExport SEXP field_count__Descriptor( SEXP );
RcppExport SEXP nested_type_count__Descriptor( SEXP );
RcppExport SEXP enum_type_count__Descriptor( SEXP );
RcppExport SEXP Descriptor_getFieldByIndex( SEXP, SEXP) ;
RcppExport SEXP Descriptor_getFieldByNumber( SEXP, SEXP ) ;
RcppExport SEXP Descriptor_getFieldByName(SEXP, SEXP) ;
RcppExport SEXP Descriptor_getNestedTypeByIndex( SEXP, SEXP) ;
RcppExport SEXP Descriptor_getNestedTypeByName( SEXP, SEXP); 
RcppExport SEXP Descriptor_getEnumTypeByIndex( SEXP, SEXP);
RcppExport SEXP Descriptor_getEnumTypeByName( SEXP, SEXP);

/* in ServiceDescriptor_wrapper.cpp */
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

RcppExport SEXP ArrayInputStream_new( SEXP, SEXP ) ;

RcppExport SEXP ArrayOutputStream_new( SEXP, SEXP ) ;

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

} // namespace rprotobuf


#endif
