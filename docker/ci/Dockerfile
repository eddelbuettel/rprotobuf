## Emacs, make this -*- mode: sh; -*-

FROM r-base:latest

LABEL org.label-schema.license="GPL-2.0" \
      org.label-schema.vcs-url="https://github.com/eddelbuettel/rprotobuf" \
      maintainer="Dirk Eddelbuettel <edd@debian.org>"

RUN apt-get update \
        && apt-get install -y --no-install-recommends \
                r-cran-rcpp \
                r-cran-rcurl \
                r-cran-runit \
                r-cran-rmarkdown \
                r-cran-knitr \
                protobuf-compiler \
                protobuf-c-compiler \
                libprotobuf-c-dev \
                libprotobuf-dev \
                libprotoc-dev \
        && install.r pinp 

CMD ["bash"]
