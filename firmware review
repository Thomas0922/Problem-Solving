# 韌體工程師面試重點大補帖
## C 語言 × OS × 嵌入式系統　全攻略速查

---

# 目錄總覽

| Section | 主題 | 涵蓋內容 |
|---------|------|----------|
| **SECTION 1** | C 語言關鍵字 | volatile、static、const、extern、inline、typedef vs #define |
| **SECTION 2** | Preprocessor 與 Macro | #define 常數、MIN 陷阱、Bit Macro、! vs ~、#error |
| **SECTION 3** | sizeof、型別陷阱、UB | sizeof 陷阱、Integer Promotion、UB 速查、struct padding、union |
| **SECTION 4** | 指標完整速查 | ++ 與 * 優先順序、指標陣列、複雜宣告解析、固定位址存取 |
| **SECTION 5** | Endianness 與 Bitwise | Little/Big Endian、偵測方法、XOR 技巧、大小寫轉換 |
| **SECTION 6** | 常見演算法與資料結構 | Linked List、Binary Search、質數篩法、Fibonacci |
| **SECTION 7** | 運算子特殊行為 | Ternary vs if-else、Maximum Munch、Short-Circuit、malloc(0) |
| **SECTION 8** | 中斷（Interrupt）與 ISR | 中斷概念、ISR 規則、ARM Cortex-M 中斷流程、經典錯誤 |
| **SECTION 9** | OS 核心概念 | Process/Thread、同步機制、Deadlock、Context Switch、Cache/MMU/TLB |
| **SECTION 10** | 記憶體佈局與管理 | 各區段速查、Startup Code、Compiler/Linker、malloc 替代方案 |
| **SECTION 11** | Ring Buffer / Double Buffer | Ring Buffer 設計、SPSC lock-free、Double Buffer 概念 |
| **SECTION 12** | 嵌入式通訊協定 | SPI vs I2C、UART、DMA vs Polling vs Interrupt |
| **SECTION 13** | RTOS 排程 | Task 狀態機、RMS 排程、Watchdog Timer |
| **SECTION 14** | Linux 開機流程 | BIOS/UEFI → Bootloader → Kernel → Init → User Space |
| **SECTION 15** | 精華速查卡（考前必看） | 陷阱總整理、Mutex vs Semaphore 使用場景 |

---

# SECTION 1　C 語言關鍵字

## ◆ volatile

作用：告訴編譯器「每次讀寫都要真正存取記憶體，不能用 register 快取」

使用場景：
- 硬體 register：`volatile uint32_t *const UART_SR = (volatile uint32_t *)0x40011000;`
- ISR 與主程式共享變數：`volatile bool data_ready = false;`
- 多執行緒共享變數（但仍需 mutex）

> ⚠ volatile ≠ atomic！flag++ 是 read-modify-write，volatile 不保護這三步的原子性

> ⚠ volatile 不防止 CPU 硬體亂序（out-of-order）！大量資料需要 memory barrier：\_\_DSB()

✓ volatile 只防編譯器優化；\_\_DSB() 防 CPU 亂序；mutex 防競態

**volatile square() 陷阱（經典面試題）：**

```c
int square(volatile int *ptr) {
  return *ptr * *ptr;   // ❌ 兩次讀取可能不同！
}
// 正確寫法：
int square(volatile int *ptr) {
  int a = *ptr;         // 只讀一次
  return a * a;
}
```

因為 \*ptr 是 volatile，編譯器每次都會去記憶體讀取，兩次讀取之間值可能被 ISR 改變，導致回傳的不是平方值。

## ◆ static

> ⚠ static global 改的是 linkage，不是 lifetime！global 本來就活到程式結束

| static 位置 | 作用 | 影響的是 |
|-------------|------|----------|
| local 函式內 | lifetime 延伸到程式結束，初始值只設一次 | lifetime（存活期） |
| global / 函式外 | 限制 linkage 為 internal，只有本檔可見 | linkage（連結性） |
| 函式前 | 限制函式為 internal linkage，外部無法呼叫 | linkage（連結性） |

**static 變數存放位置：**
- 有初值的 static 變數 → .data section
- 無初值（或初值=0）的 static 變數 → .bss section（啟動時清零）
- static storage duration 物件若未初始化，會被初始化為該型別的 0（C 標準 §6.7.11）

## ◆ const 指標四種組合

記憶法（從右往左讀）：p is a [const] pointer to [const] int

| 宣告 | 意義 |
|------|------|
| `int *p` | 可改值、可改指向（普通指標） |
| `const int *p` | 不能 \*p=x，但可 p=&other（data immutable） |
| `int * const p = &x` | 可 \*p=x，但不能 p=&other（pointer immutable） |
| `const int * const p` | 兩者都不能改（ROM register 用） |

