#include "scope.hpp"

/**
 * @brief Register Profile
 * @param account <eosio::name> Player account name
 * @author Mitch Pierias <github.com/MitchPierias>
 */
void scope::signup(const name account) {
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
void scope::add(const name account, string itemName) {
	// Create and setup a new dog
	item_table items(_self, account);
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
void scope::get(const name account) {
	// Fetch the items within the account scope
	item_table items(_self, account);
	// Iterate all rows and print
	auto iter = playerItems.lower_bound();
	while (iter != playerItems.end()) {
		print("Item ", iter->name);
		iter++;
	}
}