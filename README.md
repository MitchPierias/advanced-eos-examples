# EOS Examples
This repository contains a collection of Advanced EOS concepts and examples that are typically not covered through any educational material.

## Getting Started
#### Setting up a local environment
> Before we can run any examples, we need somewhere to deploy them. Let's setup a local EOS block producer to deploy and test our contracts.

Clone EOS recursively from the [GitHub](https://github.com/EOSIO/eos) Repository.
```
git clone https://github.com/EOSIO/eos.git --recursive
```
Enter the `eos` directory and build.
```
cd eos
./eosio_build.sh
```
Start a clean `nodeos` server locally. The `--delete-all-blocks` flag will clear any existing blocks and accounts.
```
nodeos -e -p eosio --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --delete-all-blocks
```
#### Creating deployment accounts
If your starting fresh, you'll need to create a wallet. Open another terminal and run the command
```
cleos wallet create
```
> Remember to make a copy of the password/keys printed to the terminal

Let's also create a new public/private key pair for our new wallet.

```
cleos wallet create_key
```

We can now use this public key for our new accounts. Replacing the `ACTIVE_PUBLIC_KEY` and `OWNER_PUBLIC_KEY` with the public key we just created.
```
cleos create account eosio example.singletons OWNER PUBLIC_KEY ACTIVE_PUBLIC_KEY
```
Now our `example.singletons` account is ready for our contract code.

## Cheat Sheet
Each individual example will cover how to build, deploy and interact with the contract. But as a reference, the general commands we will be using are listed below.

#### Building WebAssembly & Application binaries
Before contracts can be deployed to the blockchain, they first need to be compiled to WebAssembly. We will use the provided `eosiocpp -o [wasm-file] [source-file]` command to generate our Web Assembly file.
```
eosiocpp -o ./singletons.wast singletons.cpp
```
Interacting with our contract requires an application binary interface. This can be created with the command `eosiocpp -g [abi-file] [source-file]` like so;
```
eosiocpp -g ./singletons.abi singletons.hpp
```
#### Deploying Contracts
To publish our contract on the blockchain, we can use the command `cleos set contract [account] [wasm-file] [abi-file]`, with our newly created account, webassembly file and abi.
```
cleos set contract example.singletons ./singletons.wasm ./singletons.abi
```

#### Interacting with Contracts
Finally interacting can be done with `cleos push action [account-code] [action-name] '[data-object]' -p [permission]` like so;
```
cleos push action example.singletons add '["mitch"]' -p mitch
```