```c
// 硬體 register 典型用法
volatile uint32_t * const GPIOA_ODR = (volatile uint32_t *)0x4001080C;
//       ↑ 每次真正存取     ↑ 位址固定不能改
const uint32_t * const UART_SR = (const uint32_t *)0x40011000;
//    ↑ 狀態暫存器只能讀，防止誤寫
```

**const 不等於 read-only memory：**
- 編譯器「可以」把 const（非 volatile）放進 .rodata，但並非一定
- 透過指標強制修改 const 變數是 UB，不同編譯器結果可能不同

## ◆ extern

作用：宣告一個變數或函式定義在其他翻譯單元（translation unit），讓 linker 去連結

```c
// file_a.c
int shared_counter = 0;       // 定義在 file_a

// file_b.c
extern int shared_counter;    // 宣告：去別的 .c 找定義
void inc(void) { shared_counter++; }
```

> ⚠ extern 只是宣告，不是定義，不會分配記憶體

## ◆ inline

作用：建議編譯器將函式展開到呼叫處，避免 function call overhead（push/pop/jump）

```c
static inline int max(int a, int b) { return a > b ? a : b; }
```

- inline 只是建議，編譯器可以忽略（尤其函式太大或遞迴時）
- 嵌入式常用 static inline 放在 .h，確保每個 .c 都有自己的副本
- 相比 macro：inline 有型別檢查、不會有 double evaluation 問題

## ◆ typedef vs #define

```c
#define dPS struct s *
typedef struct s * tPS;

dPS p1, p2;   // 展開 → struct s *p1, p2; → p2 不是指標！
tPS p3, p4;   // p3, p4 都是 pointer to struct s ✓
```

✓ typedef 會建立真正的型別別名，語義比 #define 更安全、更推薦

---

# SECTION 2　Preprocessor 與 Macro

## ◆ #define 常數與 UL 後綴

```c
#define SECONDS_PER_YEAR (60UL * 60UL * 24UL * 365UL)
```

- 不加分號、用括號包起來確保運算順序
- 命名慣例：全大寫，底線分隔
- 一年 = 31,536,000 秒，超過 16-bit unsigned int 範圍（65,535），需要 UL
- 用 UL（unsigned long）避免 signed/unsigned 混算陷阱

## ◆ MIN Macro 的 Double Evaluation 陷阱

```c
#define MIN(A, B) ((A) <= (B) ? (A) : (B))

least = MIN(*p++, b);
// 展開 → ((*p++) <= (b) ? (*p++) : (b))
// 若 *p <= b，*p++ 執行兩次！p 多移了一格
```

**修正方法（C23 typeof / GCC extension）：**

```c
#define MIN(a,b) \
  ({ typeof(a) _a = (a); \
     typeof(b) _b = (b); \
     _a <= _b ? _a : _b; })
```

## ◆ 正確的 Bit 操作 Macro

```c
#define SET_BIT(reg, bit)    ((reg) |=  (1U << (bit)))  // 無分號！
#define CLEAR_BIT(reg, bit)  ((reg) &= ~(1U << (bit)))
#define TOGGLE_BIT(reg, bit) ((reg) ^=  (1U << (bit)))
#define CHECK_BIT(reg, bit)  (((reg) >> (bit)) & 1U)    // 用 >> 不用 &=
```

> ⚠ CHECK_BIT 用 &= 是 CLEAR_BIT！每次呼叫都會把 bit 清掉！

> ⚠ Macro 結尾不加分號！否則 if-else 展開後 else 找不到對應的 if

> ⚠ Bit-field 是 NON-PORTABLE！高低位元順序由編譯器決定，不同架構結果不同

## ◆ ! vs ~ 的致命差異

| 運算子 | 說明 |
|--------|------|
| `!x`（Logical NOT） | 任何非零值 → 0；0 → 1　結果只有 0 或 1 |
| `~x`（Bitwise NOT） | 逐 bit 反轉　0xFF → 0x00（uint8_t） |

```c
uint8_t reg = 0xFF;
reg &= !0x20;   // ❌ !0x20 = !(32) = 0 → reg = 0x00（全清！）
reg &= ~0x20;   // ✅ ~0x20 = 0xDF    → reg = 0xDF（只清 bit5）
```

## ◆ ~0 可攜性：不要用 0xFFFF

```c
unsigned int compzero = 0xFFFF;  // ❌ 只在 16-bit int 正確
unsigned int compzero = ~0;      // ✅ 任何平台都是全 1
```

## ◆ Macro 優先順序陷阱

```c
#define SQ(x)   x * x          // ❌ 沒括號
#define SQ2(x)  ((x) * (x))    // ✅ 有括號

SQ(2+3)       → 2+3*2+3   = 11  （不是 25）
100 / SQ(5)   → 100/5*5   = 100 （不是 4）
SQ2(2+3)      → ((5)*(5)) = 25  ✓
100 / SQ2(5)  → 100/((5)*(5)) = 4 ✓
```

