#pragma once

#include <vector>
#include <memory>

class IOServiceThread;

class IOServiceThreadManager final
{
	typedef std::shared_ptr<IOServiceThread> thread_ptr;

public:
	explicit IOServiceThreadManager(size_t thread_num = 1);
	~IOServiceThreadManager();

public:
	void Run();

	void Stop();

protected:
	IOServiceThreadManager(const IOServiceThreadManager&) = delete;
	IOServiceThreadManager& operator=(const IOServiceThreadManager&) = delete;

private:
	std::vector<thread_ptr> threads_;
};