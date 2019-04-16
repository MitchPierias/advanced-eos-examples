#include "indexes.hpp"

/**
 * @brief Register Profile
 * @param account <eosio::account_name> Player account name
 * @author Mitch Pierias <github.com/MitchPierias>
 * @author Kevin Brown <github.com/thekevinbrown>
 */
void indexes::signup(const eosio::name account)
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
 * @brief Create Item
 * @param account <eosio::account_name> Player's account name
 * @param itemName <std::string> Item's name
 * @author Mitch Pierias <github.com/MitchPierias>
 * @author Kevin Brown <github.com/thekevinbrown>
 */
void indexes::additem(const eosio::name account, const string itemName)
{
	// Create and setup a new item
	item_table items(_self, _self.value);
	auto item = items.emplace(account, [&](auto &item) {
		item.id = items.available_primary_key();
		item.name = itemName;
		item.owner = account;
	});
}

/**
 * @brief List Items by account 
 * @param account <eosio::name> Player's account name
 * @author Mitch Pierias <github.com/MitchPierias>
 * @author Kevin Brown <github.com/thekevinbrown>
 */
void indexes::get(const eosio::name account)
{
	// Fetch items and display
	item_table items(_self, _self.value);
	auto playerItems = items.get_index<"byowner"_n>();
	auto iter = playerItems.lower_bound(account.value);

	while (iter != playerItems.end())
	{
		print("Item ", iter->name);
		iter++;
	}
}