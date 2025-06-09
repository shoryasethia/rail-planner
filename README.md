# RAIL PLANNER

* [x] **Trie** and **DFS** based Autocomplete for Station Names
* [ ] Implement **KMP Algorithm** for keyword-based review search
* [ ] Use **Heap** to filter and prioritize user reviews by rating
* [ ] Represent station network as a **Graph** (client-server model)
* [ ] Store journeys using **AVL / BST Trees**
* [ ] Sort journeys or reviews using **Quicksort on Linked Lists**



# 🚉 Trie-based Autocomplete for Station Names

This is a **Trie-based autocomplete system** implementaion for station names.

## ✅ Functionality

* **Reads station data** from a CSV file (`station_name,station_id,location`).
* Converts all names and locations to lowercase for **case-insensitive matching**.
* **Stores station names** in a Trie data structure.
* **Performs prefix search** to return the **top K matching station names** using DFS.
* Outputs the matched results in lexicographical order (default DFS traversal order).

## 🔧 Key Components

* `struct Station`
  Represents a station with `name`, `id`, and `location`.

* `void getStations(const string& data, vector<Station>& stations)`
  Parses the CSV file and populates the `stations` vector.

* `class Trie`
  * `void insert(string s)` – Inserts a station name into the Trie.
  * `vector<string> search(const string& prefix, int topK)` – Returns top K station names matching the given prefix.

* `struct Node`
  Internal Trie node structure with child pointers and a flag indicating word-end.

* `int main()`
  * Loads station data from csv.
  * Inserts all station names into the Trie.
  * Searches for a given `prefix`.
  * Displays top `K` autocomplete results.
