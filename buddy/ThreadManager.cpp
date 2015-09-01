#include "ThreadManager.h"

#include <boost/assert.hpp>


ThreadManager::ThreadManager(size_t thread_num)
{
	BOOST_ASSERT(thread_num > 0);
}

ThreadManager::~ThreadManager()
{

}