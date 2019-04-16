#include <eosio/eosio.hpp>
#include <string>

using namespace eosio;
using namespace std;

class[[eosio::contract("uniqueness")]] uniqueness : public eosio::contract
{
public:
	using contract::contract;

	[[eosio::action]] void create(const name owner, const string name, const uint64_t attack);

private:
	// @abi table items i64
	struct [[eosio::table]] Item
	{
		uint64_t id;
		string name;
		uint64_t attack;
		eosio::name owner;

		auto primary_key() const { return id; };
	};

	typedef multi_index<"items"_n, Item> items_table;
};