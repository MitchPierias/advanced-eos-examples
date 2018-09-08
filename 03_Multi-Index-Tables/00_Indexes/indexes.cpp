#include "indexes.hpp"

/**
 * @brief Creates and stores a new inventory item
 * @param account <eosio::account_name> Profile account name
 * @param name <std::string> Item name
 * @param attack <uint64_t> Attact strength value
 * @author Mitch Pierias <github.com/MitchPierias>
 */
void indexes::create(const account_name account, const string name, const uint64_t attack) {
    // Create and set item
	item_table items(_self, _self);
	items.emplace(account, [&](auto& item) {
		item.id = account;
		item.name = name;
		item.attack = attack;
		item.owner = account;
	});
}

/**
 * @brief Prints Items for Account
 * @param account <eosio::account_name> Player's account name
 * @author Mitch Pierias <github.com/MitchPierias>
 */
void indexes::get(const account_name account) {
	// Fetch items and display
	item_table items(_self, _self);
	auto playerItems = items.get_index<N(byowner)>();
	auto iter = playerItems.lower_bound(account);
	while (iter != playerItems.end()) {
		print("Item ", iter->name);
		iter++;
	}
}