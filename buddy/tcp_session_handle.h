#pragma once

#include "tcp_session.h"

class io_service_thread_manager;

class tcp_session_handle : public std::enable_shared_from_this < tcp_session_handle >
{
	friend class io_service_thread_manager;

public:
	tcp_session_handle();

	virtual ~tcp_session_handle();

	void send(message_buffer &message);

	void close();

	void dispose();

	bool is_closed() const;

public:
	virtual void on_connect() = 0;

	virtual void on_message(message_buffer &message) = 0;

	virtual void on_close() = 0;

private:
	void init(session_id sid, thread_id tid, io_service_thread_manager* manager);

protected:
	tcp_session_handle(const tcp_session_handle &) = delete;
	tcp_session_handle& operator= (const tcp_session_handle &) = delete;

private:
	session_id					session_id_;
	thread_id					session_thread_id_;
	io_service_thread_manager*	io_thread_manager_;
	message_vector				messages_to_be_sent_;
};