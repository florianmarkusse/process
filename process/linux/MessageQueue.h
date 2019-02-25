#pragma once
#include "../IInterProcess.h"

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

	class MessageQueue : public IInterProcess
	{
	private:
		mqd_t m_messageQueueDescriptor;
		std::string m_messageQueueName;
		MessageQueueState m_messageQueueState;
		MessageQueueMode m_openMode;

		static struct mq_attr m_messageQueueAttributes;

		MessageQueue(mqd_t messageQueueDescriptor,
			const std::string & messageQueueName,
			MessageQueueState messageQueueState,
			MessageQueueMode openMode);

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

		static MessageQueue open(const std::string &messageQueueName,
			MessageQueueMode openMode);
		void close();

		const std::string &getMessageQueueName() const;

		size_t read(Buffer buffer) override;
		void write(Buffer buffer) override;
	};
} // namespace logger
