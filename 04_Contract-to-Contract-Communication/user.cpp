#include <eosiolib/eosio.hpp>
#include <string>

using namespace eosio;
using std::string;

class user : eosio::contract {
	
	public:

		using contract::contract;
		// @abi action
		void create(const account_name username) {
			// Check user uniqueness
			profile_table profiles(_self, _self);
			auto result = profiles.find(username);
			eosio_assert(result == profiles.end(), "User already registered");
			// Store new user profile
			profiles.emplace(_self, [&](auto& profile) {
				profile.uuid = username;
			});
		}
		// @abi action
		void validate(const account_name username) {
			// Fetch our user
			profile_table profiles(_self, _self);
			auto results = profiles.find(username);
			eosio_assert(results->active, "User inactive");
			eosio_assert(!results->flagged, "User is flagged");
			eosio_assert(results->approved, "User has not been approved");
		}
		// @abi action
		void activate(const account_name username, bool isActive) {
			// Fetch our user
			profile_table profiles(_self, _self);
			auto results = profiles.find(username);
			profiles.modify(results, 0, [&](auto& profile) {
				profile.active = isActive;
			});
		}
		// @abi table profiles i64
		struct Profile {
			uint64_t	uuid;
			bool		active = true;
			bool		approved = true;
			bool		flagged = false;

			auto primary_key() const { return uuid; }
			EOSLIB_SERIALIZE(Profile, (uuid)(active)(approved)(flagged));
		};

		typedef multi_index<N(profiles), Profile> profile_table;
};

EOSIO_ABI(user, (create)(validate)(activate));