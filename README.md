# Social Network System - Technical Documentation

## Project Overview

This project implements a social media platform simulation featuring user management, friendship networks, and post creation capabilities. The system utilizes custom-built **AVL tree data structures** to provide efficient O(log n) operations for most functionalities including friend lookups, post retrieval, and social network queries.

---

## Compilation and Execution

### Build Process
```bash
chmod +x myproj.sh
./myproj.sh
```
Run this command in the bash/zsh terminal for the script to compile and execute the program.

**Compilation Details:**
- Uses C++17 standard for modern template features
- Compiles all .cpp files into `executables/myprogram`
- Template instantiation for AVL trees with specific types at compile time

### Runtime Behavior
- **Interactive Mode:** Reads commands from stdin line by line
- **Command Parsing:** Uses stringstream for flexible argument handling
- **Case-Insensitive Usernames:** Automatically converts to lowercase
- **Global State:** Maintains Network (Graph) and PostsManager (Posts) globally

---

## System Architecture

### Core Data Structure Implementations

#### AVL Tree Implementation

**Structure:**
```cpp
template<typename Key, typename Value>
struct AVLNode {
    Key key;
    Value value;
    AVLNode* left, *right;
    int height;
};
```

**Key Operations:**
- `insert(key, value)`: O(log n) - Recursive insertion with automatic rebalancing
- `find(key)`: O(log n) - Binary search for key
- `getTopN(n)`: O(min(n, m)) - Iterative inorder traversal returning top n values
- `getTopNKeys(n)`: O(min(n, m)) - Returns top n keys

**Balancing Mechanism:**
- Uses height-based balance factors: `balance = height(left) - height(right)`
- Handles 4 rotation cases: LL, RR, LR, RL
- Automatically rebalances after insertion/deletion

**Template Instantiations:**
- `AVLTree<string, int>`: Used in Graph adjacency lists (username → user index)
- `AVLTree<time_t, string>`: Used in Posts for chronological ordering (timestamp → post text)

#### Graph Implementation

**Structure:**
```cpp
class Graph {
private:
    int V;  // Number of users
    unordered_map<string, int> userIndex;  // Username → index mapping
    vector<AVLTree<string, int>> adjList;   // Adjacency list using AVL trees
};
```

**Data Organization:**
- **Adjacency List Representation** using AVL trees for O(log F) friend lookups
- **HashMap-based User Indexing** for O(1) username lookups
- **Bidirectional Edges** for symmetric friendship relations

**Key Methods:**
- `addUser(user)`: O(1) - Creates new user with empty friend list
- `addEdge(user1, user2)`: O(log F) - Creates bidirectional friendship
- `getFriends(user)`: O(F) - Returns all friends in alphabetical order
- `suggestFriends(user, n)`: O(F×M + S×log S) - Suggests friends based on mutual connections
- `degreesOfSeparation(user1, user2)`: O(V+E) - BFS to find shortest path

#### Posts Implementation

**Structure:**
```cpp
class Posts {
private:
    vector<AVLTree<time_t, string>> AVLposts;  // Per-user post tree
    int n;  // Number of users
};
```

**Data Organization:**
- One AVL tree per user for storing posts
- Uses Unix timestamps as keys for automatic chronological ordering
- Newest posts have highest timestamps (rightmost in tree)

**Key Methods:**
- `addUser(userIndex)`: O(1) - Creates empty post tree for user
- `addPost(userIndex, text)`: O(log P) - Inserts post with current timestamp
- `getPosts(userIndex, n)`: O(min(n, log P)) - Retrieves n most recent posts

---

## Command Reference

### User Management

#### ADD_USER
**Syntax:** `ADD_USER <username>`

**Functionality:**
- Adds new user to both Graph and Posts systems
- Assigns sequential user index (0, 1, 2, ...)
- Creates empty AVL tree for friends and posts

**Output:**
- Success: `"Success New User Added"`
- Failure: `"Failed User already exists"`

**Time Complexity:** O(1)

---

#### ADD_FRIEND
**Syntax:** `ADD_FRIEND <user1> <user2>`

**Functionality:**
- Creates bidirectional friendship between two users
- Inserts each user into other's friend AVL tree
- Validates both users exist before creating edge

**Output:**
- Success: `"Success Users are now friends"`
- Already friends: `"Users are already friends"`
- User not found: `"Failed One or both users do not exist"`

**Time Complexity:** O(log F) where F = number of friends

---

### Social Network Queries

#### LIST_FRIENDS
**Syntax:** `LIST_FRIENDS <username>`

**Functionality:**
- Returns all friends in alphabetical order
- Uses inorder traversal of friend AVL tree
- Each friend printed on separate line

**Time Complexity:** O(F) where F = number of friends

---

#### SUGGEST_FRIENDS
**Syntax:** `SUGGEST_FRIENDS <username> <n>`

**Functionality:**
- Suggests potential friends based on mutual connections
- Algorithm:
  1. Get all friends of the user
  2. For each friend, get their friends (friends-of-friends)
  3. Count mutual friends for each candidate
  4. Sort by mutual count (descending), then alphabetically
  5. Return top n suggestions

**Output:** Up to n suggested usernames (one per line)

**Time Complexity:** O(F×M + S×log S) where:
- F = number of friends
- M = average friends per friend
- S = total candidates

---

#### DEGREES_OF_SEPARATION
**Syntax:** `DEGREES_OF_SEPARATION <user1> <user2>`

**Functionality:**
- Finds shortest path between two users using BFS
- Returns number of edges in shortest path
- Returns 0 if same user, -1 if not connected

