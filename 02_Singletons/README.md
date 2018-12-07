# EOS Singletons
## Overview
### Using the EOS Singleton library.
This source code is for the Advanced EOS Series of blog posts found at;
[SteemIt](https://steemit.com/eos/@mitchpierias/advanced-eos-series-part-2-singletons) | [Medium](https://medium.com/coinmonks/advanced-eos-series-part-1-cryptographic-hashes-a251a8d371b8)

## Deployment
> Assuming you've logged into your `cleos` wallet and created an account for the contract code.
```
eosiocpp -o ./singletons.wasm ./singletons.cpp
eosiocpp -g ./singletons.abi ./singletons.cpp
cleos set contract singletons . ./singletons.wasm ./singletons.abi
```

## Usage
Setting the `closed` state;
```
cleos push action singletons setclosed '[true]' -p singletons
```
### singletons::setclosed
*Source: singletons.cpp*

Sets the `closed` state of the contract.

#### Parameters
Input parameters:

* `isClosed` (New closed state)

Implied parameters: 

* `account_name` (name of the party signing the contract)


Getting the `closed` state;
```
cleos push action singletons getclosed '[]' -p singletons
```
### singletons::getclosed
*Source: singletons.cpp*

Gets the `closed` state of the contract.

#### Parameters
Implied parameters: 

* `account_name` (name of the party signing the contract)


Getting the `char_count` state;
```
cleos push action singletons getchars '[]' -p singletons
```
### singletons::getchars
*Source: singletons.cpp*

Gets the `char_count` of the contract.

#### Parameters
Implied parameters: 

* `account_name` (name of the party signing the contract)


Setting the `char_count` state;
```
cleos push action singletons setchars '[172]' -p singletons
```
### singletons::setchars
*Source: singletons.cpp*

Sets the `char_count` of the contract.

#### Parameters
Input parameters:

* `char_count` (New character count)

Implied parameters: 

* `account_name` (name of the party signing the contract)

