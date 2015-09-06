#pragma once

#include <thread>
#include <memory>
#include <asio.hpp>

class IOServiceThreadManager;

typedef std::thread::id thread_id;

class IOServiceThread final
{
	friend class IOServiceThreadManager;

public:
	IOServiceThread(IOServiceThreadManager &manager);
	~IOServiceThread() = default;

public:
	void RunThread();

	void Join();

	void Stop();

	size_t Load() const;

	template <typename CompletionHandler>
	void Post(ASIO_MOVE_ARG(CompletionHandler) handler)
	{
		io_service_.post(handler);
	}

public:
	thread_id id() const
	{
		return thread_ != nullptr ? thread_->get_id() : thread_id();
	}

	asio::io_service& io_service()
	{
		return io_service_;
	}

	IOServiceThreadManager& manager()
	{
		return manager_;
	}

private:
	void Run();

protected:
	IOServiceThread(const IOServiceThread&) = delete;
	IOServiceThread& operator=(const IOServiceThread&) = delete;

private:
	IOServiceThreadManager&					manager_;
	asio::io_service						io_service_;
	std::shared_ptr<std::thread>			thread_;
	std::unique_ptr<asio::io_service::work>	work_;
};