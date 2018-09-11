#include "Exceptions.h"

#include <string>

BW::InvalidBlockIndex::InvalidBlockIndex(const short x, const short y, const short z) 
	: logic_error("Invalid block index, x:" 
		+ std::to_string(x) + " y:" + std::to_string(y) + " z:" + std::to_string(z))
{
}