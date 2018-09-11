#pragma once
#include <stdexcept>

namespace BW {
	class InvalidBlockIndex : public std::logic_error {
		public:
		InvalidBlockIndex(const short x, const short y, const short z);
	};
}