## ◆ #error 指令

作用：在編譯階段強制中斷，輸出錯誤訊息，用於檢查配置是否正確

```c
#ifndef TARGET_BOARD
  #error "TARGET_BOARD is not defined! Please specify target."
#endif
```

---

# SECTION 3　sizeof、型別陷阱、UB

## ◆ sizeof 陷阱

```c
char s1[] = "hello";  char *s2 = "hello";
sizeof(s1) = 6    // 陣列（含 \0）
sizeof(s2) = 8    // 指標大小（64-bit）
strlen(s1) = 5    // 不含 \0
```

```c
// 函式參數 array decay：
void f(int arr[]) { sizeof(arr); }  // = 8（指標！不是陣列）
// 解法：明確傳長度  void f(int *arr, size_t len)
```

**sizeof 與 signed 混算陷阱：**

```c
int d = -1;
#define ARR_SIZE (sizeof(arr)/sizeof(arr[0]))  // 回傳 size_t (unsigned)
if (d <= ARR_SIZE) { ... }  // d 被轉成 unsigned → 超大值 → 條件 false！
```

## ◆ Integer Promotion 與 Signed/Unsigned 混算

規則：小於 int 的型別（uint8_t, int8_t, char）運算前自動提升為 int。signed vs unsigned → signed 轉成 unsigned

```c
uint8_t a=0xFF, b=0x01;
uint8_t c = a + b;   // int(255)+int(1)=256，截斷→ 0
uint32_t d = a + b;  // = 256

uint32_t g=1;  int32_t h=-1;
g > h  →  h 轉成 uint32_t = 0xFFFFFFFF → g < h → false → 0
```

> ⚠ uint32_t 與 int32_t 比較：signed 轉成 unsigned！-1 變成 UINT_MAX

## ◆ Undefined Behavior（UB）速查

| 操作 | 是否 UB | 說明 |
|------|---------|------|
| arr[5] 超出邊界 | ✅ UB | stack corruption，難以察覺 |
| int overflow (signed) | ✅ UB | -O2 下編譯器假設不發生，可能刪掉判斷式 |
| unsigned overflow | ❌ 非 UB | well-defined wrap-around (mod 2^n) |
| 使用未初始化變數 | ✅ UB | 讀到垃圾值；-O2 可能整段被刪 |
| NULL pointer dereference | ✅ UB | ARM: BusFault / MemManage Fault |
| 回傳 local 變數的位址 | ✅ UB | stack frame 釋放後 dangling pointer |
| 透過指標修改 const 變數 | ✅ UB | 不同編譯器結果可能不同 |

## ◆ struct 對齊與 Padding 規則

規則：每個成員對齊到自身大小的倍數；struct 總大小對齊到最大成員大小

```c
struct A {
  char  a;       // offset 0, size 1
  // pad 3
  int   b;       // offset 4, size 4（需 4-byte 對齊）
  short c;       // offset 8, size 2
  // pad 2        → sizeof = 12
};

#pragma pack(1)  // 強制無 padding，用於網路封包解析
struct Pkt { uint8_t cmd; uint32_t data; };  // sizeof = 5
```

**#pragma pack(N) 規則：** 每個成員對齊到 min(自身大小, N) 的倍數

## ◆ union 用法與陷阱

union 所有成員共享同一塊記憶體，大小 = 最大成員的大小

```c
union Data {
  uint32_t  word;       // 4 bytes
  uint16_t  half[2];    // 4 bytes
  uint8_t   byte[4];    // 4 bytes
};  // sizeof = 4
```

常見用途：封包解析、暫存器存取、型別轉換（type punning）

---

# SECTION 4　指標完整速查

## ◆ ++ 與 * 優先順序

| 寫法 | 行為 |
|------|------|
| `*p++` | 取 \*p 的值，然後 p 指向下一個（後置++ 優先） |
| `(*p)++` | 取 \*p 的值，然後把 \*p 的值 +1（修改目標） |
| `*++p` | p 先 +1，再取新位置的值 |
| `++*p` | 把 \*p 的值先 +1，再回傳（修改目標） |

**完整範例：**

```c
char s[] = "0123456";
char *p = s;
*p++     → '0'，p 移到 s[1]
*(p++)   → '1'，p 移到 s[2]  （同 *p++）
(*p)++   → '2'，s[2] 變成 '3'，p 不動
*++p     → '3'，p 先到 s[3]
*(++p)   → '4'，p 先到 s[4]
++*p     → '5'，s[4] 從 '4' 變 '5'，p 不動
++(*p)   → '6'，s[4] 從 '5' 變 '6'，p 不動
```

## ◆ 指標與陣列

