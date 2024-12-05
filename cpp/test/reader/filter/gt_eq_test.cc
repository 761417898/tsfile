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
#include "reader/filter/gt_eq.h"

#include <gtest/gtest.h>

#include "common/statistic.h"

using namespace storage;
using namespace common;

TEST(GtEqTest, TestSatisfyWithTimeFilter) {
    GtEq gteq((int64_t)5, TIME_FILTER);
    Statistic* stat1 = StatisticFactory::alloc_statistic(common::INT32);
    stat1->update(3, 0);
    stat1->update(7, 0);
    EXPECT_TRUE(gteq.satisfy(stat1));
    StatisticFactory::free(stat1);

    Statistic* stat2 = StatisticFactory::alloc_statistic(common::INT32);
    stat2->update(8, 0);
    stat2->update(10, 0);

    EXPECT_TRUE(gteq.satisfy(stat2));
    StatisticFactory::free(stat2);
}

TEST(GtEqTest, TestSatisfyWithValue) {
    GtEq gteq(Object(5), VALUE_FILTER);
    Object value1(5);
    Object value2(6);

    EXPECT_TRUE(gteq.satisfy(0, value1));
    EXPECT_TRUE(gteq.satisfy(0, value2));
    Object value3(4);
    EXPECT_FALSE(gteq.satisfy(0, value3));
}

TEST(GtEqTest, TestSatisfyStartEndTime) {
    GtEq gteq((int64_t)5, TIME_FILTER);

    EXPECT_TRUE(gteq.satisfy_start_end_time(3, 7));
    EXPECT_FALSE(gteq.satisfy_start_end_time(2, 3));
}

TEST(GtEqTest, TestContainStartEndTime) {
    GtEq gteq((int64_t)5, TIME_FILTER);

    EXPECT_TRUE(gteq.contain_start_end_time(5, 7));
    EXPECT_FALSE(gteq.contain_start_end_time(4, 7));
}