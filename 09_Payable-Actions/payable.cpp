#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>

using namespace eosio;

class[[eosio::contract]] payable : public eosio::contract {

  public:

    using contract::contract;

    [[eosio::on_notify("eosio.token::transfer")]] void received(const eosio::name caller, eosio::name receiver, eosio::asset value, std::string memo) {
      // Validate transaction participants and escape
      if (receiver != get_self() || caller == get_self()) return;
      // Define token symbol
      eosio::symbol token_symbol("SYM", 0);
      // Validate contract state and arguments
      eosio::check(value.amount > 0, "Insufficient value");
      eosio::check(value.symbol == token_symbol, "Illegal asset symbol");
      // Find the members wallet
      wallet_table balances(get_self(), get_self().value);
      auto wallet = balances.find(caller.value);
      // Update the wallet balance
      if (wallet != balances.end()) {
        balances.modify(wallet, get_self(), [&](auto &row) {
          row.balance += value.amount;
        });
      } else {
        balances.emplace(get_self(), [&](auto &row) {
          row.account = caller;
          row.balance = value.amount;
        });
      }
    }

  private:

    struct [[eosio::table]] WalletStruct {
      name          account;
      uint64_t      balance = 0;

      auto primary_key() const { return account.value; }
    };

    typedef multi_index<"wallets"_n, WalletStruct> wallet_table;
};