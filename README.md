# 🧠 Philosophers - When Concurrency Meets Spaghetti  

*A 42 School solution to the Dining Philosophers problem using threads/mutex (mandatory) and processes/semaphores (bonus)*  

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)  
[![42 Norm](https://img.shields.io/badge/Codestyle-42_Norm-green.svg)](https://github.com/42School/norminette)  

## 🚀 Features  
### Mandatory  
- Thread-per-philosopher architecture  
- Mutex-protected forks to prevent data races  
- Real-time death checks (millisecond precision)  
- Thread-safe logging with timestamps  

### Bonus  
- Process-based philosophers (`fork()`)  
- Semaphore-managed fork pool  
- Inter-process communication  

## 🔍 Problem Statement  
Simulate philosophers alternating between eating, sleeping, and thinking without:  
- Deadlocks (circular wait)  
- Starvation (unfair resource allocation)  
- Data races (using mutex/semaphore)  

## 🛠️ Installation  
```bash  
git clone https://github.com/<your-username>/Philosophers.git  
cd Philosophers  
make        # Mandatory  
make bonus  # Bonus
```

## 💻 Usage
#### Mandatory:

./philo 5 800 200 200  # 5 philos, die after 800ms, 200ms eat/sleep  
#### Bonus:

```
./philo_bonus 4 500 200 200 3  # Stop after 3 meals per philosopher  
```

## 📚 Implementation Details
  * **No Global Variables:** Strict parameter passing between threads/processes

* **Performance:** Optimized death-check algorithm

* **Edge Cases:** 1-philosopher, 0-meals, large input handling

## 🌟 Learning Outcomes
* **Concurrency Control:** Mutex vs. semaphore tradeoffs

* **Precision Timing:** `gettimeofday` microsecond accuracy

* **Synchronization Patterns:** Resource contention strategies
