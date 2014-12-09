# Functions to convert an arbitrary R object into a protocol buffer
# using the universal rexp.proto descriptor.
#
# Written by Jeroen Ooms
# Modified 2014 by Murray Stokely to support language and environment types

rexp_obj <- function(obj){
  sm <- typeof(obj);
  msg <- switch(sm,
    "character" = rexp_string(obj),
    "raw" = rexp_raw(obj),
    "double" = rexp_double(obj),
    "complex" = rexp_complex(obj),
    "integer" = rexp_integer(obj),
    "list" = rexp_list(obj),
    "logical" = rexp_logical(obj),
    "NULL" = rexp_null(),
    return(rexp_native(obj))
  );

  attrib <- attributes(obj)
  msg$attrName <- names(attrib)
  msg$attrValue <- lapply(attrib, rexp_obj)
  msg
}

rexp_string <- function(obj){
  xvalue <- lapply(as.list(obj), function(x){
    new(pb(rexp.STRING), strval=x, isNA=is.na(x))
  })
  new(pb(rexp.REXP), rclass = 0, stringValue=xvalue)
}

# For objects that only make sense in R, we just fall back
# to R's default serialization.

rexp_native <- function(obj){
  new(pb(rexp.REXP), rclass= 8, nativeValue = base::serialize(obj, NULL))
}

rexp_raw <- function(obj){
  new(pb(rexp.REXP), rclass= 1, rawValue = obj)
}

rexp_double <- function(obj){
  new(pb(rexp.REXP), rclass=2, realValue = obj)
}

rexp_complex <- function(obj){
  xvalue <- lapply(as.list(obj), function(x){
    new(pb(rexp.CMPLX), real=Re(x), imag=Im(x))
  })
  new(pb(rexp.REXP), rclass=3, complexValue = xvalue)
}

rexp_integer <- function(obj){
  new(pb(rexp.REXP), rclass=4, intValue = obj)
}

rexp_list <- function(obj){
  xobj <- lapply(obj, rexp_obj)
  new(pb(rexp.REXP), rclass=5, rexpValue = xobj)
}

rexp_logical <- function(obj){
  xobj <- as.integer(obj)
  xobj[is.na(obj)] <- 2
  new(pb(rexp.REXP), rclass=6, booleanValue = xobj)
}

rexp_null <- function(){
  new(pb(rexp.REXP), rclass=7)
}

unrexp <- function(msg){
  stopifnot(is(msg, "Message"))
  stopifnot(msg@type == "rexp.REXP")

  myrexp <- as.list(msg)
  xobj <- switch(as.character(myrexp$rclass),
     "0" = unrexp_string(myrexp),
     "1" = unrexp_raw(myrexp),
     "2" = unrexp_double(myrexp),
     "3" = unrexp_complex(myrexp),
     "4" = unrexp_integer(myrexp),
     "5" = unrexp_list(myrexp),
     "6" = unrexp_logical(myrexp),
     "7" = unrexp_null(),
     "8" = unrexp_native(myrexp),
     stop("Unsupported rclass:", myrexp$rclass)
  )

  if(length(myrexp$attrValue)){
    attrib <- lapply(myrexp$attrValue, unrexp)
    names(attrib) <- myrexp$attrName
    attributes(xobj) <- attrib
  }

  xobj
}

unrexp_string <- function(myrexp){
  mystring <- unlist(lapply(myrexp$stringValue, "[[", "strval"))
  isNA <- unlist(lapply(myrexp$stringValue, "[[", "isNA"))
  mystring[isNA] <- NA
  mystring
}

unrexp_raw <- function(myrexp){
  myrexp$rawValue
}

unrexp_double <- function(myrexp){
  myrexp$realValue
}

unrexp_complex <- function(myrexp){
  xvalue <- lapply(myrexp$complexValue, function(x){
    complex(real=x$real, imaginary=x$imag)
  })
  unlist(xvalue)
}

unrexp_integer <- function(myrexp){
  myrexp$intValue
}

unrexp_list <- function(myrexp){
  lapply(myrexp$rexpValue, unrexp)
}

unrexp_logical <- function(myrexp){
  xvalue <- myrexp$booleanValue
  xvalue[xvalue==2] <- NA
  as.logical(xvalue)
}

unrexp_null <- function(){
  NULL
}

unrexp_native <- function(myrexp){
  unserialize(myrexp$nativeValue)
}

#Helper function to lookup a PB descriptor
pb <- function(name){
  descriptor <- deparse(substitute(name))
  if(!exists(descriptor, "RProtoBuf:DescriptorPool")){
    stop("No ProtoBuf Descriptor for: ", descriptor)
  }
  get(descriptor, "RProtoBuf:DescriptorPool")
}

#Checks if object can be serialized
can_serialize_pb <- rexp_valid <- function(obj) {
# We can now serialize everything.  just call back to R serialization
  return(TRUE)
}
