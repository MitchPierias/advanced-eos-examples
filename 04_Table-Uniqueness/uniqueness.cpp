#include "uniqueness.hpp"

/**
 * @brief Creates and stores a new inventory item
 * @param owner <eosio::name> Profile account name
 * @param name <std::string> Item name
 * @param attack <uint64_t> Attact strength value
 * @author Mitch Pierias <github.com/MitchPierias>
 * @author Kevin Brown <github.com/thekevinbrown>
 */
void uniqueness::create(const name owner, const string name, const uint64_t attack)
{
	// Instantiate items_table
	items_table items(_self, _self.value);

	// Create and set item
	items.emplace(owner, [&](auto &item) {
		item.id = items.available_primary_key();
		item.name = name;
		item.attack = attack;
		item.owner = owner;
	});
}