## Transfers

### Symbol Precision Mismatch Error

Thrown when attempting to issue or transfer assets using a different floating point precision than was specified at creation. So if I created my asset with `10000.00 SYS`, then I'd need to issue and transfer using two decimal precision like `12.00 SYS` and not `12 SYS`.

- Ensure all your token references contain the same floating point precision that was used to issue the tokens.

## Tables

### Out of Range Error

Received when attempting to read a table using the `cleos get table CODE SCOPE TABLE_NAME` command;

```
2965831ms thread-0 main.cpp:2658 main ]
Failed with error: Out of Range (8) read datastream of length 90 over by 1
error unpacking uint64_t
Error unpacking field value
error unpacking eosio::chain::name
```

This means your abi file is out of sync with your table data, so schema mapping fails.

> Invalid with EOSIO.CDT 1.6

- Ensure your `struct` schema matches the structure of the data your accessing.
- ~~Ensure your `EOSIO_SERIALIZE(TYPE, MEMBERS)` reflects all members in your `struct`.~~
- Ensure you've deployed the correct ABI
