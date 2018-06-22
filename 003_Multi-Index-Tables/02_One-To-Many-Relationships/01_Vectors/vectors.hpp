#include <eosiolib/eosio.hpp>
#include <string>

using namespace eosio;
using namespace std;

class vectors : contract {

	public:

		explicit vectors(action_name self) : contract(self) {}
		// @abi action
		void signup(const name account);
		// @abi action
		void add(const name account, string name);

	private:
		// @abi table players i64
		struct Profile {
		    name        		account;
		    vector<uint64_t>	items;
		    auto primary_key() const { return account; };
		    EOSLIB_SERIALIZE(Profile, (account)(items));
		};
		// @abi table items i64
		struct Item {
		    uint64_t    		id;
		    string				name;
		    auto primary_key() const { return id; };
		    EOSLIB_SERIALIZE(Item, (id)(name));
		};

		typedef multi_index<N(players), Profile> profile_table;
		typedef multi_index<N(items), Item> item_table;
};

EOSIO_ABI(vectors, (signup)(add));
