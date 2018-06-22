# EOS Multi-Index Tables - One-to-Many Relationships
## Section 2: Indexes
Using secondary indexes is an alternative way we can scale the number of references but avoid excessively large arrays (vectors) filling our table rows. It also gives us a method to backwards reference the relationship, which can be combined with previous relationship methods, allowing us to move seamlessly between children and parents of table rows. For this we will use what we learned in the previous post, Secondary Table Indexes. First we’re going to modify our structures from the previous method, removing our items vector from the `Profile` struct and adding a reference to our owner within the `Item` struct.
```
struct Profile {
    name 		account;
}

struct Item {
    uint64_t	uid;
    string		name;
    name		owner;
}
```
To search `Item`s by owner we will need to create a secondary index like `indexed_by<N(byowner), const_mem_fun<Item, uint64_t, &Item::get_owner>` and add it too our `multi_index` definition. EOS allows us to define up too 16 additional indexes for each table.
```
struct Item {
    ...
    uint64_t get_owner() const { return owner; }
}

typedef multi_index<N(items), Item, indexed_by<N(byowner), const_mem_fun<Item, uint64_t, &Item::get_owner>> item_table;
```
Where the name of our index will be `byowner` and it will return the `uint64_t` owner key using the `get_owner` function.

We will no longer be updating our `Player` from within our add item function. Instead we will be storing a refefrence to the signee account in the created `Item`'s `owner` property like so;
```
items.emplace(account, [&](auto& item) {
    ...
    item.owner = account;
});
```
* We will not verify the player is registered here for the purpose of simplicity. However, you should obviously do all your validation prior to creating and assigning an item.

Now we can get all our items for a player like so;
```
void indexes::get(const name account) {
	item_table items(_self, _self);
	auto accounts_items = items.get_index<N(byowner)>();
	auto iter = accounts_items.lower_bound(account);
	// while (iter != accounts_items.end(); iter++) { // Do stuff }
}
```