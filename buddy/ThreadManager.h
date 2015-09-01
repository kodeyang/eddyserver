#pragma once


class ThreadManager final
{
public:
	explicit ThreadManager(size_t thread_num = 1);
	~ThreadManager();

protected:
	ThreadManager(const ThreadManager&) = delete;
	ThreadManager& operator=(const ThreadManager&) = delete;
};