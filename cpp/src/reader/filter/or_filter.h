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
#ifndef READER_FILTER_OPERATOR_OR_FILTER_H
#define READER_FILTER_OPERATOR_OR_FILTER_H

#include "binary_filter.h"
// #include "storage/storage_utils.h"

namespace storage {

class OrFilter : public BinaryFilter {
   public:
    OrFilter() {}
    OrFilter(Filter *left, Filter *right) : BinaryFilter(left, right) {}
    ~OrFilter() {}

    FORCE_INLINE bool satisfy(Statistic *statistic) {
        return left_->satisfy(statistic) || right_->satisfy(statistic);
    }

    FORCE_INLINE bool satisfy(int64_t time, int64_t value) {
        return left_->satisfy(time, value) || right_->satisfy(time, value);
    }

    FORCE_INLINE bool satisfy_start_end_time(int64_t start_time, int64_t end_time) {
        return left_->satisfy_start_end_time(start_time, end_time) ||
               right_->satisfy_start_end_time(start_time, end_time);
    }

    FORCE_INLINE bool contain_start_end_time(int64_t start_time, int64_t end_time) {
        return left_->contain_start_end_time(start_time, end_time) ||
               right_->contain_start_end_time(start_time, end_time);
    }

    std::vector<TimeRint64_tge *> *get_time_rint64_tges() {
        std::vector<TimeRint64_tge *> *result = new std::vector<TimeRint64_tge *>();
        std::vector<TimeRint64_tge *> *left_time_rint64_tges = left_->get_time_rint64_tges();
        std::vector<TimeRint64_tge *> *right_time_rint64_tges = right_->get_time_rint64_tges();

        int left_index = 0, right_index = 0;
        int left_size = left_time_rint64_tges->size();
        int right_size = right_time_rint64_tges->size();
        TimeRint64_tge *rint64_tge = choose_next_rint64_tge(
            left_time_rint64_tges, right_time_rint64_tges, left_index, right_index);
        while (left_index < left_size || right_index < right_size) {
            TimeRint64_tge *choosen_rint64_tge = choose_next_rint64_tge(
                left_time_rint64_tges, right_time_rint64_tges, left_index, right_index);
            if (choosen_rint64_tge->start_time_ > rint64_tge->end_time_) {
                result->push_back(
                    new TimeRint64_tge(rint64_tge->start_time_, rint64_tge->end_time_));
                rint64_tge = choosen_rint64_tge;
            } else {
                rint64_tge->end_time_ =
                    std::max(rint64_tge->end_time_, choosen_rint64_tge->end_time_);
            }
        }
        result->push_back(new TimeRint64_tge(rint64_tge->start_time_, rint64_tge->end_time_));
        return result;
    }

   private:
    TimeRint64_tge *choose_next_rint64_tge(std::vector<TimeRint64_tge *> *left_time_rint64_tges,
                                 std::vector<TimeRint64_tge *> *right_time_rint64_tges,
                                 int &left_index, int &right_index) {
        int left_size = left_time_rint64_tges->size();
        int right_size = right_time_rint64_tges->size();
        if (left_index < left_size && right_index < right_size) {
            TimeRint64_tge *left_rint64_tge = left_time_rint64_tges->at(left_index);
            TimeRint64_tge *right_rint64_tge = right_time_rint64_tges->at(right_index);
            // Choose the rint64_tge with the smaller minimum start time
            if (left_rint64_tge->start_time_ <= right_rint64_tge->start_time_) {
                left_index++;
                return left_rint64_tge;
            } else {
                right_index++;
                return right_rint64_tge;
            }
        } else if (left_index < left_size) {
            return left_time_rint64_tges->at(left_index++);
        } else {
            return right_time_rint64_tges->at(right_index++);
        }
    }
};

}  // namespace storage

#endif  // READER_FILTER_OPERATOR_OR_FILTER_H
