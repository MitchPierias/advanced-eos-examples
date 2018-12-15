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
- Ensure your `EOSIO_SERIALIZE(TYPE, MEMBERS)` reflects all members in your `struct`.
- Ensure you've deployed the correct ABI