#include <gtest/gtest.h>

#include "server.hpp"
#include "subscr_admin.hpp"

#include "hash.hpp"

#include "mock_subscriber.hpp"

class TestSubscrAdmin : public ::testing::Test {
public:
protected:
};

TEST_F(TestSubscrAdmin, TestAddSubscriberNewSubject) {
  subscr_admin::SubscriberAdmin sa;
  std::shared_ptr<MockSubscriber> sub1;

  ASSERT_NO_THROW({ sa.add_subscriber("TestSubject", sub1); });
}

TEST_F(TestSubscrAdmin, TestAdd2SubscribersNewSubject) {
  subscr_admin::SubscriberAdmin sa;
  std::shared_ptr<MockSubscriber> sub1;
  std::shared_ptr<MockSubscriber> sub2;

  ASSERT_NO_THROW({
    sa.add_subscriber("TestSubject", sub1);
    sa.add_subscriber("TestSubject", sub2);
  });
}
