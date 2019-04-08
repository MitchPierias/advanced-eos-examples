# EOS Examples
This repository contains a collection of Advanced EOS concepts and examples that are typically not covered through any educational material.

> A copy of my nodeos configuration file can be [found here](https://gist.github.com/MitchPierias/647596cacb3d33abc4f70f58bfd174a2)

This repository contains the project source files for the following 'Advanced EOS Series' blog posts:

1. [Cryptographic Hashes](https://medium.com/coinmonks/advanced-eos-series-part-1-cryptographic-hashes-a251a8d371b8)
2. [Singletons](https://medium.com/coinmonks/advanced-eos-series-part-2-singletons-9e903772f71c)
3. [Secondary Indexes](https://medium.com/coinmonks/advanced-eos-series-part-3-secondary-indexes-1798f339cbb8)
4. [Table Index Uniqueness](https://medium.com/coinmonks/advanced-eos-series-part-4-table-uniqueness-835843a207fc)
5. [One-to-many Table Relationships](https://medium.com/coinmonks/advanced-eos-series-part-5-one-to-many-relationships-42d2e075e05d)
6. [Contract-to-contract Communication](https://medium.com/coinmonks/advanced-eos-series-part-6-contract-to-contract-communication-ab352a8b60aa)
7. Remote Table Access
8. Deferred Transactions
9. The Dispatcher Extension
10. Token Transfers

## Getting Started
### Prerequisites
- EOSIO
- C++

### Local EOSIO Environment
> Before we can run any examples, we need somewhere to deploy them. Let's setup a local EOS block producer to deploy and test our contracts.

Clone the EOS project recursively from [this GitHub repository](https://github.com/EOSIO/eos).
```
git clone https://github.com/EOSIO/eos.git --recursive
```
Navigate into the `eos` directory and run the build script:
```
cd eos
./eosio_build.sh
```
Run the following commands to start a clean `nodeos` instance serving locally. Using the `--delete-all-blocks` flag clears any existing blocks, databases and accounts.
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