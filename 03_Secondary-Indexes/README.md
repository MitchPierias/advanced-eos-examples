# EOS Secondary Indexes

## Overview
Using the multi-index table secondary indexes

This source code is for the Advanced EOS Series of blog posts found at; SteemIt | [Medium](https://medium.com/@mitchpierias/advanced-eos-series-part-3-secondary-indexes-1798f339cbb8)

## Deployment
> Assuming you've logged into your cleos wallet and created an account for the contract code.

```
eosiocpp -o ./timeline.wasm ./timeline.cpp
eosiocpp -g ./timeline.abi ./timeline.cpp
cleos set contract timeline . ./timeline.wasm ./timeline.abi
```

## Usage
```
cleos push action timeline inventory '["user"]' -p timeline
```

## timeline::post
Source: timeline.cpp

Posts a message for the specified user at the specified index

### Parameters

Input parameters:

 * `account_name` (user account_name)

 * `uin64_t` (message index)

 * `std::string` (message string)

Implied parameters:

 * `account_name` (name of the party signing the contract)

## timeline::get
Source: timeline.cpp

Gets the post at the specified index

### Parameters

Input parameters:

 * `uin64_t` (message index)

Implied parameters:

 * `account_name` (name of the party signing the contract)

## timeline::inventory
Source: timeline.cpp

Finds items for the specified user account prints to console.

### Parameters

Input parameters:

 * `account_name` (user account_name)

Implied parameters:

 * `account_name` (name of the party signing the contract)