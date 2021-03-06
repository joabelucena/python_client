/*
    Copyright (c) 2017 TOSHIBA Digital Solutions Corporation.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _FIELD_H_
#define _FIELD_H_

#include "gridstore.h"
#include <iostream>
#include <string.h>

using namespace std;

namespace griddb {

struct Field {
    GSType type;
    GSValue value;
    Field() : type(GS_TYPE_STRING) {
        memset(&value, 0, sizeof(GSValue));
    };

    ~Field() {
        switch (type){
        case GS_TYPE_STRING:
            if (value.asString) {
                free(const_cast<GSChar*>(value.asString));
                value.asString = NULL;
            }
            break;
        case GS_TYPE_BLOB:
            if (value.asBlob.data) {
                free(const_cast<void*>(value.asBlob.data));
                value.asBlob.data = NULL;
            }
            break;
        case GS_TYPE_INTEGER_ARRAY:
#if GS_COMPATIBILITY_VALUE_1_1_106
            if (value.asIntegerArray.elements) {
                free(const_cast<int32_t*> (value.asIntegerArray.elements));
            }
#else
            if (value.asArray.elements.asInteger) {
                free(const_cast<int32_t*> (value.asArray.elements.asInteger));
            }
#endif
            break;
        case GS_TYPE_STRING_ARRAY:
#if GS_COMPATIBILITY_VALUE_1_1_106
            if (value.asStringArray.elements) {
                for (int j = 0; j < value.asStringArray.size; j++) {
                    if (value.asStringArray.elements[j]) {
                        free(const_cast<GSChar*> (value.asStringArray.elements[j]));
                    }
                }
                free(const_cast<GSChar**> (value.asStringArray.elements));
            }
#else
            if (value.asArray.elements.asString) {
                for (int j = 0; j < value.asArray.length; j++) {
                    if (value.asArray.elements.asString[j]) {
                        free(const_cast<GSChar*> (value.asArray.elements.asString[j]));
                    }
                }
                free(const_cast<GSChar**> (value.asArray.elements.asString));
            }
#endif
            break;
        case GS_TYPE_BOOL_ARRAY:
#if GS_COMPATIBILITY_VALUE_1_1_106
            if (value.asBoolArray.elements) {
                free(const_cast<GSBool*> (value.asBoolArray.elements));
            }
#else
            if (value.asArray.elements.asBool) {
                free(const_cast<GSBool*> (value.asArray.elements.asBool));
            }
#endif
            break;
        case GS_TYPE_BYTE_ARRAY:
#if GS_COMPATIBILITY_VALUE_1_1_106
            if (value.asByteArray.elements) {
                free(const_cast<int8_t*> (value.asByteArray.elements));
                value.asByteArray.elements = NULL;
            }
#else
            if (value.asArray.elements.asByte) {
                free(const_cast<int8_t*> (value.asArray.elements.asByte));
                value.asArray.elements.asByte = NULL;
            }
#endif
            break;
        case GS_TYPE_SHORT_ARRAY:
#if GS_COMPATIBILITY_VALUE_1_1_106
            if (value.asShortArray.elements) {
                free(const_cast<int16_t*> (value.asShortArray.elements));
            }
#else
            if (value.asArray.elements.asShort) {
                free(const_cast<int16_t*> (value.asArray.elements.asShort));
            }
#endif
            break;
        case GS_TYPE_LONG_ARRAY:
#if GS_COMPATIBILITY_VALUE_1_1_106
            if (value.asLongArray.elements) {
                free(const_cast<int64_t*> (value.asLongArray.elements));
            }
#else
            if (value.asArray.elements.asLong) {
                free(const_cast<int64_t*> (value.asArray.elements.asLong));
            }
#endif
            break;
        case GS_TYPE_FLOAT_ARRAY:
#if GS_COMPATIBILITY_VALUE_1_1_106
            if (value.asFloatArray.elements) {
                free(const_cast<float*> (value.asFloatArray.elements));
            }
#else
            if (value.asArray.elements.asFloat) {
                free(const_cast<float*> (value.asArray.elements.asFloat));
            }
#endif
            break;
        case GS_TYPE_DOUBLE_ARRAY:
#if GS_COMPATIBILITY_VALUE_1_1_106
            if (value.asDoubleArray.elements) {
                free(const_cast<double*> (value.asDoubleArray.elements));
            }
#else
            if (value.asArray.elements.asDouble) {
                free(const_cast<double*> (value.asArray.elements.asDouble));
            }
#endif
            break;
        case GS_TYPE_TIMESTAMP_ARRAY:
#if GS_COMPATIBILITY_VALUE_1_1_106
            if (value.asTimestampArray.elements) {
                free(const_cast<GSTimestamp*> (value.asTimestampArray.elements));
            }
#else
            if (value.asArray.elements.asTimestamp) {
                free(const_cast<GSTimestamp*> (value.asArray.elements.asTimestamp));
            }
#endif
            break;
        }
    }
};

}

#endif /* _FIELD_H_ */
