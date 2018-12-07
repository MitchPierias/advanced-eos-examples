#include <eosiolib/eosio.hpp>
#include <eosiolib/print.h>
#include <string>

using namespace eosio;
using std::string;

class timeline : public eosio::contract {

	public:

		using contract::contract;
		// Constructor
		timeline(action_name self) : contract(self), tweets(_self, _self) {}
		// @abi action
		void post(const account_name username, uint64_t index, const string& msg_str) {
			// Create and store tweet
			tweets.emplace(username, [&](auto& tweet) {
				tweet.id = index;
				tweet.author = username;
				tweet.msg = msg_str;
			});
		}
		// @abi action
		void get(uint64_t index) {
			// Get tweet at id
			auto tweet = tweets.get(index);
			print(tweet.msg);
		}
		// @abi action
		void find(const account_name account) {
			// Fetch tweets and display
			auto author_index = tweets.get_index<N(byowner)>();
			auto iter = author_index.lower_bound(account);
			while (iter != author_index.end()) {
				print(iter->msg);
				iter++;
			}
		}

	private:
		// @abi table tweets i64
		struct Tweet {
			uint64_t		id;
			account_name 	author;
			string			msg;
			bool			flagged = false;

			auto primary_key() const { return id; };
			uint64_t get_author() const { return author; };
			EOSLIB_SERIALIZE(Tweet, (id)(author)(msg)(flagged));
		};

		typedef multi_index<N(tweets), Tweet, indexed_by<N(byauthor), const_mem_fun<Tweet, uint64_t, &Tweet::get_author>>> tweet_table;
		tweet_table tweets;
};

EOSIO_ABI(timeline, (post)(get)(find));