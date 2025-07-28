# Ken Editor

> A minimalist, persistent, line-based text editor built from scratch in pure C. A deep dive into core systems programming concepts.

## About The Project

"Ken" is a personal engineering project designed to master the fundamental principles of the C programming language and low-level systems design. It is a tribute to Ken Thompson and the classic Unix `ed` line editor, built with a focus on clarity and manual resource management.

### Core Features

*   **Persistent State:** Load a file into memory for editing and save it back to disk.
*   **Dynamic Memory Management:** Each line of the file is dynamically allocated on the heap, demonstrating precise control of `malloc`/`free` .
*   **Command-line Interface:** All interactions are handled through a simple and efficient command loop (`list`, `add`, `del`, `save`, `exit`).
*   **Robust I/O:** Secure and robust user input handling using the `fgets` + `sscanf` pattern to prevent common vulnerabilities.

### Built With

*   Pure C
*   GCC / MinGW-w64
*   Git

## Getting Started

To get a local copy up and running, follow these simple steps.

### Prerequisites

*   A C compiler (like GCC)
    ```sh
    gcc --version
    ```

### Compilation

1.  Clone the repo
    ```sh
    git clone https://github.com/seu-usuario/Ken.git
    ```
2.  Navigate to the project directory
    ```sh
    cd Ken
    ```
3.  Compile the source code
    ```sh
    gcc ken.c -o ken
    ```

### Usage

Run the editor from the command line, passing the file you wish to edit as an argument:

```sh
./ken my_document.txt
```

Once inside the editor, use the available commands (`add`, `del`, `list`, `save`, `exit`) to manipulate the file.
