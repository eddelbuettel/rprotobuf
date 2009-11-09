#ifndef RPROTOBUF_RSourceTree_H
#define RPROTOBUF_RSourceTree_H

namespace rprotobuf{
	class RSourceTree : public SourceTree {
		public:	
			io::ZeroCopyInputStream *	Open(const string & filename) ;
		
} ;

} // namespace rprotobuf

#endif