```c
int arr[3][3] = {{1,2,3},{4,5,6},{7,8,9}};

int *ptr_arr[3] = {arr[0], arr[1], arr[2]};  // 指標陣列
int (*arr_ptr)[3] = arr;  // 指向「3個int陣列」的指標
  arr_ptr++ 移動 3*4=12 bytes（整列）
  ptr_arr++ 移動 8 bytes（一個指標）

// 指標相減：
&arr[2] - &arr[0] = 2（單位是 element）
(char*)&arr[2] - (char*)&arr[0] = 24（bytes）
```

## ◆ 複雜宣告解析（C Declaration Parsing）

解析技巧：先找變數名，從內往外、從右往左讀，優先順序 () > [] > *

| 宣告 | 中文意義 |
|------|----------|
| `int *p` | p 是指向 int 的指標 |
| `int *p[10]` | p 是有 10 個元素的陣列，每個元素是 int 指標 |
| `int (*p)[10]` | p 是指標，指向一個有 10 個 int 的陣列 |
| `int (*p)(int)` | p 是指標，指向一個接受 int 參數、回傳 int 的函式 |
| `int (*p[10])(int)` | p 是有 10 個元素的陣列，每個元素是函式指標 |
| `void (*f[10])(void *)` | f 是 10 個函式指標的陣列，函式接受 void* 無回傳 |

**函式指標典型應用（狀態機）：**

```c
typedef void (*handler_t)(void);
handler_t state_table[] = { idle_handler, run_handler, err_handler };
state_table[current_state]();  // 透過陣列索引呼叫對應 handler
```

## ◆ 存取固定記憶體位址

```c
int *ptr;
ptr = (int *) 0x67a9;
*ptr = 0xaa55;

// 或一行寫法：
*(int * const)(0x67a9) = 0xaa55;
```

---

# SECTION 5　Endianness 與 Bitwise 技巧

## ◆ Little Endian vs Big Endian

**Endianness：** 多 byte 資料在記憶體中的排列順序。Little Endian 把 LSB 放在低位址；Big Endian 把 MSB 放在低位址。

- x86、ARM（預設）：Little Endian
- 網路協定（TCP/IP）：Big Endian（Network Byte Order）

```c
uint32_t val = 0xDEADBEEF;
uint8_t *p = (uint8_t *)&val;
//   低位址             高位址
// [ 0xEF | 0xBE | 0xAD | 0xDE ]  ← Little Endian
// [ 0xDE | 0xAD | 0xBE | 0xEF ]  ← Big Endian
```

## ◆ Endianness 偵測程式

```c
int check_endian(void) {
  uint32_t x = 1;
  return *((uint8_t *)&x);  // 1=Little, 0=Big
}
```

## ◆ XOR 應用速查

```c
// 性質：A^A=0, A^0=A, 可交換、可結合

// 找唯一不重複的數
int single = 0;
for (int i=0; i<n; i++) single ^= arr[i];

// 計算 bit 數（Brian Kernighan）
int count = 0;
while (n) { n &= (n-1); count++; }

// 判斷 2 的冪次
bool is_pow2(uint32_t n) { return n && !(n & (n-1)); }

// XOR 交換兩個變數
a ^= b; b ^= a; a ^= b;
```

## ◆ 大小寫轉換（Bitwise 技巧）

```c
// ASCII: 'A'=0x41, 'a'=0x61，差別只在 bit5
char to_lower(char c) { return c | 0x20; }
char to_upper(char c) { return c & ~0x20; }
char toggle_case(char c) { return c ^ 0x20; }
```

---

# SECTION 6　常見演算法與資料結構

## ◆ Linked List 操作

```c
// 反轉：三指標法
Node *reverse(Node *head) {
  Node *prev=NULL, *curr=head, *next;
  while (curr) {
    next       = curr->next;
    curr->next = prev;
    prev       = curr;
    curr       = next;
  }
  return prev;
}

// 找中間：快慢指標
Node *find_middle(Node *head) {
  Node *slow=head, *fast=head;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }
  return slow;
}

// 合併兩個已排序 linked list
Node *merge_sorted(Node *l1, Node *l2) {
  Node dummy = {0, NULL};
  Node *tail = &dummy;
  while (l1 && l2) {
    if (l1->val <= l2->val) { tail->next = l1; l1 = l1->next; }
    else { tail->next = l2; l2 = l2->next; }
    tail = tail->next;
  }
  tail->next = l1 ? l1 : l2;
  return dummy.next;
}
```

## ◆ Binary Search

```c
int binary_search(int *arr, int n, int target) {
  int lo = 0, hi = n - 1;
  while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;  // 防 overflow！
    if (arr[mid] == target) return mid;
    else if (arr[mid] < target) lo = mid + 1;
    else hi = mid - 1;
  }
  return -1;
}

// lower_bound：找第一個 >= target 的位置
int lower_bound(int *arr, int n, int target) {
  int lo = 0, hi = n;
  while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (arr[mid] < target) lo = mid + 1;
    else hi = mid;
  }
  return lo;
}
```

