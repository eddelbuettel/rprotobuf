
all: clean RProtoBuf.pdf RProtoBuf-quickref.pdf RProtoBuf-unitTests.pdf

clean:
	rm -fr *.pdf

RProtoBuf.pdf: RProtoBuf.Rnw
	Rscript --default-packages="RProtoBuf,tools,utils" -e "Sweave( 'RProtoBuf.Rnw' ); texi2dvi( 'RProtoBuf.tex', pdf = TRUE )"
	
RProtoBuf-quickref.pdf: RProtoBuf-quickref.Rnw
	Rscript --default-packages="RProtoBuf,tools,utils" -e "Sweave( 'RProtoBuf-quickref.Rnw' ) ; texi2dvi( 'RProtoBuf-quickref.tex', pdf = TRUE )"

RProtoBuf-unitTests.pdf: RProtoBuf-unitTests.Rnw.brew
	Rscript --default-packages="RProtoBuf,brew,RUnit,tools,utils" -e "brew( 'RProtoBuf-unitTests.Rnw.brew', 'RProtoBuf-unitTests.tex' ); texi2dvi( 'RProtoBuf-unitTests.tex', pdf = TRUE ) ; unlink( 'RProtoBuf-unitTests.tex'); file.copy( 'RProtoBuf-unitTests.pdf', '/tmp', overwrite = TRUE ) ; file.copy( 'RProtoBuf-unitTests.html', '/tmp', overwrite = TRUE )"

