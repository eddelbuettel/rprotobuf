// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-

#include "TradeData.pb.h"

#include <Rcpp.h>
#include <iostream>
#include <fstream>

extern "C" SEXP pbload(SEXP b) {

	std::string pbfile = Rcpp::as<std::string>(b);

	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	TradeData::Trades tr;
	
	std::fstream fs(pbfile.c_str(), std::ios::in | std::ios::binary);

	if (!tr.ParseFromIstream(&fs)) {
		std::cerr << "Trouble parsing..." << std::cout;
		return R_NilValue;
	}

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

    //google::protobuf::ShutdownProtobufLibrary();
    return Rcpp::DataFrame::create(Rcpp::Named("times")  = timestamp,
                                   Rcpp::Named("symbol") = tsym,
                                   Rcpp::Named("price")  = tprice,
                                   Rcpp::Named("size")   = tsize);
}
