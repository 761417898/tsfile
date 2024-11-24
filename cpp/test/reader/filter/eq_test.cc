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
#include "reader/filter/eq.h"

#include <gtest/gtest.h>

#include "common/statistic.h"

using namespace storage;
using namespace common;

TEST(EqTest, TestSatisfyWithTimeFilter) {
   Eq eq(int64_t (5), TIME_FILTER);
   Statistic* stat = StatisticFactory::alloc_statistic(common::INT32);
   stat->update(3, 0);
   stat->update(5, 0);
   EXPECT_TRUE(eq.satisfy(stat));
   StatisticFactory::free(stat);
}

TEST(EqTest, TestSatisfyStartEndTime) {
   Eq eq(int64_t (5), TIME_FILTER);

   EXPECT_TRUE(eq.satisfy_start_end_time(3, 7));
   EXPECT_FALSE(eq.satisfy_start_end_time(6, 7));
}

TEST(EqTest, TestContainStartEndTime) {
   Eq eq(int64_t (5), TIME_FILTER);

   EXPECT_TRUE(eq.contain_start_end_time(5, 5));
   EXPECT_FALSE(eq.contain_start_end_time(4, 5));
}

TEST(EqTest, TestSatisfyWithValue) {
   Eq eq(Object(int64_t (5)), VALUE_FILTER);
   EXPECT_TRUE(eq.satisfy(0, Object(int64_t(5))));
   EXPECT_FALSE(eq.satisfy(0, Object(int64_t(6))));
}