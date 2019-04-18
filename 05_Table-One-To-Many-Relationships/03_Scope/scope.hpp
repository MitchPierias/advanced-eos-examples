#include <eosio/eosio.hpp>
#include <string>

using namespace eosio;
using namespace std;

class[[eosio::contract]] scope : public contract
{
  public:
	using contract::contract;

	[[eosio::action]] void signup(const name account);
	[[eosio::action]] void add(const name account, string itemName);
	[[eosio::action]] void get(const name account);

  private:
	struct [[eosio::table]] Profile
	{
		name account;
		auto primary_key() const { return account.value; };
	};

	struct [[eosio::table]] Item
	{
		uint64_t id;
		string name;
		auto primary_key() const { return id; };
	};

	typedef multi_index<"players"_n, Profile> profile_table;
	typedef multi_index<"items"_n, Item> item_table;
};
