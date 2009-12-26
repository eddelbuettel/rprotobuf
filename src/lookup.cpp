#include "rprotobuf.h"
#include "DescriptorPoolLookup.h" 

/* This uses the mechanism of the RObjectTables package
   see: http://www.omegahat.org/RObjectTables/ */

namespace rprotobuf{

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
Rboolean rProtoBufTable_exists(const char * const name, Rboolean *canCache, R_ObjectTable *tb){

#ifdef LOOKUP_DEBUG
 Rprintf( "  >> rProtoBufTable_exists\n" ); 
#endif
	
 if(tb->active == _FALSE_)
    return( _FALSE_ );

 tb->active = _FALSE_;
 Rboolean val = _FALSE_ ;
 if( DescriptorPoolLookup::contains( name ) ){
 	 /* first check the cache */
 	 val = _TRUE_ ;
 } else {
 	/* try the generated pool */
 	const GPB::DescriptorPool*  pool = GPB::DescriptorPool::generated_pool() ;
 	if( pool->FindMessageTypeByName( name ) ||  pool->FindEnumTypeByName( name ) || pool->FindServiceByName( name ) || pool->FindMethodByName( name ) ){
 		DescriptorPoolLookup::add( name ) ;
 		val = _TRUE_ ;
 	} else {
 		/* try the runtime pool */
 		pool = DescriptorPoolLookup::pool() ;
 		if( pool->FindMessageTypeByName( name ) ||  pool->FindEnumTypeByName( name ) || pool->FindServiceByName( name ) || pool->FindMethodByName( name ) ){
 			DescriptorPoolLookup::add( name ) ;
 			val = _TRUE_ ;
 		}
 	}
 }
 tb->active = _TRUE_;
 
 return( val );
}

SEXP findSomething( const GPB::DescriptorPool* pool, const char * const name){
	const GPB::Descriptor*  desc = pool->FindMessageTypeByName( name ) ;
 	if( desc ){
 		/* message */
 		DescriptorPoolLookup::add( name ) ;
 		SEXP res = PROTECT( new_RS4_Descriptor( desc ) ); 
 		UNPROTECT(1); 
 		return( res ) ;
 	} else {
 		 const GPB::EnumDescriptor* enum_desc = pool->FindEnumTypeByName( name ) ;
 		 if( enum_desc ){
 		 	/* enum */
 		 	DescriptorPoolLookup::add( name ) ;
 		 	SEXP res = PROTECT( new_RS4_EnumDescriptor( enum_desc ) ); 
 			UNPROTECT(1); 
 			return( res ) ;
 		 } else{
			const GPB::ServiceDescriptor* service_desc = pool->FindServiceByName( name ) ;
			if( service_desc ){
				DescriptorPoolLookup::add( name ) ;
				SEXP res = PROTECT( new_RS4_ServiceDescriptor( service_desc ) ); 
				UNPROTECT(1); 
				return( res ) ;
 		 	} else {
 		 		const GPB::MethodDescriptor* method_desc = pool->FindMethodByName( name ); 
 		 		if( method_desc ){
					DescriptorPoolLookup::add( name ) ;
					SEXP res = PROTECT( new_RS4_MethodDescriptor( method_desc ) ); 
					UNPROTECT(1); 
					return( res ) ;
 		 		} else{
 		 			return( R_NilValue ) ;
 		 		}
 		 	}
 		 }    
 	}
 
}


/**
 * Returns a new "Descriptor" if there is such a message type
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

 if(tb->active == _FALSE_)
    return(R_UnboundValue);

 tb->active = _FALSE_;
 
 SEXP res ;
 
 /* first try the generated pool */
 const GPB::DescriptorPool*  pool = GPB::DescriptorPool::generated_pool() ;
 res = findSomething( pool, name ) ;
 if( res == R_NilValue ){
 	/* try the runtime pool */
 	pool = DescriptorPoolLookup::pool() ;
 	res = findSomething( pool, name ) ;
 }
 tb->active = _TRUE_;
 if( res != R_NilValue ) return res ; 
 return R_getUnboundValue() ; // -Wall
}

/**
 * Does nothing. Not applicable
 */
int rProtoBufTable_remove(const char * const name,  R_ObjectTable *tb){
#ifdef LOOKUP_DEBUG
 Rprintf( "  >> rProtoBufTable_remove( %s) \n", name ); 
#endif
	Rf_error( "cannot remove from protobuf descriptor pool" ) ;
 	return(0); // make -Wall happy
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
    Rf_error("can't assign to protocol buffer descriptor pool");
 	return(R_NilValue); // make -Wall happy
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
	SEXP objects = PROTECT( DescriptorPoolLookup::getElements() ) ; 
	tb->active = _TRUE_;
	UNPROTECT(1); /* objects */
	
	return( objects ); 
}

SEXP newProtocolBufferLookup(){
#ifdef LOOKUP_DEBUG
 Rprintf( "<newProtocolBufferLookup>\n" ); 
#endif

 R_ObjectTable *tb;
 SEXP val, klass;

  tb = (R_ObjectTable *) malloc(sizeof(R_ObjectTable));
  if(!tb)
      Rf_error( "cannot allocate space for an internal R object table" );
  
  tb->type = RPROTOBUF_LOOKUP ; /* FIXME: not sure what this should be */
  tb->cachedNames = NULL;
  
  tb->privateData = (void*)0 ;

  tb->exists = rProtoBufTable_exists;
  tb->get = rProtoBufTable_get;
  tb->remove = rProtoBufTable_remove;
  tb->assign = rProtoBufTable_assign;
  tb->objects = rProtoBufTable_objects;
  tb->canCache = rProtoBufTable_canCache;

  tb->onAttach = NULL;
  tb->onDetach = NULL;

  PROTECT(val = R_MakeExternalPtr(tb, Rf_install("UserDefinedDatabase"), R_NilValue));
  PROTECT(klass = Rf_mkString( "UserDefinedDatabase" ) );
  Rf_setAttrib(val, R_ClassSymbol, klass) ;
  UNPROTECT(2); /* val, klass */

#ifdef LOOKUP_DEBUG
 Rprintf( "</newProtocolBufferLookup>\n" ); 
#endif
  return(val);
}



} // namespace rprotobuf

