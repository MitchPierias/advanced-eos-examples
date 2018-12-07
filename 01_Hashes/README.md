# EOS Hashes
## Overview
### Using the EOS Crypto library.
This source code is for the Advanced EOS Series of blog posts found at;
[SteemIt](https://steemit.com/eos/@mitchpierias/advanced-eos-series-part-1-cryptographic-hashes) | [Medium](https://medium.com/@mitchpierias/advanced-eos-series-part-1-cryptographic-hashes-a251a8d371b8)

## Deployment
> Assuming you've logged into your `cleos` wallet and created an account for the contract code.
```
eosiocpp -o ./checksum.wasm ./checksum.cpp
eosiocpp -g ./checksum.abi ./checksum.cpp
cleos set contract checksum . ./checksum.wasm ./checksum.abi
```

## Usage
```
cleos push action checksum hash '["test string"]' -p checksum
```

## checksum::hash
*Source: checksum.cpp*

Hashes a given input string and prints to console.

### Parameters
Input parameters:

* `str` (string to hash)

Implied parameters: 

* `account_name` (name of the party signing the contract)