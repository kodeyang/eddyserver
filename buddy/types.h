#pragma once

#include <thread>
#include <vector>
#include <cstdint>

typedef std::thread::id				thread_id;
typedef uint32_t					session_id;
typedef std::vector<uint8_t>		message_buffer;
typedef std::vector<message_buffer>	message_vector;