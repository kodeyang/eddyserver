#pragma once

#include <vector>
#include "io_service_thread.h"


class io_service_thread_manager final
{
	typedef std::shared_ptr<io_service_thread> thread_ptr;

public:
	explicit io_service_thread_manager(const size_t thread_num = 1);
	~io_service_thread_manager();

public:
	void run();

	void stop();

	io_service_thread& thread();

	io_service_thread& thread(thread_id id);

	io_service_thread& main_thread();

protected:
	io_service_thread_manager(const io_service_thread_manager&) = delete;
	io_service_thread_manager& operator=(const io_service_thread_manager&) = delete;

private:
	std::vector<thread_ptr> threads_;
};