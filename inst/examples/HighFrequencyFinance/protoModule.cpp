// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-

#include "TradeData.pb.h"

#include <Rcpp.h>
#include <fstream>

class TradeModule : public TradeData::Trades 
{
private:
    TradeData::Trades tr;
public:
	int init(const char *pbfile) {
		std::fstream fs(pbfile, std::ios::in | std::ios::binary);

		if (!tr.ParseFromIstream(&fs)) {
			std::cerr << "Trouble parsing..." << std::cout;
			return -1;
		}
		return 0;
	}

	int numberOfFills(void) {
		return tr.fill_size();
	}
};

RCPP_MODULE(yada){
	using namespace Rcpp ;
	                  
	class_<TradeModule>( "Trades" )
		.method( "init",          &TradeModule::init )
		.method( "numberOfFills", &TradeModule::numberOfFills )
		;
	
}                     

