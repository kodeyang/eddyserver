#include "IOServiceThreadManager.h"

#include <cassert>
#include <cstdint>

#include "IOServiceThread.h"

const uint32_t kMainThreadIndex = 0;


IOServiceThreadManager::IOServiceThreadManager(size_t thread_num)
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