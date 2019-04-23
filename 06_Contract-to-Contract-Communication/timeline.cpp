#include <eosio/eosio.hpp>
#include <eosio/singleton.hpp>
#include <string>
#include "user.cpp"

using namespace eosio;
using std::string;

class[[eosio::contract]] timeline : public eosio::contract
{
  public:
	using contract::contract;

	[[eosio::action]] void publish(const name username, const string &msg_str) {
		// Ensure only the user trying to publish the tweet can call this function.
		require_auth(username);

		// First we get the name of our user contract so we can ask it to validate the user.
		settings_table config(_self, _self.value);
		Config existing_config = config.get();

		// This prepares the call using the action wrapper we defined in the user contract.
		user::validate_action validate(existing_config.user_contract, {get_self(), "active"_n});

		// This does the call as an inline action, passing username as a parameter to the action
		validate.send(username);

		// Ok, they've passed validation. Initialize and store message.
		tweet_table tweets(_self, _self.value);
		tweets.emplace(username, [&](auto &obj) {
			obj.id = tweets.available_primary_key();
			obj.author = username;
			obj.msg = msg_str;
		});
	}

		[[eosio::action]] void
		remove(const uint64_t id)
	{
		// Validate tweet
		tweet_table tweets(_self, _self.value);
		auto tweet = tweets.find(id);

		// Validate ownership
		require_auth(tweet->author);

		// Remove entry
		tweets.erase(tweet);
	}

	[[eosio::action]] void setuser(name user_contract_name) {
		// This is an owner action.
		require_auth(_self);

		// Set it on in.
		Config new_config;
		new_config.user_contract = user_contract_name;

		settings_table config(_self, _self.value);
		config.set(new_config, _self);
	}

	struct [[eosio::table]] Tweet {
		uint64_t id;
		name author;
		string msg;
		bool flagged;

		auto primary_key() const { return id; }
	};

	typedef multi_index<"tweets"_n, Tweet> tweet_table;

	// This is so we can store the user contract address as a setting.
	struct [[eosio::table]] Config
	{
		name user_contract;
	};

	typedef eosio::singleton<"settings"_n, Config> settings_table;

	// This next typedef is only here because of this bug: https://github.com/EOSIO/eosio.cdt/issues/280
	// Once that's fixed this can be removed.
	typedef eosio::multi_index<"settings"_n, Config> settings_table_for_abi;
};
