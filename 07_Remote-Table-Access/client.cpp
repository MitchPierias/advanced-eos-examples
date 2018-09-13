#include <eosiolib/eosio.hpp>
#include <eosiolib/print.h>
#include <string>

//#include "../server.cpp"

using namespace eosio;
using std::string;

class client : eosio::contract {
	
	public:

		using contract::contract;
		// @abi action
		void read(const account_name scope, const uint64_t uuid) {
			
			database_index database(N(server), scope);

			for (auto& row : database) {
				eosio::print("Msg: ", row.msg.c_str());
			}
		}

	private:
		// @abi table database i64
		struct Database {
			uint64_t	uuid;
			string		msg;

			auto primary_key() const { return uuid; }
			EOSLIB_SERIALIZE(Database, (uuid)(msg));
		};

		typedef multi_index<N(database), Database> database_index;
};

EOSIO_ABI(client, (read));