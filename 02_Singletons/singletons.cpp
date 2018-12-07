#include <eosiolib/eosio.hpp>
#include <eosiolib/print.h>
#include <eosiolib/singleton.hpp>
#include <string>

using namespace eosio;
using std::string;

class singletons : eosio::contract {


	public:

		using contract::contract;

		singletons(action_name self) : contract(self), config(_self, _self) {}
		// @abi action
		void setclosed(bool isClosed) {
			auto state = config.get();
			state.closed = isClosed;
			config.set(state, _self);
			print(state.closed);
		}
		// @abi action
		void getclosed() {
			auto state = config.get();
			print(state.closed);
		}
		// @abi action
		void setchars(uint32_t char_count) {
			auto state = config.get();
			state.char_count = char_count;
			config.set(state, _self);
		}
		// @abi action
		void getchars() {
			auto state = config.get();
			print(state.char_count);
		}

	private:

		struct Config {
			bool		closed = false;
			uint32_t	char_count = 144;
		};

		typedef singleton<N(settings), Config> settings_table;

		settings_table config;
};

EOSIO_ABI(singletons, (setclosed)(getclosed)(setchars)(getchars));