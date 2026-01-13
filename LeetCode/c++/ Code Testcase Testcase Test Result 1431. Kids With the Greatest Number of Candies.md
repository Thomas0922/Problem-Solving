# 學習筆記：LeetCode 1431. Kids With the Greatest Number of Candies

## 1. 題目說明

**目標**：判斷每個孩子在拿到額外糖果後，是否能成為擁有最多糖果的孩子。

**輸入**：
* `candies`：每個孩子目前擁有的糖果數量
* `extraCandies`：額外可分配的糖果數量

**輸出**：布林陣列，表示每個孩子加上 `extraCandies` 後是否 >= 當前最大值

**範例**：
```
輸入: candies = [2,3,5,1,3], extraCandies = 3
輸出: [true,true,true,false,true]
解釋: 
- 孩子 0: 2 + 3 = 5 (等於最大值 5) ✓
- 孩子 1: 3 + 3 = 6 (大於最大值 5) ✓
- 孩子 2: 5 + 3 = 8 (大於最大值 5) ✓
- 孩子 3: 1 + 3 = 4 (小於最大值 5) ✗
- 孩子 4: 3 + 3 = 6 (大於最大值 5) ✓
```

---

## 2. 原始解法

```cpp
class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int max = candies[0];
        vector<bool> result;
        
        // 第一次遍歷：找出最大值
        for(int i = 0; i < candies.size(); i++){
            if(max <= candies[i]) max = candies[i];
        }
        
        // 第二次遍歷：判斷每個孩子是否能達到最大值
        for(int j : candies){
            result.push_back((extraCandies + j) >= max);
        }
        
        return result;
    }
};
```

### ⚠️ 可改進之處

#### 1. 變數命名衝突風險
```cpp
int max = candies[0]; // 可能與 std::max 衝突
```
雖然 `max` 不是 C++ 關鍵字，但 `std::max` 是常用函式，容易造成混淆。

**建議改名**：`maxCandies` 或 `maxValue`

