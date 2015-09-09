#include "io_service_thread_manager.h"

#include <queue>
#include "io_service_thread.h"
#include "tcp_session_handle.h"

static const std::size_t kMainThreadIndex = 0;


io_service_thread_manager::io_service_thread_manager(size_t thread_num)
{
	assert(thread_num > kMainThreadIndex);

	threads_.reserve(thread_num);
	for (size_t i = 0; i < threads_.size(); ++i)
	{
		threads_[i] = std::make_shared<io_service_thread>(*this);
	}
}

io_service_thread_manager::~io_service_thread_manager()
{
	stop();
}

void io_service_thread_manager::run()
{
	if (threads_.empty())
	{
		return;
	}

	for (size_t i = 0; i < threads_.size(); ++i)
	{
		if (i != kMainThreadIndex)
		{
			threads_[i]->run_thread();
		}
	}
	threads_[kMainThreadIndex]->run();
}

void io_service_thread_manager::stop()
{
	if (threads_.empty())
	{
		return;
	}

	for (size_t i = 0; i < threads_.size(); ++i)
	{
		if (i != kMainThreadIndex)
		{
			threads_[i]->stop();
		}
	}

	for (size_t i = 0; i < threads_.size(); ++i)
	{
		if (i != kMainThreadIndex)
		{
			threads_[i]->join();
		}
	}

	threads_[kMainThreadIndex]->stop();
}

io_service_thread& io_service_thread_manager::thread()
{
	if (threads_.size() == 1)
	{
		return *threads_[kMainThreadIndex];
	}

	typedef std::pair<size_t, size_t> value_type;
	std::priority_queue<value_type, std::vector<value_type>, std::greater<value_type>> que;
	for (size_t i = 0; i < threads_.size(); ++i)
	{
		que.push(std::make_pair(threads_[i]->load(), i));
	}
	return *threads_[que.top().second];
}

io_service_thread& io_service_thread_manager::thread(thread_id id)
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

io_service_thread& io_service_thread_manager::main_thread()
{
	return *threads_[kMainThreadIndex];
}

void io_service_thread_manager::on_session_connect(session_ptr session, session_handler_ptr handler)
{
	session_id id = kInvalidSessionID;
	if (id_generator_.get(id))
	{
		handler->init(id, session->thread().id(), this);
		session_handler_map_.insert(std::make_pair(id, handler));
		session->thread().post(std::bind(&tcp_session::init, session, id));
		handler->on_connect();
	}
}

void io_service_thread_manager::on_session_close(session_id id)
{
	assert(id != kInvalidSessionID);
	session_handler_map::iterator itr = session_handler_map_.find(id);
	if (itr != session_handler_map_.end())
	{
		session_handler_ptr handler = itr->second;
		if (handler != nullptr)
		{
			handler->on_close();
			handler->dispose();
		}
		session_handler_map_.erase(itr);
	}
	id_generator_.put(id);
}

io_service_thread_manager::session_handler_ptr io_service_thread_manager::session_handler(session_id id) const
{
	session_handler_map::const_iterator itr = session_handler_map_.find(id);
	if (itr != session_handler_map_.end())
	{
		return itr->second;
	}
	return session_handler_ptr();
}