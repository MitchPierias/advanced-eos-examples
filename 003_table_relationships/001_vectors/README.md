# Advanced EOS 003 - One-to-Many Table Relationships
### Part 1 - Vectors
[C++ Vectors](http://www.cplusplus.com/reference/vector/vector/) represent the structure of a dynamic array, allowing us to store a collection of values or sub-collections.

```
struct Owner {
    name            	account;
    vector<uint64_t>  	dogs;
}

struct Dog {
    uint64_t        	uid;
    string				name;
}
```

Now inside our `void example_table_vectors::create(... )` method, we're goind to push a reference to the `Dog` using the `Dog.uid` we stored prior.

```
owners.modify(dogOwner, 0, [&](auto& profile) {
	profile.dogs.push_back(dogID);
});
```