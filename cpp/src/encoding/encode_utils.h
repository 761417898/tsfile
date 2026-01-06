/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * License); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#ifndef ENCODING_ENCODE_UTILS_H
#define ENCODING_ENCODE_UTILS_H

#include "utils/util_define.h"

namespace storage {

FORCE_INLINE int32_t number_of_leading_zeros(int32_t i) {
    return i == 0 ? 32 : __builtin_clz(static_cast<uint32_t>(i));
}

FORCE_INLINE int32_t number_of_trailing_zeros(int32_t i) {
    return i == 0 ? 32 : __builtin_ctz(static_cast<uint32_t>(i));
}

FORCE_INLINE int get_int32_max_bit_width(const std::vector<int32_t>& nums) {
    int ret = 1;
    for (auto num : nums) {
        int bit_width = 32 - number_of_leading_zeros(num);
        ret = std::max(ret, bit_width);
    }
    return ret;
}

FORCE_INLINE int32_t number_of_leading_zeros(int64_t i) {
    return i == 0 ? 64 : __builtin_clzll(static_cast<uint64_t>(i));
}

FORCE_INLINE int32_t number_of_trailing_zeros(int64_t i) {
    return i == 0 ? 64 : __builtin_ctzll(static_cast<uint64_t>(i));
}

FORCE_INLINE int get_int64_max_bit_width(const std::vector<int64_t>& nums) {
    int ret = 1;
    for (auto num : nums) {
        int bit_width = 64 - number_of_leading_zeros(num);
        ret = std::max(ret, bit_width);
    }
    return ret;
}

}  // end namespace storage
#endif  // ENCODING_ENCODE_UTILS_H
