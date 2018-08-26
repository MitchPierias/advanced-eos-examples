# EOS Multi-Index Tables - One-to-Many Relationships
## Section 1: Vectors
[C++ Vectors](http://www.cplusplus.com/reference/vector/vector/) represent the structure of a dynamic array, allowing us to store an arbitrarily sized collection of values.

In the following example we will use a vector to represent an array of unique `Item` identifiers. The identifiers stored in the `Profile` table will serve as a reference to the `primary_key` of rows in our `Item` table.

```
struct Profile {
    name            	account;
    vector<uint64_t>  	items;
}

struct Item {
    uint64_t	id;
    string	name;
}
```

Now inside our `void example_table_vectors::create(... )` method, we're going to push a reference to the `Item` using the `Item.id` we stored prior.

```
owners.modify(currentPlayer, 0, [&](auto& owner) {
	owner.items.push_back(itemID);
});
```

The `push_back()` function appends our value to the end of the items vector.

We can even go a step further and define a sub-collection within our item vector
```vector<uint64_t, uint32_t> items;```
where `uint64_t` is our item identifier and `uint32_t` is the item’s age. Alternatively a secondary struct (collection) can be stored inside the vector like `vector<Item> items;`.

#### Conclusion
Vectors are a great method when we want to store related data directly within our table, however table rows could quickly grow excessively large from user abuse or improper data management. In the next section we will explore the use of Secondary Indexes to create relationships between tables.
