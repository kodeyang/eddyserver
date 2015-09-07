#pragma once

#include <vector>
#include <cassert>
#include <cstdint>
#include "config.h"

template <typename _Alloc = std::allocator<uint8_t> >
class message_buffer final
{
public:
	typedef size_t size_type;
	typedef uint8_t value_type;

public:
	message_buffer()
		: read_pos_(0)
		, write_pos_(0)
		, buffer_(kBufferOriginalSize)
	{

	}

	explicit message_buffer(size_type size)
		: read_pos_(0)
		, write_pos_(0)
		, buffer_(size)
	{

	}

	~message_buffer() = default;

	message_buffer(message_buffer &&rhs)
	{
		read_pos_ = rhs.read_pos_;
		write_pos_ = rhs.write_pos_;
		buffer_ = std::move(rhs.buffer_);
		rhs.read_pos_ = 0;
		rhs.write_pos_ = 0;
	}

	message_buffer& operator= (message_buffer &&rhs)
	{
		if (&rhs != this)
		{
			read_pos_ = rhs.read_pos_;
			write_pos_ = rhs.write_pos_;
			buffer_ = std::move(rhs.buffer_);
			rhs.read_pos_ = 0;
			rhs.write_pos_ = 0;
		}	
		return *this;
	}

public:
	void reset()
	{
		write_pos_ = read_pos_ = 0;
	}

	void clear()
	{
		reset();
		buffer_.clear();
	}

	size_type content_size() const
	{
		return write_pos_ - read_pos_;
	}

	bool readable(size_type size) const
	{
		return content_size() >= size;
	}

	size_type read(void *user_data, size_type size)
	{
		assert(size > 0 && user_data);

		if (!readable(size))
		{
			return 0;
		}
		else
		{
			memcpy(user_data, buffer_.data() + read_pos_, size);
			read_pos_ += size;
			return size;
		}
	}

	size_type write(void *user_data, size_type size)
	{
		assert(user_data && size > 0);

		if (buffer_.size() - write_pos_ >= size)
		{
			memcpy(buffer_.data() + write_pos_, user_data, size);
			write_pos_ += size;
		}
		else if (read_pos_ >= size)
		{
			memcpy(buffer_.data() + (read_pos_ - size), user_data, size);
			read_pos_ -= size;
		}
		else if (buffer_.size() - content_size() >= size)
		{
			memmove(buffer_.data(), buffer_.data() + read_pos_, content_size());
			write_pos_ -= read_pos_;
			read_pos_ = 0;
			memcpy(buffer_.data() + write_pos_, user_data, size);
			write_pos_ += size;
		}
		else
		{
			buffer_.resize(buffer_.empty() ? size : buffer_.size() * 2);
			write(user_data, size);
		}
		return size;
	}

private:
	message_buffer(const message_buffer &that) = delete;
	message_buffer& operator= (const message_buffer &that) = delete;

private:
	size_type						read_pos_;
	size_type						write_pos_;
	std::vector<value_type, _Alloc>	buffer_;
};