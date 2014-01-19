// S4_classes.h: R/C++ interface class library
//
// Copyright (C) 2010 - 2014  Dirk Eddelbuettel and Romain Francois
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

#ifndef RPROTOBUF_S4CLASSES_H
#define RPROTOBUF_S4CLASSES_H

//1. Place using Rcpp::S4; somewhere in the top of S4_classes.h in the
//src directory (so S4 is looked up in the right place),
//2. Replace setSEXP with set__, and asSexp with get__.

namespace rprotobuf {

// deal with Rcpp API changes
#if defined(RCPP_VERSION) && RCPP_VERSION <= Rcpp_Version(0,10,6)
    #define SetSexp setSEXP
    #define AsSexp  asSexp
#else
    #define SetSexp set__
    #define AsSexp  get__
#endif

using Rcpp::S4;

class ZeroCopyInputStreamWrapper;
class ZeroCopyOutputStreamWrapper;

class S4_EnumValueDescriptor : public Rcpp::S4 {
   public:
    S4_EnumValueDescriptor(const GPB::EnumValueDescriptor* d) : S4("EnumValueDescriptor") {

        if (d) {
            slot("pointer") = Rcpp::XPtr<GPB::EnumValueDescriptor>(
                const_cast<GPB::EnumValueDescriptor*>(d), false);
            slot("name") = d->name();
            slot("full_name") = d->full_name();
        } else {
            SetSexp(R_NilValue);
        }
    }

    S4_EnumValueDescriptor(const S4_EnumValueDescriptor& other) : S4() { SetSexp(other.AsSexp()); }
    S4_EnumValueDescriptor& operator=(const S4_EnumValueDescriptor& other) {
        SetSexp(other.AsSexp());
        return *this;
    }
};

class S4_Descriptor : public Rcpp::S4 {
   public:
    S4_Descriptor(const GPB::Descriptor* d) : S4("Descriptor") {
        slot("pointer") = Rcpp::XPtr<GPB::Descriptor>(const_cast<GPB::Descriptor*>(d), false);
        if (!d) {
            slot("type") = Rcpp::StringVector(0);
        } else {
            slot("type") = d->full_name();
        }
    }

    S4_Descriptor(const S4_Descriptor& other) : S4() { SetSexp(other.AsSexp()); }
    S4_Descriptor& operator=(const S4_Descriptor& other) {
        SetSexp(other.AsSexp());
        return *this;
    }
};

class S4_FileDescriptor : public Rcpp::S4 {
   public:
    S4_FileDescriptor(const GPB::FileDescriptor* d) : S4("FileDescriptor") {
        slot("pointer") =
            Rcpp::XPtr<GPB::FileDescriptor>(const_cast<GPB::FileDescriptor*>(d), false);
        if (!d) {
            slot("package") = Rcpp::StringVector(0);
            slot("filename") = Rcpp::StringVector(0);
        } else {
            slot("package") = d->package();
            slot("filename") = d->name();
        }
    }

    S4_FileDescriptor(const S4_FileDescriptor& other) : S4() { SetSexp(other.AsSexp()); }
    S4_FileDescriptor& operator=(const S4_FileDescriptor& other) {
        SetSexp(other.AsSexp());
        return *this;
    }
};

class S4_FieldDescriptor : public Rcpp::S4 {
   public:
    S4_FieldDescriptor(const GPB::FieldDescriptor* d) : S4("FieldDescriptor") {
        slot("pointer") =
            Rcpp::XPtr<GPB::FieldDescriptor>(const_cast<GPB::FieldDescriptor*>(d), false);
        slot("name") = d->name();
        slot("full_name") = d->full_name();
        slot("type") = d->containing_type()->full_name();
    }

    S4_FieldDescriptor(const S4_FieldDescriptor& other) : S4() { SetSexp(other.AsSexp()); }
    S4_FieldDescriptor& operator=(const S4_FieldDescriptor& other) {
        SetSexp(other.AsSexp());
        return *this;
    }
};

class S4_ServiceDescriptor : public Rcpp::S4 {
   public:
    S4_ServiceDescriptor(const GPB::ServiceDescriptor* d) : S4("ServiceDescriptor") {
        slot("pointer") =
            Rcpp::XPtr<GPB::ServiceDescriptor>(const_cast<GPB::ServiceDescriptor*>(d), false);
    }

