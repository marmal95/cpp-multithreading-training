
# thread_sync

## ex1_read_shared.cpp

- Problemy w dostępnie do współdzielonych zasobów
    - **Race-condition** - Race condition (wyścig danych) to sytuacja, w której dwa lub więcej wątków jednocześnie odczytuje i modyfikuje współdzielony zasób, powodując nieprzewidywalne lub błędne wyniki. Występuje, gdy poprawność programu zależy od kolejności wykonywania operacji przez wątki, ale ta kolejność nie jest gwarantowana.
    - **Deadlock** - Deadlock (zakleszczenie) to sytuacja, w której dwa lub więcej wątków czeka na siebie nawzajem, blokując się w nieskończoność. Występuje, gdy wątki próbują zablokować te same zasoby w różnej kolejności, co prowadzi do cyklicznej zależności.


## ex2_write_shared_atomic.cpp

- std::atomic
- Kiedy używać?
- Do jakich typów można użyć? (podstawowe/trivially-copyable)

## ex3_write_shared_mutex.cpp

- std::mutex
- .lock() / .unlock()
- Sekcja krytyczna
- Wprowadzenie do problemów z mutexami
- std::lock_guard
- Porównanie std::atomic vs std::mutex

## ex4_write_shared_mutex.cpp

- Deadlock avoidance in README