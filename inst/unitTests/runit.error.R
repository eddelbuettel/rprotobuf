
test.error <- function(){
	stop( "boom" )
}

test.failure <- function(){
	checkEquals( 1, 2 )
}


