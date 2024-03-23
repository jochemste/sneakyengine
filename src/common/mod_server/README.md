# Module server

Common submodule used for modules to sent messages between modules.
Uses a subscription based server, that will act as mediator between
poster and subscriber.

To receive messages from the server, a subscriber instance should
be created, which can be polled for messages.
To send messages using the server, a poster instance and message
instance should be created. This poster instance should hold some
basic information about the sender
