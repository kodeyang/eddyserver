#pragma once

#include <array>
#include <vector>
#include <cstdint>
#include <thread>

static const uint32_t kDefaultBufferSize = 1024;

typedef std::thread::id								thread_id;
typedef uint32_t									session_id;
typedef std::vector<message_buffer>					message_vector;