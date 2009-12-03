// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 8; -*-

// add_person_R.cpp -- R wrapper / version for add_person.cc example

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "addressbook.pb.h"

#include <Rcpp.h>		

RcppExport SEXP addPerson(SEXP paramSEXP, SEXP emailsSEXP, 
			  SEXP phonesSEXP, SEXP typesSEXP) {

    SEXP rl = R_NilValue;
    char* exceptionMesg = NULL;
    
    try {

	RcppParams params(paramSEXP);      // parameter from R based on parms
	std::string filename = params.getStringValue("filename");
	std::cout << "File is " << filename << std::endl;

	RcppResultSet rs;

	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	tutorial::AddressBook address_book;

	// Read the existing address book.
	std::fstream input(filename.c_str(), std::ios::in | std::ios::binary);
	if (!address_book.ParseFromIstream(&input)) {
	    throw std::range_error("add_people_R.cpp: file " + filename + 
				   " failed to parse as address book.");
	}

	tutorial::Person *person = address_book.add_person();

	// Add an address.
	//PromptForAddress(address_book.add_person());
	int id = params.getIntValue("id");
	person->set_id(id);
	std::cout << "Id is " << id << std::endl;
	
	std::string name = params.getStringValue("name");
	person->set_name(name);
	std::cout << "Name is " << name << std::endl;

	RcppStringVector emails(emailsSEXP);    // vector of strings
	for (int i=0; i<emails.size(); i++) {
	    person->set_email(emails(i));
	    std::cout << "Email is " << emails(i) << std::endl;
	}

	RcppStringVector numbers(phonesSEXP); 	// vector of strings
	RcppStringVector types(typesSEXP);      // vector of strings
	if (numbers.size() != types.size()) {
	    throw std::range_error("add_people_R.cpp: phone numbers and types " 
				   "disagree on length.");
	}

	for (int i=0; i<numbers.size(); i++) {

	    tutorial::Person::PhoneNumber* phone_number = person->add_phone();
	    phone_number->set_number(numbers(i));
	    std::cout << "Nb is " << numbers(i) << std::endl;
	    
	    std::string type = types(i);
	    if (type == "mobile") {
		phone_number->set_type(tutorial::Person::MOBILE);
	    } else if (type == "home") {
		phone_number->set_type(tutorial::Person::HOME);
	    } else if (type == "work") {
		phone_number->set_type(tutorial::Person::WORK);
	    } else {
		Rf_warning("Unknown phone type.  Using default.");
	    }


	}

	// Write the new address book back to disk.
	std::fstream output(filename.c_str(), 
			    std::ios::out | std::ios::trunc | std::ios::binary);
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