## ◆ 質數篩法（Sieve of Eratosthenes）

```c
// O(n log log n) 時間，O(n) 空間
void sieve(int n) {
  bool *is_prime = calloc(n+1, 1);
  memset(is_prime, true, n+1);
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i * i <= n; i++)
    if (is_prime[i])
      for (int j = i*i; j <= n; j += i)
        is_prime[j] = false;
}
```

## ◆ Fibonacci：Loop vs Recursion

```c
// Loop 版本：O(n) 時間，O(1) 空間
uint64_t fib_loop(int n) {
  if (n <= 1) return n;
  uint64_t a = 0, b = 1;
  for (int i = 2; i <= n; i++) { uint64_t t = a+b; a=b; b=t; }
  return b;
}

// 遞迴版本：O(2^n)！
uint64_t fib_rec(int n) {
  if (n <= 1) return n;
  return fib_rec(n-1) + fib_rec(n-2);
}
```

---

# SECTION 7　運算子特殊行為

## ◆ Ternary Operator vs if-else

Ternary operator 可讓編譯器產生 branchless 的 cmov 指令，避免 branch misprediction。在高頻迴圈中差異可達 2 倍以上。

## ◆ Maximum Munch Rule

```c
int a = 5, b = 7, c;
c = a+++b;  // 解析成 (a++) + b → c=12, a=6
```

## ◆ Short-Circuit Evaluation

```c
// A && B：若 A 是 false，B 不會被求值
// A || B：若 A 是 true，B 不會被求值
```

## ◆ malloc(0) 行為

```c
char *ptr = (char *)malloc(0);
// C 標準：implementation-defined
// GNU GCC (glibc)：回傳 non-NULL pointer
```

---

# SECTION 8　中斷（Interrupt）與 ISR

## ◆ 名詞定義

**中斷（Interrupt）：** 一種硬體或軟體機制，讓 CPU 暫停目前程式，轉而處理更緊急的事件。分為硬體中斷（GPIO、UART、Timer）和軟體中斷（SVC 指令）。

**ISR（Interrupt Service Routine）：** 中斷處理函式，設計原則是「越短越好」。

**NVIC（Nested Vectored Interrupt Controller）：** ARM Cortex-M 的中斷控制器，管理優先權、啟用/禁用、支援巢狀中斷。

**Vector Table（中斷向量表）：** 記憶體起始位址的函式指標陣列，每個 entry 對應一個 ISR 位址。

**Reentrant（可重入）：** 函式執行到一半被中斷，中斷中又呼叫該函式仍能正確運作。printf 不是 reentrant。

## ◆ ISR 絕對禁止事項

- ❌ 不能 printf / sprintf → 內部有 mutex、malloc，不是 ISR-safe
- ❌ 不能 xSemaphoreTake（等待型）→ ISR 不能 block
- ❌ 不能做浮點運算 → FPU context 可能未保存
- ❌ 不能做耗時操作 → ISR 要越短越好
- ❌ 不能動態 malloc → 非 ISR-safe
- ❌ 不能用 Mutex（有 ownership）

## ◆ ISR 正確做法（Deferred Interrupt Handling）

**Deferred Interrupt Handling：** ISR 只做最少工作（設 flag、放資料進 buffer、通知 task），複雜邏輯交給一般 task。

```c
void UART_RX_IRQHandler(void) {
  data_buf[idx++] = UART_DR;
  if (idx >= 64) {
    data_ready = true;
    BaseType_t woken = pdFALSE;
    xSemaphoreGiveFromISR(sem, &woken);
    portYIELD_FROM_ISR(woken);
  }
}
```

## ◆ ARM Cortex-M 中斷流程

```
外部中斷 → 硬體 push [xPSR|PC|LR|R12|R3|R2|R1|R0] 到 PSP
→ 切換到 MSP → Vector Table 讀 ISR 地址 → 執行 ISR
→ 結束：EXC_RETURN 寫入 PC → 硬體 pop 還原
```

NVIC Priority 數值越小 = 優先權越高（0 最高！）

## ◆ ISR 經典錯誤範例

```c
__interrupt double compute_area(double radius) {
  double area = PI * radius * radius;
  printf("Area = %f", area);
  return area;
}
// 錯誤：1.有回傳值 2.有參數 3.浮點運算 4.printf
```

---

# SECTION 9　OS 核心概念

## ◆ 基本名詞定義

**Process（行程）：** OS 中資源分配的基本單位。每個 process 擁有獨立的 virtual address space、file descriptors、register 狀態。互相隔離。

**Thread（執行緒）：** CPU 排程的基本單位，同一 process 的 thread 共享記憶體，但各有自己的 stack 和 register set。

