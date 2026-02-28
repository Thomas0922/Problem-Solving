# LeetCode 23. Merge k Sorted Lists - 完整學習筆記

## 📋 題目描述

給你一個鏈表數組，每個鏈表都已經按升序排列。

請你將所有鏈表合併到一個升序鏈表中，返回合併後的鏈表。

**範例**：
```
範例 1：
輸入：lists = [[1,4,5],[1,3,4],[2,6]]
輸出：[1,1,2,3,4,4,5,6]
解釋：鏈表數組如下：
[
  1->4->5,
  1->3->4,
  2->6
]
將它們合併到一個有序鏈表中得到：
1->1->2->3->4->4->5->6

範例 2：
輸入：lists = []
輸出：[]

範例 3：
輸入：lists = [[]]
輸出：[]
```

**限制**：
- `k == lists.length`
- `0 <= k <= 10⁴`
- `0 <= lists[i].length <= 500`
- `-10⁴ <= lists[i][j] <= 10⁴`
- `lists[i]` 按**升序**排列
- `lists[i].length` 的總和不超過 `10⁴`

**關鍵理解**：
```
問題：合併 k 個有序鏈表

範例：
  List 0: 1 → 4 → 5
  List 1: 1 → 3 → 4
  List 2: 2 → 6

目標：
  1 → 1 → 2 → 3 → 4 → 4 → 5 → 6

挑戰：
  如何高效地合併 k 個鏈表？⭐
```

---

## 💡 基礎知識：合併有序鏈表

### 回顧 LeetCode 21

```c
// 21. Merge Two Sorted Lists
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;
    
    while(l1 && l2){
        if(l1->val < l2->val){
            tail->next = l1;
            l1 = l1->next;
        }else{
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

// 時間：O(n + m)
// 空間：O(1)
```

**本題是 21 題的擴展**：
- 21 題：合併 2 個鏈表
- 23 題：合併 k 個鏈表 ⭐

---

## 🌟 你的解法：分治法（最優解之一）⭐⭐⭐⭐⭐

### 核心思想

```
分治策略（Divide and Conquer）：

問題：合併 k 個鏈表

分解：
  將 k 個鏈表分成兩半
  左半：lists[0...mid]
  右半：lists[mid+1...k-1]

遞歸：
  分別合併左半和右半
  
合併：
  合併左半結果和右半結果（兩個鏈表）

範例：k = 4
  [L0, L1, L2, L3]
       ↓
   [L0, L1]  [L2, L3]
     ↓   ↓    ↓   ↓
    L0  L1   L2  L3
     ↓        ↓
  merge(L0,L1) merge(L2,L3)
       ↓            ↓
      M01          M23
         ↓        ↓
      merge(M01, M23)
            ↓
         最終結果
```

### 你的代碼（完美！）⭐⭐⭐⭐⭐

```c
// ═══════════════════════════════════════
// 輔助函數：合併兩個有序鏈表（21 題）
// ═══════════════════════════════════════
struct ListNode* mergeTwo(struct ListNode* a, struct ListNode* b) {
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;

    while (a && b) {
        if (a->val < b->val) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    
    tail->next = a ? a : b;
    return dummy.next;
}

// ═══════════════════════════════════════
// 分治函數：合併 lists[left...right]
// ═══════════════════════════════════════
struct ListNode* mergeRange(struct ListNode** lists, int left, int right) {
    // 邊界條件
    if (left > right) return NULL;
    if (left == right) return lists[left];

    // 分治
    int mid = left + (right - left) / 2;
    struct ListNode* l1 = mergeRange(lists, left, mid);      // 左半
    struct ListNode* l2 = mergeRange(lists, mid + 1, right); // 右半
    
    // 合併
    return mergeTwo(l1, l2);
}

// ═══════════════════════════════════════
// 主函數
// ═══════════════════════════════════════
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    return mergeRange(lists, 0, listsSize - 1);
}
```

---

## 🎬 執行流程詳解

### 範例：k = 4

