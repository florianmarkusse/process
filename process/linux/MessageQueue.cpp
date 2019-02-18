#include "MessageQueue.h"

namespace logger
{

    constexpr static unsigned int MAX_MESSAGES = 10;
    constexpr static unsigned int MAX_MESSAGE_SIZE = 4096;

    struct mq_attr MessageQueue::m_messageQueueAttributes = {
        0,
        MAX_MESSAGES,
        MAX_MESSAGE_SIZE,
        0,
        0
    };

    MessageQueue::MessageQueue(mqd_t messageQueueDescriptor, std::string messageQueueName, MessageQueueState messageQueueState, MessageQueueMode openMode)
        : m_messageQueueDescriptor(messageQueueDescriptor), m_messageQueueName(messageQueueName), m_messageQueueState(messageQueueState), m_openMode(openMode)  
    {

    }

    void MessageQueue::connect() 
    {

        if (m_messageQueueState != MessageQueueState::serverDisconnected) {
			return;
		}

        m_messageQueueDescriptor = mq_open(m_messageQueueName.c_str(), 
            static_cast<std::underlying_type<MessageQueueMode>::type>(m_openMode),
            m_openMode);

		if ((m_messageQueueDescriptor) == -1) {
            perror ("cant connect to queue\n");
            exit(1);
        }

		m_messageQueueState = MessageQueueState::serverConnected;
    }

    void MessageQueue::disconnect() 
    {

        if (m_messageQueueState == MessageQueueState::serverConnected) {
			mq_close(m_messageQueueDescriptor);
            if ((m_messageQueueDescriptor) == -1) {
                perror("cant disconnect from queue\n");
                exit(1);
            }
			m_messageQueueState = MessageQueueState::serverDisconnected;
		}

    }

    MessageQueue::MessageQueue(MessageQueue && other) noexcept
		: m_messageQueueDescriptor { other.m_messageQueueDescriptor }, 
		m_messageQueueName { other.m_messageQueueName }, 
		m_messageQueueState { std::move(other.m_messageQueueState) },
        m_openMode { std::move(other.m_openMode) }
	{
		// "other" is no longer valid.
		other.m_messageQueueDescriptor = -1;
	}

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

    MessageQueue::~MessageQueue() {
        close();
    }

    MessageQueue MessageQueue::create(
			const std::string &messageQueueName,
			MessageQueueMode openMode)
    {
        mqd_t messageQueueDescriptorServer;

        messageQueueDescriptorServer = mq_open(messageQueueName.c_str(), 
        static_cast<std::underlying_type<MessageQueueMode>::type>(openMode) | O_CREAT, 
        S_IRWXU, 
        &m_messageQueueAttributes);

        if (messageQueueDescriptorServer == -1) {
			perror("failed to create queue\n");
			exit(EXIT_FAILURE);
		}

        return MessageQueue { messageQueueDescriptorServer, messageQueueName, MessageQueueState::serverConnected, openMode };
    }

    MessageQueue MessageQueue::open(const std::string &messageQueueName, MessageQueueMode openMode) 
    {

        mqd_t messageQueueDescriptorClient;

        messageQueueDescriptorClient = mq_open(messageQueueName.c_str(), 
        static_cast<std::underlying_type<MessageQueueMode>::type>(openMode), 
        S_IRWXU, 
        &m_messageQueueAttributes);

        if (messageQueueDescriptorClient == -1) {
			perror("failed to open queue\n");
			exit(EXIT_FAILURE);
		}

        return MessageQueue { messageQueueDescriptorClient, messageQueueName, MessageQueueState::client, openMode };
    }

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

    const std::string & MessageQueue::getMessageQueueName() const
	{
		return m_messageQueueName;
	}

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