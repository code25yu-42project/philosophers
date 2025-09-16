
---

# Philosophers 요구사항

## 1. 프로젝트 개요

* **목표**: 스레드(Thread)와 뮤텍스(Mutex)의 기초를 배우는 시뮬레이션 구현
* **내용**: 철학자들이 원탁에 앉아 식사, 생각, 수면을 반복하는 상황을 모델링
* **종료 조건**:
  1. 철학자가 굶어 죽으면 시뮬레이션 종료
  2. (옵션) 모든 철학자가 지정된 횟수 이상 식사하면 종료
* **출처:** 42 School philosophers(version 11.0)

---

## 2. 실행 형식

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

* **number_of_philosophers** : 철학자(=포크) 수
* **time_to_die** (ms) : 마지막 식사 후 이 시간이 지나면 철학자 사망
* **time_to_eat** (ms) : 식사 시간 (포크 2개 필요)
* **time_to_sleep** (ms) : 수면 시간
* **number_of_times_each_philosopher_must_eat** *(선택)* : 각 철학자가 최소 이 횟수만큼 먹으면 종료

---

## 3. 출력 형식 (로그)

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

* **timestamp_in_ms** : 현재 시각 (ms)
* **X** : 철학자 번호
* 메시지는 **뒤섞이면 안 됨**
* 죽음 메시지는 실제 사망 후 **10ms 이내**에 출력

---

## 4. 환경 및 규칙
* **글로벌 변수 사용 금지**
* **메모리 누수 금지**
* 허용 함수만 사용
* 데이터 레이스 방지
* Makefile 필수 (규칙: `NAME`, `all`, `clean`, `fclean`, `re`)

---

## 5. Mandatory Part
* **프로그램명**: `philo`
* **구현 방식**:
  * 철학자 = 스레드
  * 각 포크 = 뮤텍스로 보호
  * 철학자는 양옆 포크를 사용하여 식사
  * 철학자가 1명일 경우 포크 1개만 존재
* **허용 함수**:
  ```
  memset, printf, malloc, free, write,
  usleep, gettimeofday,
  pthread_create, pthread_detach, pthread_join,
  pthread_mutex_init, pthread_mutex_destroy,
  pthread_mutex_lock, pthread_mutex_unlock
  ```
* **libft 사용 불가**

---

## 6. Bonus Part
* **프로그램명**: `philo_bonus`
* **구현 방식**:
  * 철학자 = 프로세스 (메인 프로세스는 철학자 X)
  * 포크는 중앙에 모두 모아두고, **세마포어**로 관리
* **허용 함수**:
  ```
  memset, printf, malloc, free, write,
  fork, kill, exit,
  pthread_create, pthread_detach, pthread_join,
  usleep, gettimeofday,
  waitpid,
  sem_open, sem_close, sem_post, sem_wait, sem_unlink
  ```
* **조건**: Mandatory part가 **완벽**해야 평가 진행

---

## 7. 핵심 구현 포인트
* **시간 측정**: `gettimeofday` 사용
* **동기화**: 뮤텍스(필수), 세마포어(보너스)
* **출력 순서 보장**: 로그가 섞이지 않도록 출력 제어
* **종료 조건 관리**:
  * 철학자 사망 감지
  * (선택) 식사 횟수 조건 충족 시 종료
* **데이터 레이스 방지**

---
