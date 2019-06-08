# Advanced EOS Development Examples
A collection of Advanced EOS contract examples.
> All contracts have now been updated to conform with the latest EOSIO.CDT release version 1.6

This repository contains a collection of Advanced EOS concepts and examples that are typically not covered through any educational material.
1. [Cryptographic Hashes](https://medium.com/coinmonks/advanced-eos-series-part-1-cryptographic-hashes-a251a8d371b8)
2. [Singletons](https://medium.com/coinmonks/advanced-eos-series-part-2-singletons-9e903772f71c)
3. [Secondary Indexes](https://medium.com/coinmonks/advanced-eos-series-part-3-secondary-indexes-1798f339cbb8)
4. [Table Index Uniqueness](https://medium.com/coinmonks/advanced-eos-series-part-4-table-uniqueness-835843a207fc)
5. [One-to-many Table Relationships](https://medium.com/coinmonks/advanced-eos-series-part-5-one-to-many-relationships-42d2e075e05d)
    - Inline Vectors
    - Index references
    - Scope grouping
6. [Contract-to-contract Communication](https://medium.com/coinmonks/advanced-eos-series-part-6-contract-to-contract-communication-ab352a8b60aa)
7. Remote Table Access
8. Deferred Transactions
9. *The Dispatcher Extension*
10. *Token Transfers*

## Usage
If this is your first time running the examples, you'll first need to clone the repo and install all required dependencies.
```
git clone https://github.com/MitchPierias/Advanced-EOS-Examples
cd Advanced-EOS-Examples
npm install
```
Next you can validate the examples by running
```
npm run test
```
It may take a while to install the docker images initially, this is Lamington's development environment setup stage. Be patient and take a coffee break. Next Lamington will compile and deploy the contracts before executing tests. If all this passes, it means the examples do what they say they do and your safe to copy them to your hearts content.

## Requirements
These examples expect a moderate understanding of the following languages

| Language       | Version |
|----------------|---------|
| C++            |         |
| JavaScript ES6 | ES2016  |
| TypeScript     | 3       |
| CLI            |         |

## Technologies

| Library                                                         | Version |
|-----------------------------------------------------------------|---------|
| [EOSIO](https://github.com/EOSIO/eos)                           | 20      |
| [EOSIO.CDT](https://github.com/EOSIO/eosio.cdt)                 | 1.6     |
| Docker                                                          |         |
| [Lamington](https://github.com/CoinageCrypto/lamingtongton)     | 1       |

## Contributors

[Mitch Pierias](https://github.com/MitchPierias), Creator & Developer

[Kevin Brown](https://github.com/thekevinbrown), Developer

## Special Thanks
A special thanks to [Kevin Brown](https://github.com/thekevinbrown) who volunteered to completely rewrite the series to conform with the latest CDT release version 1.6. Additionaly, Kevin developed and implemented a Truffle inspired tool suite called [Lamington](https://github.com/CoinageCrypto/lamington) which simplifies deployment and testing into one command.
