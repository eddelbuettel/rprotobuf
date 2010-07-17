
# Rmath is in /usr/include on my system
CPPFLAGS=		-I/usr/include -I. -Wall -O3

# libRmath.so is in /usr/lib on my system, as are the proto library
LDLIBS=			-L/usr/lib -lprotobuf -lprotoc -lpthread 

RCPPINC=		$(shell Rscript -e 'Rcpp:::CxxFlags()')
RCPPLIB=		$(shell Rscript -e 'Rcpp:::LdFlags()')

protoCreate:		protoCreate.cpp TradeData.pb.cc
			$(CXX) $(CPPLFLAGS) -o protoCreate protoCreate.cpp TradeData.pb.cc -lRmath $(LDLIBS)

protoDump:		protoDump.cpp TradeData.pb.cc
			$(CXX) $(CPPLFLAGS) -o protoDump protoDump.cpp TradeData.pb.cc $(LDLIBS)

protoLoadForR.so:	protoLoadForR.cpp TradeData.pb.cc
			PKG_CXXFLAGS="$(CPPFLAGS) $(RCPPINC)" PKG_LIBS="$(LDLIBS) $(RCPPLIB)" \
				R CMD SHLIB protoLoadForR.cpp TradeData.pb.cc

protoModule.so:		protoModule.cpp TradeData.pb.cc
			PKG_CXXFLAGS="$(CPPFLAGS) $(RCPPINC)" PKG_LIBS="$(LDLIBS) $(RCPPLIB)" \
				R CMD SHLIB protoModule.cpp TradeData.pb.cc

TradeData.pb.cc:	TradeData.proto
			protoc --cpp_out=. TradeData.proto