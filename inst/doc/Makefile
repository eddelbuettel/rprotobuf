
all: clean RProtoBuf-unitTests.pdf RProtoBuf.pdf RProtoBuf-quickref.pdf

clean:
	rm -fr *.pdf

RProtoBuf-unitTests.pdf: unitTests/RProtoBuf-unitTests.R
	Rscript --default-packages="RProtoBuf,Rcpp,brew,RUnit,tools,utils" unitTests/RProtoBuf-unitTests.R

RProtoBuf.pdf: RProtoBuf/RProtoBuf.Rnw
	rm RProtoBuf.Rnw
	cp RProtoBuf/RProtoBuf.Rnw RProtoBuf.Rnw
	Rscript -e "require( 'highlight' ); require('tools'); Sweave('RProtoBuf.Rnw', driver = HighlightWeaveLatex() ) ; texi2dvi('RProtoBuf.tex', pdf = TRUE, clean = TRUE)"
	rm -fr RProtoBuf.tex
	rm -fr RProtoBuf.Rnw
	cp RProtoBuf/RProtoBuf-fake.Rnw

RProtoBuf-quickref.pdf: RProtoBuf-quickref.Rnw.in
	cp RProtoBuf-quickref.Rnw.in RProtoBuf-quickref.Rnw
	Rscript -e "require( 'highlight' ); require('tools'); Sweave('RProtoBuf-quickref.Rnw', driver = HighlightWeaveLatex() ) ; texi2dvi('RProtoBuf-quickref.tex', pdf = TRUE, clean = TRUE)"
	rm -fr RProtoBuf-quickref.tex

