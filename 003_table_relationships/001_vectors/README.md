# Advanced EOS 003 - One-to-Many Table Relationships
## Section 1 - Vectors
[C++ Vectors](http://www.cplusplus.com/reference/vector/vector/) represent the structure of a dynamic array, allowing us to store a collection of values or sub-collections. In the following example we will use a vector to represent an array of unique dog identifiers. The identifiers stored in the `Owner` table will reference the unique `primary_key` of dogs in our `Dog` table.

```
struct Owner {
    name            	account;
    vector<uint64_t>  	dogs;
}

struct Dog {
    uint64_t     		uid;
    string				name;
}
```

Now inside our `void example_table_vectors::create(... )` method, we're going to push a reference to the `Dog` using the `Dog.uid` we stored prior.

```
owners.modify(dogOwner, 0, [&](auto& owner) {
	owner.dogs.push_back(dogID);
});
```

The `push_back()` function appends our value to the end of the dogs vector.

We can even go a step further and define a sub-collection within our dog vector
```vector<uint64_t, uint32_t> dogs;```
where `uint64_t` is our dog identifier and `uint32_t` is the dog’s age. Alternatively you can store another stuct inside a vector like `vector<Dog> dogs;`.

Vectors are a great method when we want to store related data directly within our table, however table rows could quickly grow excessively large from user abuse or improper data management. In the next section we will explore the use of Secondary Indexes to create relationships between tables.