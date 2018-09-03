#include <eosiolib/eosio.hpp>
#include <eosiolib/print.h>
#include <string>

using namespace eosio;
using namespace std;

class indexes : public eosio::contract {

	public:

		using contract::contract;
		// @abi action
		void create(const account_name account, const string name, const uint64_t attack);
		// @abi action
		void get(const account_name account);

	private:
		// @abi table items i64
		struct Item {
			auto     		  id;
			string            name;
			uint64_t          attack;
			account_name      owner;

			auto primary_key() const { return id; };
			uint64_t get_owner() const { return owner; };
			EOSLIB_SERIALIZE(Item, (id)(name)(attack)(owner));
		};

		typedef multi_index<N(items), Item, indexed_by<N(byowner), const_mem_fun<Item, uint64_t, &Item::get_owner>>> item_table;
};

EOSIO_ABI(indexes, (create)(get));