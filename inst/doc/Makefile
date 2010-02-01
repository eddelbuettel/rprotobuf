
all: clean RProtoBuf-unitTests.pdf

clean:
	touch RProtoBuf-unitTests.pdf
	rm -fr RProtoBuf-unitTests.pdf

RProtoBuf-unitTests.pdf: unitTests/RProtoBuf-unitTests.R
	Rscript --default-packages="RProtoBuf,Rcpp,brew,RUnit,tools,utils" unitTests/RProtoBuf-unitTests.R

