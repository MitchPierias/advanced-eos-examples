# EOS Singletons
> Singletons should be used to store contract state, or as a multi-index table alternative when only one row is required.

**Persistence**
We're going to use singleton's as a method to persist our contract state. Using a table for this would be a waste of resources given that we would only ever occupy one row, and assuming we don't want to maintain a history of our contract state.

## Defining the Singleton
Our contracts configuration is a perfect example of data you might want to persist in a singleton. To start we will define our object struct and assign it to a type definition.
```
struct Config {
	bool		closed = false;
	uint32_t	chars = 144;
};

typedef singleton<N(settings), Config> settings_table;
```
Defining the singleton takes a `name` and `object-type` argument, much the same as a multi-index table. We will also create an instance of our singleton called `config` which we will initialize in our constructor and use to access data later.
```
settings_table config;
```

## Initializing the Singleton
We're going to initialize our singleton in our contracts constructor so it's ready to use in all our contracts member functions. 
```
explicit singletons(action_name self) : contract(self), config(_self, _self) {}
```
Just like initializing a multi-index table, the singleton takes a contract-code and scope. We've set both the code and scope to `_self` here.

## Getting Singleton Values
Let's start interacting with our singleton by getting it's stored values. We're going to simply get the `chars` and print it to the console.
```
auto state = config.get();
print(state.chars);
```
And that's it! Our `config.get()` retrieves the struct object we defined earlier and assigns it to our variable `state`. Now we can access the properties of our struct using dot notation.

## Setting Singleton Values
In this example we will update the `chars` property using the member function `singleton.set(STRUCT,PAYER)`. Let's look at a few methods of building our struct to update our singleton.

#### 1. Inline Updating
The simplest method is to build our struct inline, passing it directly to our set function like so.
```
config.set(Config{true, char_count}, _self);
```
Here we are statically setting `closed` to `true` while setting our `chars` to the variable passed as input to our action. This method is ideal for a singleton with only a few properties or when values can be statically set. But what about if we want to update a value while maintaining the previous state on our other properties? 

#### 2. Get & Update
For this we are going to use a fetch then update method. We will first get our current state using the `singleton.get()` function.
```
auto state = config.get();
```
**a. Inline with previous state**
Now we can build our struct again using values from our previous state and passing in our new variables. However, this method becomes cumbersome quickly if your struct has a large amount of properties.
```
config.set(Config{state.closed, char_count}, _self);
```
**b. Updating previous state**
Alternatively, you can simply update the property on the `state` object we fetched earlier, then pass the updated object to the `set` function like so.
```
state.chars = char_count;
config.set(state, _self);
```