#include <gtest/gtest.h>

#include "message_impl.hpp"

#include <functional>
#include <string>

class TestMessageImplDefault : public ::testing::Test {
public:
protected:
  unsigned long int get_hashed_subj() {
    std::hash<std::string> hasher;
    return hasher(m_subject);
  }

  const std::string m_subject     = "Some subject";
  const std::string m_message_str = "Some message string";

private:
};

namespace srv = common::mod_server;

/// Test the default constructor without parameters
TEST_F(TestMessageImplDefault, TestConstructorNoParam) {
  ASSERT_NO_THROW({ srv::MessageImpl msg; });
}

/// Test the constructor with only the subject as a parameter
TEST_F(TestMessageImplDefault, TestConstructorSubjectAsParam) {
  ASSERT_NO_THROW({ srv::MessageImpl msg(m_subject); });
}

/// Test the constructor with the subject and message string as parameter
TEST_F(TestMessageImplDefault, TestConstructorSubjectMessStrAsParam) {
  ASSERT_NO_THROW({ srv::MessageImpl msg(m_subject, m_subject); });
}

/// Test if get_subject() works as expected by setting the subject in the
/// constructor and comparing the results of get_subject() to the set subject
TEST_F(TestMessageImplDefault, TestGetSubject) {
  srv::MessageImpl msg(m_subject, m_message_str);
  auto subj_ret = msg.get_subject();

  EXPECT_EQ(m_subject, subj_ret);
}

/// Test if the subject id is set to the hashed value of the set subject by
/// setting the subject in the constructor and comparing the results of
/// get_subject_id() to the expected hash
TEST_F(TestMessageImplDefault, TestGetSubjectID) {
  srv::MessageImpl msg(m_subject, m_message_str);

  EXPECT_EQ(get_hashed_subj(), msg.get_subject_id());
}
