## File Structure

- **`Main.c`**  
  Core implementation of the Inventory Processing System.

- **`Products.txt`**  
  Stores product details (created dynamically if not present).

- **`Transactions.txt`**  
  Logs all deposit and withdrawal transactions (created dynamically if not present).

- **`login.txt`**  
  Stores credentials for user authentication (needs to be preconfigured).

---

## How to Run

### Prerequisites

- **Windows OS**  
  (uses `conio.h` and `windows.h` libraries).

- **C Compiler**  
  (e.g., GCC, Turbo C, Dev C++, VSC).

### Input Requirements

### Logging In

1. Open the program.
2. Enter your username and password as stored in **`login.txt`**.
   - **Format:** `username password`
3. If login fails, retry up to 3 times before the program exits.

- Ensure **`login.txt`** is present in the directory with valid credentials.  
  - **Format:** `username password`
