# EOS Deferred Transactions
**Before we start...**
> Executing inline actions requires custom account permissions

Due to security reasons, the release version of EOS now requires the `eosio.code` permission on the contract invoking an inline action.

**Modifying Account Permissions**
We first need to modify the permissions of our `defer` account before we can schedule delayed transactions. We're going to overwrite our `active` key on our `defer` account with the `eosio.code` permission and use this later to invoke our inline action. Let's use the `cleos set account permission` command to achieve this.
```
cleos set account permission defer active
'{
  "threshold":1,
  "keys":[{
    "key":"YOUR_PUBLIC_KEY",
    "weight":1
  }],
  "accounts":[{
    "permission":{
      "actor":"defer",
      "permission":"eosio.code"
    },"weight":1
  }]
}'
owner -p defer@owner
```
## Deferred Transactions
> Technically there's no guarantee a deferred transaction will ever execute.

Deferred transactions are actions which execute after the invoking transaction has completed executing. This means the invoking transaction is not notified and does not rollback if the deferred transaction asserts.

**Creating an instance**
The transaction class is part of the eosiolib and needs to first be included with `#include <eosiolib/transaction.hpp>` in the head of your file. Now we can initialize a transaction instance and call it *"tx"*.
```
eosio::transaction tx;
```
**Adding actions**
The transaction's `actions` vector will hold a list of `action` objects which will be invoked after the delay elapses. Let's add our spam action to our *tx* object. We will construct a tuple with all our variables, and increment our index counter for the next iteration.
```
tx.actions.emplace_back(
  permission_level{_self, N(active)},
  _self,
  N(spam),
  std::make_tuple(sender, _self, msg_str, interval, ++index, iterations)
);
```

**Setting Delay**
Now we have an action to execute, we can now set our delay. The `delay_sec` property controls how long to wait before the list of actions should execute. The value is in seconds and defaults to zero, which executes immediately after it's parent transaction completes. We will set this to our `uint64_t interval` property passed through the arguments.
```
tx.delay_sec = interval;
```

**Executing the transaction**
Now we're ready to publish the deferred transaction by sending it to the blockchain. Sending a deferred transaction requires both a `uint64_t sender_id` to reference the transaction, and an `account_name payer` which will provide the RAM to store our delayed transaction until it's executed.
```
tx.send(sender_id, payer);
```