
#include "rprotobuf.h"

class RProtoBufLookup {
	
} ;

/* This uses the mechanism of the RObjectTables package
   see: http://www.omegahat.org/RObjectTables/ */

/**
 * Returns the R_UnboundValue
 */
SEXP R_getUnboundValue() {
    return(R_UnboundValue);
}

/**
 * @param name potential message type
 * @param canCache Can R cache this object
 * @param tb object table
 *
 * @return _TRUE_ if there is a message of the given type in the DescriptorPool
 */
/* not actually used by R */
Rboolean rProtoBufTable_exists(const char * const name, Rboolean *canCache, R_ObjectTable *tb){

#ifdef LOOKUP_DEBUG
 Rprintf( "  >> rProtoBufTable_exists\n" ); 
#endif
	
 if(tb->active == _FALSE_)
    return( _FALSE_ );

 tb->active = _FALSE_;
 Rboolean val = _FALSE_ ;
 tb->active = _TRUE_;
 
 return( val );
}

/**
 * Returns a new "protobufDescriptor" if there is such a message type
 * in the descriptor pool. NULL otherwise
 *
 * @param name message type name (without package path)
 * @param canCache 
 * @param tb lookup table
 */
SEXP rProtoBufTable_get(const char * const name, Rboolean *canCache, R_ObjectTable *tb){

#ifdef LOOKUP_DEBUG
 Rprintf( "  >> rProtoBufTable_get\n" ); 
#endif

 SEXP val;
 if(tb->active == _FALSE_)
    return(R_UnboundValue);

 tb->active = _FALSE_;
 val = R_getUnboundValue() ;
 tb->active = _TRUE_;

 return(val);
}

/**
 * Does nothing. Not applicable
 */
int rProtoBufTable_remove(const char * const name,  R_ObjectTable *tb){
#ifdef LOOKUP_DEBUG
 Rprintf( "  >> rProtoBufTable_remove( %s) \n", name ); 
#endif
	error( "cannot remove from protobuf descriptor pool" ) ;
}

/**
 * Indicates if R can cache the variable name. 
 * Currently allways return _FALSE_
 *
 * @param name message type name
 * @param tb lookup table
 * @return allways _FALSE_ (for now)
 */ 
Rboolean rProtoBufTable_canCache(const char * const name, R_ObjectTable *tb){
#ifdef LOOKUP_DEBUG
 Rprintf( "  >> rProtoBufTable_canCache\n" ); 
#endif
	return( _FALSE_ );
}

/**
 * Generates an error. assign is not possible on this lookup table
 */
SEXP rProtoBufTable_assign(const char * const name, SEXP value, R_ObjectTable *tb){
#ifdef LOOKUP_DEBUG
 Rprintf( "  >> rProtoBufTable_assign( %s ) \n", name ); 
#endif
    error("can't assign to protocol buffer descriptor pool");
}

/**
 * Returns the list of classes known to be included in the 
 * packages. 
 *
 * @param tb lookup table
 */ 
SEXP rProtoBufTable_objects(R_ObjectTable *tb) {
#ifdef LOOKUP_DEBUG
 Rprintf( "  >> rProtoBufTable_objects\n" ); 
#endif
	
	tb->active = _FALSE_;
	SEXP res = R_NilValue ; 
	tb->active = _TRUE_;
	return( res ); 
}

RcppExport SEXP newProtocolBufferLookup(){
#ifdef LOOKUP_DEBUG
 Rprintf( "<newProtocolBufferLookup>\n" ); 
#endif

 R_ObjectTable *tb;
 SEXP val, klass;

  tb = (R_ObjectTable *) malloc(sizeof(R_ObjectTable));
  if(!tb)
      error( "cannot allocate space for an internal R object table" );
  
  tb->type = RPROTOBUF_LOOKUP ; /* FIXME: not sure what this should be */
  tb->cachedNames = NULL;
  
  /* replace this with a pointer to the descriptor pool */
  tb->privateData = (void*)0 ; 

  tb->exists = rProtoBufTable_exists;
  tb->get = rProtoBufTable_get;
  tb->remove = rProtoBufTable_remove;
  tb->assign = rProtoBufTable_assign;
  tb->objects = rProtoBufTable_objects;
  tb->canCache = rProtoBufTable_canCache;

  tb->onAttach = NULL;
  tb->onDetach = NULL;

  PROTECT(val = R_MakeExternalPtr(tb, install("UserDefinedDatabase"), R_NilValue));
  PROTECT(klass = NEW_CHARACTER(1));
   SET_STRING_ELT(klass, 0, COPY_TO_USER_STRING("UserDefinedDatabase"));
   SET_CLASS(val, klass);
  UNPROTECT(2);

#ifdef LOOKUP_DEBUG
 Rprintf( "</newProtocolBufferLookup>\n" ); 
#endif
  return(val);
}