```

---

## 3. 效能分析

| 項目 | 原始解法 |
|------|---------|
| **時間複雜度** | $O(N) |
| **空間複雜度** | $O(N) |

**說明**：
* **時間**：兩次遍歷陣列，$O(N) + O(N) = O(2N) = O(N)
* **空間**：result 陣列需要 $O(N) 空間（回傳值不計入）

---

## 4. 優化解法

### ✅ 解法 A：使用 STL 找最大值

使用 `<algorithm>` 的 `*max_element` 讓程式碼更簡潔。

```cpp
#include <algorithm>

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        // 使用 STL 找最大值（更直觀）
        int maxCandies = *max_element(candies.begin(), candies.end());
        
        vector<bool> result;
        result.reserve(candies.size()); // 預先配置空間
        
        for (int candy : candies) {
            result.push_back(candy + extraCandies >= maxCandies);
        }
        
        return result;
    }
};
```

**優點**：
* 語意清晰：`max_element` 直接表達「找最大值」的意圖
* 避免命名衝突
* 加上 `reserve()` 減少記憶體重新配置

---

### ✅ 解法 B：使用 `transform` 函式式風格

使用 STL 演算法 `transform` 搭配 Lambda 表達式。

```cpp
#include <algorithm>
#include <vector>

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int maxCandies = *max_element(candies.begin(), candies.end());
        
        vector<bool> result(candies.size()); // 直接建立指定大小的陣列
        
        // transform 函數說明：
        // transform(輸入起點, 輸入終點, 輸出起點, 轉換函數)
        // 
        // 參數說明：
        // 1. candies.begin()     - 輸入範圍的起點
        // 2. candies.end()       - 輸入範圍的終點
        // 3. result.begin()      - 輸出位置的起點
        // 4. Lambda 表達式       - 定義如何轉換每個元素
        //
        // Lambda 捕獲列表 [maxCandies, extraCandies]：
        // - 以「值捕獲」的方式將外部變數傳入 Lambda
        // - 這兩個變數在 Lambda 內部可以直接使用
        //
        // Lambda 參數 (int candy)：
        // - 代表 candies 中的每一個元素
        // - transform 會自動遍歷，依序傳入每個值
        //
        // 執行流程：
        // candies[0] -> Lambda -> result[0]
        // candies[1] -> Lambda -> result[1]
        // ...
        // candies[n] -> Lambda -> result[n]
        
        transform(candies.begin(), candies.end(), result.begin(),
                  [maxCandies, extraCandies](int candy) {
                      return candy + extraCandies >= maxCandies;
                  });
        
        return result;
    }
};
```

**transform 等價的傳統寫法**：
```cpp
// 以下程式碼與上面的 transform 完全等價
for (int i = 0; i < candies.size(); i++) {
    int candy = candies[i];  // 對應 Lambda 參數
    result[i] = candy + extraCandies >= maxCandies;  // 對應 Lambda 回傳值
}
```

**優點**：
* 函式式程式設計風格，程式碼更聲明式（Declarative）
* 避免手動管理迴圈索引，減少 off-by-one 錯誤
* 適合對 STL 熟悉的開發者
* 可讀性高：清楚表達「將陣列 A 轉換成陣列 B」的意圖

**補充說明**：
* `transform` 是 `<algorithm>` 標頭檔中的函數
* Lambda 表達式格式：`[捕獲列表](參數列表) { 函數本體 }`
* 捕獲方式：
  - `[var]`：以值捕獲（複製）
  - `[&var]`：以參考捕獲
  - `[=]`：以值捕獲所有外部變數
  - `[&]`：以參考捕獲所有外部變數

---

### ✅ 解法 C：一次初始化結果陣列（最推薦）

```cpp
#include <algorithm>

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int maxCandies = *max_element(candies.begin(), candies.end());
        
        // 直接建立指定大小的陣列，避免 push_back 開銷
        vector<bool> result(candies.size());
        
        for (int i = 0; i < candies.size(); i++) {
            result[i] = candies[i] + extraCandies >= maxCandies;
        }
        
        return result;
    }
};
```

**優點**：
* 直接建立固定大小陣列：`vector<bool> result(candies.size())`
* 比 `reserve() + push_back()` 更高效
* 使用索引存取，效能最佳

---


## 6. 常見錯誤

### ❌ 錯誤一：未處理空陣列

```cpp
int max = candies[0]; // 如果 candies 為空會崩潰！
```

**修正**：加入邊界檢查
```cpp
if (candies.empty()) return {};
```

### ❌ 錯誤二：變數命名衝突

```cpp
int max = candies[0]; // 與 std::max 可能衝突
```

**修正**：使用更明確的名稱
```cpp
int maxCandies = candies[0];
```

### ❌ 錯誤三：比較運算子錯誤

```cpp
result.push_back(extraCandies + j > max); // 應該是 >= 不是 >
```

題目要求「大於等於」，使用 `>` 會漏掉「等於」的情況。

---

## 7. 總結與建議

### 🎯 你的解法已經很好！

你的核心邏輯完全正確，只需要小幅優化：

1. **立即可改進**：
   ```cpp
   // 改名避免混淆
   int maxCandies = candies[0];
   
   // 預配置空間
   vector<bool> result;
   result.reserve(candies.size());
   ```

2. **進階優化**：
   ```cpp
   // 使用 STL + 預分配陣列
   int maxCandies = *max_element(candies.begin(), candies.end());
   vector<bool> result(candies.size());
   ```

### 📚 學習重點

1. ✅ **善用 STL 演算法**：`max_element`、`transform` 讓程式碼更簡潔
2. ✅ **記憶體管理**：`reserve()` 或直接初始化大小避免動態擴展
3. ✅ **變數命名**：避免與標準庫函式衝突
4. ✅ **邊界檢查**：考慮空陣列等極端情況

---

## 8. 推薦的最終版本

結合可讀性與效能的平衡寫法：

```cpp
#include <algorithm>

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        // 處理邊界情況
        if (candies.empty()) return {};
        
        // 使用 STL 找最大值
        int maxCandies = *max_element(candies.begin(), candies.end());
        
        // 預分配結果陣列
        vector<bool> result(candies.size());
        
        // 判斷每個孩子
        for (int i = 0; i < candies.size(); i++) {
            result[i] = candies[i] + extraCandies >= maxCandies;
        }
        
        return result;
    }
};
```

**時間複雜度**：$O(N)
**空間複雜度**：$O(N)$（回傳值不計）  
**特點**：清晰、高效、穩健 ✨
