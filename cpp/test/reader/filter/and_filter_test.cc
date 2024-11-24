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
#include "reader/filter/and_filter.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "common/statistic.h"
#include "reader/filter/filter.h"

using namespace storage;
using namespace common;

class MockFilter : public Filter {
   public:
    MOCK_METHOD(bool, satisfy, (Statistic * statistic), (override));
    MOCK_METHOD(bool, satisfy, (int64_t time, Object value), (override));
    MOCK_METHOD(bool, satisfy_start_end_time, (int64_t start_time, int64_t end_time),
                (override));
    MOCK_METHOD(bool, contain_start_end_time, (int64_t start_time, int64_t end_time),
                (override));
    MOCK_METHOD(std::vector<TimeRange*>*, get_time_ranges, (), (override));
};

class MockStatistic : public Statistic {};

class AndFilterTest : public ::testing::Test {
   protected:
    void SetUp() override {
        left_filter_ = new MockFilter();
        right_filter_ = new MockFilter();
        and_filter_ = new storage::AndFilter(left_filter_, right_filter_);
    }

    void TearDown() override {
        delete and_filter_;
        delete left_filter_;
        delete right_filter_;
    }

    MockFilter* left_filter_;
    MockFilter* right_filter_;
    storage::AndFilter* and_filter_;
};

TEST_F(AndFilterTest, SatisfyStatistic) {
    MockStatistic statistic;
    EXPECT_CALL(*left_filter_, satisfy(&statistic))
        .WillOnce(testing::Return(true));
    EXPECT_CALL(*right_filter_, satisfy(&statistic))
        .WillOnce(testing::Return(true));

    EXPECT_TRUE(and_filter_->satisfy(&statistic));
}

TEST_F(AndFilterTest, SatisfyTimeValue) {
    EXPECT_CALL(*left_filter_, satisfy(123L, Object(456)))
        .WillOnce(testing::Return(true));
    EXPECT_CALL(*right_filter_, satisfy(123L, Object(456)))
        .WillOnce(testing::Return(true));

    EXPECT_TRUE(and_filter_->satisfy(123L, Object(456)));
}

TEST_F(AndFilterTest, SatisfyStartEndTime) {
    EXPECT_CALL(*left_filter_, satisfy_start_end_time(1000L, 2000L))
        .WillOnce(testing::Return(true));
    EXPECT_CALL(*right_filter_, satisfy_start_end_time(1000L, 2000L))
        .WillOnce(testing::Return(true));

    EXPECT_TRUE(and_filter_->satisfy_start_end_time(1000L, 2000L));
}

TEST_F(AndFilterTest, ContainStartEndTime) {
    EXPECT_CALL(*left_filter_, contain_start_end_time(1000L, 2000L))
        .WillOnce(testing::Return(true));
    EXPECT_CALL(*right_filter_, contain_start_end_time(1000L, 2000L))
        .WillOnce(testing::Return(true));

    EXPECT_TRUE(and_filter_->contain_start_end_time(1000L, 2000L));
}

TEST_F(AndFilterTest, GetTimeRanges) {
    TimeRange range1(1000L, 2000L);
    TimeRange range2(1500L, 2500L);
    TimeRange range3(3000L, 4000L);
    std::vector<TimeRange*> left_ranges = {&range1, &range3};
    std::vector<TimeRange*> right_ranges = {&range2};

    EXPECT_CALL(*left_filter_, get_time_ranges())
        .WillOnce(testing::Return(&left_ranges));
    EXPECT_CALL(*right_filter_, get_time_ranges())
        .WillOnce(testing::Return(&right_ranges));

    std::vector<TimeRange*>* result = and_filter_->get_time_ranges();

    ASSERT_EQ(result->size(), 1);
    EXPECT_EQ(result->at(0)->start_time_, 1500L);
    EXPECT_EQ(result->at(0)->end_time_, 2000L);

    for (auto range : *result) {
        delete range;
    }
    delete result;
}
