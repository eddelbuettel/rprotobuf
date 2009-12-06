// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 8; -*-

// clear_person_R.cpp -- remove a single person given an id

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "addressbook.pb.h"

#include "rprotobuf.h"

RcppExport SEXP clearPerson(SEXP paramSEXP) {

    SEXP rl = R_NilValue;
    char* exceptionMesg = NULL;
    
    try {

	RcppParams params(paramSEXP);      // parameter from R based on parms
	std::string filename = params.getStringValue("filename");
	int id = params.getIntValue("id");

	RcppResultSet rs;

	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	//
	// TODO -- should we throw() here? The macro probably dies on us...
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	tutorial::AddressBook address_book;

	// Read the existing address book.
	std::fstream input(filename.c_str(), std::ios::in | std::ios::binary);
	if (!address_book.ParseFromIstream(&input)) {
	    throw std::range_error("clear_person_R.cpp: file " + filename + 
				   " failed to parse as address book.");
	}
	
	// Iterates though all people in the AddressBook 
	int n = address_book.person_size();
	for (int i = 0; i < n; i++) {
	    tutorial::Person *person = address_book.mutable_person(i);
	    if (id == person->id()) {
		const GPB::Reflection *ref = address_book.GetReflection() ;
		const GPB::FieldDescriptor* fd = address_book.GetDescriptor()->FindFieldByName( "person" ) ;
		ref->SwapElements( &address_book, fd, i, address_book.person_size() - 1 ) ;
		ref->RemoveLast( &address_book, fd) ;
		break ;
	    }
	}

	// Write the new address book back to disk.
	std::fstream output(filename.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
	if (!address_book.SerializeToOstream(&output)) {
	    throw std::range_error("add_people_R.cpp: file " + filename + 
				   " could not be written to for address book.");
	}

	// Optional:  Delete all global objects allocated by libprotobuf.
	//google::protobuf::ShutdownProtobufLibrary();
	
	rs.add("status", 0);
    
        rl = rs.getReturnList();

    } catch(std::exception& ex) {
        exceptionMesg = copyMessageToR(ex.what());
    } catch(...) {
        exceptionMesg = copyMessageToR("unknown reason");
    }
  
    if (exceptionMesg != NULL)
        Rf_error(exceptionMesg);
    
    return rl;
}
