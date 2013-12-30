/*
 * Copyright 2012 Google Inc. All Rights Reserved.
 * Author: Murray Stokely
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#include "rprotobuf.h"
#include "fieldtypes.h"
#include "Rcppsupport.h"

namespace rprotobuf {

RcppExport SEXP getExtension(SEXP pointer, SEXP sfielddesc) {
    /* grab the Message pointer */
    Rcpp::XPtr<GPB::Message> message(pointer);
    const Reflection* ref = message->GetReflection();
    const GPB::FieldDescriptor* field_desc =
        GET_FIELD_DESCRIPTOR_POINTER_FROM_S4(sfielddesc);

    // extractFieldAsSEXP returns a default (e.g. 0) even when
    // field doesn't exist, but returning NULL probably makes more
    // sense.
    //
    // TODO(mstokely): move this logic into extractField so that
    // all fields get this updated behavior, not just extensions.

    if (field_desc->is_repeated()) {
        if (ref->FieldSize(*message, field_desc) < 1) {
            return R_NilValue;
        }
    } else {
        if (!ref->HasField(*message, field_desc)) {
            return R_NilValue;
        }
    }
    return (extractFieldAsSEXP(message, field_desc));
}

}  // namespace rprotobuf
