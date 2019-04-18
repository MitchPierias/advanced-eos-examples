#include <eosio/eosio.hpp>
#include <string>

using namespace eosio;
using namespace std;

class[[eosio::contract("vectors")]] vectors : public contract
{

  public:
	using contract::contract;

	[[eosio::action]] void signup(const name account);
	[[eosio::action]] void add(const name account, string name);

  private:
	struct [[eosio::table]] Profile
	{
		name account;
		vector<uint64_t> items;

		uint64_t primary_key() const { return account.value; };
	};

	struct [[eosio::table]] Item
	{
		uint64_t id;
		string name;

		uint64_t primary_key() const { return id; };
	};

	typedef multi_index<"players"_n, Profile> profile_table;
	typedef multi_index<"items"_n, Item> item_table;
};
