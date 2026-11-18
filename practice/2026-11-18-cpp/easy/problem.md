# Easy — Package Prefix Inventory

A deployment catalog holds a list of lowercase package names. Each occurrence is a separately deployed package, even if another package has exactly the same name.

For each requested lowercase prefix, report **how many entries begin with that prefix**. A query of the empty prefix matches every catalog entry; an empty catalog returns zero for every query. Package names are nonempty.

Implement this C++17 interface exactly:

~~~cpp
std::vector<int> countPackagePrefixes(
    const std::vector<std::string>& packages,
    const std::vector<std::string>& prefixes);
~~~

### Example

- packages = ["core", "codec", "core", "config", "db"]
- prefixes = ["co", "cor", "core", "db", "x", ""]
- result = [4, 2, 2, 1, 0, 5]

The two copies of "core" count twice.

### Constraints

- 0 <= packages.size(), prefixes.size() <= 100,000
- All characters are lowercase 'a' to 'z'.
- Every package has at least one character; a query prefix may be empty.
- Total characters across packages <= 5,000,000 and across queries <= 500,000.
- Do not modify inputs. Target O(total package characters + total query characters + number of queries) time.
- Return query answers in original order.

### Think first

A naive solution checks each catalog entry for every prefix. A trie shares common prefixes; what integer counter should each trie node store to answer a query without scanning the subtree? Watch for duplicate names and C++ vector reallocation.
