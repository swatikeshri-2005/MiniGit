  **Title**

Mini Git - Version Control System Using Data Structures

**Abstract**

This project implements a simplified Version Control System similar to Git.
It maintains versions of files, tracks changes, and supports rollback.
The system is implemented in C++ using Linked Lists, Hashing, and File Handling

**Objectives**

-Track multiple versions of a file

-Maintain commit history

-Restore old versions

-Demonstrate system-level & DSA concepts

**Technologies Used**

-Language: C++

-Data Structures:

-Linked List → Commit History

-Hash Table → Fast lookup & change detection

-File Handling

-Hashing Algorithm (DJB2-like)

**System Design**

1️⃣ Linked List (Commit Chain)

Each commit = node in linked list
HEAD → Commit3 → Commit2 → Commit1

2️⃣ Hash Table

Stores filename + checksum for uniqueness

3️⃣ File System
repo/
   commits/
   index.txt
   log.txt

**Algorithm**

1️⃣ Initialize → Create repo

2️⃣ Add → Register file + compute hash

3️⃣ Commit →
Store file snapshot → create linked list node

4️⃣ Log → Traverse linked list

5️⃣ Rollback → Move HEAD pointer & restore files

**Output**

Shows commit history
Restores exact old files

**Time & Space Complexity**

Operation	Time
Add	O(n)
Commit	O(n)
Log	O(n)
Rollback	O(n)

Space Complexity → O(n)

**Conclusion**

Mini Git successfully demonstrates how version control works internally using fundamental data structures.
It is an excellent DSA + System project with strong real-world relevance.