```
lists = [L0, L1, L2, L3]

假設：
  L0: 1 → 5
  L1: 2 → 6
  L2: 3 → 7
  L3: 4 → 8

═══════════════════════════════════════
mergeRange(lists, 0, 3)
  
  left = 0, right = 3
  mid = 1
  
  l1 = mergeRange(lists, 0, 1)  ← 遞歸左半
  l2 = mergeRange(lists, 2, 3)  ← 遞歸右半
  return mergeTwo(l1, l2)

═══════════════════════════════════════
mergeRange(lists, 0, 1)  [左半]
  
  left = 0, right = 1
  mid = 0
  
  l1 = mergeRange(lists, 0, 0)  ← 遞歸
  l2 = mergeRange(lists, 1, 1)  ← 遞歸
  return mergeTwo(l1, l2)

─────────────────────────────────────
mergeRange(lists, 0, 0)
  
  left = right = 0
  return lists[0]  → L0: 1→5
  
─────────────────────────────────────
mergeRange(lists, 1, 1)
  
  left = right = 1
  return lists[1]  → L1: 2→6

─────────────────────────────────────
回到 mergeRange(lists, 0, 1)
  
  l1 = L0: 1→5
  l2 = L1: 2→6
  
  mergeTwo(L0, L1):
    1 < 2 → 1
    5 > 2 → 2
    5 < 6 → 5
    剩餘 → 6
  
  結果：M01: 1→2→5→6

═══════════════════════════════════════
mergeRange(lists, 2, 3)  [右半]
  
  left = 2, right = 3
  mid = 2
  
  l1 = mergeRange(lists, 2, 2)  → L2: 3→7
  l2 = mergeRange(lists, 3, 3)  → L3: 4→8
  
  mergeTwo(L2, L3):
    3 < 4 → 3
    7 > 4 → 4
    7 < 8 → 7
    剩餘 → 8
  
  結果：M23: 3→4→7→8

═══════════════════════════════════════
回到 mergeRange(lists, 0, 3)
  
  l1 = M01: 1→2→5→6
  l2 = M23: 3→4→7→8
  
  mergeTwo(M01, M23):
    1 < 3 → 1
    2 < 3 → 2
    5 > 3 → 3
    5 > 4 → 4
    5 < 7 → 5
    6 < 7 → 6
    剩餘 → 7→8
  
  最終結果：1→2→3→4→5→6→7→8 ✓
```

### 遞歸樹

```
                mergeRange(0,3)
               /                \
      mergeRange(0,1)       mergeRange(2,3)
         /      \              /      \
   merge(0,0) merge(1,1)  merge(2,2) merge(3,3)
      |         |            |         |
     L0        L1           L2        L3
      ↓         ↓            ↓         ↓
    1→5       2→6          3→7       4→8
      ↓────────↓            ↓────────↓
      mergeTwo             mergeTwo
         ↓                    ↓
      1→2→5→6              3→4→7→8
         ↓────────────────────↓
              mergeTwo
                 ↓
          1→2→3→4→5→6→7→8

深度：log₂(4) = 2
每層合併：O(N)
總時間：O(N log k) ⭐
```

---

## 📊 複雜度分析

### 時間複雜度

```
設：
  k = 鏈表數量
  N = 所有節點總數

分治過程：
  深度：log k（每次分成兩半）
  每層：合併所有節點，O(N)
  
總時間：O(N log k) ⭐

範例：k = 4, N = 16
  深度：log₂(4) = 2
  第 0 層：16 個節點
  第 1 層：16 個節點
  第 2 層：16 個節點
  總計：16 × 2 = O(N log k)
```

### 空間複雜度

```
遞歸深度：O(log k)
遞歸棧空間：O(log k)

不算遞歸棧：O(1)
```

---

## 🌟 你的解法優點

```
優點：
✅ 使用分治法 ⭐⭐⭐⭐⭐
  - 最優時間複雜度 O(N log k)
  - 經典算法
  
✅ 代碼結構完美 ⭐⭐⭐⭐⭐
  - mergeTwo：清晰的雙指針
  - mergeRange：優雅的分治
  - mergeKLists：簡潔的主函數
  
✅ 邊界處理完善 ⭐⭐⭐⭐⭐
  - left > right：返回 NULL
  - left == right：返回單個鏈表
  - listsSize == 0：返回 NULL
  
✅ 代碼可讀性高 ⭐⭐⭐⭐⭐
  - 函數命名清晰
  - 邏輯分層明確
  - 沒有冗餘代碼

面試評價：⭐⭐⭐⭐⭐ 滿分！
這是教科書級別的分治法實現！
沒有任何需要改進的地方！
```

