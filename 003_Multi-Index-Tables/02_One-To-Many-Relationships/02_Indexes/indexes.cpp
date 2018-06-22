#include "indexes.hpp"

/**
 * @brief Register Profile
 * @param account <eosio::name> Player account name
 * @author Mitch Pierias <github.com/MitchPierias>
 */
void indexes::signup(const name account) {
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
 * @brief Assign Item
 * @param account <eosio::name> Player's account name
 * @param itemName <std::string> Item's name
 * @author Mitch Pierias <github.com/MitchPierias>
 */
void indexes::add(const name account, string itemName) {
	// Create and setup a new dog
	item_table items(_self, _self);
	auto item = items.emplace(account, [&](auto& item) {
		item.id = items.available_primary_key();
		item.name = itemName;
		item.owner = account;
	});
}

/**
 * @brief List Items
 * @param account <eosio::name> Player's account name
 * @author Mitch Pierias <github.com/MitchPierias>
 */
void indexes::get(const name account) {
	// Fetch items and display
	item_table items(_self, _self);
	auto playerItems = items.get_index<N(byowner)>();
	auto iter = playerItems.lower_bound(account);
	while (iter != playerItems.end()) {
		print("Item ", iter->name);
		iter++;
	}
}