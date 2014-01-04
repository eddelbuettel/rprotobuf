// rprotobuf.h: support for using Rcpp
//
// Copyright (C) 2010 Dirk Eddelbuettel and Romain Francois
//
// This file is part of RProtoBuf.
//
// RProtoBuf is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// RProtoBuf is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RProtoBuf.  If not, see <http://www.gnu.org/licenses/>.

#ifndef RPROTOBUF__RCPPSUPPORT__H
#define RPROTOBUF__RCPPSUPPORT__H

#include <ostream>              /* for stringstream, basic_ostream */
#include <string>               /* for string */

#include "rprotobuf.h"

namespace rprotobuf {

/* support for Rcpp::wrap protobuf repeated fields, this essentially uses
   the same macro trick as in protobuf, but reversed */

struct enum_field{};
struct message_field{};

class Int64AsStringRepeatedFieldImporter {
public:
    // Probably want to convert to strings here.
    typedef std::string r_import_type;
    Int64AsStringRepeatedFieldImporter(const GPB::Reflection* ref_ ,
                                       const GPB::Message& message_,
                                       const GPB::FieldDescriptor* field_)
        : ref(ref_), message(message_), field(field_) {}
    inline int size() const {
        return ref->FieldSize(message, field);
    }
    inline std::string get(int i) const {
        std::stringstream stream;
        int64 val = ref->GetRepeatedInt64(message, field, i);
        stream << val;
        return stream.str();
    }
  private:
    const GPB::Reflection* ref;
    const GPB::Message& message;
    const GPB::FieldDescriptor* field;
};

class UInt64AsStringRepeatedFieldImporter {
public:
    // Probably want to convert to strings here.
    typedef std::string r_import_type;
    UInt64AsStringRepeatedFieldImporter(const GPB::Reflection* ref_,
                                        const GPB::Message& message_,
                                        const GPB::FieldDescriptor* field_)
        : ref(ref_), message(message_), field(field_) {}
    inline int size() const {
        return ref->FieldSize(message, field) ;
    }
    inline std::string get(int i) const {
        std::stringstream stream;
        uint64 val = ref->GetRepeatedUInt64(message, field, i);
        stream << val;
        return stream.str();
    }
  private:
    const GPB::Reflection* ref;
    const GPB::Message& message;
    const GPB::FieldDescriptor* field;
};

// TODO(mstokely): Rcpp doesn't handle uint32 properly as of 2013/12
// See https://r-forge.r-project.org/tracker/index.php?func=detail&aid=1360&group_id=155&atid=637
class UInt32RepeatedFieldImporter {
public:
    // Represent as doubles, since R doesn't have uint32s.
    typedef double r_import_type;
    UInt32RepeatedFieldImporter(const GPB::Reflection* ref_ ,
				const GPB::Message& message_,
				const GPB::FieldDescriptor* field_)
        : ref(ref_), message(message_), field(field_) {}
    inline int size() const {
        return ref->FieldSize(message, field);
    }
    inline double get(int i) const {
	return double(ref->GetRepeatedUInt32(message, field, i));
    }
  private:
    const GPB::Reflection* ref;
    const GPB::Message& message;
    const GPB::FieldDescriptor* field;
};


template <typename T> class RepeatedFieldImporter{} ;

#undef GENERATE__FIELD__IMPORTER__DECL
#define GENERATE__FIELD__IMPORTER__DECL(__TYPE__, __CAMEL__)     \
template<> class RepeatedFieldImporter<__TYPE__> {               \
public:                                                          \
    typedef __TYPE__ r_import_type;                              \
    RepeatedFieldImporter(                                       \
        const GPB::Reflection* ref_,                             \
        const GPB::Message& message_,                            \
        const GPB::FieldDescriptor* field_):                     \
        ref(ref_), message(message_), field(field_) {}           \
    inline int size() const {                                    \
        return ref->FieldSize( message, field );                 \
    }                                                            \
    inline __TYPE__ get(int i) const {                           \
        return ref->GetRepeated##__CAMEL__(message, field, i);   \
    }                                                            \
private:                                                         \
    const GPB::Reflection* ref;                                  \
    const GPB::Message& message;                                 \
    const GPB::FieldDescriptor* field;                           \
};

GENERATE__FIELD__IMPORTER__DECL(GPB::int32, Int32)
GENERATE__FIELD__IMPORTER__DECL(GPB::uint32, UInt32)
GENERATE__FIELD__IMPORTER__DECL(GPB::int64, Int64)
GENERATE__FIELD__IMPORTER__DECL(GPB::uint64, UInt64)
GENERATE__FIELD__IMPORTER__DECL(float, Float)
GENERATE__FIELD__IMPORTER__DECL(double, Double)
GENERATE__FIELD__IMPORTER__DECL(bool, Bool)
GENERATE__FIELD__IMPORTER__DECL(std::string, String)
#undef GENERATE__FIELD__IMPORTER__DECL

template<> class RepeatedFieldImporter<enum_field>{
public:
	typedef int r_import_type ;
	RepeatedFieldImporter(
	 	const GPB::Reflection* ref_,
		const GPB::Message& message_,
		const GPB::FieldDescriptor* field_):
		ref(ref_), message(message_), field(field_) {};
	inline int size() const {
		return ref->FieldSize( message, field );
	}
	inline int get(int i) const {
		return ref->GetRepeatedEnum(message, field, i)->number();
	}
private:
	const GPB::Reflection* ref;
	const GPB::Message& message;
	const GPB::FieldDescriptor* field;
} ;

template<> class RepeatedFieldImporter<message_field>{
public:
	typedef message_field r_import_type ;
	RepeatedFieldImporter(
	 	const GPB::Reflection* ref_ ,
		const GPB::Message& message_,
		const GPB::FieldDescriptor* field_):
		ref(ref_), message(message_), field(field_) {};
	inline int size() const {
		return ref->FieldSize( message, field );
	}
	inline SEXP wrap(int i) const {
		return S4_Message(CLONE(&ref->GetRepeatedMessage(message, field, i)));
	}
private:
	const GPB::Reflection* ref;
	const GPB::Message& message;
	const GPB::FieldDescriptor* field;
};

} // namespace rprotobuf

#endif
