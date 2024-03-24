#include <gtest/gtest.h>

#include "message_impl.hpp"

#include <functional>
#include <string>

class TestMessageImplDefault : public ::testing::Test {
public:
protected:
  unsigned long int get_hashes_subj() {
    std::hash<std::string> hasher;
    return hasher(m_subject);
  }

  const std::string m_subject     = "Some subject";
  const std::string m_message_str = "Some message string";

private:
};

namespace srv = common::mod_server;

TEST_F(TestMessageImplDefault, TestConstructorNoParam) {
  ASSERT_NO_THROW({ srv::MessageImpl msg; });
}

TEST_F(TestMessageImplDefault, TestConstructorSubjectAsParam) {
  ASSERT_NO_THROW({ srv::MessageImpl msg(m_subject); });
}

TEST_F(TestMessageImplDefault, TestConstructorSubjectMessStrAsParam) {
  ASSERT_NO_THROW({ srv::MessageImpl msg(m_subject, m_subject); });
}

TEST_F(TestMessageImplDefault, TestGetSubject) {
  srv::MessageImpl msg(m_subject, m_message_str);
  auto subj_ret = msg.get_subject();

  EXPECT_EQ(m_subject, subj_ret);
}
