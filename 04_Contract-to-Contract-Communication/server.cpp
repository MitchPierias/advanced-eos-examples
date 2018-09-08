#include <eosiolib/eosio.hpp>
#include <string>

using namespace eosio;
using std::string;

class server : eosio::contract {
	
	public:

		using contract::contract;
		// @abi action
		void publish(const account_name scope, const string& msg) {
			// Initialize and store message
			database_index database(_self, _self);
			database.emplace(_self, [&](auto& obj) {
				obj.uuid = database.available_primary_key();
				obj.msg = msg;
			});

			print("Published message: '", msg, "'");
		}
		// @abi action
		void remove(const account_name scope, uint64_t uuid) {
			// Initialize table and Validate entry exists
			database_index database(_self, scope);
			auto results = database.find(uuid);
			eosio_assert(results != database.end(), "Entry not found");
			// Remove entry
			database.erase(results);
		}
		// @abi table database i64
		struct Database {
			uint64_t	uuid;
			string		msg;

			auto primary_key() const { return uuid; }
			EOSLIB_SERIALIZE(Database, (uuid)(msg));
		};

		typedef multi_index<N(database), Database> database_index;
};

EOSIO_ABI(server, (publish)(remove));