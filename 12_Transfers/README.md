> You only have permission to trasnfer your own funds (contract funds) to another account.

> To receive payments, you must respond to the inline actions called by eosio.token when a transfer is made

The eosio.token contract calls three inline actions whenever a valid transfer is executed.
- The first notifies the `eosio.token` contract itself that a successful transfer was made.
- The additional two actions notify the sender a receiver accounts of the transfer, if these accounts are contract themselves, then they can handle the notification with a modified `apply` function by extending the `EOSIO_ABI`.