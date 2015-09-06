#pragma once

#include <vector>
#include "IOServiceThread.h"

class IOServiceThreadManager final
{
	typedef std::shared_ptr<IOServiceThread> thread_ptr;

public:
	explicit IOServiceThreadManager(const size_t thread_num = 1);
	~IOServiceThreadManager();

public:
	void Run();

	void Stop();

	IOServiceThread& GetThread();

	IOServiceThread& GetThread(thread_id id);

	IOServiceThread& GetMainThread();

protected:
	IOServiceThreadManager(const IOServiceThreadManager&) = delete;
	IOServiceThreadManager& operator=(const IOServiceThreadManager&) = delete;

private:
	std::vector<thread_ptr> threads_;
};