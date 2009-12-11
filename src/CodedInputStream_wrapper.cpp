#include "rprotobuf.h"

namespace rprotobuf {

void CodedInputStream_Finalizer(SEXP xp) {
  if (TYPEOF(ref)==EXTPTRSXP) {
  	  GPB::CodedInputStream* stream = (GPB::CodedInputStream*)EXTPTR_PTR(xp) ;
  	  /* TODO: should we also clear the underlying ZeroCopyInputStream */
  	  delete stream ;
  }
}


} // namespace rprotobuf
