// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-

#include "TradeData.pb.h"
#include <iostream>
#include <fstream>
#include <cmath>

std::string formatTimestamp(const double ts) {
    // tt is the nb of seconds, ignores fractional microsec
    time_t tt = static_cast<time_t>(floor(ts));	
    struct tm tm = *localtime(&tt);			// parse time type into time structure 

    // m_us is fractional (micro)secs is diff. between (fractional) m_d and m_tm
    unsigned int us = static_cast<int>( round( (ts - tt) * 1.0e6 ) );	

    char buf[32], usec[16];
    strftime(buf, 31, "%Y-%m-%d %H:%M:%S", &tm);
	char txt[32];
    snprintf(txt, 31, "%s.%.06d", buf, us);
    return std::string(txt);
}

int main(int argc, char **argv)
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	const char* pbfile = "trades.pb";

	TradeData::Trades tr;

	std::fstream fs(pbfile, std::ios::in | std::ios::binary);
	if (!tr.ParseFromIstream(&fs)) {
		std::cerr << "Trouble parsing...\n";
		return -1;
	}

	for (int i=0; i<tr.fill_size(); i++) {
		const TradeData::Fill &fill = tr.fill(i); 
		std::cout << formatTimestamp(fill.timestamp()) << " " 
				  << fill.symbol() << " " 
				  << fill.price() << " " 
				  << fill.size() << std::endl;
	}
		
	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}
