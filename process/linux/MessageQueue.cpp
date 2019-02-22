#include "MessageQueue.h"

/*
	Class for managing the creation and usage of pipes for logging purposes.

	Florian Markusse
*/
namespace logger
{
	// 10 messages at most int the message queue.
	constexpr static unsigned int MAX_MESSAGES = 10;
	// Each message of at most 4096 bytes.
	constexpr static unsigned int MAX_MESSAGE_SIZE = 4096;

	// Define standard message queue attributes that is used for every logger.
	struct mq_attr MessageQueue::m_messageQueueAttributes = {
		0,
		MAX_MESSAGES,
		MAX_MESSAGE_SIZE,
		0,
		0
	};

	/*
		<Constructor>
		Creates a MessageQueue instance

		@param messageQueueDescriptor; Descriptor used to connect to the message queue.
		@param messageQueueName; The name of the message queue.
		@param messageQueueState; The state of the message queue.
		@param openMode; How the message queue should be opened.

		@return The created Pipe instance
	*/
	MessageQueue::MessageQueue(mqd_t messageQueueDescriptor, std::string messageQueueName, MessageQueueState messageQueueState, MessageQueueMode openMode)
		: m_messageQueueDescriptor(messageQueueDescriptor), m_messageQueueName(messageQueueName), m_messageQueueState(messageQueueState), m_openMode(openMode)
	{
	}

	/*
		Connects the MessageQueue instance to the actual message queue.
	*/
	void MessageQueue::connect()
	{
		if (m_messageQueueState != MessageQueueState::serverDisconnected) {
			return;
		}

		m_messageQueueDescriptor = mq_open(m_messageQueueName.c_str(),
			static_cast<std::underlying_type<MessageQueueMode>::type>( m_openMode ),
			m_openMode);

		if (( m_messageQueueDescriptor ) == -1) {
			perror("cant connect to queue\n");
			exit(1);
		}

		m_messageQueueState = MessageQueueState::serverConnected;
	}

	/*
		Disconnects the Pipe instance from the actual pipe.
	*/
	void MessageQueue::disconnect()
	{
		if (m_messageQueueState == MessageQueueState::serverConnected) {
			mq_close(m_messageQueueDescriptor);
			if (( m_messageQueueDescriptor ) == -1) {
				perror("cant disconnect from queue\n");
				exit(1);
			}
			m_messageQueueState = MessageQueueState::serverDisconnected;
		}
	}

	/*
		<Move constructor>
		Moves the member variables of the "other" instance to this instance and
		sets the "other" instance to an invalid message queue.

		@param other; The other MessageQueue instance.
	*/
	MessageQueue::MessageQueue(MessageQueue && other) noexcept
		: m_messageQueueDescriptor { other.m_messageQueueDescriptor },
		m_messageQueueName { other.m_messageQueueName },
		m_messageQueueState { std::move(other.m_messageQueueState) },
		m_openMode { std::move(other.m_openMode) }
	{
		// "other" is no longer valid.
		other.m_messageQueueDescriptor = -1;
	}

	/*
		<Move assignment operator>
		Closes the message queue, moves the member variables of the "other" instance to
		this instance and sets the "other" instance to an invalid message queue.
		Afterwards, returns the current instance.

		@param other; The other MessageQueue instance.

		@return The current MessageQueue instance.
	*/
	MessageQueue & MessageQueue::operator=(MessageQueue && other) noexcept
	{
		// Have to close this pipe first before using "other"'s pipe.
		close();

		m_messageQueueDescriptor = other.m_messageQueueDescriptor;
		m_messageQueueName = other.m_messageQueueName;
		m_messageQueueState = std::move(other.m_messageQueueState);
		m_openMode = std::move(other.m_openMode);

		// "other" is no longer valid.
		other.m_messageQueueDescriptor = -1;

		return *this;
	}

	/*
		<Deconstructor>, <virtual>
		Closes the message queue.
	*/
	MessageQueue::~MessageQueue()
	{
		close();
	}

	/*
		Creates the message queue and returns a MessageQueue instance.

		@param messageQueueName; The name of the message queue in the file system.
		@param openMode; Which mode the message queue is to be opened.

		@return the created MessageQueue instance.
	*/
	MessageQueue MessageQueue::create(
		const std::string &messageQueueName,
		MessageQueueMode openMode)
	{
		mqd_t messageQueueDescriptorServer;

		messageQueueDescriptorServer = mq_open(messageQueueName.c_str(),
			static_cast<std::underlying_type<MessageQueueMode>::type>( openMode ) | O_CREAT,
			S_IRWXU,
			&m_messageQueueAttributes);

		if (messageQueueDescriptorServer == -1) {
			perror("failed to create queue\n");
			exit(EXIT_FAILURE);
		}

		return MessageQueue { messageQueueDescriptorServer, messageQueueName, MessageQueueState::serverConnected, openMode };
	}

	/*
		Opens the message queue in the supplied mode. Returns the correct instance or an
		invalid instance if opening was unsuccessful.

		@param messageQueueName; The name of the message queue in the file system.
		@param openMode; Which mode the message queue is to be opened in.

		@return the created MessageQueue instance.
	*/
	MessageQueue MessageQueue::open(const std::string &messageQueueName, MessageQueueMode openMode)
	{
		mqd_t messageQueueDescriptorClient;

		messageQueueDescriptorClient = mq_open(messageQueueName.c_str(),
			static_cast<std::underlying_type<MessageQueueMode>::type>( openMode ),
			S_IRWXU,
			&m_messageQueueAttributes);

		if (messageQueueDescriptorClient == -1) {
			perror("failed to open queue\n");
			exit(EXIT_FAILURE);
		}

		return MessageQueue { messageQueueDescriptorClient, messageQueueName, MessageQueueState::client, openMode };
	}

	/*
		Closes the message queue and sets this instance to invalid.
	*/
	void MessageQueue::close()
	{
		if (m_messageQueueDescriptor != -1) {
			disconnect();
			int result = mq_unlink(m_messageQueueName.c_str());
			if (result == -1) {
				perror("failed to unlink queue\n");
				exit(EXIT_FAILURE);
			}
			m_messageQueueDescriptor = -1;
		}
	}

	/*
		Returns the name of the message queue.

		@return m_messageQueueName.
	*/
	const std::string & MessageQueue::getMessageQueueName() const
	{
		return m_messageQueueName;
	}

	/*
		Reads bytes from the message queue into the buffer.

		@param buffer; The buffer to which the content of the message queue have to be
		written into.

		@return The amount of bytes read.
	*/
	size_t MessageQueue::read(Buffer buffer)
	{
		connect();

		ssize_t bytesRead = mq_receive(m_messageQueueDescriptor,
			buffer.data,
			buffer.size.value,
			nullptr);

		if (bytesRead == -1) {
			perror("failed to read from queue\n");
			exit(EXIT_FAILURE);
		}

		return bytesRead;
	}

	/*
		Writes bytes from the buffer into the message queue.

		@param buffer; The buffer from which the content will be written to the
		message queue.
	*/
	void MessageQueue::write(const Buffer buffer)
	{
		connect();

		int result = mq_send(m_messageQueueDescriptor, buffer.data, buffer.size.value, 0);

		if (result == -1) {
			perror("failed to write to queue\n");
			exit(EXIT_FAILURE);
		}
	}
} // namespace logger
