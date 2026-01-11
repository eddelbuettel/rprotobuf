
## This Makefile is not included in the package sources so we can use GNUmake idioms. Yay.

rmdsources := 		$(wildcard *.Rmd)
rmdvignettes := 	$(rmdsources:.Rmd=.pdf)

%.pdf:			%.Rmd
			Rscript -e 'rmarkdown::render("$<")'
			Rscript -e 'tools::compactPDF("$@", gs_quality="ebook")'
			cp -vax $@ ..

all:			${rmdvignettes} RProtoBuf-paper.pdf

RProtoBuf-paper.pdf:	RProtoBuf-paper.Rnw
			Rscript -e 'Sweave("RProtoBuf-paper.Rnw")'
			pdflatex RProtoBuf-paper.tex
			bibtex RProtoBuf-paper.aux
			pdflatex RProtoBuf-paper.tex
			pdflatex RProtoBuf-paper.tex
			Rscript -e 'tools::compactPDF("$@", gs_quality="ebook")'
			cp -vax $@ ..

clean:
			@rm -rf *.aux *.log *.out *.tex *.pdf RPrototBuf-*_cache pinp.cls
