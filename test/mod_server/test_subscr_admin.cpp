#include <gtest/gtest.h>

#include "server.hpp"
#include "subscr_admin.hpp"

#include "hash.hpp"

#include "mock_subscriber.hpp"

using ::testing::Return;

class TestSubscrAdmin : public ::testing::Test {
public:
protected:
};

TEST_F(TestSubscrAdmin, TestAddSubscriberNewSubject) {
  subscr_admin::SubscriberAdmin sa;
  std::shared_ptr<MockSubscriber> sub1;
  bool result = false;

  ASSERT_NO_THROW({ result = sa.add_subscriber("TestSubject", sub1); });
  EXPECT_TRUE(result);
}

TEST_F(TestSubscrAdmin, TestAdd2SubscribersNewSubject) {
  subscr_admin::SubscriberAdmin sa;
  std::shared_ptr<MockSubscriber> sub1;
  std::shared_ptr<MockSubscriber> sub2;
  bool r1, r2 = false;

  ASSERT_NO_THROW({
    r1 = sa.add_subscriber("TestSubject", sub1);
    r2 = sa.add_subscriber("TestSubject", sub2);
  });

  EXPECT_TRUE(r1);
  EXPECT_TRUE(r2);
}

TEST_F(TestSubscrAdmin, TestAddMultiSubscribersNewSubjects) {
  subscr_admin::SubscriberAdmin sa;
  std::shared_ptr<MockSubscriber> sub1;
  std::shared_ptr<MockSubscriber> sub2;
  std::shared_ptr<MockSubscriber> sub3;
  std::shared_ptr<MockSubscriber> sub4;
  bool r1, r2, r3, r4 = false;

  ASSERT_NO_THROW({
    r1 = sa.add_subscriber("TestSubject", sub1);
    r2 = sa.add_subscriber("TestSubject2", sub2);
    r3 = sa.add_subscriber("TestSubject2", sub3);
    r4 = sa.add_subscriber("TestSubject", sub4);
  });

  EXPECT_TRUE(r1);
  EXPECT_TRUE(r2);
  EXPECT_TRUE(r3);
  EXPECT_TRUE(r4);
}

TEST_F(TestSubscrAdmin, TestRemoveExistingSubscriber) {
  subscr_admin::SubscriberAdmin sa;
  std::shared_ptr<MockSubscriber> sub1 = std::make_shared<MockSubscriber>();
  const hash::hash_t id                = 42;
  bool r_add, r_rm = false;

  // ERROR
  EXPECT_CALL(*sub1.get(), get_id()).WillOnce(Return(id));

  ASSERT_NO_THROW({
    r_add = sa.add_subscriber("TestSubject", sub1);
    r_rm  = sa.remove_subscriber(id);
  });

  EXPECT_TRUE(r_add);
  EXPECT_TRUE(r_rm);
}

TEST_F(TestSubscrAdmin, TestRemoveNonExistingSubscriber) {
  subscr_admin::SubscriberAdmin sa;
  std::shared_ptr<MockSubscriber> sub1 = std::make_shared<MockSubscriber>();
  const hash::hash_t id                = 42;
  bool r_add, r_rm = false;

  EXPECT_CALL(*sub1.get(), get_id()).WillOnce(Return(id - 1));

  ASSERT_NO_THROW({
    r_add = sa.add_subscriber("TestSubject", sub1);
    r_rm  = sa.remove_subscriber(id);
  });

  EXPECT_TRUE(r_add); // Adding should have succeeded
  EXPECT_FALSE(r_rm); // Removing should have failed
}

TEST_F(TestSubscrAdmin, TestRemove2Subscribers) {
  using subptr_t = std::shared_ptr<MockSubscriber>;
  subscr_admin::SubscriberAdmin sa;
  std::vector<subptr_t> subscr_v = {std::make_shared<MockSubscriber>(),
                                    std::make_shared<MockSubscriber>()};

  hash::hash_t start_id         = 42; // ID to start counting from
  std::vector<hash::hash_t> ids = {}; // vector to store unique IDs
  std::vector<bool> r_add{}; // results of adding
  std::vector<bool> r_rm{}; // results of removing

  // Setup expectations and IDs
  for (size_t i = 0; i < subscr_v.size(); i++) {
    EXPECT_CALL(*(subscr_v.at(i)).get(), get_id())
        .WillRepeatedly(Return(start_id));
    ids.push_back(start_id++);
  }

  ASSERT_NO_THROW({
    int i = 0;
    for (auto &sub : subscr_v) {
      r_add.push_back(sa.add_subscriber("TestSubject", sub));
      r_rm.push_back(sa.remove_subscriber(ids.at(i++)));
    }
  });

  EXPECT_EQ(r_add.size(), subscr_v.size());
  EXPECT_EQ(r_rm.size(), subscr_v.size());
  for (const auto &result : r_add) {
    EXPECT_TRUE(result);
  }
  for (const auto &result : r_rm) {
    EXPECT_TRUE(result);
  }
}

