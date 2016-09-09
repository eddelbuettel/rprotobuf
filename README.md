## RProtoBuf [![Build Status](https://travis-ci.org/eddelbuettel/rprotobuf.svg)](https://travis-ci.org/eddelbuettel/rprotobuf) [![License](http://img.shields.io/badge/license-GPL%20%28%3E=%202%29-brightgreen.svg?style=flat)](http://www.gnu.org/licenses/gpl-2.0.html) [![CRAN](http://www.r-pkg.org/badges/version/RProtoBuf)](https://cran.r-project.org/package=RProtoBuf) [![Downloads](http://cranlogs.r-pkg.org/badges/RProtoBuf?color=brightgreen)](http://www.r-pkg.org/pkg/RProtoBuf)

R Interface to [Google Protocol Buffers](https://developers.google.com/protocol-buffers/)

### What are Protocol Buffers?

A serialization format developed by [Google](https://www.google.com) and used
widely within Google, and by numerous other projects.  Quoting from the
[official website](https://developers.google.com/protocol-buffers/):

> Protocol buffers are Google's language-neutral, platform-neutral,
extensible mechanism for serializing structured data – think XML, but
smaller, faster, and simpler. You define how you want your data to be
structured once, then you can use special generated source code to easily
write and read your structured data to and from a variety of data streams and
using a variety of languages.

[Protocol Buffers](https://developers.google.com/protocol-buffers/) natively
support C++, C#, Go, Java and Python. Many other languages are supported via
contributed extensions. This package adds support for
[R](https://www.r-project.org).

### Installation

You can either install from source via this repo, or install
[the CRAN package](https://cran.r-project.org/package=RProtoBuf)
the usual way from [R](https://www.r-project.org) via

```r
R> install.packages("RProtoBuf")
```

but do make sure you have the system requirements covered when building from
source. Under Debian/Ubuntu you may need

```
$ sudo apt-get install protobuf-compiler libprotobuf-dev libprotoc-dev 
```

with similar commands on other operating systems or distributions.

### Documentation

The package contains two pdf vignettes; the second one corresponds to 
[our JSS paper](https://www.jstatsoft.org/article/view/v071i02).

### Authors

Romain Francois, Dirk Eddelbuettel, Murray Stokely and Jeroen Ooms

### License

GPL (>= 2)


