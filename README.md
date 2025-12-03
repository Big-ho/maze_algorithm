# 🧩 Maze Algorithm – Develop (C)

_프로그래밍 실습 – 개인 프로젝트_

## 소개

어떤 (NxN 사이즈) maze map을 넣어도 자동으로 맵을 축소시켜 미로 탈출 게임을 즐길 수 있게 해준다.

## 실행

### example 폴더 확인‼️

### 영상 확인‼️

### guide.md 확인‼️

---

## 🚀 현재 개발 진행 상황 (Progress)

### ✓ 구현 완료

- ✅ **Binary file → 2D array 변환**
- ✅ **Map Reduce Algorithm**
- ✅ **Thinning Algorithm**
- ✅ **Game Program Tool**
- ✅ **2D Map Display**
- ✅ **2D Game (Test Map)**
- ✅ **Image Reader**
- ✅ **Image → Binary File 변환**
- ✅ **BFS**
- ✅ **추격자 알고리즘**

---

### 😢 개발 실패

- ❌ **2D Game (Custom Map)**
- ❌ **3D Game (Prototype)**
- ❌ **3D Game (Release)**
- ❌ **Random Map 생성** (TBC)
- ❌ **Map Solver – DFS** (TBC)
- ❌ **Map Solver – BFS** (TBC)
- ❌ **Map Solver – A\*** (TBC)

---

## ⚙️ 코드 관련 설명

### 1. 개발 환경 및 도구

- 💻 **환경**: C17 · Clang 21.1.4 · macOS(M1) · VSCode
- 🧹 **코드 스타일**: `.clang-format` 규칙 기반 자동 포맷팅
- 🔍 **정적 분석**: `clang-tidy`로 버그, 메모리 누수, 스타일 검사

---

### 2. 네이밍 컨벤션 (Naming Convention)

#### 🔸 a. `is_` (Boolean Prefix)

값이 **true/false (1/0)** 의미를 가지는 함수 또는 변수에 사용합니다.

예:

```c
int is_valid;
int is_collision();
```

#### 🔸 b. `out_` (Output Parameter Prefix)

포인터 인자로 값을 출력하는 경우 사용합니다. (최근 코드에서는 미사용)

예:

```c
void get_size(int* out_width, int* out_height);
```
