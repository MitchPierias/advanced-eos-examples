# Advanced EOS 003
## One-to-Many Table Relationships
I come from a background in [Graph Databases](https://neo4j.com/developer/graph-database/), a wonderful land where data is directly linked too it’s related data, like MySQL joins but on steroids. So if you’re like me and mastered the basics of EOS tables, then you’ve probably asked the question, but how do I create a relationship between multiple tables and rows? Well in this example we’ll be looking into not one, but multiple methods for creating one-to-many relationships using EOS `multi_index` tables.

### Part 1 - Vectors
[C++ Vectors](http://www.cplusplus.com/reference/vector/vector/) represent the structure of a dynamic array, allowing us to store a collection of values or sub-collections.