TEST_F(TestSubscrAdmin, TestRemoveMultiSubscribers) {
  using subptr_t = std::shared_ptr<MockSubscriber>;
  subscr_admin::SubscriberAdmin sa;
  const int multi = 42; // random nr for how many subscribers to create
  std::vector<subptr_t> subscr_v = {};

  hash::hash_t start_id         = 42; // ID to start counting from
  std::vector<hash::hash_t> ids = {}; // vector to store unique IDs
  std::vector<bool> r_add{}; // results of adding
  std::vector<bool> r_rm{}; // results of removing

  // Setup all subscriber mocks
  for (int i = 0; i < multi; i++)
    subscr_v.push_back(std::make_shared<MockSubscriber>());

  // Setup expectations and IDs
  for (size_t i = 0; i < subscr_v.size(); i++) {
    EXPECT_CALL(*(subscr_v.at(i)).get(), get_id())
        .WillRepeatedly(Return(start_id));
    ids.push_back(start_id++);
  }

  ASSERT_NO_THROW({
    int i = 0;
    for (auto &sub : subscr_v) {
      r_add.push_back(sa.add_subscriber("TestSubject", sub));
      r_rm.push_back(sa.remove_subscriber(ids.at(i++)));
    }
  });

  EXPECT_EQ(r_add.size(), subscr_v.size());
  EXPECT_EQ(r_rm.size(), subscr_v.size());
  for (const auto &result : r_add) {
    EXPECT_TRUE(result);
  }
  for (const auto &result : r_rm) {
    EXPECT_TRUE(result);
  }
}

// UNFINISHED, need to add multiple subjects
TEST_F(TestSubscrAdmin, TestRemoveMultiSubscribersMultiSubjects) {
  using subptr_t = std::shared_ptr<MockSubscriber>;
  subscr_admin::SubscriberAdmin sa;
  const int multi = 42; // random nr for how many subscribers to create
  std::vector<subptr_t> subscr_v = {};

  hash::hash_t start_id         = 42; // ID to start counting from
  std::vector<hash::hash_t> ids = {}; // vector to store unique IDs
  std::vector<bool> r_add{}; // results of adding
  std::vector<bool> r_rm{}; // results of removing

  // Setup all subscriber mocks
  for (int i = 0; i < multi; i++)
    subscr_v.push_back(std::make_shared<MockSubscriber>());

  // Setup expectations and IDs
  for (size_t i = 0; i < subscr_v.size(); i++) {
    EXPECT_CALL(*(subscr_v.at(i)).get(), get_id())
        .WillRepeatedly(Return(start_id));
    ids.push_back(start_id++);
  }

  ASSERT_NO_THROW({
    int i = 0;
    for (auto &sub : subscr_v) {
      r_add.push_back(sa.add_subscriber("TestSubject", sub));
      r_rm.push_back(sa.remove_subscriber(ids.at(i++)));
    }
  });

  EXPECT_EQ(r_add.size(), subscr_v.size());
  EXPECT_EQ(r_rm.size(), subscr_v.size());
  for (const auto &result : r_add) {
    EXPECT_TRUE(result);
  }
  for (const auto &result : r_rm) {
    EXPECT_TRUE(result);
  }
}

// TEST_F(TestSubscrAdmin, TestAddMultiSubscribersNewSubjects) {
//   subscr_admin::SubscriberAdmin sa;
//   std::shared_ptr<MockSubscriber> sub1;
//   std::shared_ptr<MockSubscriber> sub2;
//   std::shared_ptr<MockSubscriber> sub3;
//   std::shared_ptr<MockSubscriber> sub4;

//   ASSERT_NO_THROW({
//     sa.add_subscriber("TestSubject", sub1);
//     sa.add_subscriber("TestSubject2", sub2);
//     sa.add_subscriber("TestSubject2", sub3);
//     sa.add_subscriber("TestSubject", sub4);
//   });
// }

TEST_F(TestSubscrAdmin, TestContainsSubject) {
  subscr_admin::SubscriberAdmin sa;
  std::shared_ptr<MockSubscriber> sub1;
  const std::string subject = "TestSubject";

  sa.add_subscriber(subject, sub1);

  EXPECT_TRUE(sa.contains_subject(subject));
}