**Context Switch（上下文切換）：** 暫停一個 task，保存其狀態，恢復另一個 task 的狀態並執行。

**Scheduler（排程器）：** 決定下一個要執行哪個 task 的模組。策略有 Round-Robin、Priority-based、Rate Monotonic。

**Race Condition（競態條件）：** 多個 thread 同時存取共享資源且至少一個寫入，結果取決於執行順序。

**Critical Section（臨界區域）：** 存取共享資源的程式碼段，同一時間只能一個 thread 進入。

## ◆ Process vs Thread

| 特性 | Process | Thread |
|------|---------|--------|
| 記憶體空間 | 獨立 | 共享同一 process |
| 建立成本 | 高 | 低（只需 stack + register） |
| Context Switch | 慢（需切換 page table） | 快 |
| 通訊 | IPC：pipe、shared memory、socket | 直接讀寫共享變數 |
| 安全性 | 高（隔離） | 低（一個 crash 拖垮全部） |

**IPC（Inter-Process Communication）：** Process 間的通訊機制，因各自記憶體獨立，需透過 OS 機制交換資料。常見：Pipe、Named Pipe、Message Queue、Shared Memory、Socket、Signal。

## ◆ 同步機制名詞解釋

**Mutex（互斥鎖）：** 同一時間只允許一個 task 持有。有 ownership：只有鎖住它的 task 才能解鎖。支援 Priority Inheritance。

**Semaphore（信號量）：** 計數器型同步機制。Binary Semaphore（0/1）常用於 ISR 通知 task。Counting Semaphore 限制同時存取數。沒有 ownership。

**Spinlock（自旋鎖）：** Busy-wait 同步機制，拿不到就一直迴圈等。適合多核、critical section 極短（< 1μs）的情境。

**Atomic Operation（原子操作）：** 不可被中斷的操作，硬體保證。例如 ARM LDREX/STREX。

## ◆ Mutex vs Binary Semaphore vs Counting Semaphore

| 特性 | Mutex | Binary Semaphore | Counting Semaphore |
|------|-------|------------------|--------------------|
| 初始值 | 1（unlocked） | 0 或 1 | 0 ~ N |
| Ownership | ✅ 有 | ❌ 無 | ❌ 無 |
| Priority Inheritance | ✅ 有 | ❌ 無 | ❌ 無 |
| ISR 中 give | ❌ 不行 | ✅ | ✅ |
| 用途 | 保護共享資源 | ISR 通知 task | 限制同時存取數 |

## ◆ Priority Inversion 與 Priority Inheritance

**Priority Inversion：** 高優先權 task 等待低優先權 task 持有的資源，中優先權 task 搶占低優先權 → 高優先權被間接阻塞。

**Priority Inheritance：** 系統自動把持有 mutex 的低優先權 task 提升到等待者的優先權，讓它盡快完成。

## ◆ Deadlock（死鎖）

**Deadlock：** 兩個以上 task 互相等待對方持有的資源，導致所有 task 都無法繼續。

**四個必要條件（缺一不可）：**

| 條件 | 說明 | 如何破壞 |
|------|------|----------|
| Mutual Exclusion | 資源一次只一個 task 持有 | 幾乎無法破壞 |
| Hold and Wait | 持有 A 時等待 B | try-lock with backoff |
| No Preemption | 資源不能被強奪 | 設 timeout |
| Circular Wait | A 等 B，B 等 A | 統一加鎖順序（最常用） |

## ◆ Race Condition 與解法

```c
// 解法（依輕量程度排序）：
// 1. disable_irq（單核最輕量）
// 2. atomic operation（硬體保護單一變數）
// 3. spinlock（多核短時間 busy-wait）
// 4. mutex（可 block，支援 priority inheritance）
```

## ◆ Context Switch 保存內容（ARM Cortex-M）

```
硬體自動 push：xPSR, PC, LR, R12, R3, R2, R1, R0
RTOS 軟體 push：R4~R11，若有 FPU：S0~S31, FPSCR
```

**TCB（Task Control Block）：** RTOS 為每個 task 維護的資料結構，存放 stack pointer、優先權、狀態。

**FPU（Floating Point Unit）：** 浮點運算硬體單元。Context switch 時需額外保存浮點暫存器。

## ◆ Cache、MMU、TLB、Virtual Memory

**Cache（快取）：** CPU 與主記憶體間的高速緩存，利用 temporal / spatial locality 加速存取。L1→L2→L3。Write-through vs Write-back。

**Cache Coherence（快取一致性）：** 多核系統中確保各核 cache 一致。MESI Protocol。

**MMU（Memory Management Unit）：** 負責 Virtual Address → Physical Address 轉換 + 記憶體保護。

**TLB（Translation Lookaside Buffer）：** Page Table 的快取。TLB Miss → 查 Page Table。Context Switch 時需 flush。

