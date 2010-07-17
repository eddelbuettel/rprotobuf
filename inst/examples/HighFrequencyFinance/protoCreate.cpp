// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-

#include "TradeData.pb.h"		// auto-generated ProtoBuffer data structure accessor
#include <iostream>
#include <fstream>

#define MATHLIB_STANDALONE 1	// so that we get set_seed()
#include <Rmath.h>				// to use R's RNGs and random distribution functions

int main(int argc, char **argv)
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	const char* pbfile = "trades.pb";
	const int N = 1000;

    set_seed(123, 456);

	double tstamp = 1277973000;		// 2010-07-01 08:30:00
	double tprice = 100.0;			// gotta start somewhere
	char sym[] = "ABC";

	TradeData::Trades tr;
	for (int i=0; i<N; i++) {
		TradeData::Fill *fill = tr.add_fill();
		tstamp += runif(0.000, 0.100); 		 	 	// time steps anywhere between 0 and 100 msec
		tprice += round(rt(5) * 0.01 * 100)/100;  	// price move as dampened t(5), rounded to pennies
		int tsize = 100 + round(runif(0,9))*100;	 // size in 100 lots

		fill->set_timestamp(tstamp); 
		fill->set_price(tprice); 
		fill->set_symbol(sym); 
		fill->set_size(tsize); 
	}

    // Write the new address book back to disk.
	std::fstream output(pbfile, std::ios::out | std::ios::binary);
    if (!tr.SerializeToOstream(&output)) {
		std::cerr << "Failed to write address book." << std::endl;
		return -1;
    }
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}
