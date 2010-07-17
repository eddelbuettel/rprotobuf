// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-

#include "TradeData.pb.h"

#include <Rcpp.h>
#include <fstream>

class TradeModule 
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

	Rcpp::DataFrame getData(void) {
		int n = tr.fill_size();
		Rcpp::DatetimeVector timestamp(n);
		Rcpp::CharacterVector tsym(n);
		Rcpp::NumericVector tprice(n);
		Rcpp::IntegerVector tsize(n);

		for (int i=0; i<n; i++) {
			const TradeData::Fill &fill = tr.fill(i);
			timestamp[i] = fill.timestamp();
			tsym[i]      = fill.symbol();
			tprice[i]    = fill.price();
			tsize[i]     = fill.size();
		}

 		return Rcpp::DataFrame::create(Rcpp::Named("times")  = timestamp,
									   Rcpp::Named("symbol") = tsym,
									   Rcpp::Named("price")  = tprice,
									   Rcpp::Named("size")   = tsize);
	}

};

RCPP_MODULE(trades){
	using namespace Rcpp ;
	                  
	class_<TradeModule>( "Trades" )
		.method( "init",          &TradeModule::init )
		.method( "numberOfFills", &TradeModule::numberOfFills )
		.method( "getData",       &TradeModule::getData )
		;
	
}                     

