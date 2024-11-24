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
#ifndef READER_FILTER_BASIC_UNARY_FILTER_H
#define READER_FILTER_BASIC_UNARY_FILTER_H

#include "reader/filter/filter.h"
#include "reader/filter/filter_type.h"

namespace storage {

class UnaryFilter : public Filter {
   public:
    UnaryFilter() : Filter() {}
    UnaryFilter(Object value, FilterType type) : Filter() {
        value_ = value;
        type_ = type;
    }
    virtual ~UnaryFilter() {}

    Object get_value() { return value_; }

    void set_value(Object value) { value_ = value; }

    FilterType get_filter_type() { return type_; }

    virtual bool satisfy(Statistic *statistic) {
        ASSERT(false);
        return false;
    }
    virtual bool satisfy(int64_t time, Object value) {
        ASSERT(false);
        return false;
    }
    virtual bool satisfy_start_end_time(int64_t start_time, int64_t end_time) {
        ASSERT(false);
        return false;
    }
    virtual bool contain_start_end_time(int64_t start_time, int64_t end_time) {
        ASSERT(false);
        return false;
    }

   protected:
    Object value_;
    FilterType type_;
};

}  // namespace storage

#endif  // READER_FILTER_BASIC_UNARY_FILTER_H
