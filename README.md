<div align="center">

# 🍽️ Philosophers

**A classical concurrency problem — manage threads and mutexes to keep philosophers alive.**

![C](https://img.shields.io/badge/language-C-blue?style=for-the-badge&logo=c)
![Threading](https://img.shields.io/badge/concurrency-pthread-purple?style=for-the-badge)
![42](https://img.shields.io/badge/school-42-black?style=for-the-badge)
![Score](https://img.shields.io/badge/score-100%2F100-brightgreen?style=for-the-badge)

</div>

---

## 🎯 About

`Philosophers` is an implementation of the classic **dining philosophers problem**. Manage multiple philosophers sitting at a table trying to eat spaghetti with limited forks. Learn **multithreading**, **mutex synchronization**, **deadlock prevention**, and **concurrent resource management**.

This project teaches you the fundamentals of **concurrent programming** and how to safely coordinate multiple threads accessing shared resources.

---

## 🚀 Quick Start

### Clone & Build

```bash
git clone https://github.com/mohamedmazouz7/philosophers philosophers
cd philosophers/philo
make
```

### Run the Simulation

```bash
./philo 5 800 200 200
```

This starts a simulation with:
- 5 philosophers
- 800ms to die (if they don't eat)
- 200ms to eat
- 200ms to sleep

### Output Example

```
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
400 2 has taken a fork
400 2 is eating
...
```

---

## 🍝 The Problem

### Setup

- **Philosophers:** Sit around a circular table
- **Forks:** One fork between each pair of philosophers
- **Goal:** Each philosopher must eat without starving
- **Challenge:** Limited forks require coordination

### The Cycle

Each philosopher continuously:

1. **🤔 Think** — Contemplate life
2. **🍴 Eat** — Need both left AND right fork
3. **😴 Sleep** — Rest after eating
4. **→ Repeat** — Until full or they die

### The Constraint

- Need **2 forks** to eat (left + right)
- Can't eat with just 1 fork
- Only 1 philosopher per fork at a time
- Forks must be protected (mutex)

---

## 📋 Arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | How many philosophers (and forks) |
| `time_to_die` | Milliseconds until death without eating |
| `time_to_eat` | Milliseconds to eat |
| `time_to_sleep` | Milliseconds to sleep |
| `number_of_meals` | *(Optional)* Times each must eat to finish |

---

## 💡 Usage Examples

### Basic 5 Philosophers

```bash
./philo 5 800 200 200
```

Simulation runs until a philosopher dies.

### With Meal Limit

```bash
./philo 4 410 200 200 5
```

Stops after all 4 philosophers eat 5 times.

### Single Philosopher (Edge Case)

```bash
./philo 1 800 200 200
```

Output:
```
0 1 has taken a fork
800 1 died
```

(One fork isn't enough to eat!)

### Larger Group

```bash
./philo 10 500 200 200 3
```

10 philosophers must eat 3 times and survive.

---

## 🏗️ Architecture

### Core Components

| File | Purpose |
|------|---------|
| `main.c` | Initialization and setup |
| `thread.c` | Thread creation and management |
| `actions.c` | Philosopher actions (eat, sleep, think) |
| `parsing.c` | Argument validation |
| `utils.c` | Timing and utility functions |

### Data Structures

```c
typedef struct philosopher {
    int id;                      // Philosopher number (1 to N)
    int num_time_ate;           // Meals eaten
    unsigned long long last_time_eat;  // Last meal timestamp
    pthread_t thread_id;        // Thread handle
    pthread_mutex_t eat_mutex;  // Eating synchronization
    int left_fork;              // Left fork index
    int right_fork;             // Right fork index
    struct s_data *data;        // Global data reference
} t_philosopher;

typedef struct s_data {
    int n_thread;               // Thread count
    unsigned long long start_time;  // Simulation start
    int philo_dead;             // Death flag
    pthread_mutex_t *forks;     // Fork mutexes (one per fork)
    pthread_mutex_t mutex;      // General lock
    pthread_mutex_t philo_dead_mutex;  // Death lock
    pthread_t monitor;          // Monitor thread
    t_philosopher *philo;       // Philosopher array
} t_data;
```

---

## 🔄 Simulation Flow

```
┌──────────────────────────────────┐
│   Initialize Philosophers        │
├──────────────────────────────────┤
│   For each philosopher:          │
│   • Create thread               │
│   • Initialize mutex            │
│   • Assign forks                │
├──────────────────────────────────┤
│   Philosopher Thread Loop:       │
│   1. Try to pick up left fork   │
│   2. Try to pick up right fork  │
│   3. Eat (hold both forks)      │
│   4. Release forks              │
│   5. Sleep                       │
│   6. Think                       │
│   7. Check if alive             │
│   8. Repeat                      │
├──────────────────────────────────┤
│   Monitor Thread:                │
│   • Check if anyone died        │
│   • Check if all ate enough     │
│   • Update status               │
└──────────────────────────────────┘
```

---

## 🎯 State Transitions

```
┌─────────┐
│ Thinking│
└────┬────┘
     │
     ↓ (gets 2 forks)
┌─────────┐
│ Eating  │
└────┬────┘
     │
     ↓ (releases forks)
┌─────────┐
│ Sleeping│
└────┬────┘
     │
     ↓ (sleep done)
┌─────────┐
│ Thinking│ (loop continues)
└─────────┘
```

---

## 🛠️ Build Options

### Standard Build

```bash
make
```

Creates `philo` executable.

### Clean

```bash
make clean       # Remove object files
make fclean      # Remove executable
make re          # Full rebuild
```

---

## 💪 What You'll Learn

✅ **Multithreading** — Creating and managing POSIX threads  
✅ **Mutexes** — Mutual exclusion for shared resources  
✅ **Deadlock prevention** — Coordinating access to multiple locks  
✅ **Race condition handling** — Protecting shared data  
✅ **Synchronization** — Coordinating thread execution  
✅ **Concurrent programming** — Managing parallel execution  
✅ **State management** — Tracking philosopher states  
✅ **Performance tuning** — Optimizing thread efficiency  

---

## ⚙️ Key Implementation Details

### Mutex Strategy

```c
// Fork protection
pthread_mutex_t forks[number_of_philosophers];

// Take forks with timeout to prevent deadlock
pthread_mutex_lock(&forks[left_fork]);
pthread_mutex_lock(&forks[right_fork]);

// Eat while holding both
// ... eating logic ...

// Release forks
pthread_mutex_unlock(&forks[left_fork]);
pthread_mutex_unlock(&forks[right_fork]);
```

### Death Detection

```c
// Monitor checks at intervals
if (current_time - last_eat_time > time_to_die)
{
    philo_dead = 1;  // Set death flag
    print_death_message();
}
```

### Avoiding Deadlock

✅ **Consistent fork ordering** — Always take left then right  
✅ **Timeout detection** — Monitor for stuck threads  
✅ **Non-blocking checks** — Use `pthread_mutex_trylock()` where beneficial  

---

## 📊 Timing Considerations

| Operation | Typical Time |
|-----------|-------------|
| Mutex lock/unlock | < 1 μs |
| Thread creation | 1-10 ms |
| Context switch | 0.1-1 ms |
| System call overhead | 1-10 μs |

The simulation must respect millisecond precision for:
- Eating duration
- Sleeping duration
- Death detection (within 10ms)

---

## 🚫 Constraints

- ❌ **No global variables** — Use struct parameters only
- ❌ **No data races** — All shared data protected
- ❌ **No deadlocks** — Proper synchronization
- ✅ **Clean timestamps** — Accurate time tracking
- ✅ **Proper cleanup** — All threads joined/detached
- ✅ **No memory leaks** — All malloc'd memory freed

---

## 🧪 Testing

### Test Case 1: Basic Run

```bash
./philo 5 800 200 200
```

Should run indefinitely with philosophers eating/sleeping/thinking.

### Test Case 2: Someone Dies

```bash
./philo 4 310 200 100
```

Philosopher 1 dies because 200ms eating + 100ms sleeping > 310ms available.

### Test Case 3: Meal Limit

```bash
./philo 3 600 200 200 5
```

Ends cleanly after all 3 philosophers eat 5 times.

### Test Case 4: Single Philosopher

```bash
./philo 1 800 200 200
```

Should show death after 800ms (can't eat with 1 fork).

---

## 📝 Output Format

Each state change logs:

```
[timestamp] [philosopher_number] [state]
```

Valid states:
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

Example:
```
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

---

## 🎓 Real-World Applications

- **Resource allocation** — Managing limited resources among processes
- **Concurrency control** — Database transactions and locking
- **OS scheduling** — Process management and synchronization
- **Distributed systems** — Coordinating nodes in a cluster
- **Lock-free programming** — Understanding synchronization challenges

---

<div align="center">

**Where philosophy meets concurrency.**

*Part of the 42 School Common Core curriculum.*

</div>
