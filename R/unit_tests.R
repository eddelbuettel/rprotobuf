
run_unit_tests <- function(){
	script <- system.file( "unitTests", "runTests.R", 
		package = "RProtoBuf" ) 
	source( script )
}
