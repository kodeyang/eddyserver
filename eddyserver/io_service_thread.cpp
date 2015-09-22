#include "io_service_thread.h"

#include <iostream>
#include "tcp_session.h"


io_service_thread::io_service_thread(io_service_thread_manager &manager)
	: manager_(manager_)
	, work_(nullptr)
{

}

void io_service_thread::run()
{
	if (work_ == nullptr)
	{
		work_.reset(new asio::io_service::work(io_service_));
	}

	asio::error_code error;
	io_service_.run(error);

	if (error)
	{
		std::cerr << error.message() << std::endl;
	}
}

void io_service_thread::run_thread()
{
	if (thread_ == nullptr)
	{
		thread_ = std::make_shared<std::thread>(std::bind(&io_service_thread::run, this));
	}
}

size_t io_service_thread::load() const
{
	return session_queue_.size();
}

void io_service_thread::join()
{
	if (thread_ != nullptr)
	{
		thread_->join();
	}
}

void io_service_thread::stop()
{
	if (work_ != nullptr)
	{
		work_.reset();
	}
}