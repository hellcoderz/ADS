Some Data Structure to insert and search key/values; more to come <br>
Tags: B+-Tree in C++ , AVL Tree in C++
<h3>Compiling: </h3>
<pre>make</pre>
<h3>Performance Testing:</h3>
<pre>make run</pre>
<h3>Cleaning:</h3>
<pre>make clean</pre>
<h3>Default parameters: </h3>
no. of nodes = 1000000<br>
order of B+-tree = 50<br>
size of hash = 11
<br><br>
Converted all data structures .cpp to header files located in ./dictionary directory and also a driver .cpp file.<br>
Compiling and running instructions are same.<br><br>
Hash data structure just contain hashmap with each node pointing to a B+tree, AVLtree or RBtree. This is done to reduce insert and search time.

<h3>Implemted so far: </h3>
  AVL Tree:
    <ol>
      <li>insert</li>
      <li>search</li>
      <li>inorder traversal</li>
      <li>preorder traversal</li>
      <li>level oreder traversal</li>
    </ol>
  AVL Hash Tree:
    <ol>
      <li>insert</li>
      <li>search</li>
      <li>inorder traversal</li>
      <li>preorder traversal</li>
      <li>level oreder traversal</li>
    </ol>
  B+-Tree:
    <ol>
      <li>insert</li>
      <li>search</li>
      <li>inorder traversal</li>
      <li>preorder traversal</li>
      <li>level oreder traversal</li>
    </ol>
  B+-Tree Hash:
    <ol>
      <li>insert</li>
      <li>search</li>
      <li>inorder traversal</li>
      <li>preorder traversal</li>
      <li>level oreder traversal</li>
    </ol>
<h3>TO DO</h3>
  <ol>
    <li>Optimize Code for minimum space requirement for all data structure: convert deep copy to shallow copy</li>
  </ol>
