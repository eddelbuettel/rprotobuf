
## this is a 'fake' all as R-devel gets a race condition on RProtoBuf-intro and deletes the .tex file
all: 	RProtoBuf-unitTests.pdf RProtoBuf-quickref.pdf

## 'real all'
pdfall: RProtoBuf-unitTests.pdf RProtoBuf-intro.pdf RProtoBuf-quickref.pdf

pdfclean:
	rm -fr *.pdf

clean:
	rm -f RProtoBuf-intro.aux RProtoBuf-intro.log RProtoBuf-intro.out
	rm -f RProtoBuf-quickref.aux RProtoBuf-quickref.log RProtoBuf-quickref.out
	rm -f RProtoBuf-unitTests.aux RProtoBuf-unitTests.log RProtoBuf-unitTests.out
	rm -rf auto/

setvars:
ifeq (${R_HOME},)
R_HOME=	$(shell R RHOME)
endif
RPROG=	$(R_HOME)/bin/R
RSCRIPT=$(R_HOME)/bin/Rscript

RProtoBuf-unitTests.pdf: unitTests/RProtoBuf-unitTests.R
	$(RSCRIPT) --default-packages="RProtoBuf,Rcpp,brew,RUnit,tools,utils" unitTests/RProtoBuf-unitTests.R

RProtoBuf-intro.pdf: RProtoBuf/RProtoBuf.Rnw
	cp -f RProtoBuf/RProtoBuf.Rnw RProtoBuf-intro.Rnw
	$(RSCRIPT) -e "require('highlight'); require('tools'); Sweave('RProtoBuf-intro.Rnw', driver=HighlightWeaveLatex()); texi2dvi('RProtoBuf-intro.tex', pdf=TRUE, clean=TRUE)"
	cp -f RProtoBuf/RProtoBuf-fake.Rnw RProtoBuf-intro.Rnw

RProtoBuf-quickref.pdf: RProtoBuf-quickref/RProtoBuf-quickref.Rnw
	touch RProtoBuf-quickref.Rnw
	rm RProtoBuf-quickref.Rnw
	cp -f RProtoBuf-quickref/RProtoBuf-quickref.Rnw .
	$(RSCRIPT) -e "require( 'highlight'); require('tools'); Sweave('RProtoBuf-quickref.Rnw', driver=HighlightWeaveLatex()); texi2dvi('RProtoBuf-quickref.tex', pdf=TRUE, clean=TRUE)"
	cp -f RProtoBuf-quickref/RProtoBuf-quickref-fake.Rnw RProtoBuf-quickref.Rnw

