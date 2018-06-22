#include <eosiolib/eosio.hpp>
#include <eosiolib/crypto.h>
#include <string>

using namespace eosio;
using namespace std;

class crypto : contract {

	public:

		explicit crypto(action_name self) : contract(self) {}
		// @abi action
		void generate();

	private:
		

};

EOSIO_ABI(crypto);
