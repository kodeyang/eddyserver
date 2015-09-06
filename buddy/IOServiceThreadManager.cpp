#include "IOServiceThreadManager.h"

#include <queue>
#include <cassert>
#include <algorithm>

const size_t kMainThreadIndex = 0;

IOServiceThreadManager::IOServiceThreadManager(const size_t thread_num)
{
	assert(thread_num > kMainThreadIndex);

	threads_.reserve(thread_num);
	for (size_t i = 0; i < threads_.size(); ++i)
	{
		threads_[i] = std::make_shared<IOServiceThread>(*this);
	}
}

IOServiceThreadManager::~IOServiceThreadManager()
{
	Stop();
}

void IOServiceThreadManager::Run()
{
	if (threads_.empty())
	{
		return;
	}

	for (size_t i = 0; i < threads_.size(); ++i)
	{
		if (i != kMainThreadIndex)
		{
			threads_[i]->RunThread();
		}
	}
	threads_[kMainThreadIndex]->Run();
}

void IOServiceThreadManager::Stop()
{
	if (threads_.empty())
	{
		return;
	}

	for (size_t i = 0; i < threads_.size(); ++i)
	{
		if (i != kMainThreadIndex)
		{
			threads_[i]->Stop();
		}
	}

	for (size_t i = 0; i < threads_.size(); ++i)
	{
		if (i != kMainThreadIndex)
		{
			threads_[i]->Join();
		}
	}

	threads_[kMainThreadIndex]->Stop();
}

IOServiceThread& IOServiceThreadManager::GetThread()
{
	if (threads_.size() == 1)
	{
		return *threads_[kMainThreadIndex];
	}

	typedef std::pair<size_t, size_t> value_type;
	std::priority_queue<value_type, std::vector<value_type>, std::greater<value_type>> que;
	for (size_t i = 0; i < threads_.size(); ++i)
	{
		que.push(std::make_pair(threads_[i]->Load(), i));
	}
	return *threads_[que.top().second];
}

IOServiceThread& IOServiceThreadManager::GetThread(thread_id id)
{
	for (size_t i = 0; i < threads_.size(); ++i)
	{
		if (threads_[i]->id() == id)
		{
			return *threads_[i];
		}
	}
	throw std::runtime_error("not found thread");
}

IOServiceThread& IOServiceThreadManager::GetMainThread()
{
	return *threads_[kMainThreadIndex];
}