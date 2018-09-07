## Emacs, make this -*- mode: sh; -*-

FROM rprotobuf:ci

LABEL org.label-schema.license="GPL-2.0" \
      org.label-schema.vcs-url="https://github.com/eddelbuettel/rprotobuf" \
      maintainer="Dirk Eddelbuettel <edd@debian.org>"

RUN install.r RProtoBuf

## Alternatively for Github installations
##RUN install.r remotes && installGithub.r eddelbuettel/rprotobuf

CMD ["bash"]
