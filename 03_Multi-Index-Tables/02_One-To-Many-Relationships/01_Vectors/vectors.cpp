#include "vectors.hpp"

/**
 * @brief Register Profile
 * @param account <eosio::name> Player account name
 * @author Mitch Pierias <github.com/MitchPierias>
 */
void vectors::signup(const name account) {
	// Validate account isn't stored
	profile_table players(_self, _self);
	auto iter = players.find(account);
	eosio_assert(iter == players.end(), "Account already registered");
	// Create and store account
	players.emplace(account, [&](auto& user) {
		user.account = account;
	});
}

/**
 * @brief Assign item
 * @param account <eosio::name> Player's profile account name
 * @param name <std::string> Item's name
 * @author Mitch Pierias <github.com/MitchPierias>
 */
void vectors::add(const name account, string name) {
	// Find and validate our dog owner
	profile_table players(_self, _self);
	auto currentPlayer = players.find(account);
	eosio_assert(currentPlayer != players.end(), "Account not registered");
	// Create and setup a new dog
	item_table items(_self, _self);
	auto item = items.emplace(account, [&](auto& item) {
		item.id = items.available_primary_key();
		item.name = name;
	});
	// Add the item id reference to the player's items
	players.modify(currentPlayer, 0, [&](auto& player) {
		player.items.push_back(item->id);
	});
}