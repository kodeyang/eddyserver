#include "IOServiceThread.h"

#include <iostream>


IOServiceThread::IOServiceThread(IOServiceThreadManager &manager)
	: manager_(manager_)
	, work_(nullptr)
{

}

void IOServiceThread::Run()
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

void IOServiceThread::RunThread()
{
	if (thread_ == nullptr)
	{
		thread_ = std::make_shared<std::thread>(std::bind(&IOServiceThread::Run, this));
	}
}

size_t IOServiceThread::Load() const
{
	return 0;
}

void IOServiceThread::Join()
{
	if (thread_ != nullptr)
	{
		thread_->join();
	}
}

void IOServiceThread::Stop()
{
	if (work_ != nullptr)
	{
		work_.reset();
	}
}