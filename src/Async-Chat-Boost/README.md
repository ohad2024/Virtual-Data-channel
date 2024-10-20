# ChatServerBoost

This project is a simple chat application implemented in C++ using Boost.Asio. It supports multiple clients connecting to a server, enabling them to send messages to each other in both broadcast and multicast modes.

## Struct: ChatMessage

The `ChatMessage` struct is responsible for constructing and deconstructing messages sent between clients and the server. It contains:

- **`std::string _senderUserName`**: The username of the person sending the message.
- **`std::string _time`**: The time when the message was sent.
- **`std::string _message`**: The actual message text.
- **`MessageType _messageType`**: Determines if the message is a broadcast or multicast.
- **`std::vector<std::string> _recipients`**: A list of recipients (used for multicast).

### Serialization and Deserialization

The `ChatMessage` struct has methods for serializing (turning the message into a string format for sending) and deserializing (converting a received string back into a `ChatMessage` object).

- **`serialize()`**: Combines the message fields into a single string.
- **`deserialize(const std::string& data)`**: Splits the received string back into the original message fields.

## Class: ChatClient

The `ChatClient` class is responsible for handling the client's connection to the server, sending messages, and receiving messages from the server.

### Private Member Variables

1. **`boost::asio::io_context _ioContext`**: Manages asynchronous I/O.
2. **`boost::asio::ip::tcp::socket _clientSocket`**: The socket used to connect to the server.
3. **`std::string _userName`**: Stores the client's username.
4. **`bool _isRunning`**: Controls the main loop for the client.
5. **`const int bufferSize`**: Size of the buffer used for reading messages.
6. **`const std::string serverIp`**: IP address of the server.
7. **`const int serverPort`**: Port used for communication with the server.

### Functions

1. **`runClient()`**: Starts the client's main loop for user input and message sending.
2. **`asyncConnect()`**: Asynchronously connects to the server.
3. **`asyncRead()`**: Asynchronously reads messages from the server.
4. **`asyncWrite(const std::string& message)`**: Asynchronously sends a message to the server.
5. **`createChatMessage(const std::string& input)`**: Creates a `ChatMessage` from user input.
6. **`parseRecipientUsernames(const std::string& input)`**: Extracts recipient usernames from the input for multicast messaging.

## Class: ChatServer

The `ChatServer` class handles multiple client connections, processes messages from clients, and broadcasts or multicasts messages to the appropriate recipients.

### Struct: ClientInfo

The `ClientInfo` struct is used to store the client’s username and socket information:

- **`std::string _username`**: The username of the client.
- **`std::shared_ptr<boost::asio::ip::tcp::socket> _socket`**: The socket used for communicating with this client.

### Private Member Variables

1. **`boost::asio::io_context _ioContext`**: Manages asynchronous I/O for the server.
2. **`boost::asio::ip::tcp::acceptor _acceptor`**: Accepts new client connections.
3. **`std::vector<ClientInfo> _clients`**: Stores all connected clients.

### Functions

1. **`runServer()`**: Starts the server and begins accepting clients.
2. **`asyncAccept()`**: Asynchronously accepts incoming client connections.
3. **`receiveUsername(std::shared_ptr<boost::asio::ip::tcp::socket> clientSocket)`**: Receives a client's username after connection.
4. **`asyncRead(std::shared_ptr<boost::asio::ip::tcp::socket> clientSocket)`**: Asynchronously reads messages from a client.
5. **`handleMessage(const ChatMessage& message, std::shared_ptr<boost::asio::ip::tcp::socket> senderSocket)`**: Handles both broadcast and multicast messages.
6. **`broadcastMessage(const ChatMessage& message, std::shared_ptr<boost::asio::ip::tcp::socket> senderSocket = nullptr)`**: Sends a broadcast message to all connected clients except the sender.
7. **`processRecipients(const ChatMessage& message)`**: Sends a multicast message to specific recipients.
8. **`asyncWrite(std::shared_ptr<boost::asio::ip::tcp::socket> clientSocket, const std::string& message)`**: Sends messages to a client asynchronously.
9. **`removeClient(std::shared_ptr<boost::asio::ip::tcp::socket> clientSocket)`**: Removes a disconnected client from the list.

## Messaging

- **Broadcast**: Send a message to all clients by simply typing and pressing enter.
- **Multicast**: Send a message to specific clients by prefixing their usernames with `@`. For example:
@user1 @user2 Hello!

- **Exiting**: To disconnect from the server, type `exit`.

