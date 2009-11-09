#ifndef RPROTOBUF_DescriptorPoolLookup_H
#define RPROTOBUF_DescriptorPoolLookup_H

namespace rprotobuf{

	class DescriptorPoolLookup {
		public:
			static void add( std::string element) ;
			
			static bool contains( std::string element) ; 
		
			static SEXP getElements() ;
		
		private:	
			
			static std::vector<std::string> elements ;
			
} ;

} // namespace rprotobuf

#endif
