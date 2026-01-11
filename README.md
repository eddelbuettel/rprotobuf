## RProtoBuf: R Interface to [Google Protocol Buffers](https://protobuf.dev/)

[![CI](https://github.com/eddelbuettel/rprotobuf/workflows/ci/badge.svg)](https://github.com/eddelbuettel/rprotobuf/actions?query=workflow%3Aci)
[![License](https://eddelbuettel.github.io/badges/GPL2+.svg)](https://www.r-project.org/Licenses/GPL-2)
[![CRAN](https://www.r-pkg.org/badges/version/RProtoBuf)](https://cran.r-project.org/package=RProtoBuf)
[![Dependencies](https://tinyverse.netlify.app/badge/RProtoBuf)](https://cran.r-project.org/package=RProtoBuf)
[![Downloads](https://cranlogs.r-pkg.org/badges/RProtoBuf?color=brightgreen)](https://www.r-pkg.org/pkg/RProtoBuf)
[![Last Commit](https://img.shields.io/github/last-commit/eddelbuettel/rprotobuf)](https://github.com/eddelbuettel/rprotobuf)
[![JSS](https://img.shields.io/badge/JSS-10.18637%2Fjss.v071.i02-brightgreen)](https://doi.org/10.18637/jss.v071.i02)

### What are Protocol Buffers?

A serialization format developed by [Google](https://www.google.com) and used
widely within Google, and by numerous other projects.  Quoting from the
[official website](https://protobuf.dev/):

> Protocol buffers are Google's language-neutral, platform-neutral,
extensible mechanism for serializing structured data – think XML, but
smaller, faster, and simpler. You define how you want your data to be
structured once, then you can use special generated source code to easily
write and read your structured data to and from a variety of data streams and
using a variety of languages.

[Protocol Buffers](https://protobuf.dev/) natively
support C++, C#, Go, Java and Python. Many other languages are supported via
contributed extensions. This package adds support for
[R](https://www.r-project.org).

### Installation

You can either install from source via this repo, or install
[the CRAN package](https://cran.r-project.org/package=RProtoBuf)
the usual way from [R](https://www.r-project.org) via

```r
install.packages("RProtoBuf")
```

but do make sure you have the system requirements covered when building from
source.

Under Debian/Ubuntu you may need

```bash
sudo apt-get install protobuf-compiler libprotobuf-dev libprotoc-dev
```

with similar commands on other operating systems or distributions.

### Documentation

The package contains two pdf vignettes; the second one corresponds to
[our JSS paper](https://doi.org/10.18637/jss.v071.i02).

### Authors

Romain Francois, Dirk Eddelbuettel, Murray Stokely and Jeroen Ooms

### License

GPL (>= 2)
