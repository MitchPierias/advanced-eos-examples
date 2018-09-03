#include "unique.hpp"

/**
 * @brief Generate Unique Hash
 * @param account <eosio::account_name> Profile account name
 * @author Mitch Pierias <github.com/MitchPierias>
 */
void unique::create(const account_name account, const string name, const uint64_t attack) {

	items_table items(_self, _self);

	items.emplace(account, account, [&](auto& item) {
		item.id = items.available_primary_key();
		item.name = name;
		item.attack = attack;
		item.owner = account;
	});
}