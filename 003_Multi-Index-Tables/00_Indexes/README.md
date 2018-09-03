

# EOS Multi-Index Tables - Indexes
## Table Primary & Secondary Indexes

Let's take a look at tables and utilizing indexes too store and retrieve our data.

### Primary Indexes
**Defining our Struct**
The simplest and required index for each table is the `primary_key`. The `primary_key` property is used to ensure uniqueness between rows just like any conventional database. 

Let's setup our `struct` and define our `primary_key` index as `id`. We will use the users `account_name` for uniqueness and cover a more versatile method in the following chapter.

```
// @abi table items i64
struct Item {
  account_name      id;
  string            name;
  uint64_t          attack;
  account_name      owner;

  auto primary_key() const { return id; };
  EOSLIB_SERIALIZE(Item, (id)(name)(attack)(owner));
};
```

And our `typedef` with a primary index

```
typedef multi_index<N(items), Item> items_table;
```
### Secondary Indexes
**Defining our Indexes**
Now let's define a secondary index to fetch items by their respective owner. We will start by updating our `struct` to use a secondary index called `get_owner()`.
```
// @abi table items i64
struct Item {
  auto              id;
  string            name;
  uint64_t          attack;
  account_name      owner;

  auto primary_key() const { return id; };
  uint64_t get_owner() const { return owner; };
  EOSLIB_SERIALIZE(Item, (id)(name)(attack)(owner));
};
```
The `get_owner()` function returns the `owner` property of a table row. Before we can search items by owner, we first need to define our index and attach our function. Let's modify our `typedef` to utilize our new lookup.
```
typedef multi_index<N(items), Item, indexed_by<N(byowner), const_mem_fun<Item, uint64_t, &Item::get_owner>>> item_table;
```

If we now take a closer look at our `typedef` you can see we've added a new argument, `indexed_by<>`. The `indexed_by<NAME,FUNCTION>` macro takes two arguments; The index name `N(byowner)` which we will use to recall our index later, and the function `const_mem_fun<Item, uint64_t, &Item::get_owner>` defined as `
const_mem_fun<STRUCT,INDEX_RETURN_TYPE,LOOKUP_FUNCTION>
`, which attaches our `get_owner()` to our index.

**Using our Indexes**
We've indexed our item's owner, but how do we now find items owned by a particular user? Let's create a `get()` function to do just that.
```
// @abi action
void get(const account_name account) {
  // Fetch items and print
  item_table items(_self, _self);
  auto playerItems = items.get_index<N(byowner)>();
  auto iter = playerItems.lower_bound(account);
  while (iter != playerItems.end()) {
    print("Item ", iter->name);
    iter++;
  }
}
```
First we instantiate the `item_table` within the scope of the contract using `_self`. Then we get the index we set earlier using the table's `get_index<NAME>` macro by passing in the indexes name `N(byowner)`. Now we have the index reference, we can fetch an iterator from the first object using the `lower_bound(QUERY_VALUE)` method and the `account_name` passed into the action. Finally we loop through the iterator, printing out each objects `name` value until we reach the indexes `end()`.
