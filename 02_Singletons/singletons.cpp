#include <eosio/eosio.hpp>
#include <eosio/singleton.hpp>
#include <string>

using namespace eosio;
using std::string;

class[[eosio::contract("singletons")]] singletons : public contract
{

  public:
	using contract::contract;

	singletons(name receiver, name code, datastream<const char *> ds) : contract(receiver, code, ds), config(_self, _self.value) {

	} [[eosio::action]] void init() {
		ConfigStruct default_config;
		// This way, multi-initialisation simply does nothing as the singleton already exists.
		config.get_or_create(_self, default_config);
	}

	[[eosio::action]] void setclosed(bool is_closed) {
		auto state = config.get();
		state.closed = is_closed;
		config.set(state, _self);
		print(state.closed);
	};

	[[eosio::action]] void getclosed() {
		auto state = config.get();
		print(state.closed);
	};

	[[eosio::action]] void setchars(uint32_t char_count) {
		auto state = config.get();
		state.char_count = char_count;
		config.set(state, _self);
	};

	[[eosio::action]] void getchars() {
		auto state = config.get();
		print(state.char_count);
	};

  private:

	struct [[eosio::table]] ConfigStruct {
		bool closed = false;
		uint32_t char_count = 144;
	};

	typedef eosio::singleton<"settings"_n, ConfigStruct> settings_table;

	// This next typedef is only here because of this bug: https://github.com/EOSIO/eosio.cdt/issues/280
	// Once that's fixed this can be removed.
	typedef eosio::multi_index<"settings"_n, ConfigStruct> settings_table_for_abi;

	settings_table config;
};