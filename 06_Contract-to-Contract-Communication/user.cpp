#include <eosio/eosio.hpp>
#include <string>

using namespace eosio;
using std::string;

class[[eosio::contract]] user : public eosio::contract
{
  public:
	using contract::contract;

	[[eosio::action]] void create(const name username) {
		// Check user uniqueness
		profile_table profiles(_self, _self.value);
		auto result = profiles.find(username.value);

		eosio::check(result == profiles.end(), "User already registered");

		// Store new user profile
		profiles.emplace(_self, [&](auto &profile) {
			profile.user_name = username;
		});
	}

	[[eosio::action]] void validate(const name username) {
		// Fetch our user
		profile_table profiles(_self, _self.value);
		auto results = profiles.find(username.value);
		eosio::check(!results->flagged, "User is flagged");
		eosio::check(results->approved, "User has not been approved");
	}

	// This is an action wrapper, which makes it easy for other contracts to
	// find this action and call it externally. You'll see us referencing
	// validate_action from timeline.cpp in order to call this.
	using validate_action = action_wrapper<"validate"_n, &user::validate>;

	[[eosio::action]] void approve(const name username, bool isApproved) {
		// This is an administrative action that only we can take.
		require_auth(_self);

		// Fetch our user and set them to the new approved status.
		profile_table profiles(_self, _self.value);
		auto results = profiles.find(username.value);
		profiles.modify(results, _self, [&](auto &profile) {
			profile.approved = isApproved;
		});
	}

	[[eosio::action]] void flag(const name username, bool isFlagged) {
		// This is an administrative action that only we can take.
		require_auth(_self);

		// Fetch our user and set them to the new flagged status.
		profile_table profiles(_self, _self.value);
		auto results = profiles.find(username.value);
		profiles.modify(results, _self, [&](auto &profile) {
			profile.flagged = isFlagged;
		});
	}

	struct [[eosio::table]] Profile {
		name user_name;
		bool approved = false;
		bool flagged = false;

		auto primary_key() const { return user_name.value; }
	};

	typedef multi_index<"profiles"_n, Profile> profile_table;
};
