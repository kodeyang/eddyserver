#include <vector>

#include <cstdint>

class message_buffer final
{
public:
	message_buffer();
	~message_buffer();

private:
	size_t read(void *data, size_t size);

	size_t write(void *data, size_t size);

private:
	std::vector <uint8_t> buffer_;
};