# EOS Multi-Index Tables - One-to-Many Relationships
## Section 1: Indexes
Using secondary indexes is an alternative way we can scale the number of references but avoid excessively large arrays (vectors) filling our table rows. It also gives us a method to backwards reference the relationship, which can be combined with previous relationship methods, allowing us to move seamlessly between children and parents of data. For this we will use what we learned in the previous post, Secondary Table Indexes. First we’re going to modify our structures from the previous method, removing our dogs vector from the Owner struct and adding a reference to our owner within the Dog struct.
```
struct Owner {
    name 		account;
}

struct Dog {
    uint64_t	uid;
    string		name;
    name		owner;
}
```
Then we will need to create a secondary index for our Dog struct so we can look them up by owner;
```
struct Dog {
    ...
    uint64_t get_owner() const { return owner; }
}

typedef multi_index<N(dogs), Dog, indexed_by<N(byowner), const_mem_fun<Dog, uint64_t, &Dog::get_owner>> dog_table;
```
Where the name of our index will be `byowner` and it will return the `uint64_t` owner key using the `get_owner` function.

Now we can get all our dogs for an owner like so;
```
void example_table_vectors::dogs(const name account) {
	dog_table dogs(_self, _self);
	auto accounts_dogs = dogs.get_index<N(byowner)>();
	auto iter = accounts_dogs.lower_bound(account);
	// while (iter != accounts_dogs.end(); iter++) { // Do stuff }
}
```