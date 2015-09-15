#pragma once

#include <memory>
#include <unordered_set>
#include <asio/io_service.hpp>
#include "types.h"

class tcp_session;
class io_service_thread_manager;

class io_service_thread final
{
	friend class io_service_thread_manager;
	typedef std::shared_ptr<tcp_session> session_ptr;

public:
	io_service_thread(io_service_thread_manager &manager);
	~io_service_thread() = default;

public:
	void run_thread();

	void join();

	void stop();

	size_t load() const;

	template <typename CompletionHandler>
	void post(ASIO_MOVE_ARG(CompletionHandler) handler)
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

	io_service_thread_manager& manager()
	{
		return manager_;
	}

	std::unordered_set<session_ptr>& session_queue()
	{
		return session_queue_;
	}

private:
	void run();

protected:
	io_service_thread(const io_service_thread&) = delete;
	io_service_thread& operator=(const io_service_thread&) = delete;

private:
	io_service_thread_manager&				manager_;
	asio::io_service						io_service_;
	std::shared_ptr<std::thread>			thread_;
	std::unique_ptr<asio::io_service::work>	work_;
	std::unordered_set<session_ptr>			session_queue_;
};