#pragma once

#include <boost/noncopyable.hpp>

class ThreadManager final : public boost::noncopyable
{
public:
	explicit ThreadManager(size_t thread_num = 1);
	~ThreadManager();
};