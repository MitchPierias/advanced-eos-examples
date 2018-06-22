# EOS Multi-Index Tables - One-to-Many Relationships
## One-to-Many Table Relationships
I come from a background in [Graph Databases](https://neo4j.com/developer/graph-database/), a wonderful land where data is directly linked too it’s related data, like MySQL joins but on steroids. So if you’re like me and have mastered the basics of EOS tables, then you’ve probably asked the question, but how do I create a relationship between multiple tables and rows? Well in this example we’ll be looking into not one, but multiple methods for creating one-to-many relationships using EOS `multi_index` tables.

In these examples we will look at three diferent methods for creating relationships between our EOS table rows.
1. Vectors
2. Indexes
3. Scopes

For these examples we will won't be validating the account using `require_auth()` function.