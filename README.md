# System Guardian (Linux)

System Guardian is a lightweight Linux system monitoring tool written in C.

The program monitors CPU and memory usage in real time and provides automated alerts when system resources exceed defined thresholds, logging every reading to a file.

This project was developed as a systems programming project to gain practical experience with Linux internals and low-level C programming.

---

## Features

- CPU usage monitoring (accurate 8-field `/proc/stat` calculation)
- Memory usage monitoring (uses `MemAvailable` for real-world accuracy)
- Configurable alert thresholds via `config.h`
- Continuous monitoring loop with clean `Ctrl+C` / `SIGTERM` shutdown
- Timestamped logging to `guardian.log`
- Terminal alerts when CPU or memory exceed thresholds

### Planned Features

- Configurable monitoring intervals via CLI flags
- Process-level monitoring (`/proc/[pid]/stat`)
- Daemon mode with background execution
- PID file management

---

## Technologies

- C Programming Language (C11)
- Linux System Programming (`/proc` filesystem)
- GCC with `-Wall -Wextra -pedantic`

---

## How It Works

The program reads system statistics directly from Linux virtual filesystem files:

- `/proc/stat` — CPU usage (two samples, `MONITOR_INTERVAL` seconds apart)
- `/proc/meminfo` — Memory usage (`MemTotal` and `MemAvailable`)

Each reading is printed to the terminal and appended to `guardian.log` with a timestamp. If CPU or memory usage exceeds the configured thresholds in `config.h`, an alert is printed immediately.

Signal handlers for `SIGINT` and `SIGTERM` ensure the program exits cleanly without cutting off a log write mid-operation.

---

## Project Structure

```
.
├── config.h      # Thresholds and monitoring interval
├── cpu.c / .h    # CPU usage from /proc/stat
├── memory.c / .h # Memory usage from /proc/meminfo
├── logger.c / .h # Timestamped file logging
├── guardian.c    # Main loop, alerts, signal handling
└── Makefile
```

---

## Installation & Usage

Clone the repository and build with `make`:

```bash
git clone https://github.com/yourname/system-guardian.git
cd system-guardian
make
./guardian
```

To stop the program cleanly:

```bash
Ctrl+C
```

To clean build artifacts:

```bash
make clean
```

---

## Configuration

Edit `config.h` to adjust behaviour before compiling:

```c
#define CPU_THRESHOLD    80.0   // Alert when CPU  exceeds 80%
#define MEM_THRESHOLD    85.0   // Alert when RAM  exceeds 85%
#define MONITOR_INTERVAL 2      // Seconds between samples
```

---

## Log Format

Readings are appended to `guardian.log` in the following format:

```
[2025-03-04 14:22:01] CPU: 12.45% | MEM: 63.20%
[2025-03-04 14:22:03] CPU: 78.30% | MEM: 63.25%
```
