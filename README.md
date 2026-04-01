# cppify-doubly-linked-lists

## 📌 Overview
A console-based audio player implementation in C++. The core focus of this project is not the user interface, but the manual management of dynamic memory and the implementation of custom data structures to simulate the operations of a music streaming service.

## ⚙️ Architecture & Data Structures
* **Circular Doubly Linked List:** Enables continuous, infinite bidirectional navigation (next/previous) between audio nodes (`Cancion`). Insertion and deletion at the ends operate in O(1) time complexity.
* **Dynamic Memory Management:** Intensive use of pointers for node traversal (`*sig`, `*ant`). Strict implementation of `delete` operations during node removal to prevent memory leaks and ensure optimal RAM usage.
* **I/O & Hardware Interaction:** * Asynchronous `.wav` audio handling using the native Windows API (`mmsystem.h`).
  * Data decoupling through dynamic reading of `.txt` files (`std::ifstream`) to stream lyrics to the console in real-time, separating data logic from visualization.

## 🚀 Compilation & Execution
This project interacts directly with the Windows Multimedia API. If you are using GCC/MinGW, you must link the `winmm` library during compilation using the `-lwinmm` flag.

To compile and run from the terminal:

```bash
g++ main.cpp -o cppify.exe -lwinmm
./cppify.exe
