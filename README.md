# System Guardian (Linux)

System Guardian is a lightweight Linux system monitoring tool written in C.

The program monitors CPU and memory usage and provides automated alerts when system resources exceed defined limits.

This project was developed as a systems programming project to gain practical experience with Linux internals and low-level programming.

---

## Features

### Current Features

- CPU usage monitoring
- Memory usage monitoring
- Continuous monitoring loop
- Terminal output
- Logging to file
- Basic alerts

### Planned Features

- Signal handling (Ctrl+C safe exit)
- Configurable monitoring intervals
- Process monitoring
- Daemon mode
- Background execution
- PID file management

---

## Technologies

- C Programming Language
- Linux System Programming
- GCC Compiler

---

## How It Works

The program reads system statistics directly from Linux system files:

- `/proc/stat` for CPU usage
- `/proc/meminfo` for memory usage

System information is printed to the terminal and stored in a log file.

---

## Installation

Clone the repository:
