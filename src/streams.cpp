#include "rprotobuf.h"

/* :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1: */

namespace rprotobuf{
	
	// {{{ ZeroCopyInputStream
	SEXP ZeroCopyInputStream_Next( SEXP xp, SEXP size){
		GPB::io::ZeroCopyInputStream* stream = (GPB::io::ZeroCopyInputStream*)XPP(xp) ;
		int s = GET_int(size, 0) ;
		SEXP result = R_NilValue ; // -Wall 
		const void* in ;
		bool res = stream->Next( &in, &s );
		if( !res ){
			Rf_error( "cannot read from stream" ) ;
		} else{
			result = PROTECT( Rf_allocVector(RAWSXP, s) ) ;
			memcpy( RAW(result), in, s ) ;
			UNPROTECT(1) ; /* result */
		}
		return result ;
	}
	
	SEXP ZeroCopyInputStream_BackUp(SEXP xp, SEXP size){
		GPB::io::ZeroCopyInputStream* stream = (GPB::io::ZeroCopyInputStream*)XPP(xp);
		int s = GET_int(size, 0) ;
		if( s <= 0 ){
			Rf_error( "can only BackUp with positive numbers" ) ;
		}
		stream->BackUp( s ) ;
		return R_NilValue ;
	}
	
	
	SEXP ZeroCopyInputStream_Skip(SEXP xp, SEXP size){
		GPB::io::ZeroCopyInputStream* stream = (GPB::io::ZeroCopyInputStream*)XPP(xp);
		int s = GET_int(size, 0) ;
		bool res = stream->Skip(s) ;
		return( Rf_ScalarLogical( res ? _TRUE_ : _FALSE_ ) ) ;
	}
	
	SEXP ZeroCopyInputStream_ByteCount(SEXP xp){
		GPB::io::ZeroCopyInputStream* stream = (GPB::io::ZeroCopyInputStream*)XPP(xp);
		return( Rf_ScalarReal((double)stream->ByteCount())) ;
	}
	// }}}
	
	// {{{ ZeroCopyOutputStream
	SEXP ZeroCopyOutputStream_Next( SEXP xp, SEXP payload){
		GPB::io::ZeroCopyOutputStream* stream = (GPB::io::ZeroCopyOutputStream*)XPP(xp) ;
		void* out ;
		int s = LENGTH(payload) ;
		bool res = stream->Next( &out, &s );
		if( !res ){
			Rf_error( "cannot write from stream" ) ;
		} 
		memcpy( out, RAW(payload), s ) ;
		return Rf_ScalarInteger(s) ;
	}
	
	SEXP ZeroCopyOutputStream_ByteCount(SEXP xp){
		GPB::io::ZeroCopyOutputStream* stream = (GPB::io::ZeroCopyOutputStream*)XPP(xp);
		return( Rf_ScalarReal((double)stream->ByteCount())) ;
	}
	
	SEXP ZeroCopyOutputStream_BackUp(SEXP xp, SEXP count){
		GPB::io::ZeroCopyOutputStream* stream = (GPB::io::ZeroCopyOutputStream*)XPP(xp);
		int s = GET_int(count, 0) ;
		stream->BackUp( s ) ;
		return R_NilValue ;
	}
	// }}}
	
	
} // namespace rprotobuf

