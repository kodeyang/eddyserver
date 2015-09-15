#pragma once

#include <numeric>
#include "types.h"

static const size_t kMessageAnySize = size_t(-1);

class message_filter_interface
{
public:
	message_filter_interface() = default;
	virtual ~message_filter_interface() = default;

public:
	virtual size_t on_read(message_vector &messages_received, message_buffer &buffer) = 0;
	virtual size_t on_write(message_vector &messages_to_be_sent, message_buffer &buffer) = 0;
	virtual size_t bytes_wanna_read() = 0;
	virtual size_t bytes_wanna_write(message_vector &messages_to_be_sent) = 0;
};


class message_filter final : public message_filter_interface
{
public:
	typedef uint16_t message_header;
	static const size_t kHeaderSize = sizeof(message_header);

public:
	message_filter();

	~message_filter() = default;

public:
	size_t on_read(message_vector &messages_received, message_buffer &buffer) override;

	size_t on_write(message_vector &messages_to_be_sent, message_buffer &buffer) override;

	size_t bytes_wanna_read() override;

	size_t bytes_wanna_write(message_vector &messages_to_be_sent) override;

private:
	bool			header_read_;
	message_header	header_;
};