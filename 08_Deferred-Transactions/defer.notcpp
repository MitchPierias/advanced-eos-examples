#include <eosiolib/eosio.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/print.hpp>
#include <string>

using namespace eosio;
using std::string;

class defer : eosio::contract {

	public:

		using contract::contract;
		// @abi action
		void spam(const account_name sender, const string& msg_str, uint64_t interval, uint64_t index, uint32_t iterations) {
			if (index < iterations) {
				// Iteration loop
				eosio::transaction tx;
				tx.actions.emplace_back(
					permission_level{_self, N(active)},
					_self,
					N(spam),
					std::make_tuple(sender, msg_str, interval, ++index, iterations)
				);
				tx.delay_sec = interval;
				tx.send(index, sender);
			} else {
				// Store the message
				save_message(sender, index, msg_str);
			}
		}

	private:
		// @abi table database i64
		struct Data {
			uint64_t 	id;
			string 		msg;

			auto primary_key() const { return id; }
			EOSLIB_SERIALIZE(Data, (id)(msg));
		};

		typedef multi_index<N(database), Data> data_index;

		void save_message(const account_name sender, const uint64_t index, const string& msg_str) {
			data_index database(_self, sender);
			// Fetch message
			auto iter = database.find(index);
			if (iter == database.end())
				// Store message
				database.emplace(_self, [&](auto& obj) {
					obj.id = index;
					obj.msg = msg_str;
				});
			else
				// Update message
				database.modify(iter, 0, [&](auto& obj) {
					obj.msg = msg_str;
				});
		}
};

EOSIO_ABI(defer, (spam));