#include "message_filter.h"
#include <asio.hpp>


message_filter::message_filter()
	: header_read_(false)
{

}

size_t message_filter::on_read(message_vector &messages_received, message_buffer &buffer)
{
	if (!header_read_)
	{
		header_ = ntohs(*reinterpret_cast<message_header*>(buffer.data()));
		header_read_ = true;
		return header_;
	}
	else
	{
		return 0;
	}
}

size_t message_filter::on_write(message_vector &messages_to_be_sent, message_buffer &buffer)
{
	return 0;
}

size_t message_filter::bytes_wanna_read()
{
	return header_read_ ? kHeaderSize : header_;
}

size_t message_filter::bytes_wanna_write(message_vector &messages_to_be_sent)
{
	if (messages_to_be_sent.empty())
	{
		return 0;
	}
	return std::accumulate(messages_to_be_sent.begin(), messages_to_be_sent.end(), 0, [=](size_t sum, const message_buffer &buffer)
	{
		return sum + kHeaderSize + buffer.size();
	});
}