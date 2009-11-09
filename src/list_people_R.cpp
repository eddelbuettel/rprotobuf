// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 8; -*-

// list_people_R.cpp -- R wrapper / version for list_people.cc example

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "addressbook.pb.h"

#include <Rcpp.h>		

RcppExport SEXP listPeopleAsList(SEXP paramSEXP) {

    SEXP rl = R_NilValue;
    char* exceptionMesg = NULL;
  
    try {

	RcppParams params(paramSEXP);      // parameter from R based on parms
	std::string filename = params.getStringValue("filename");
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
	    throw std::range_error("list_people_R.cpp: file " + filename + 
				   " failed to parse as address book.");
	}
	
	RcppList idlist, peoplelist, emaillist, phonelist;
	idlist.setSize(address_book.person_size());
	peoplelist.setSize(address_book.person_size());
	emaillist.setSize(address_book.person_size());
	phonelist.setSize(address_book.person_size());

	//ListPeople(address_book); 

	// Iterates though all people in the AddressBook and prints info about them.
	//void ListPeople(const tutorial::AddressBook& address_book) {
	for (int i = 0; i < address_book.person_size(); i++) {
	    const tutorial::Person& person = address_book.person(i);

	    idlist.append("id", person.id());
	    peoplelist.append("name", person.name());
	    emaillist.append("email", person.has_email() ? person.email(): "NA");

	    RcppList phones;

	    if (person.phone_size() == 0) {
		phones.setSize(1);
		phones.append("NA", "NA");
	    } else {
		phones.setSize(person.phone_size());
		for (int j = 0; j < person.phone_size(); j++) {
		    const tutorial::Person::PhoneNumber& phone_number = person.phone(j);
		    std::string txt;
		    switch (phone_number.type()) {
		    case tutorial::Person::MOBILE:
			txt = "mobile";
			break;
		    case tutorial::Person::HOME:
			txt = "home";
			break;
		    case tutorial::Person::WORK:
			txt = "work";
			break;
		    }
		    phones.append(txt, phone_number.number());
		}
	    }
	    phonelist.append("phones", phones.getList());
	}

 	rs.add("id", idlist);
	rs.add("name", peoplelist);
	rs.add("email", emaillist);
	rs.add("phones", phonelist);

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

RcppExport SEXP listPeopleAsDataFrame(SEXP paramSEXP) {

    SEXP rl = R_NilValue;
    char* exceptionMesg = NULL;
  
    try {

	RcppParams params(paramSEXP);      // parameter from R based on parms
	std::string filename = params.getStringValue("filename");
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
	    throw std::range_error("list_people_R.cpp: file " + filename + 
				   " failed to parse as address book.");
	}
	
	const int ncol = 3;
	const char* tvec1[ncol] =  { "Id", "Name", "Email" };
	std::vector<std::string> colnames1(tvec1, &tvec1[ncol]); 
	RcppFrame preframe1(colnames1);

	const char* tvec2[ncol] =  { "Id", "Type", "Number" };
	std::vector<std::string> colnames2(tvec2, &tvec2[ncol]); 
	RcppFrame preframe2(colnames2);

	//ListPeople(address_book);

	// Iterates though all people in the AddressBook and prints info about them.
	//void ListPeople(const tutorial::AddressBook& address_book) {
	for (int i = 0; i < address_book.person_size(); i++) {
	    const tutorial::Person& person = address_book.person(i);

	    std::vector<ColDatum> row1(ncol);
	    row1[0].setIntValue(static_cast<int>(person.id()));
	    row1[1].setStringValue(person.name());

	    if (person.has_email()) {
		row1[2].setStringValue(person.email());
	    } else {
		row1[2].setStringValue("NA");
	    }

	    preframe1.addRow(row1);

	    if (person.phone_size() > 0) {
		for (int j = 0; j < person.phone_size(); j++) {
		    const tutorial::Person::PhoneNumber& phone_number = person.phone(j);
		
		    std::vector<ColDatum> row2(ncol);

		    row2[0].setIntValue(static_cast<int>(person.id())); // id of user

		    std::string txt;
		    switch (phone_number.type()) {
		    case tutorial::Person::MOBILE:
			txt = "mobile";
			break;
		    case tutorial::Person::HOME:
			txt = "home";
			break;
		    case tutorial::Person::WORK:
			txt = "work";
			break;
		    }
		    row2[1].setStringValue(txt);
		    row2[2].setStringValue(phone_number.number());

		    preframe2.addRow(row2);
		}
	    } else {
		std::vector<ColDatum> row2(ncol);
		row2[0].setIntValue(static_cast<int>(person.id())); // id of user
		row2[1].setStringValue("NA");
		row2[2].setStringValue("NA");
		preframe2.addRow(row2);
	    }
	}

	rs.add("preframe1", preframe1);
	rs.add("preframe2", preframe2);

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

