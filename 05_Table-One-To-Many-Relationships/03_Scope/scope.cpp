#include "scope.hpp"

/**
 * @brief Register Profile
 * @param account <eosio::name> Player account name
 * @author Mitch Pierias <github.com/MitchPierias>
 * @author Kevin Brown <github.com/thekevinbrown>
 */
void scope::signup(const name account)
{
	// Validate account isn't stored
	profile_table players(_self, _self.value);
	auto iter = players.find(account.value);

	eosio::check(iter == players.end(), "Account already registered");

	// Create and store account
	players.emplace(account, [&](auto &user) {
		user.account = account;
	});
}

/**
 * @brief Assign Item
 * @param account <eosio::name> Player's account name
 * @param itemName <std::string> Item's name
 * @author Mitch Pierias <github.com/MitchPierias>
 * @author Kevin Brown <github.com/thekevinbrown>
 */
void scope::add(const name account, string itemName)
{
	// Create and setup a new dog
	item_table items(_self, account.value);

	auto item = items.emplace(account, [&](auto &item) {
		item.id = items.available_primary_key();
		item.name = itemName;
	});
}

/**
 * @brief List Items
 * @param account <eosio::name> Player's account name
 * @author Mitch Pierias <github.com/MitchPierias>
 * @author Kevin Brown <github.com/thekevinbrown>
 */
void scope::get(const name account)
{
	// Fetch the items within the account scope
	item_table items(_self, account.value);

	// Iterate all rows and print
	for (auto &item : items)
	{
		print("Item ", item.name);
	}
}