**Algorithm:** Breadth-First Search (BFS)
- Explores level by level ensuring shortest path
- Uses queue and visited set
- Terminates on first encounter with target

**Time Complexity:** O(V+E) where V = users, E = friendships

---

### Post Management

#### ADD_POST
**Syntax:** `ADD_POST <username> <text>`

**Functionality:**
- Creates new post for user with current timestamp
- Timestamp serves as key for chronological ordering
- AVL tree automatically maintains sorted order

**Output:**
- Success: `"Success Post added"`
- Failure: `"Failed User invalid"` or `"Failed Post cant be created"`

**Time Complexity:** O(log P) where P = posts by user

---

#### OUTPUT_POSTS
**Syntax:** `OUTPUT_POSTS <username> <n>`

**Functionality:**
- Retrieves n most recent posts for user
- Uses descending inorder traversal (newest first)
- Pass n=-1 to retrieve all posts

**Output:** Up to n posts (one per line, newest first)

**Time Complexity:** O(min(n, log P)) where P = posts by user

---

### System Control

#### EXIT
**Syntax:** `EXIT`

**Functionality:** Terminates program execution and cleans up memory

---

## Implementation Details

### Username Normalization
All usernames automatically converted to lowercase for case-insensitive matching:
```cpp
string getUser(string user) {
    for (int i = 0; i < user.length(); i++) {
        if (user[i] >= 'A' && user[i] <= 'Z') {
            user[i] = user[i] + 32;  // Convert to lowercase
        }
    }
    return user;
}
```

### Memory Management
- AVL tree destructors recursively delete all nodes (post-order traversal)
- Vector containers automatically manage dynamic resizing
- Global objects cleaned up on program termination

### Friend Suggestion Algorithm
```cpp
// Mark direct friends as excluded (-1)
for (friend : friends) {
    mutualFriendCount[friend] = -1;
}

// Count mutual friends using hash map
for (friend : friends) {
    for (fof : getFriends(friend)) {
        if (fof != user && mutualFriendCount[fof] != -1) {
            mutualFriendCount[fof]++;
        }
    }
}

// Sort by (mutualCount DESC, username ASC)
sort(candidates.begin(), candidates.end(), greater<pair<int, string>>());
```

### BFS for Shortest Path
```cpp
queue<pair<string, int>> q;  // (username, distance)
unordered_map<string, bool> visited;

q.push({user1, 0});
visited[user1] = true;

while (!q.empty()) {
    auto [currUser, currDist] = q.front();
    q.pop();
    
    for (friend : getFriends(currUser)) {
        if (friend == user2) return currDist + 1;
        if (!visited[friend]) {
            visited[friend] = true;
            q.push({friend, currDist + 1});
        }
    }
}
return -1;  // Not connected
```

---

## Time Complexity Summary

| Operation | Time Complexity | 
|-----------|----------------|
| ADD_USER | O(1) | Hash map |
| ADD_FRIEND | O(log F) | 
| LIST_FRIENDS | O(F) | 
| SUGGEST_FRIENDS | O(F×M + S×log S) | 
| DEGREES_OF_SEPARATION | O(V+E) | 
| ADD_POST | O(log P) | 
| OUTPUT_POSTS | O(min(n, log P)) |

**Legend:**
- F = number of friends of a user
- M = average friends per friend
- S = number of suggestion candidates
- V = total users in network
- E = total friendships
- P = posts by specific user
- n = requested number of results

---

## Design Rationale

### AVL Trees vs Vectors for Adjacency Lists
- **AVL Trees:** O(log F) friend existence checks, automatic alphabetical ordering
- **Vectors:** O(F) lookups, requires manual sorting
- **Trade-off:** Slightly slower iteration but faster lookups and built-in ordering

### Timestamps as Post Keys
- **Automatic Ordering:** No manual sorting required
- **Efficient Retrieval:** Newest posts naturally at rightmost nodes
- **Scalability:** O(log P) insertion regardless of post count

### Bidirectional Edge Storage
- **Query Efficiency:** O(1) to access any user's friend list
- **Symmetry:** Friendships are inherently bidirectional
- **Trade-off:** 2× space usage, acceptable for social network scale

---

## Usage Example

### Sample Workflow
```
ADD_USER Alice
ADD_USER Bob
ADD_USER Charlie
ADD_USER David

ADD_FRIEND Alice Bob
ADD_FRIEND Alice Charlie
ADD_FRIEND Bob David
ADD_FRIEND Charlie David

LIST_FRIENDS Alice
→ bob
→ charlie

SUGGEST_FRIENDS Alice 2
→ david

DEGREES_OF_SEPARATION Alice David
→ 2

ADD_POST Alice Hello World!
ADD_POST Alice Second post!

OUTPUT_POSTS Alice 1
→ Second post!

EXIT
```

### Network Visualization
```
    Alice
    /   \
  Bob   Charlie
    \   /
    David
```

**Explanation:**
- Alice's friends: Bob, Charlie (alphabetically)
- Suggestion for Alice: David (2 mutual friends: Bob and Charlie)
- Degrees of separation Alice → David: 2 hops (Alice → Bob → David or Alice → Charlie → David)
- Posts ordered by timestamp (newest first)

---

## Conclusion

This social network system demonstrates effective use of self-balancing binary search trees (AVL trees) to achieve efficient operations in a social media context. The design prioritizes:

- **Performance:** O(log n) operations for critical paths
- **Simplicity:** Clean separation of concerns (Graph, Posts, Interface)
- **Correctness:** Consistent state management across systems
- **Extensibility:** Template-based structures allow easy adaptation

The implementation showcases practical applications of advanced data structures including AVL tree rotations, graph traversal algorithms (BFS), and efficient chronological data management.
