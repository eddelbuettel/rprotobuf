#include "rprotobuf.h"

/* :tabSize=4:indentSize=4:noTabs=false:folding=explicit:collapseFolds=1: */

namespace rprotobuf{
	
	// {{{ input streams
	
	// {{{ ZeroCopyInputStream
	SEXP ZeroCopyInputStream_Next( SEXP xp ){
		GPB::io::ZeroCopyInputStream* stream = (GPB::io::ZeroCopyInputStream*)XPP(xp) ;
		int s = 0 ;
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
	// {{{ ArrayInputStream
	void ArrayInputStream_finalizer(SEXP xp){
		if (TYPEOF(xp)==EXTPTRSXP) {
			GPB::io::ArrayInputStream* stream = (GPB::io::ArrayInputStream*)XPP(xp) ;
			FIN_DBG( stream, "ArrayInputStream" ) ;
			delete stream;
		}
	}
	
	SEXP ArrayInputStream_new( SEXP payload, SEXP block_size){
		if( TYPEOF(payload) != RAWSXP ){
			Rf_error( "expecting a raw vector" );  
		}
		
		int bs = INTEGER(block_size)[0];
		
		SEXP oo = PROTECT( NEW_OBJECT(MAKE_CLASS("ArrayInputStream")) );
  		if (!Rf_inherits(oo, "ArrayInputStream"))
  		  throwException("unable to create 'ArrayInputStream' S4 object", "CannotCreateObjectException" );
  		
		/* FIXME: should we memcpy the payload or is this fine */
		GPB::io::ArrayInputStream* stream = 
			new GPB::io::ArrayInputStream( RAW(payload), LENGTH(payload), bs ) ;
		
		/* we keep the payload protected from GC */
		SEXP ptr = PROTECT( 
			R_MakeExternalPtr( (void*)stream, R_NilValue, payload));
		
		/* delete the stream when the xp is GC'ed*/
		R_RegisterCFinalizerEx( ptr, ArrayInputStream_finalizer , _FALSE_ ) ;
		SET_SLOT( oo, Rf_install("pointer"), ptr ) ;
		
		UNPROTECT(2); /* oo, ptr */
		return oo ;
	}
	// }}}
	// }}}
	
	// {{{ output streams
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
	// }}}
	
} // namespace rprotobuf

