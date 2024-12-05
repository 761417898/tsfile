/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * License); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License a
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
#include "reader/filter/lt_eq.h"

#include <gtest/gtest.h>

#include "common/statistic.h"

using namespace storage;
using namespace common;

TEST(LtEqTest, TestSatisfyWithTimeFilter) {
    LtEq lteq((int64_t)5, TIME_FILTER);
    Statistic* stat = StatisticFactory::alloc_statistic(common::INT32);
    stat->update(3, 0);
    stat->update(6, 0);

    EXPECT_TRUE(lteq.satisfy(stat));
    StatisticFactory::free(stat);
}

TEST(LtEqTest, TestSatisfyWithValue) {
    LtEq lteq(Object(5), VALUE_FILTER);
    Object value(4);

    EXPECT_TRUE(lteq.satisfy(0, value));
}

TEST(LtEqTest, TestSatisfyWithHigherValue) {
    LtEq lteq(Object(5), VALUE_FILTER);
    Object value(6);

    EXPECT_FALSE(lteq.satisfy(0, value));
}

TEST(LtEqTest, TestSatisfyStartEndTime) {
    LtEq lteq((int64_t)5, TIME_FILTER);

    EXPECT_TRUE(lteq.satisfy_start_end_time(3, 7));
    EXPECT_FALSE(lteq.satisfy_start_end_time(6, 8));
}

TEST(LtEqTest, TestContainStartEndTime) {
    LtEq lteq((int64_t)5, TIME_FILTER);

    EXPECT_TRUE(lteq.contain_start_end_time(2, 5));
    EXPECT_FALSE(lteq.contain_start_end_time(6, 7));
}