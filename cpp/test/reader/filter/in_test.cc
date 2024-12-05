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
#include "reader/filter/in.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

#include "common/statistic.h"

using namespace storage;
using namespace common;

TEST(InTest, TestSatisfyWithValue) {
    std::vector<Object> values = {1, 3, 5, 7, 9};
    In inFilter(values, VALUE_FILTER, false);

    Object value1(3);
    Object value2(6);

    EXPECT_TRUE(inFilter.satisfy(0, value1));
    EXPECT_FALSE(inFilter.satisfy(0, value2));
}

TEST(InTest, TestSatisfyStartEndTime) {
    std::vector<Object> values = {1, 3, 5, 7, 9};
    In inFilter(values, TIME_FILTER, false);

    EXPECT_TRUE(inFilter.satisfy_start_end_time(1, 5));
    EXPECT_TRUE(inFilter.satisfy_start_end_time(4, 6));
}

TEST(InTest, TestContainStartEndTime) {
    std::vector<Object> values = {1, 3, 5, 7, 9};
    In inFilter(values, TIME_FILTER, false);

    EXPECT_TRUE(inFilter.contain_start_end_time(2, 6));
    EXPECT_TRUE(inFilter.contain_start_end_time(3, 7));
}