
# Rmath is in /usr/include on my system
CXXFLAGS=		-I/usr/include -I. -Wall -O3 -pipe

# libRmath.so is in /usr/lib on my system, as are the proto library
LDLIBS=			-L/usr/lib -lprotobuf -lprotoc -lpthread 

RCPPINC=		$(shell Rscript -e 'Rcpp:::CxxFlags()')
RCPPLIB=		$(shell Rscript -e 'Rcpp:::LdFlags()')

TARGETS=		protoCreate protoDump protoLoadForR.so protoModule.so TradeData.pb.cc

all:			$(TARGETS)

protoCreate:		protoCreate.cpp TradeData.pb.cc
			$(CXX) $(CXXFLAGS) $^ -o $@ -lRmath $(LDLIBS)

protoDump:		protoDump.cpp TradeData.pb.cc
			$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

protoLoadForR.so:	protoLoadForR.cpp TradeData.pb.cc
			PKG_CXXFLAGS="$(CXXFLAGS) $(RCPPINC)" PKG_LIBS="$(LDLIBS) $(RCPPLIB)" \
				R CMD SHLIB $^

protoModule.so:		protoModule.cpp TradeData.pb.cc
			PKG_CXXFLAGS="$(CXXFLAGS) $(RCPPINC)" PKG_LIBS="$(LDLIBS) $(RCPPLIB)" \
				R CMD SHLIB $^

TradeData.pb.cc:	TradeData.proto
			protoc --cpp_out=. $^

clean:
			$(RM) $(TARGETS) TradeData.pb.h