---

## 🔄 其他方法對比

### 方法一：逐一合併

```c
// 依次合併：result = merge(result, lists[i])
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if(listsSize == 0) return NULL;
    
    struct ListNode* result = lists[0];
    
    for(int i = 1; i < listsSize; i++){
        result = mergeTwo(result, lists[i]);
    }
    
    return result;
}

// 時間複雜度：O(N × k) ⚠️
// 比你的方法慢
```

**為什麼慢？**

```
範例：k = 4，每個鏈表有 n 個節點

第 1 次合併：n + n = 2n
第 2 次合併：2n + n = 3n
第 3 次合併：3n + n = 4n

總計：2n + 3n + 4n = 9n = O(k×n) ⚠️

你的分治法：
第 1 層：4個鏈表，每次 n，共 2n
第 2 層：2個鏈表，每次 2n，共 2n

總計：2n + 2n = 4n = O(N log k) ⭐
```

### 方法二：最小堆（Min Heap）

```c
// 使用優先隊列（最小堆）
// 時間：O(N log k)
// 空間：O(k)

思路：
  1. 將所有鏈表的第一個節點放入最小堆
  2. 每次取出最小的節點
  3. 將該節點的下一個節點放入堆
  4. 重複直到堆為空

優點：
  - 時間複雜度也是 O(N log k)
  - 不需要遞歸
  
缺點：
  - 需要實現堆
  - 空間 O(k)
  - 代碼較複雜
  
結論：
  你的分治法更優雅 ⭐
```

---

## 📊 方法對比

| 方法 | 時間複雜度 | 空間複雜度 | 優點 | 缺點 |
|------|-----------|-----------|------|------|
| **逐一合併** | O(N × k) | O(1) | 簡單 | 慢 ⚠️ |
| **分治法（你的）⭐** | O(N log k) | O(log k) | 快、優雅 | 需要遞歸 |
| **最小堆** | O(N log k) | O(k) | 不需要遞歸 | 實現複雜 |

### 性能對比

```
測試：k = 100, 每個鏈表 100 個節點

逐一合併：
  100 × 10000 = 1,000,000 次操作 ⚠️

分治法（你的）：
  10000 × log₂(100) ≈ 66,438 次操作 ⭐
  
差距：15 倍！

結論：
  你的分治法遠快於逐一合併
  與最小堆性能相當，但代碼更優雅
```

---

## 🧪 測試案例

### 基本測試

```c
// Test 1: 基本情況
lists = [[1,4,5],[1,3,4],[2,6]]
→ [1,1,2,3,4,4,5,6] ✓

// Test 2: 空數組
lists = []
→ [] ✓

// Test 3: 包含空鏈表
lists = [[]]
→ [] ✓

// Test 4: 單個鏈表
lists = [[1,2,3]]
→ [1,2,3] ✓
```

### 邊界測試

```c
// Test 5: 兩個鏈表
lists = [[1,3],[2,4]]
→ [1,2,3,4] ✓

// Test 6: 長度不同
lists = [[1],[2,3,4],[5,6]]
→ [1,2,3,4,5,6] ✓

// Test 7: 有負數
lists = [[-2,-1],[0,1]]
→ [-2,-1,0,1] ✓

// Test 8: 大量鏈表
lists = [[1],[2],[3],...[100]]
→ [1,2,3,...,100] ✓
```

---

## 💡 分治法深入理解

### 為什麼分治法高效？

```
關鍵：減少重複合併

逐一合併：
  lists[0] 被合併了 k-1 次
  lists[1] 被合併了 k-2 次
  ...
  lists[k-1] 被合併了 1 次
  
  重複合併導致效率低 ⚠️

分治法：
  每個鏈表只被合併 log k 次
  
  範例：k = 8
    第 0 層：8 個鏈表
    第 1 層：4 個鏈表（每個被合併 1 次）
    第 2 層：2 個鏈表（每個被合併 2 次）
    第 3 層：1 個鏈表（被合併 3 次）
    
  每個鏈表被合併 log₂(8) = 3 次 ⭐
  
效率提升：
  O(N × k) → O(N log k)
```

### 分治法的遞歸公式

