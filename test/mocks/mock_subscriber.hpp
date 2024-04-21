#include <gmock/gmock.h>

#include "hash.hpp"
#include "server.hpp"

using namespace common::mod_server;

class MockSubscriber : public ISubscriber {
public:
  MOCK_METHOD(hash::hash_t, get_id, (), (override));
  MOCK_METHOD(bool, has_message, (), (override));
  MOCK_METHOD(void, set_message, (std::shared_ptr<IMessage> message),
              (override));
  MOCK_METHOD(std::shared_ptr<IMessage>, get_message, (), (override));
};
