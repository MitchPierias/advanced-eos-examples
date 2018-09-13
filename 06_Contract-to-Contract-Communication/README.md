**Before we start...**
> Executing inline actions requires custom account permissions

Due to security reasons, the release version of EOS now requires the `eosio.code` permission on the contract invoking an inline action.

**Modifying Account Permissions**
We first need to modify the permissions of our `timeline` account before we can invoke actions on our `user` contract. We're going to overwrite our `active` key on our caller account with the `eosio.code` permission and use this later to invoke our inline action. Let's use the `cleos set account permission` command to achieve this.
```
cleos set account permission timeline active
'{
  "threshold":1,
  "keys":[{
    "key":"YOUR_PUBLIC_KEY",
    "weight":1
  }],
  "accounts":[{
    "permission":{
      "actor":"timeline",
      "permission":"eosio.code"
    },"weight":1
  }]
}'
owner -p timeline@owner
```
# EOS Inter-contract Communication
Let's take a look at `eosio::action` to invoke actions between one contract and another. We will write a `user` contract to handle user registration, activation and validation, and a `timeline` contract to handle publishing and removing tweets. 

Our communication will happen when we attempt to `publish` a tweet though the `timeline` contract. Before we store the tweet, we're first going to call `action(PERMISSIONS,TO_ACCOUNT,TO_ACTION,DATA_TUPLE).send()` to validate our user's profile.
```
require_auth(username);
// Validate user
eosio::action(
  permission_level{_self, N(active)},
  N(user),
  N(validate),
  std::make_tuple(username)
).send();
...
// Store tweet
```
It's as simple as that! You should be able to call another contract as long as your `eosio.code` permissions are setup for the contract account making the calls.