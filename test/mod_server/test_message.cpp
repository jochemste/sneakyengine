#include <gtest/gtest.h>

#include "message_impl.hpp"

#include "types.hpp"

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
  const int m_message_int         = 42;

private:
};

class TestMessageInterface : public ::testing::Test {
protected:
  const std::string m_subject     = "Some subject";
  const std::string m_message_str = "Some message string";
  const int m_message_int         = 42;
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

/// Test if get_message() retrieved message string and errors at trying to
/// retrieve message int
TEST_F(TestMessageImplDefault, TestGetMessageStr) {
  srv::MessageImpl msg(m_subject, m_message_str);
  std::string message_str;
  int message_int;

  EXPECT_TRUE(msg.get_message(message_str));
  EXPECT_FALSE(msg.get_message(message_int));

  EXPECT_EQ(m_message_str, message_str);
}

/// Test if get_message() retrieved message int and errors at trying to
/// retrieve message string
TEST_F(TestMessageImplDefault, TestGetMessageInt) {
  srv::MessageImpl msg(m_subject);
  std::string message_str;
  int message_int;

  msg.set_message(m_message_int);

  EXPECT_TRUE(msg.get_message(message_int));
  EXPECT_FALSE(msg.get_message(message_str));

  EXPECT_EQ(m_message_int, message_int);
}

/// Test the same as the other tests, but then through the external interface,
/// by calling the factory class to get a IMessage instance
TEST_F(TestMessageInterface, TestFullInterfaceStr) {
  using utils::types::e_STRING;
  auto imsg           = srv::MessageFactory().create();
  std::string msg_str = "";

  ASSERT_NO_THROW({
    imsg->set_subject(m_subject);
    imsg->set_message(m_message_str);
    imsg->get_message(msg_str);
  });

  EXPECT_EQ(m_subject, imsg->get_subject());
  EXPECT_EQ(m_message_str, msg_str);
  EXPECT_NE(imsg->get_message_id(), 0);
  EXPECT_EQ(imsg->get_type(), e_STRING);
  EXPECT_NE(imsg->get_subject_id(), 0);
}

/// Test the same as the other tests, but then through the external interface,
/// by calling the factory class to get a IMessage instance
TEST_F(TestMessageInterface, TestFullInterfaceInt) {
  using utils::types::e_INT;
  auto imsg   = srv::MessageFactory().create();
  int msg_int = 0;

  ASSERT_NO_THROW({
    imsg->set_subject(m_subject);
    imsg->set_message(m_message_int);
    imsg->get_message(msg_int);
  });

  EXPECT_EQ(m_subject, imsg->get_subject());
  EXPECT_EQ(m_message_int, msg_int);
  EXPECT_NE(imsg->get_message_id(), 0);
  EXPECT_EQ(imsg->get_type(), e_INT);
  EXPECT_NE(imsg->get_subject_id(), 0);
}
