# EOS Examples
This repository contains a collection of Advanced EOS concepts and examples.

## Examples
**Topics covered**
- [ ] Local Structs
- [ ] Singletons
- [X] Multi-Index Tables
- [ ] Contract-to-Contract Communication
- [ ] Delayed Transactions

## Getting Started
**Setting up a local environment**
Before we can run any examples, we need somewhere to deploy them. Let's setup a local EOS block producer to deploy and test our contracts.
> I recommend you run a local instance of the EOS blockchain for the examples in this repository to avoid unwarranted code on the testnet or mainnet

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
**Creating deployment accounts**
If your starting fresh, you'll need to create a wallet. Open another terminal and run the command
```
cleos wallet create
```
*Remember to copy down the password printed in the terminal.*


**Building Typescript & Application binaries**

**Deploying Contracts**

**Interacting with Contracts**