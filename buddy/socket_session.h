#pragma once

#include <memory>
#include <cstdint>

class message_filter;
class io_service_thread;

typedef uint32_t session_id;


template <typename SocketType>
class socket_session final : public std::enable_shared_from_this < socket_session >
{
	typedef SocketType sock_type;

public:
	socket_session(io_service_thread &thread, );
	~socket_session();

private:
	session_id			id_;
	sock_type			socket_;
	io_service_thread	thread_;
};