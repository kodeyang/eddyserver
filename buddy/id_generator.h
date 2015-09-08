#pragma once

#include <vector>
#include <cstdint>
#include <cassert>

class id_generator
{
public:
	id_generator(uint32_t threshold = 4096)
		: next_(0)
		, threshold_(threshold)
	{

	}

	bool get(uint32_t &id)
	{
		if (pool_.size() > threshold_)
		{
			id = pool_.back();
			pool_.pop_back();
			return true;
		}
		else if (next_ <= threshold_)
		{
			id = ++next_;
			return true;
		}
		return false;
	}

	void put(uint32_t id)
	{
		pool_.push_back(id);
	}

private:
	uint32_t				next_;
	const size_t			threshold_;
	std::vector<uint32_t>	pool_;
};