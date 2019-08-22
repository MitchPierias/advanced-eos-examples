#include <eosio/eosio.hpp>
#include <eosio/name.hpp>
#include <eosio/print.hpp>
#include <string>

using namespace eosio;
using std::string;

class[[eosio::contract("timeline")]] timeline : public eosio::contract {

public:
	using contract::contract;

	[[eosio::action]] void post(const name username, uint64_t id, const string &msg_str) {
		tweet_table tweets(_self, _self.value);
		// Create and store tweet
		tweets.emplace(username, [&](auto &tweet) {
			tweet.id = id;
			tweet.author = username;
			tweet.msg = msg_str;
		});
	}
	
	[[eosio::action]] void get(uint64_t id) {
		tweet_table tweets(_self, _self.value);
		// Get tweet at id
		auto tweet = tweets.get(id);
		print(tweet.msg);
	}

	[[eosio::action]] void inventory(const name account) {

		tweet_table tweets(_self, _self.value);
		// Fetch tweets and display
		auto author_index = tweets.get_index<"byauthor"_n>();
		auto iter = author_index.find(account.value);

		while (iter != author_index.end()) {
			print(iter->msg);
			iter++;
		}
	}

	private :

		struct [[eosio::table]] Tweet {
			uint64_t id;
			name author;
			string msg;
			bool flagged = false;

			auto primary_key() const { return id; };
			uint64_t get_author() const { return author.value; };
		};

	typedef multi_index<"tweets"_n, Tweet, indexed_by<"byauthor"_n, const_mem_fun<Tweet, uint64_t, &Tweet::get_author>>> tweet_table;
};
