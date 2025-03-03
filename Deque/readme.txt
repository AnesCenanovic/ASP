# Double-Ended Queue (Deque) in C++

This code implements a double-ended queue (deque) data structure using templates in C++. A deque is a type of queue that allows elements to be added or removed from both ends.

## Features

* **Generic implementation:** The deque can store elements of any data type.
* **Doubly linked list:** The deque is implemented using a doubly linked list for efficient insertion and deletion at both ends.
* **Standard queue operations:** The code provides methods for adding elements to the front or back, removing elements from the front or back, accessing the front and back elements, checking the size, and clearing the deque.
* **Exception handling:** The code throws exceptions for error conditions such as attempting to access elements from an empty deque.
* **Test functions:** The code includes test functions to verify the functionality of the deque implementation.

## Usage

To use the deque, you can create an instance of the `DvostraniRed` class with the desired data type as the template argument. For example, to create a deque of integers, you would use the following code:

```c++
DvostraniRed<int> deque;