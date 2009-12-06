#ifndef RPROTOBUF_RSourceTree_H
#define RPROTOBUF_RSourceTree_H

namespace rprotobuf{
	class RSourceTree : public GPB::compiler::SourceTree {
		public:	
			GPB::io::ZeroCopyInputStream *	Open(const std::string & filename) ;
		
} ;

} // namespace rprotobuf

#endif
