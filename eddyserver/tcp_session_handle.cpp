#include "tcp_session_handle.h"


tcp_session_handle::tcp_session_handle()
	: session_id_(kInvalidSessionID)
{

}

tcp_session_handle::~tcp_session_handle()
{

}

void tcp_session_handle::send(message_buffer &message)
{

}

void tcp_session_handle::close()
{

}

void tcp_session_handle::dispose()
{
	session_id_ = kInvalidSessionID;
}

bool tcp_session_handle::is_closed() const
{
	return kInvalidSessionID == session_id_;
}

void tcp_session_handle::init(session_id sid, thread_id tid, io_service_thread_manager* manager)
{
	session_id_ = sid;
	session_thread_id_ = tid;
	io_thread_manager_ = manager;
}