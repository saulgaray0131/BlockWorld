#pragma once
#include "../Block/Block.h"

namespace BW {
	class ItemStack {
		public:
		ItemStack() = default;
		ItemStack(BlockType id, short amount = 1);
		~ItemStack();

		short getAmount();
		BlockType getId();

		private:
		short amount;
		BlockType id;
	};

}
