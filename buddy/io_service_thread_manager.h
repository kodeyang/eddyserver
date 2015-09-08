#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include "types.h"
#include "id_generator.h"

class tcp_session;
class io_service_thread;
class tcp_session_handle;

class io_service_thread_manager final
{
	typedef std::shared_ptr<tcp_session> session_ptr;
	typedef std::shared_ptr<io_service_thread> thread_ptr;
	typedef std::shared_ptr<tcp_session_handle> session_handler_ptr;
	typedef std::unordered_map<session_id, session_handler_ptr > session_handler_map;

public:
	explicit io_service_thread_manager(size_t thread_num = 1);

	~io_service_thread_manager();

public:
	void run();

	void stop();

	io_service_thread& thread();

	io_service_thread& thread(thread_id id);

	io_service_thread& main_thread();

	void on_session_connect(session_ptr session, session_handler_ptr handler);

	void on_session_close(session_id id);

	session_handler_ptr session_handler(session_id id) const;

protected:
	io_service_thread_manager(const io_service_thread_manager&) = delete;
	io_service_thread_manager& operator=(const io_service_thread_manager&) = delete;

private:
	std::vector<thread_ptr> threads_;
	session_handler_map		session_handler_map_;
	id_generator			id_generator_;
};