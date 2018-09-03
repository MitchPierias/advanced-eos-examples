#include "indexes.hpp"

/**
 * @brief Register Profile
 * @param account <eosio::account_name> Player account name
 * @author Mitch Pierias <github.com/MitchPierias>
 */
void indexes::signup(const account_name account) {
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
 * @brief Create Item
 * @param account <eosio::account_name> Player's account name
 * @param itemName <std::string> Item's name
 * @author Mitch Pierias <github.com/MitchPierias>
 */
void indexes::create(const account_name account, const string itemName, const uint64_t attack) {
	// Create and setup a new dog
	item_table items(_self, _self);
	auto item = items.emplace(account, [&](auto& item) {
		item.id = items.available_primary_key();
		item.name = itemName;
		item.attack = attack;
		item.owner = account;
	});
}

/**
 * @brief List Itemsaccount_name
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