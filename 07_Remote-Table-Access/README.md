# EOS Contract-to-Contract Communication
## Remote Table Access

### Access table data from secondary contracts
Before we can access table data from a secondary contract, we first need to know the structure of the table. We can do this by importing the other contract and using deinfed `struct` for that table, presuming the definition is `public`. Alternatively we can simply look over the other contract and essentially duplicate it's structure within our contract.