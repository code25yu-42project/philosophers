# Philosophers

[日本語](#日本語) | [English](#english) | [한글](#한글)

<a id="日本語"></a>
## 日本語

### プロジェクト概要
古典的な哲学者問題(Philosophers Problem)を、プロセス方式とスレッド方式の2種類で実装したプロジェクトです。  
並行処理における競合状態、デッドロック、同期の考え方を学ぶことを目的としています。

### 主な機能
- 哲学者がフォークを取り、食事する流れを同期してデッドロックを防止
- プロセス版とスレッド版の両方を実装
- 哲学者が死亡した場合、または全員が指定回数食事した場合に終了
- 各状態(食べる、寝る、考えるなど)をログとして出力

### 使用技術
- POSIXスレッド(pthread)とプロセス生成・同期
- セマフォ、ミューテックス、シグナルなどの同期制御
- ミリ秒単位の時間計測と管理
- 安全なメモリ管理とエラーハンドリング

### ディレクトリ構成
```
.
├── docs/
│   └── 00_requirements.md      # プロジェクト要件
├── includes/
│   ├── errno.h
│   ├── philo_proc.h            # プロセス版ヘッダ
│   └── philo_thread.h          # スレッド版ヘッダ
├── srcs/
│   ├── philo_proc/             # プロセス版ソース
│   │   ├── exit.c
│   │   ├── init.c
│   │   ├── libft.c
│   │   ├── main.c
│   │   ├── monitor.c
│   │   ├── proc.c
│   │   ├── routine.c
│   │   └── utils.c
│   └── philo_thread/           # スレッド版ソース
│       ├── exit.c
│       ├── init.c
│       ├── libft.c
│       ├── main.c
│       ├── monitor.c
│       ├── routine.c
│       ├── thread.c
│       └── utils.c
├── Makefile
└── README.md
```

### ビルド方法
- `make` : プロセス版とスレッド版を両方ビルド
- `make philo_proc` : プロセス版のみビルド
- `make philo_thread` : スレッド版のみビルド
- `make clean` : オブジェクトファイル(.o)を削除
- `make fclean` : オブジェクトファイルと実行ファイルを削除
- `make re` : `fclean` の後に再ビルド

### 実行方法
両方の実行ファイルは、以下の引数を受け取って動作します。

```bash
./philo_proc number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
./philo_thread number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers` : 哲学者の人数(1以上)
- `time_to_die` : 最後の食事から死亡するまでの時間(ミリ秒)
- `time_to_eat` : 食事にかかる時間(ミリ秒)
- `time_to_sleep` : 睡眠にかかる時間(ミリ秒)
- `number_of_times_each_philosopher_must_eat` : 省略可。各哲学者が最低何回食べれば終了するかを指定

### 実行例
#### 例(1)
```bash
./philo_thread 3 400 200 100
```

出力例:
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

#### 例(2)
```bash
./philo_proc 3 600 200 200
```

出力例:
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

<a id="english"></a>
## English

### Project Overview
This project implements the classic Philosophers Problem in two versions: process-based and thread-based.  
It is designed to study concurrency issues such as race conditions, deadlocks, and synchronization.

### Key Features
- Synchronized philosopher eating flow to prevent deadlocks
- Both process and thread versions implemented
- Program ends when a philosopher dies or when every philosopher has eaten the required number of times
- Logs each state change such as eating, sleeping, and thinking

### Technologies Used
- POSIX threads (pthread), process creation, and synchronization
- Semaphores, mutexes, and signals for concurrency control
- Millisecond-level time measurement and management
- Safe memory handling and error management

### Directory Structure
```
.
├── docs/
│   └── 00_requirements.md      # project requirements
├── includes/
│   ├── errno.h
│   ├── philo_proc.h            # process version header
│   └── philo_thread.h          # thread version header
├── srcs/
│   ├── philo_proc/             # process version source files
│   │   ├── exit.c
│   │   ├── init.c
│   │   ├── libft.c
│   │   ├── main.c
│   │   ├── monitor.c
│   │   ├── proc.c
│   │   ├── routine.c
│   │   └── utils.c
│   └── philo_thread/           # thread version source files
│       ├── exit.c
│       ├── init.c
│       ├── libft.c
│       ├── main.c
│       ├── monitor.c
│       ├── routine.c
│       ├── thread.c
│       └── utils.c
├── Makefile
└── README.md
```

### Build
- `make` : build both process and thread versions
- `make philo_proc` : build the process version only
- `make philo_thread` : build the thread version only
- `make clean` : remove object files (.o)
- `make fclean` : remove object files and executables
- `make re` : rebuild after `fclean`

### Usage
Both executables accept the following arguments:

```bash
./philo_proc number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
./philo_thread number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers` : number of philosophers (must be at least 1)
- `time_to_die` : time in milliseconds before a philosopher dies after the last meal
- `time_to_eat` : time in milliseconds spent eating
- `time_to_sleep` : time in milliseconds spent sleeping
- `number_of_times_each_philosopher_must_eat` : optional, minimum number of meals required for each philosopher to finish

### Example Runs
#### Example 1
```bash
./philo_thread 3 400 200 100
```

Sample output:
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

#### Example 2
```bash
./philo_proc 3 600 200 200
```

Sample output:
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

<a id="한글"></a>
## 한글

### 프로젝트 개요
고전적인 철학자 문제(Philosophers Problem)를 프로세스 방식과 스레드 방식 두 가지로 구현한 프로젝트입니다.  
동시성 문제, 경쟁 상태, 교착 상태, 동기화 개념을 학습하는 것을 목표로 합니다.

### 주요 기능
- 철학자가 포크를 집고 식사하는 과정을 동기화하여 교착 상태를 방지
- 프로세스 버전과 스레드 버전 모두 구현
- 철학자가 죽거나, 모든 철학자가 정해진 횟수만큼 식사하면 종료
- 먹기, 잠자기, 생각하기 등 상태 변화를 로그로 출력

### 사용 기술
- POSIX 스레드(pthread), 프로세스 생성 및 동기화
- 세마포어, 뮤텍스, 시그널 등 동시성 제어 수단
- 밀리초 단위 시간 측정 및 관리
- 안전한 메모리 관리와 에러 처리

### 디렉터리 구조
```
.
├── docs/
│   └── 00_requirements.md      # 프로젝트 요구사항 문서
├── includes/
│   ├── errno.h
│   ├── philo_proc.h            # 프로세스 버전 헤더
│   └── philo_thread.h          # 스레드 버전 헤더
├── srcs/
│   ├── philo_proc/             # 프로세스 버전 소스 코드
│   │   ├── exit.c
│   │   ├── init.c
│   │   ├── libft.c
│   │   ├── main.c
│   │   ├── monitor.c
│   │   ├── proc.c
│   │   ├── routine.c
│   │   └── utils.c
│   └── philo_thread/           # 스레드 버전 소스 코드
│       ├── exit.c
│       ├── init.c
│       ├── libft.c
│       ├── main.c
│       ├── monitor.c
│       ├── routine.c
│       ├── thread.c
│       └── utils.c
├── Makefile
└── README.md
```

### 빌드 방법
- `make` : 프로세스 버전과 스레드 버전 모두 빌드
- `make philo_proc` : 프로세스 버전만 빌드
- `make philo_thread` : 스레드 버전만 빌드
- `make clean` : 오브젝트 파일(.o) 삭제
- `make fclean` : 오브젝트 파일과 실행 파일 삭제
- `make re` : `fclean` 이후 다시 빌드

### 실행 방법
두 실행 파일은 다음 인자를 받습니다.

```bash
./philo_proc number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
./philo_thread number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers` : 철학자 수(1 이상)
- `time_to_die` : 마지막 식사 후 죽기까지 걸리는 시간(밀리초)
- `time_to_eat` : 식사하는 데 걸리는 시간(밀리초)
- `time_to_sleep` : 잠자는 데 걸리는 시간(밀리초)
- `number_of_times_each_philosopher_must_eat` : 선택 사항, 각 철학자가 최소 몇 번 식사해야 종료되는지 지정

### 실행 예시
#### 예시 1
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

#### 예시 2
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