
RProtoBuf.http.handler <- function(path, query, body) { 
	
	if( !all( c("service", "method" ) %in% names(query) ) ){
		stop( "need service and method " )
	}
	service <- query[["service"]]
	method  <- query[["method"]]
	  
	m <- get( 
		sprintf( "%s.%s", service, method ), 
		as.environment( "RProtoBuf:DescriptorPool" )
		)
	if( is.null( m ) ){
		stop( "unknown method" )
	}
	input <- if( length( body ) ){
		m$input_type()$read( body )
	} else{
		new( m$input_type() )
	}
	res <- invoke( m, input )
	list( serialize( res, NULL ) )
}

