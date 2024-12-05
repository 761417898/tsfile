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
#include "reader/filter/lt.h"

#include <gtest/gtest.h>

#include "common/statistic.h"

using namespace storage;
using namespace common;

TEST(LtTest, TestSatisfyWithTimeFilter) {
    Lt lt((int64_t)5, TIME_FILTER);
    Statistic* stat = StatisticFactory::alloc_statistic(common::INT32);
    stat->update(3, 0);
    stat->update(6, 0);

    EXPECT_TRUE(lt.satisfy(stat));
    StatisticFactory::free(stat);
}

TEST(LtTest, TestSatisfyWithValue) {
    Lt lt(Object(5), VALUE_FILTER);
    Object value(4);

    EXPECT_TRUE(lt.satisfy(0, value));
}

TEST(LtTest, TestSatisfyWithHigherValue) {
    Lt lt(Object(5), VALUE_FILTER);
    Object value(6);

    EXPECT_FALSE(lt.satisfy(0, value));
}

TEST(LtTest, TestSatisfyStartEndTime) {
    Lt lt((int64_t)5, TIME_FILTER);

    EXPECT_TRUE(lt.satisfy_start_end_time(3, 7));
    EXPECT_FALSE(lt.satisfy_start_end_time(6, 8));
}

TEST(LtTest, TestContainStartEndTime) {
    Lt lt((int64_t)5, TIME_FILTER);

    EXPECT_TRUE(lt.contain_start_end_time(4, 3));
    EXPECT_FALSE(lt.contain_start_end_time(6, 5));
}