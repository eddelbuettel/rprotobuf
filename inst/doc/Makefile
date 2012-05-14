
all: RProtoBuf-unitTests.pdf RProtoBuf.pdf RProtoBuf-quickref.pdf

pdfclean:
	rm -fr *.pdf

clean:
	rm -f RProtoBuf.tex RProtoBuf.aux RProtoBuf.logRProtoBuf.out
	rm -f RProtoBuf-quickref.tex RProtoBuf-quickref.Rnw RProtoBuf-quickref.aux RProtoBuf-quickref.log RProtoBuf-quickref.out
	rm -f RProtoBuf-unitTests.texRProtoBuf-unitTests.Rnw RProtoBuf-unitTests.aux RProtoBuf-unitTests.log RProtoBuf-unitTests.out

setvars:
ifeq (${R_HOME},)
R_HOME=	$(shell R RHOME)
endif
RPROG=	$(R_HOME)/bin/R
RSCRIPT=$(R_HOME)/bin/Rscript

RProtoBuf-unitTests.pdf: unitTests/RProtoBuf-unitTests.R
	$(RSCRIPT) --default-packages="RProtoBuf,Rcpp,brew,RUnit,tools,utils" unitTests/RProtoBuf-unitTests.R

RProtoBuf.pdf: RProtoBuf/RProtoBuf.Rnw
	cp -f RProtoBuf/RProtoBuf.Rnw RProtoBuf.Rnw
	$(RSCRIPT) -e "require( 'highlight' ); require('tools'); Sweave('RProtoBuf.Rnw', driver = HighlightWeaveLatex() ) ; texi2dvi('RProtoBuf.tex', pdf = TRUE, clean = TRUE)"
	cp -f RProtoBuf/RProtoBuf-fake.Rnw RProtoBuf.Rnw

RProtoBuf-quickref.pdf: RProtoBuf-quickref/RProtoBuf-quickref.Rnw
	touch RProtoBuf-quickref.Rnw
	rm RProtoBuf-quickref.Rnw
	cp -f RProtoBuf-quickref/RProtoBuf-quickref.Rnw .
	$(RSCRIPT) -e "require( 'highlight' ); require('tools'); Sweave('RProtoBuf-quickref.Rnw', driver = HighlightWeaveLatex() ) ; texi2dvi('RProtoBuf-quickref.tex', pdf = TRUE, clean = TRUE)"
	cp -f RProtoBuf-quickref/RProtoBuf-quickref-fake.Rnw RProtoBuf-quickref.Rnw

