// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-

#include "TradeData.pb.h"

#include <Rcpp.h>
#include <fstream>

static TradeData::Trades tr;

int init(const char *pbfile) {
	std::fstream fs(pbfile, std::ios::in | std::ios::binary);

	if (!tr.ParseFromIstream(&fs)) {
		std::cerr << "Trouble parsing..." << std::cout;
		return -1;
	}
	return 0;
}
	
int nbfills(void) {
	int n = tr.fill_size();
	return n;
}

RCPP_MODULE(yada){
	using namespace Rcpp ;
	                  
	class_<TradeData::Trades>( "Trades" )
		.method( "fill_size", &TradeData::Trades::fill_size )
		;
	
	function( "init",    &init);
	function( "nbfills", &nbfills);

	// Hmpf. So how do I return the data.frame via Modules?
}                     

