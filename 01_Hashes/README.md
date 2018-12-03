# EOS Hashes
Using the EOS Crypto library.
> We use hashes everywhere when writing smart contracts, but how do we go about hashing an input in EOS?

## Overview

This source code is for the Advanced EOS Series of blog posts found at the following;
[SteemIt](https://steemit.com/eos/@mitchpierias/advanced-eos-series-part-1-cryptographic-hashes) | [Medium](https://medium.com/@mitchpierias/advanced-eos-series-part-1-cryptographic-hashes-a251a8d371b8)

## Usage
* Note: This usage example assumes you've logged into your `cleos` wallet and created an account for the contract code.

#### Deploy Contract
```
eosiocpp -o ./checksum.wasm ./checksum.cpp
eosiocpp -g ./checksum.abi ./checksum.cpp
cleos set contract checksum . ./checksum.wasm ./checksum.abi
```
#### Calling Action
```
cleos push action checksum hash '["test string"]' -p checksum
```

## ACTION NAME: hash
* Source: checksum.cpp

### Parameters
Input parameters:

* `str` (string to hash)

Implied parameters: 

* `account_name` (name of the party signing the contract)

### Intent
INTENT. Hashes a given input string and prints to console.

### Term
TERM. This Contract expires at the conclusion of code execution.