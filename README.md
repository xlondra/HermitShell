# HermitShell

A simple reverse shell created for the sake of learning.

---

## Compile

**Server:**
```bash
cd Server/src
g++ *.cpp *.hpp -o hermit_server
```

**Client:**
```bash
cd Client/src
g++ *.cpp *.hpp -o hermit_client
```

---

## Run

**Start the server** (default port: 8000, configurable in `Server/src/program.cpp`):
```bash
./Server/src/hermit_server
```

**Connect with the client:**
```bash
./Client/src/hermit_client <ip> <port>
```

Example:
```bash
./Client/src/hermit_client 127.0.0.1 8000
```

You will get an interactive prompt showing the current working directory on the server. Type commands and press Enter to execute them.

---

## Notes

- `cd` is handled natively and updates the prompt path.
- Command output including errors (stderr) is returned to the client.