    S4_ServiceDescriptor(const S4_ServiceDescriptor& other) : S4() { SetSexp(other.AsSexp()); }
    S4_ServiceDescriptor& operator=(const S4_ServiceDescriptor& other) {
        SetSexp(other.AsSexp());
        return *this;
    }
};

class S4_MethodDescriptor : public Rcpp::S4 {
   public:
    S4_MethodDescriptor(const GPB::MethodDescriptor* d) : S4("MethodDescriptor") {
        slot("pointer") =
            Rcpp::XPtr<GPB::MethodDescriptor>(const_cast<GPB::MethodDescriptor*>(d), false);
    }

    S4_MethodDescriptor(const S4_MethodDescriptor& other) : S4() { SetSexp(other.AsSexp()); }
    S4_MethodDescriptor& operator=(const S4_MethodDescriptor& other) {
        SetSexp(other.AsSexp());
        return *this;
    }
};

class S4_EnumDescriptor : public Rcpp::S4 {
   public:
    S4_EnumDescriptor(const GPB::EnumDescriptor* d) : S4("EnumDescriptor") {
        slot("pointer") =
            Rcpp::XPtr<GPB::EnumDescriptor>(const_cast<GPB::EnumDescriptor*>(d), false);
        slot("type") = Rcpp::StringVector(0);
        if (d) {
            slot("name") = d->name();
            slot("full_name") = d->full_name();
            const GPB::Descriptor* type_desc = d->containing_type();
            if (type_desc) {
                slot("type") = type_desc->full_name();
            }
        } else {
            slot("name") = Rcpp::StringVector(0);
            slot("full_name") = Rcpp::StringVector(0);
        }
    }

    S4_EnumDescriptor(const S4_EnumDescriptor& other) : S4() { SetSexp(other.AsSexp()); }
    S4_EnumDescriptor& operator=(const S4_EnumDescriptor& other) {
        SetSexp(other.AsSexp());
        return *this;
    }
};

class S4_Message : public Rcpp::S4 {
   public:
    S4_Message(const GPB::Message* d) : S4("Message") {
        slot("pointer") = Rcpp::XPtr<GPB::Message>(const_cast<GPB::Message*>(d), true);
        slot("type") = d->GetDescriptor()->full_name();
    }
    S4_Message(const S4_Message& other) : S4() { SetSexp(other.AsSexp()); }
    S4_Message& operator=(const S4_Message& other) {
        SetSexp(other.AsSexp());
        return *this;
    }
};

class S4_ArrayOutputStream : public Rcpp::S4 {

   public:
    S4_ArrayOutputStream(int size, int block_size) : S4("ArrayOutputStream") {

        Rcpp::RawVector payload(size);
        GPB::io::ArrayOutputStream* stream =
            new GPB::io::ArrayOutputStream(payload.begin(), size, block_size);

        Rcpp::XPtr<ZeroCopyOutputStreamWrapper> wrapper(new ZeroCopyOutputStreamWrapper(stream),
                                                        true, R_NilValue, payload);
        slot("pointer") = wrapper;
    }

    S4_ArrayOutputStream(const S4_ArrayOutputStream& other) { SetSexp(other.AsSexp()); }
    S4_ArrayOutputStream& operator=(const S4_ArrayOutputStream& other) {
        SetSexp(other.AsSexp());
        return *this;
    }
};

class S4_ArrayInputStream : public Rcpp::S4 {
   public:
    S4_ArrayInputStream(Rcpp::RawVector payload, int block_size) : S4("ArrayInputStream") {
        GPB::io::ArrayInputStream* stream =
            new GPB::io::ArrayInputStream(payload.begin(), payload.size(), block_size);
        Rcpp::XPtr<ZeroCopyInputStreamWrapper> wrapper(
            new ZeroCopyInputStreamWrapper(stream), true, R_NilValue, payload);
        slot("pointer") = wrapper;
    }
};

   #undef SetSexp
   #undef AsSexp

}  // namespace rprotobuf

#endif
