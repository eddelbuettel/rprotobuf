// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 8; -*-

// list_people_R.cpp -- R wrapper / version for list_people.cc example

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "addressbook.pb.h"

#include <Rcpp.h>		

class RcppList {
public:
    RcppList(void): 
	numProtected(0), currListPosn(0), listSize(0), listArg(R_NilValue) { }; 
    ~RcppList() {
	UNPROTECT(numProtected);
    }
    void setSize(int size);
    void append(std::string name, double value);
    void append(std::string name, int value);
    void append(std::string name, std::string value);
    //void append(std::string name, RcppDate& date);
    //void append(std::string name, RcppDatetime& datetime);
    void append(std::string name, SEXP sexp);
    void clearProtectionStack() {
	UNPROTECT(numProtected);
	numProtected = 0;
    }
    SEXP getList(void) const { 
	SEXP li = PROTECT(Rf_allocVector(VECSXP, listSize));
	SEXP nm = PROTECT(Rf_allocVector(STRSXP, listSize));
	for (int i=0; i<listSize; i++) {
	    SET_VECTOR_ELT(li, i, VECTOR_ELT(listArg, i));
	    SET_STRING_ELT(nm, i, Rf_mkChar(names[i].c_str()));
	}
	Rf_setAttrib(li, R_NamesSymbol, nm);
	UNPROTECT(2);
	return li; 
    }
private:
    SEXP listArg;
    int listSize, currListPosn, numProtected;
    std::vector<std::string> names;
};

void RcppList::setSize(int n) {
    listSize = n;
    listArg = PROTECT(Rf_allocVector(VECSXP, n));
    numProtected++;
}

void RcppList::append(std::string name, double value) {
    if (currListPosn < 0 || currListPosn >= listSize)
	throw std::range_error("RcppList::append(double): list posn out of range");
    SEXP valsxp = PROTECT(Rf_allocVector(REALSXP,1));
    numProtected++;
    REAL(valsxp)[0] = value;
    SET_VECTOR_ELT(listArg, currListPosn++, valsxp);
    names.push_back(name);
}

void RcppList::append(std::string name, int value) {
    if (currListPosn < 0 || currListPosn >= listSize)
	throw std::range_error("RcppList::append(int): posn out of range");
    SEXP valsxp = PROTECT(Rf_allocVector(INTSXP,1));
    numProtected++;
    INTEGER(valsxp)[0] = value;
    SET_VECTOR_ELT(listArg, currListPosn++, valsxp);
    names.push_back(name);
}

void RcppList::append(std::string name, std::string value) {
    if (currListPosn < 0 || currListPosn >= listSize)
	throw std::range_error("RcppList::append(string): posn out of range");
    SEXP valsxp = PROTECT(Rf_allocVector(STRSXP,1));
    numProtected++;
    SET_STRING_ELT(valsxp, 0, Rf_mkChar(value.c_str()));
    SET_VECTOR_ELT(listArg, currListPosn++, valsxp);
    names.push_back(name);
}

void RcppList::append(std::string name, SEXP sexp) {
    if (currListPosn < 0 || currListPosn >= listSize)
	throw std::range_error("RcppList::append(sexp): posn out of range");
    SET_VECTOR_ELT(listArg, currListPosn++, sexp);
    names.push_back(name);
}

RcppExport SEXP listPeopleAsLists(SEXP paramSEXP) {

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

	    //row1[0].setIntValue(static_cast<int>(person.id()));
	    idlist.append("id", person.id());
	    peoplelist.append("name", person.name());
	    emaillist.append("email", person.has_email() ? person.email(): "NA");

	    RcppList phoneslist;
	    phoneslist.setSize(person.phone_size());

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
		phoneslist.append(txt, phone_number.number());
	    }
	    phonelist.append("phones", phoneslist.getList());
	}

	rs.add("id", idlist.getList(), false);
	rs.add("name", peoplelist.getList(), false);
	rs.add("email", emaillist.getList(), false);
	rs.add("phones", phonelist.getList(), false);

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

RcppExport SEXP listPeopleAsDataFrames(SEXP paramSEXP) {

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

RcppExport SEXP listPeopleV1(SEXP paramSEXP) {

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

	{
	  // Read the existing address book.
	  std::fstream input(filename.c_str(), std::ios::in | std::ios::binary);
	  if (!address_book.ParseFromIstream(&input)) {
	      throw std::range_error("list_people_R.cpp: file " 
				     + filename + 
				     " failed to parse as address book.");
	  }
	}

	std::vector<int> id;
	std::vector<std::string> name;
	std::vector<std::string> email;

	//ListPeople(address_book);

	// Iterates though all people in the AddressBook and prints info about them.
	//void ListPeople(const tutorial::AddressBook& address_book) {
	for (int i = 0; i < address_book.person_size(); i++) {
	    const tutorial::Person& person = address_book.person(i);

	    std::cout << "Person ID: " << person.id() << std::endl;
	    std::cout << "  Name: " << person.name() << std::endl;
	    id.push_back(static_cast<int>(person.id()));
	    name.push_back(person.name());
	    if (person.has_email()) {
		std::cout << "  E-mail address: " << person.email() << std::endl;
		email.push_back(person.email());
	    } else {
		email.push_back("NA");
	    }

	    for (int j = 0; j < person.phone_size(); j++) {
		const tutorial::Person::PhoneNumber& phone_number = person.phone(j);

		switch (phone_number.type()) {
		case tutorial::Person::MOBILE:
		    std::cout << "  Mobile phone #: ";
		    break;
		case tutorial::Person::HOME:
		    std::cout << "  Home phone #: ";
		    break;
		case tutorial::Person::WORK:
		    std::cout << "  Work phone #: ";
		    break;
		}
		std::cout << phone_number.number() << std::endl;
	    }
	}
	//}

	rs.add("id", id);
	rs.add("name", name);
	rs.add("email", email);

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
