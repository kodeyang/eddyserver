#pragma once

#include <memory>
#include "types.h"
#include <asio/ip/tcp.hpp>

class message_filter;
class io_service_thread;
class message_filter_interface;

static const uint32_t kInvalidSessionID = 0;

class tcp_session final : public std::enable_shared_from_this < tcp_session >
{
public:
	typedef asio::ip::tcp::socket						socket_type;
	typedef std::shared_ptr<message_filter_interface>	message_filter_ptr;

public:
	tcp_session(io_service_thread &thread, message_filter_ptr filter);
	~tcp_session();

public:
	socket_type& socket()
	{
		return socket_;
	}

private:
	void init(session_id id);

private:
	session_id				id_;
	socket_type				socket_;
	io_service_thread&		thread_;
	message_filter_ptr		filter_;
};