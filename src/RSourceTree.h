#ifndef RPROTOBUF_RSourceTree_H
#define RPROTOBUF_RSourceTree_H

namespace rprotobuf{
	class RSourceTree : public GPB::compiler::SourceTree {
		public:
			RSourceTree() ;
			GPB::io::ZeroCopyInputStream *	Open(const std::string & filename) ;
			void addDirectory( const std::string& directory) ;
			void addDirectories( SEXP dirs) ;
			void removeDirectory( const std::string& directory ) ;
			void removeDirectories( SEXP dirs ) ;
			
		private:
			std::set<std::string> directories ;
} ;

} // namespace rprotobuf

#endif