**Page Fault：** 虛擬頁面不在 RAM 中 → OS 從磁碟載入 → 更新 Page Table → 重新執行。

**Virtual Memory 優點：** 隔離保護、超過實體 RAM 的位址空間、簡化管理、支援 memory-mapped I/O。

---

# SECTION 10　記憶體佈局與管理

## ◆ 各區段速查

| 區段 | 存什麼 | 屬性 |
|------|--------|------|
| .text | 程式碼、函式 | r-x Flash |
| .rodata | 字串常數、const 全域 | r-- Flash |
| .data | 有初值非零全域、static | rw- RAM（Flash 複製） |
| .bss | 無初值或=0 的全域 | rw- RAM（清零） |
| Stack | local 變數、參數、return addr | rw- RAM（向下↓） |
| Heap | malloc 動態配置 | rw- RAM（向上↑） |

## ◆ Startup Code（進 main() 前）

1. 從 Flash 把 .data 複製到 RAM
2. 把 .bss 清零
3. 初始化 C++ 靜態物件（若有）
4. 呼叫 main()

## ◆ Compiler vs Linker

**Compiler：** C 原始碼 → object file (.o)。預處理→語法分析→優化→組譯。

**Linker：** 多個 .o + library → 可執行檔。解析 symbol reference、重定位。

## ◆ Static Linking vs Dynamic Linking

**Static Linking：** 編譯時把 library 複製進執行檔。大但獨立。

**Dynamic Linking：** 執行時載入 .so/.dll。小但需確保 library 存在。

| 特性 | Static | Dynamic |
|------|--------|---------|
| 時機 | 編譯時 | 執行時 |
| 檔案 | .a | .so / .dll |
| 執行檔大小 | 大 | 小 |
| 更新 library | 需重編 | 替換 .so |
| 嵌入式 | ✅ 常用 | 較少 |

## ◆ 嵌入式不用 malloc 的原因

- Fragmentation：碎片化
- Non-deterministic：時間不確定
- 無保護：heap 溢出到 stack

替代：Memory Pool（O(1) alloc/free）

**FreeRTOS 5 種 heap：** heap_1（只 alloc）、heap_2（best-fit 不合併）、heap_3（包裝 stdlib）、heap_4（first-fit+合併，最常用）、heap_5（多塊記憶體）

---

# SECTION 11　Ring Buffer / Double Buffer

**Ring Buffer：** 固定大小的 FIFO 佇列，head/tail 索引繞回形成環形。常用於 ISR 與主程式間傳資料。

**Double Buffer：** 兩塊 buffer 交替，一塊寫一塊讀，永不衝突。

## ◆ Ring Buffer 設計

```c
#define N 16
typedef struct {
  uint8_t buf[N];
  volatile uint32_t head;  // producer
  volatile uint32_t tail;  // consumer
} RingBuf;

bool rb_full(RingBuf *r)  { return (r->head+1)%N == r->tail; }
bool rb_empty(RingBuf *r) { return r->head == r->tail; }

// push：先寫資料，再更新 head
bool rb_push(RingBuf *r, uint8_t d) {
  if (rb_full(r)) return false;
  uint32_t next = (r->head+1) % N;
  r->buf[r->head] = d;   // 1. 先寫
  r->head = next;         // 2. 再更新
  return true;
}
```

**SPSC（Single Producer Single Consumer）：** head 只被 producer 改，tail 只被 consumer 改 → 不需 lock。

## ◆ Double Buffer

```c
volatile uint8_t active = 0;
uint8_t buf[2][64];
void isr_rx(uint8_t byte) {
  buf[active][fill++] = byte;
  if (fill >= 64) { ready=true; active=1-active; fill=0; }
}
```

---

# SECTION 12　嵌入式通訊協定

## ◆ 名詞定義

**UART：** 非同步串列通訊，TX/RX 兩條線，無 clock，需約定 baud rate。用於 debug、GPS、藍牙。

**SPI：** 同步 4 線（MOSI/MISO/SCLK/CS），全雙工，高速（數十 MHz）。

**I2C：** 同步 2 線（SDA/SCL），半雙工，7-bit 位址區分 slave。省線但慢。

**DMA（Direct Memory Access）：** 硬體機制讓周邊直接搬資料到記憶體，不需 CPU 逐 byte 搬。CPU 只需設定一次，傳完 DMA 發中斷通知。

## ◆ SPI vs I2C

| 特性 | SPI | I2C |
|------|-----|-----|
| 線數 | 4 | 2 |
| 速度 | 數十 MHz | 100k/400k/3.4M |
| 全雙工 | ✅ | ❌ |
| 多 slave | 獨立 CS | 位址區分 |

**SPI 四種 Mode：**

