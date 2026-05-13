# HermitShell

A simple reverse shell created for the sake of learning

---

## Compile

```bash
g++ *.cpp *.hpp -o hermit
```

---

## Run

```bash
./hermit
```

---

## Connect from Client

Using netcat:

```bash
nc 127.0.0.1 8080
```

You can then send commands directly to the server.
