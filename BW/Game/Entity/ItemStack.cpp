#include "ItemStack.h"

BW::ItemStack::ItemStack(BlockType id,short amount) {
	this->id = id;
	this->amount = amount;
}

BW::ItemStack::~ItemStack() {
}

short BW::ItemStack::getAmount() {
	return amount;
}

BW::BlockType BW::ItemStack::getId() {
	return id;
}
