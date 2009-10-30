#include "rprotobuf.h"
#include "fieldtypes.h"

namespace org{
namespace rproject{
namespace rprotobuf{
namespace{

SEXP extractFieldAsSEXP( const Message * message, const Descriptor* desc, const FieldDescriptor * fieldDesc ){
	
	/* depending on the type, we need to create some regular SEXP (INTSXP) 
       or a message */
	
    FieldDescriptor::Type type =    fieldDesc->type() ;
    
	return R_NilValue; 
	
}


} // namespace
} // namespace rprotobuf
} // namespace rproject
} // namespace org

