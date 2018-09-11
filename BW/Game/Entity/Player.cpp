#include "Player.h"

BW::Player::Player() {
	selected = &inventory[0];
}

BW::Player::~Player() {
}

void BW::Player::setItem(int slot, BlockType id, short amount) {
	if (slot < 0 || slot >= Player::INVENTORY_SIZE)
		throw "TODO add excction";

	inventory[slot] = ItemStack(id, amount);
}

BW::ItemStack& BW::Player::getItem(int slot) {
	if (slot < 0 || slot >= Player::INVENTORY_SIZE)
		throw "TODO add excction";

	return inventory[slot];
}

BW::ItemStack& BW::Player::getSelectedItem() {
	return *selected;
}

void BW::Player::updatePosition(Camera& camera) {
	location = camera.getPosition();
	front = camera.getFront();
}

glm::vec3 BW::Player::getPosition() {
	return location;
}

glm::vec3 BW::Player::getFront() {
	return front;
}
