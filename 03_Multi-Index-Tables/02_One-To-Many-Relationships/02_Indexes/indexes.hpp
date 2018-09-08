#include <eosiolib/eosio.hpp>
#include <eosiolib/print.h>
#include <string>

using namespace eosio;
using namespace std;

class indexes : contract {

	public:

		explicit indexes(action_name self) : contract(self) {}
		// @abi action
		void signup(const account_name account);
		// @abi action
		void add(const account_name account, const string itemName, const uint64_t attack);
		// @abi action
		void get(const account_name account);

	private:
		// @abi table players i64
		struct Profile {
		    account_name	account;
		    auto primary_key() const { return account; };
		    EOSLIB_SERIALIZE(Profile, (account));
		};
		// @abi table items i64
		struct Item {
		    uint64_t    	id;
		    string			name;
		    uint64_t 		owner;
		    auto primary_key() const { return id; };
		    uint64_t get_owner() const { return owner; };
		    EOSLIB_SERIALIZE(Item, (id)(name)(owner));
		};

		typedef multi_index<N(players), Profile> profile_table;
		typedef multi_index<N(items), Item, indexed_by<N(byowner), const_mem_fun<Item, uint64_t, &Item::get_owner>>> item_table;
};

EOSIO_ABI(indexes, (signup)(add)(get));