# EOS Hashes
## Checksum Hashes
We seem to use hashes everywhere when writing smart contracts... after all, they are the foundation of blockchains. But how do we go about creating a hash in EOS? Let's start by including a new library.
```
include <eosiolib/crypto.h>
```
Notice the *.h* file extension in our `crypto.h` include? This means we're using a *C* library and not *C++*, so our methods will be expecting *C* type inputs. Now let's create an action which will take a string as input, hash our string and then print the result.

We will start by making allocating a `checksum256` reference.
```
checksum256 sum{}
```
Then use our `eosio::sha256(CHARS,LENGTH,REFERENCE)` method.
```
sha256(const_cast<char*>(str.c_str()), str.size(), &sum);
```
Now all that remains is printing the result.
```
printhex(&sum, sizeof(sum));
```