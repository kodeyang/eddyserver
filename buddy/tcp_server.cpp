#include "tcp_server.h"

#include "tcp_session.h"
#include "message_filter.h"
#include "io_service_thread.h"
#include "tcp_session_handle.h"
#include "io_service_thread_manager.h"


tcp_server::tcp_server(asio::ip::tcp::endpoint &endpoint,
		   io_service_thread_manager &io_thread_manager,
		   const session_handler_creator &handler_creator,
		   const message_filter_creator &filter_creator)
		   : io_thread_manager_(io_thread_manager)
		   , session_handler_creator_(handler_creator)
		   , message_filter_creator_(filter_creator)
		   , acceptor_(io_thread_manager.main_thread().io_service(), endpoint)
{
	session_ptr session = std::make_shared<tcp_session>(io_thread_manager.thread(), message_filter_creator_());
	//acceptor_.async_accept(session->socket(), std::bind(&tcp_server::handle_accept, this, session, std::placeholders::_1));
}

asio::io_service& tcp_server::io_service()
{
	return io_thread_manager_.main_thread().io_service();
}

void tcp_server::handle_accept(session_ptr session, asio::error_code error)
{

}