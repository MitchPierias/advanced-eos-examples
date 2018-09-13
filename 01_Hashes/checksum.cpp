#include <eosiolib/eosio.hpp>
#include <eosiolib/print.h>
#include <eosiolib/crypto.h>
#include <string.h>

using namespace eosio;
using std::string;

class crypto : eosio::contract {

	public:

		using contract::contract;

		void hash(const string& str) {
			// Hash the string to a checksum
			checksum256 sum{};
			sha256(const_cast<char*>(str.c_str()), str.size(), &sum);
			// Print output
			printhex(&sum, sizeof(sum));
		}
};

EOSIO_ABI(crypto, (hash));