| Mode | CPOL | CPHA | 說明 |
|------|------|------|------|
| 0 | 0 | 0 | Rising edge 採樣（最常見） |
| 1 | 0 | 1 | Falling edge 採樣 |
| 2 | 1 | 0 | Falling edge 採樣 |
| 3 | 1 | 1 | Rising edge 採樣 |

**I2C 細節：** Start=SCL High 時 SDA 下降沿、ACK/NACK、Clock Stretching

## ◆ DMA vs Polling vs Interrupt

| 方式 | CPU 佔用 | 適用 |
|------|----------|------|
| Polling | 100% | Debug、1~2 bytes |
| Interrupt | 中（中斷 overhead） | 中等速度 |
| DMA | 幾乎 0 | 大量資料 |

---

# SECTION 13　RTOS 排程

**RTOS（Real-Time Operating System）：** 專為即時系統設計，保證在 deadline 內完成 task。排程延遲低且可預測。常見：FreeRTOS、Zephyr、RT-Thread。

## ◆ Task 狀態機

```
Blocked（等 semaphore/delay）
    ↕
  Ready ◄── Created
    ↕
  Running
```

## ◆ RMS（Rate Monotonic Scheduling）

周期越短 → 優先權越高。CPU 利用率上限：U ≤ n(2^(1/n) - 1)

| n | 上限 |
|---|------|
| 1 | 100% |
| 2 | 82.8% |
| 3 | 78.0% |
| ∞ | ln2 ≈ 69.3% |

## ◆ Watchdog Timer

**Watchdog Timer：** 硬體計時器，需定期餵狗。軟體 crash 沒餵 → 系統重置。

- ❌ 不能在 ISR 餵
- ❌ 不能在 while(1) 最外層餵
- ✅ 只有所有 task 都成功才餵

---

# SECTION 14　Linux 開機流程

**完整流程：Power On → Firmware → Bootloader → Kernel → Init → User Space**

## ◆ Firmware（BIOS / UEFI）

**BIOS：** 傳統 firmware，POST 自檢 → 從 MBR 載入 bootloader。限制 2TB。

**UEFI：** 現代替代品，支援 GPT、Secure Boot、從 ESP 載入 .efi。

## ◆ Bootloader（GRUB2 / U-Boot）

**Bootloader：** 初始化硬體 → 載入 kernel 到 RAM → 跳入 kernel。

**U-Boot：** 嵌入式最常用。SPL → DDR 初始化 → 完整 U-Boot → 載入 Kernel + DTB。

**Device Tree：** 描述硬體資訊的資料結構，讓同一 kernel 支援不同板子。

## ◆ Kernel 啟動

解壓縮 → 初始化 CPU/MMU/中斷 → 掛載 initramfs → 驅動初始化 → 掛載 rootfs → PID 1

**initramfs：** 暫時的 RAM 檔案系統，提供掛載真正 rootfs 前需要的驅動。

## ◆ Init（PID 1）

**Init：** 第一個 user-space process。SysVinit（依序慢）、systemd（並行快）、BusyBox init（嵌入式輕量）。

## ◆ 嵌入式流程（ARM）

```
Power On → BootROM → SPL(SRAM) → U-Boot(DDR)
→ Kernel + DTB → rootfs → /sbin/init → 應用程式
```

---

# SECTION 15　精華速查卡（考前必看）

## ◆ 面試陷阱總整理

| 陷阱 | 正確答案 |
|------|----------|
| CHECK_BIT 用 &= 還是 >>? | `(reg >> bit) & 1U`　用 &= 是 CLEAR！ |
| Macro 結尾要加 ; 嗎？ | 不加！ |
| !0xFF = ? | 0 |
| ~uint8_t 0xFF = ? | int(0xFFFFFF00)！需 cast |
| volatile 保證 atomic？ | 不！需要 mutex |
| ISR 能 xSemaphoreTake？ | 不能！用 GiveFromISR |
| static global 改什麼？ | linkage，不是 lifetime |
| uint32_t g=1; int32_t h=-1; g>h? | false（-1→UINT_MAX） |
| Little Endian p[0]? (0xDEADBEEF) | 0xEF |
| NVIC 數值越小？ | 優先權越高 |
| MIN(\*p++, b) macro？ | double evaluation |
| volatile \*ptr; \*ptr \* \*ptr？ | 兩次讀取可能不同 |
| 0xFFFF 是 ~0？ | 只在 16-bit！用 ~0 |
| malloc(0)？ | impl-defined，GCC 回傳 non-NULL |

## ◆ Mutex vs Semaphore 場景

| 場景 | 用什麼 |
|------|--------|
| 保護 linked-list（< 1μs） | disable_irq / Spinlock |
| 限制最多 3 個 task | Counting Semaphore |
| ISR 通知 task | Binary Semaphore |
| 兩 task 同時寫 UART（5ms） | Mutex |
| 單核 2 行 register 操作 | disable_irq |
