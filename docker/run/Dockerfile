## Emacs, make this -*- mode: sh; -*-

FROM rprotobuf/ci

LABEL org.label-schema.license="GPL-2.0" \
      org.label-schema.vcs-url="https://github.com/eddelbuettel/rprotobuf" \
      maintainer="Dirk Eddelbuettel <edd@debian.org>"

## Install the latest version from CRAN
RUN install.r RProtoBuf

## Alternatively, install from Github (after first installing remotes)
##RUN install.r remotes && installGithub.r eddelbuettel/rprotobuf

CMD ["bash"]
