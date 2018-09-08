# EOS Multi-Index Tables - One-to-Many Relationships
## Section 3: Scopes
For this final method we're going to use the table scope to represent relationships between our tables. Using the scope adds a sort of protected security by storing data within the specified EOS account (scope).

> ### The EOS data structure

> – code — The account name assigned write permission (contract)

> —- scope — The account where the data is stored

> —–- table — Name of the table being stored

> —–—- record — A table row

We're going to modify our player's `Item`'s to be stored within the scope of our player's account, the use the account scope to look up all the player's items. To start we can remove the `owner` reference in `get_owner()` index for our multi_index `Item` table. You could, and probably should keep this in most cases, but we are being simplistic in these examples and cutting straight to the point.
```
// The cleaned Item table
struct Item {
    uint64_t    	id;
    string			name;
    auto primary_key() const { return id; };
    EOSLIB_SERIALIZE(Item, (id)(name));
};
// And our multi_index definition
typedef multi_index<N(items), Item> item_table;
```
The real magic happens over in our setters and getters, let's take a look at how they've changed.
```
item_table items(_self, account);
auto item = items.emplace(account, [&](auto& item) {
	... setup
});
```
If you look closely, we are now instantiating our table within the scope of our account, rather than the contract `code` itself. Our get function has been modified in the same way.
```
item_table items(_self, account);
auto iter = playerItems.lower_bound();
while (iter != playerItems.end()) { ... }
```
#### Security
It’s important to realise this is not private storage, it’s just protected by the difficulty of guessing a users public account address along with the contract address (code) and table name.

#### Conclusion
This method makes accessing all items from all accounts extremely difficult, however it's allowing users to own their data within the contract.