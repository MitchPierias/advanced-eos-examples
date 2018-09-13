# EOS Multi-Index Tables - Uniqueness
## Unique Primary Keys

By now we're able to create rows in our tables indexed by our unique `account_name` identifiers, but how do we use a different `primary_key` and ensure it's unique? Fortunately the developers at EOSio have provided us with the  `available_primary_key()` function.

Let's begin by changing our structure's `id` property type definition to `uint64_t`. Remember `account_name` and `name` both compile too `uint64_t`, the only difference is readability. 

```
// @abi table items i64
struct Item {
  uint64_t          id;
  string            name;
  uint64_t          attack;
  account_name      owner;

  auto primary_key() const { return id; };
  EOSLIB_SERIALIZE(Item, (id)(name)(attack));
};

typedef multi_index<N(items), Item> items_table;
```

Then we will update our `create` action to generate and set a unique `id` for each new item we create. Now we will update our create action to use the tables `available_primary_key()` function like like so;

```
void inventory::create(const account_name account, const string name, const uint64_t attack) {

  items_table items(_self, _self);

  items.emplace(account, account, [&](auto& item) {
    item.id = items.available_primary_key();
    item.name = name;
    item.attack = attack;
    item.owner = account;
  });
}
```

Now we're able to lookup each `Item` by it's unique `id` index.
