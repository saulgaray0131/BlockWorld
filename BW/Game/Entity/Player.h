#pragma once
#include "ItemStack.h"
#include "../../Camera.h"

namespace BW {
	class Player {
		public:
		Player();
		~Player();

		static constexpr int INVENTORY_SIZE = 16;

		Player(const Player&) = delete;
		Player& operator=(const Player&) = delete;

		void setItem(int slot, BlockType id, short amount);
		ItemStack& getItem(int slot);
		ItemStack& getSelectedItem();

		void updatePosition(Camera& camera);
		glm::vec3 getPosition();
		glm::vec3 getFront();

		private:
		glm::vec3 location;
		glm::vec3 front;

		ItemStack* selected;
		std::array<ItemStack, INVENTORY_SIZE> inventory;
	};
}

