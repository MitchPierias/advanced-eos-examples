#include <eosiolib/eosio.hpp>
#include <string>

using namespace eosio;
using namespace std;


class example_table_vectors : contract {

	public:

		explicit example_table_vectors(action_name self) : contract(self) {}
		// @abi action
		void create(const name account, string dogName);

	private:
		// @abi table owners i64
		struct Owner {
		    name        		account;
		    vector<uint64_t>	dogs;

		    auto primary_key() { return account; };

		    EOSLIB_SERIALIZE(Owner, (account)(dogs));
		};
		// @abi table dogs i64
		struct Dog {
		    uint64_t    		uid;
		    string				name;

		    auto primary_key() { return uid; };

		    EOSLIB_SERIALIZE(Dog, (uid)(name));
		};

		typedef multi_index<N(owners), Owner> owner_table;
		typedef multi_index<N(dogs), Dog> dog_table;
};

EOSIO_ABI(example_table_vectors, (create));
