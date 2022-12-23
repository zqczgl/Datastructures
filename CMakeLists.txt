cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled 3/reverse.cpp 3/hello.cpp DataStructures/chainlist.cpp DataStructures/Chainlist.h 3/test.cpp DataStructures/ArrayList.h DataStructures/graph.cpp)

add_executable(hello 3/hello.cpp DataStructures/Chainlist.h)
add_executable(reverse 3/reverse.cpp)

add_executable(chainlist DataStructures/chainlist.cpp DataStructures/Chainlist.h DataStructures/spareMatrix.cpp DataStructures/stack.cpp DataStructures/arrayQueue.cpp DataStructures/hashtable.cpp DataStructures/binaryTree.cpp DataStructures/minHeap.cpp DataStructures/huffman.cpp DataStructures/IndexedBSTree.cpp DataStructures/Slot.cpp)
add_executable(spareMatrix DataStructures/spareMatrix.cpp)

add_executable(stack DataStructures/stack.cpp)
add_executable(test 3/test.cpp)
add_executable(arrayQueue DataStructures/arrayQueue.cpp DataStructures/skipNode.cpp DataStructures/skipNode.h DataStructures/main.cpp DataStructures/loserTree.h DataStructures/CatalogTree.h DataStructures/booster.h)
add_executable(binaryTree DataStructures/binaryTree.cpp)
add_executable(minHeap DataStructures/minHeap.cpp)
add_executable(huffman DataStructures/huffman.cpp)
add_executable(IndexedBSTree DataStructures/IndexedBSTree.cpp)
add_executable(graph DataStructures/graph.cpp)
add_executable(Slot DataStructures/Slot.cpp)
add_executable(skipNode DataStructures/skipNode.h)
add_executable(main DataStructures/main.cpp)

add_executable(loserTree DataStructures/loserTree.h)
add_executable(CatalogTree DataStructures/CatalogTree.h)