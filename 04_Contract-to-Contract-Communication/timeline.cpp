#include <eosiolib/eosio.hpp>
#include <string>

using namespace eosio;
using std::string;

class timeline : eosio::contract {
	
	public:

		using contract::contract;
		// @abi action
		void publish(const account_name username, const string& msg_str) {
			// Limit access to user contract
			require_auth(username);
			// Validate user
			eosio::action(permission_level{_self, N(active)}, N(user), N(validate), std::make_tuple(username)).send();
			// Initialize and store message
			tweet_table tweets(_self, _self);
			tweets.emplace(_self, [&](auto& obj) {
				obj.id = tweets.available_primary_key();
				obj.author = username;
				obj.msg = msg_str;
			});
		}
		// @abi action
		void remove(const uint64_t id) {
			// Validate tweet
			tweet_table tweets(_self, _self);
			auto tweet = tweets.find(id);
			// Validate ownership
			require_auth(tweet->author);
			// Remove entry
			tweets.erase(tweet);
		}
		// @abi table tweets i64
		struct Tweet {
			uint64_t		id;
			account_name 	author;
			string			msg;
			bool			flagged;

			auto primary_key() const { return id; }
			EOSLIB_SERIALIZE(Tweet, (id)(author)(msg)(flagged));
		};

		typedef multi_index<N(tweets), Tweet> tweet_table;
};

EOSIO_ABI(timeline, (publish)(remove));