#pragma once
#include <fcntl.h>           /* For O_* constants */
#include <mqueue.h>
#include <string>

/*
	Class for managing the creation and usage of pipes for logging purposes.

	Florian Markusse
*/

namespace logger
{

	enum class MessageQueueState
	{
		client,
		serverConnected,
		serverDisconnected
	};

	enum class MessageQueueMode
	{
		read = O_RDONLY,
		write = O_WRONLY,
		readAndWrite = O_RDWR
	};

	enum class LogLevel
	{
		// White color font.
		info,
		// Yellow/amber color font.
		warn,
		// Red color font.
		error,
		// Green color font.
		success
    };

	// Need to know the size of the number of bytes that we have to write to the
	// pipe.
	struct BufferSize
	{
		const size_t value;

		explicit BufferSize(const size_t value)
			: value { value }
		{
		}
	};

	struct ReadBufferSize : public BufferSize
	{
		explicit ReadBufferSize(const size_t value)
			: BufferSize { value }
		{
		}
	};

	struct WriteBufferSize : BufferSize
	{
		explicit WriteBufferSize(const size_t value)
			: BufferSize { value }
		{
		}
	};

	struct Buffer
	{
		char *data;
		BufferSize size;

		Buffer(char *data, size_t size)
			: data { data }, size { size } {}
	};

	class MessageQueue
	{

	private:
		mqd_t m_messageQueueDescriptor;
		std::string m_messageQueueName;
	    MessageQueueState m_messageQueueState;
        MessageQueueMode m_openMode;

        static struct mq_attr m_messageQueueAttributes;

		MessageQueue(mqd_t messageQueueDescriptor, std::string messageQueueName, MessageQueueState messageQueueState, MessageQueueMode openMode);

		void connect();
		void disconnect();

	public:
		MessageQueue(const MessageQueue &other) = delete;
		MessageQueue(MessageQueue &&other) noexcept;

		MessageQueue &operator=(const MessageQueue &other) = delete;
		MessageQueue &operator=(MessageQueue && other) noexcept;

		virtual ~MessageQueue();

		static MessageQueue create(
			const std::string &messageQueueName,
			MessageQueueMode openMode);

		static MessageQueue open(const std::string &messageQueueName, MessageQueueMode openMode);

		void close();
		const std::string &getMessageQueueName() const;
		size_t read(Buffer buffer);
		void write(Buffer buffer);
	};

} // namespace logger