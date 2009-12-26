
test.draft <- function(){
	checkTrue( TRUE )
	checkEquals( 1, 1 )
	checkException( stop( "ouch" ) )
}