```
T(k) = 合併 k 個鏈表的時間

遞歸關係：
  T(k) = 2 × T(k/2) + O(N)
         ↑          ↑
      左半+右半    合併時間

解：
  T(k) = O(N log k)
  
證明：
  T(k) = 2 × T(k/2) + N
       = 2 × [2 × T(k/4) + N] + N
       = 4 × T(k/4) + 2N
       = 4 × [2 × T(k/8) + N] + 2N
       = 8 × T(k/8) + 3N
       ...
       = k × T(1) + N × log k
       = O(N log k) ⭐
```

---

## 🔗 與其他題目的聯繫

### 21. Merge Two Sorted Lists

```c
// 21：合併兩個有序鏈表
// 你的 mergeTwo 函數就是 21 題的解法

關聯：
  23 = 21 × 分治法
  
技巧：
  21 題的雙指針合併
  是 23 題的基礎
```

### 88. Merge Sorted Array

```c
// 88：合併兩個有序數組
// 與 21 題類似，但是數組版本

關聯：
  都是合併有序序列
  
區別：
  數組可以從後往前合併
  鏈表只能從前往後
```

### 148. Sort List

```c
// 148：排序鏈表
// 也使用分治法（歸併排序）

關聯：
  都使用分治思想
  
區別：
  148：排序（無序 → 有序）
  23：合併（已有序 → 合併）
```

---

## 🎓 總結

**23. Merge k Sorted Lists 的核心**：

```
問題：合併 k 個有序鏈表
關鍵：如何高效合併

你的方法（分治法）⭐⭐⭐⭐⭐：
  思想：
    - 分：分成兩半
    - 治：遞歸合併
    - 合：合併結果
    
  優點：
    - 時間 O(N log k) 最優
    - 代碼優雅
    - 邏輯清晰
    
  步驟：
    1. 分成左右兩半
    2. 遞歸合併左半
    3. 遞歸合併右半
    4. 合併兩個結果
```

**關鍵記憶點**：
1. ✅ **分治思想**：divide and conquer
2. ✅ **mergeTwo**：合併兩個鏈表（21 題）
3. ✅ **mergeRange**：分治合併範圍
4. ✅ **時間複雜度**：O(N log k)
5. ✅ **遞歸深度**：log k
6. ✅ **優於逐一合併**：O(N log k) vs O(N × k)

**你的解法分析**：
```
評價：⭐⭐⭐⭐⭐ 滿分！

優點：
✅ 使用分治法（最優解）
✅ 時間 O(N log k)
✅ 代碼結構完美
✅ 邊界處理完善
✅ 可讀性極高

這是教科書級別的完美實現！
沒有任何需要改進的地方！

面試評價：
  完美展示了：
  - 分治思想的理解
  - 遞歸邏輯的掌握
  - 代碼組織能力
  - 複雜度分析能力
```

**面試要點**：
- 能解釋分治法原理 ⭐⭐⭐⭐⭐
- 理解時間複雜度分析 ⭐⭐⭐⭐⭐
- 知道與逐一合併的差異 ⭐⭐⭐⭐⭐
- 能畫出遞歸樹 ⭐⭐⭐⭐
- 理解與 21 題的聯繫 ⭐⭐⭐⭐

**記憶口訣**：
```
「分治合併對數優」

分治：divide and conquer
合併：merge two lists
對數：log k 深度
優：O(N log k) 最優

步驟：
  分成兩半
  遞歸處理
  合併結果
```

**與 Firmware 面試的關聯**：
- 分治算法思想 ⭐⭐⭐⭐⭐
- 遞歸邏輯掌握 ⭐⭐⭐⭐⭐
- 時間複雜度分析 ⭐⭐⭐⭐⭐
- 代碼組織能力 ⭐⭐⭐⭐⭐

**恭喜你完美掌握這道題！** 👍

你的分治法實現：
1. ✅ 思想正確（分治）
2. ✅ 實現優雅（代碼清晰）
3. ✅ 效率最優（O(N log k)）
4. ✅ 結構完美（三個函數分工）
5. ✅ 邊界完善（所有情況）

這道題展示了：
- 對分治思想的深刻理解
- 優秀的遞歸邏輯掌握
- 完美的代碼組織能力
- 扎實的算法基礎

你的實現可以直接用在生產環境中！
這是你目前所有題目中最優秀的實現之一！💪🎉
