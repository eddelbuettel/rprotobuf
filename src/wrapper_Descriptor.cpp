#include "rprotobuf.h"

namespace rprotobuf{

#undef METHOD
#define METHOD(__NAME__) RCPP_PP_CAT(Descriptor__,__NAME__)	

RCPP_XP_METHOD_0( METHOD(as_character), GPB::Descriptor          , DebugString)
RCPP_XP_METHOD_0( METHOD(field_count), GPB::Descriptor, field_count )
RCPP_XP_METHOD_0( METHOD(nested_type_count), GPB::Descriptor, nested_type_count )
RCPP_XP_METHOD_0( METHOD(enum_type_count), GPB::Descriptor, enum_type_count )

RCPP_XP_METHOD_CAST_0( METHOD(containing_type), GPB::Descriptor, containing_type, S4_Descriptor )


/**
 * returns the names of the members contained in the descriptor
 * (nested types, enums, fields)
 *
 * @param xp external pointer to a Descriptor
 *
 * @return member names, as an R character vector (STRSXP)
 */
RCPP_FUNCTION_1( Rcpp::CharacterVector, METHOD(getMemberNames), Rcpp::XPtr<GPB::Descriptor> desc ){
	
	int nfields = desc->field_count() ;
	int ntypes  = desc->nested_type_count() ;
	int nenums  = desc->enum_type_count() ;
	
	Rcpp::CharacterVector res(nfields + ntypes + nenums ) ;
	int j=0; 
	for (int i=0; i<nfields; i++, j++){
		res[j] = desc->field(i)->name() ;
	}
	for (int i=0;i<ntypes; i++, j++){
		res[j] = desc->nested_type(i)->name() ;
	}
	for (int i=0; i<nenums; i++, j++){
		res[j] = desc->enum_type(i)->name();
	}
	return( res );
}

/**
 * @param xp external pointer to a Descriptor
 * @return the descriptor as an R list
 */
RCPP_FUNCTION_1( Rcpp::List, METHOD(as_list), Rcpp::XPtr<GPB::Descriptor> desc ){
	
	int nfields = desc->field_count() ;
	int ntypes  = desc->nested_type_count() ;
	int nenums  = desc->enum_type_count() ;
	int n       = nfields + ntypes + nenums ;
	
 	Rcpp::CharacterVector names(n) ; 
	Rcpp::List res(n); 
	int i=0;
	int j=0; 
	for( i=0; i<nfields; j++, i++){
		const GPB::FieldDescriptor* fd = desc->field(i) ;
		res[j] = S4_FieldDescriptor( fd );
		names[j] = fd->name() ; 
	}
	for( i=0; i<ntypes; j++, i++){
		const GPB::Descriptor* d  = desc->nested_type(i) ;
		res[j] = S4_Descriptor( d );
		names[j] = d->name() ;
	}
	for( i=0; i<nenums; j++, i++){
		const GPB::EnumDescriptor* ed = desc->enum_type(i) ;
		res[j] = S4_EnumDescriptor( ed );
		names[j] = ed->name() ;
	}
	res.names() = names ;
	
	return res; 
}

RCPP_FUNCTION_1(S4_Message, METHOD(as_Message) , Rcpp::XPtr<GPB::Descriptor> d ){
	GPB::DescriptorProto* message = new GPB::DescriptorProto() ; 
	d->CopyTo( message ); 
	return message  ;
}

RCPP_FUNCTION_2( S4_FieldDescriptor, METHOD(field), Rcpp::XPtr<GPB::Descriptor> d, int i){
	return d->field( i ) ;
}

RCPP_FUNCTION_2( S4_FieldDescriptor, METHOD(FindFieldByNumber), Rcpp::XPtr<GPB::Descriptor> d, int num){
	return d->FindFieldByNumber( num ) ;
}

RCPP_FUNCTION_2( S4_FieldDescriptor, METHOD(FindFieldByName), Rcpp::XPtr<GPB::Descriptor> d, std::string nam ){
	return d->FindFieldByName( nam ) ;
}

RCPP_FUNCTION_2( S4_Descriptor, METHOD(nested_type), Rcpp::XPtr<GPB::Descriptor> d, int i){
	return d->nested_type( i ) ;
}

RCPP_FUNCTION_2( S4_Descriptor, METHOD(FindNestedTypeByName), Rcpp::XPtr<GPB::Descriptor> d, std::string nam){
	return d->FindNestedTypeByName( nam ) ;
}

RCPP_FUNCTION_2( S4_EnumDescriptor, METHOD(enum_type), Rcpp::XPtr<GPB::Descriptor> d, int i){
	return d->enum_type( i ) ;
}

// FIXME: two methods cant have the same name
// RCPP_FUNCTION_2( S4_EnumDescriptor, METHOD(enum_type), Rcpp::XPtr<GPB::Descriptor> d, std::string name){
// 	return d->FindEnumTypeByName( i ) ;
// }

RCPP_FUNCTION_1( S4_FileDescriptor, METHOD(fileDescriptor), Rcpp::XPtr<GPB::Descriptor> desc){
	return S4_FileDescriptor( desc->file() ); 
}

RCPP_FUNCTION_2( std::string, METHOD(name), Rcpp::XPtr<GPB::Descriptor> d, bool full){
	return full ? d->full_name() : d->name() ;
}

RCPP_FUNCTION_2( S4_Message, METHOD(readMessageFromFile), Rcpp::XPtr<GPB::Descriptor> desc, std::string filename ){
	/* open the file to read in binary mode */
	int file = open( filename.c_str() , O_RDONLY | O_BINARY);
	
	/* create a prototype of the message we are going to read */
	GPB::Message* message = PROTOTYPE( desc ) ; 
	if( !message ){
		throw std::range_error( "could not call factory->GetPrototype(desc)->New()" ) ; 
	}
	
	/* read the message from the file */
	message->ParsePartialFromFileDescriptor( file ); 
	close( file ) ;
	return( S4_Message( message ) ) ;
}

RCPP_FUNCTION_2( S4_Message, METHOD(readMessageFromConnection), Rcpp::XPtr<GPB::Descriptor> desc, int conn_id ){
	RconnectionCopyingInputStream wrapper( conn_id ) ;
	GPB::io::CopyingInputStreamAdaptor stream( &wrapper ) ;
	GPB::io::CodedInputStream coded_stream(&stream ) ;
	
	/* create a prototype of the message we are going to read */
	GPB::Message* message = PROTOTYPE( desc ) ; 
	if( !message ){
		throw std::range_error( "could not call factory->GetPrototype(desc)->New()" ) ; 
	}
	message->ParsePartialFromCodedStream( &coded_stream) ;
	
	S4_Message res( message ) ;
	return res ;
}

RCPP_FUNCTION_2( S4_Message, METHOD(readMessageFromRawVector), Rcpp::XPtr<GPB::Descriptor> desc, Rcpp::RawVector raw){
	GPB::io::ArrayInputStream ais( (void*)raw.begin(), raw.size() ); 
	GPB::io::CodedInputStream stream( &ais ) ; 
	
	GPB::Message* message = PROTOTYPE( desc ) ; 
	if( !message ){
		throw std::range_error( "could not call factory->GetPrototype(desc)->New()" ) ; 
	}
	
	message->MergePartialFromCodedStream( &stream ) ;
	return( S4_Message( message ) ) ;
}

RCPP_FUNCTION_2( S4_Message, METHOD(readASCII_FromString), Rcpp::XPtr<GPB::Descriptor> desc, std::string input){
	GPB::Message* message = PROTOTYPE( desc ) ; 
	GPB::TextFormat::ParseFromString( input, message ) ;
	return( S4_Message( message ) ) ;
}

#undef METHOD

} // namespace rprotobuf
