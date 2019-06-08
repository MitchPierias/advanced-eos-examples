#include <eosio/eosio.hpp>
#include <string>

using namespace eosio;
using namespace std;

class[[eosio::contract]] indexes : public contract
{

  public:
	using contract::contract;

	[[eosio::action]] void signup(const eosio::name account);
	[[eosio::action]] void additem(const eosio::name account, const string itemName);
	[[eosio::action]] void get(const eosio::name account);

  private:
	struct [[eosio::table]] Profile
	{
		eosio::name account;
		uint64_t primary_key() const { return account.value; };
	};

	struct [[eosio::table]] Item
	{
		uint64_t id;
		string name;
		eosio::name owner;
		uint64_t primary_key() const { return id; };
		uint64_t get_owner() const { return owner.value; };
	};

	typedef multi_index<"players"_n, Profile> profile_table;
	typedef multi_index<"items"_n, Item, indexed_by<"byowner"_n, const_mem_fun<Item, uint64_t, &Item::get_owner>>> item_table;
};
