
all: clean RProtoBuf.pdf RProtoBuf-quickref.pdf RProtoBuf-unitTests.pdf

clean:
	rm -fr *.pdf

RProtoBuf.pdf: RProtoBuf.Rnw
	Rscript --default-packages="RProtoBuf,tools,utils" -e "Sweave( 'RProtoBuf.Rnw' ); texi2dvi( 'RProtoBuf.tex', pdf = TRUE )"
	
RProtoBuf-quickref.pdf: RProtoBuf-quickref.Rnw
	Rscript --default-packages="RProtoBuf,tools,utils" -e "Sweave( 'RProtoBuf-quickref.Rnw' ) ; texi2dvi( 'RProtoBuf-quickref.tex', pdf = TRUE )"

RProtoBuf-unitTests.pdf: RProtoBuf-unitTests.Rnw RProtoBuf-unitTests.R
	Rscript --default-packages="RProtoBuf,Rcpp,brew,RUnit,tools,utils" RProtoBuf-unitTests.R

