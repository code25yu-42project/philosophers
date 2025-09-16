
---

# Philosophers

## 프로젝트 개요

고전적인 철학자 문제(Philosophers Problem)를 프로세스와 스레드 두 가지 방식으로 구현.  
동시성 문제와 교착 상태, 경쟁 조건 등을 이해하고 이를 해결하기 위한 동기화 방법을 학습.

### 주요 기능 및 특징
* 철학자들이 포크를 들고 식사하는 과정을 동기화하여 교착 상태 방지
* 프로세스 버전과 스레드 버전 모두 구현 (프로세스 간 통신, 스레드 동기화 사용)
* 철학자가 죽거나 모든 철학자가 정해진 횟수만큼 식사하면 종료
* 각 상태(먹기, 잠자기, 생각하기 등)에 따른 로그 출력


### 사용된 기술 및 개념
* POSIX 스레드 (pthread) 및 프로세스 생성, 동기화 기법
* 세마포어, 뮤텍스, 시그널 등 동시성 제어 수단
* 시간 측정 및 관리 (밀리초 단위 정확도)
* 안전한 메모리 관리 및 에러 처리

---

## 디렉토리 구조

```
.
├── docs/
│   └── 00_requirements.md      # 프로젝트 요구사항 문서
├── includes/
│   ├── errno.h
│   ├── philo_proc.h            # 프로세스 방식 헤더
│   └── philo_thread.h          # 스레드 방식 헤더
├── srcs/
│   ├── philo_proc/             # 프로세스 방식 소스 코드
│   │   ├── exit.c
│   │   ├── init.c
│   │   ├── libft.c
│   │   ├── main.c
│   │   ├── monitor.c
│   │   ├── proc.c
│   │   ├── routine.c
│   │   └── utils.c
│   └── philo_thread/           # 스레드 방식 소스 코드
│       ├── exit.c
│       ├── init.c
│       ├── libft.c
│       ├── main.c
│       ├── monitor.c
│       ├── routine.c
│       ├── thread.c
│       └── utils.c
├── Makefile
└── README.md
```

---

## 빌드 방법
* 개별 빌드
  * `make`: 프로세스, 스레드 버전 모두 빌드 
  * `make philo_proc`: 프로세스 버전 빌드
  * `make philo_thread`: 스레드 버전 빌드
  * `make clean` : 오브젝트 파일(.o) 삭제
  * `make fclean`: 오브젝트 및 실행파일 삭제
  * `make re`: `fclean` 후 다시 빌드

---
## 실행 방법
두 실행파일 모두 인자를 받아 동작한다.

```bash
./philo_proc number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
./philo_thread number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
* `number_of_philosophers` : 철학자 수 (1 이상)
* `time_to_die` : 밀리초 단위, 마지막 식사 후 죽기까지 시간
* `time_to_eat` : 밀리초 단위, 식사하는 데 걸리는 시간
* `time_to_sleep` : 밀리초 단위, 잠자는 데 걸리는 시간
* `number_of_times_each_philosopher_must_eat` : 선택 사항, 각 철학자가 최소 몇 번 식사해야 종료할지

---

## 실행 예시 
### 예시(1)
```bash
./philo_thread 3 400 200 100
```
출력 예시:
```
0 2 is sleeping
0 3 is sleeping
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
100 2 is thinking
100 3 is thinking
100 3 has taken a fork
200 1 is sleeping
200 3 has taken a fork
200 3 is eating
200 2 has taken a fork
300 1 is thinking
400 3 is sleeping
400 2 has taken a fork
400 2 is eating
400 1 has taken a fork
410 1 died
```
### 예시(2)
```bash
./philo_proc 3 600 200 200
```
출력 예시:
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
1 2 is sleeping
1 3 is sleeping
200 1 is sleeping
201 2 is thinking
201 3 is thinking
201 2 has taken a fork
201 3 has taken a fork
201 2 has taken a fork
201 2 is eating
400 1 is thinking
401 2 is sleeping
401 3 has taken a fork
401 1 has taken a fork
401 3 is eating
601 2 is thinking
.
.
.
```