#pragma once

#include <memory>
#include <functional>
#include <asio.hpp>

class tcp_session;
class tcp_session_handle;
class message_filter_interface;
class io_service_thread_manager;

class tcp_server final
{
public:
	typedef std::shared_ptr<tcp_session>				session_ptr;
	typedef std::shared_ptr<tcp_session_handle>			session_handler_ptr;
	typedef std::function<session_handler_ptr()>		session_handler_creator;
	typedef std::shared_ptr<message_filter_interface>	message_filter_ptr;
	typedef std::function<message_filter_ptr()>			message_filter_creator;

public:
	tcp_server(asio::ip::tcp::endpoint &endpoint,
			   io_service_thread_manager &io_thread_manager,
			   const session_handler_creator &handler_creator,
			   const message_filter_creator &filter_creator);

	asio::io_service& io_service();

private:
	void handle_accept(session_ptr session, asio::error_code error);

private:
	asio::ip::tcp::acceptor			acceptor_;
	io_service_thread_manager&		io_thread_manager_;
	session_handler_creator			session_handler_creator_;
	message_filter_creator			message_filter_creator_;
};