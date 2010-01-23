pkg <- "RProtoBuf"

path <- system.file("unitTests", package = pkg)
testSuite <- defineTestSuite(name=paste(pkg, "unit testing"), dirs = path)
tests <- runTestSuite(testSuite)
printHTMLProtocol(tests, fileName= sprintf( "%s-unitTests.html" , pkg ) )
printTextProtocol(tests, fileName= sprintf( "%s-unitTests.txt"  , pkg ) )
if( file.exists( "/tmp" ) ){
	file.copy( sprintf( "%s-unitTests.txt" , pkg ) , "/tmp", overwrite = TRUE )
	file.copy( sprintf( "%s-unitTests.html", pkg ) , "/tmp", overwrite = TRUE )
}
Sweave( sprintf('%s-unitTests.Rnw', pkg) )
texi2dvi( sprintf( '%s-unitTests.tex', pkg) , pdf = TRUE, clean = TRUE )
unlink( sprintf( '%s-unitTests.tex', pkg) )
