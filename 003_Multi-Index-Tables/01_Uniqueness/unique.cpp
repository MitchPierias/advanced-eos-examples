#include "unique.hpp"

/**
 * @brief Creates and stores a new inventory item
 * @param account <eosio::account_name> Profile account name
 * @param name <std::string> Item name
 * @param attack <uint64_t> Attact strength value
 * @author Mitch Pierias <github.com/MitchPierias>
 */
void uniqueness::create(const account_name account, const string name, const uint64_t attack) {
    // Instantiate items_table
	items_table items(_self, _self);
    // Create and set item
	items.emplace(account, [&](auto& item) {
		item.id = items.available_primary_key();
		item.name = name;
		item.attack = attack;
		item.owner = account;
	});
}