#include "tcp_session.h"

#include <cassert>
#include "message_filter.h"
#include "io_service_thread.h"


tcp_session::tcp_session(io_service_thread &thread, message_filter_ptr filter)
	: thread_(thread)
	, filter_(filter)
	, id_(kInvalidSessionID)
	, socket_(thread.io_service())
{

}

tcp_session::~tcp_session()
{

}

void tcp_session::init(session_id id)
{
	assert(id != kInvalidSessionID);

	id_ = id;
	socket_.set_option(asio::ip::tcp::no_delay(true));
	thread_.session_queue().insert(shared_from_this());

	size_t size = filter_->bytes_wanna_read();
}