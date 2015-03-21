% 字串
% c2251393
% 資訊之芽語法班 2015

# 字串是啥

## 情感上

一堆字母接起來的字詞或句子

這些是字串 : 

- "aaaa"

- "sprout"

- "sprout hwo bang bang"

- "suhorng how way"


## C++裡

字串 $\equiv$ $char$ 這個型別的陣列

ex :

```cpp
char a[11]; // a string
int b[125]; // not a string
char c; // not a string
bool d; // not a string 
```

# 字串宣告

## 像陣列一樣宣告

```cpp
char str[11];
```

## 原始人初始化

```cpp
char str[11];
str[0] = 'm';
str[1] = 'u';
str[2] = 'd';
str[3] = 'r';
str[4] = 'e';
str[5] = 'a';
str[6] = 'm';
str[7] = '\0'; // 宇宙戰艦級重要!!!!!!代表字串的結尾
```


## 還記得陣列嗎

```cpp
char str[11] = {'m', 'u', 'd', 'r', 'e', 'a', 'm', '\0'};
// 別忘記 '\0'
```

or

```cpp
char str[] = {'m', 'u', 'd', 'r', 'e', 'a', 'm', '\0'};
// str 會是有8個格子的char陣列
// 別忘記 '\0'
```

## 別忘了這是字串

```cpp
char str[11] = "mudream";
```

or

```cpp
char str[] = "mudream";
// str 有幾個元素呢？
```


# 字串IO

## 輸出

```cpp
char str[] = "suhorng how bang bang";
std::cout << str << std::endl; // 輸出:suhorng how bang bang
char str2[] = "mud\0dream";
std::cout << str2 << std::endl; // 輸出:mud
```

## 輸出(cont.)

```cpp
char str[] = "akaiN\0eko";
std::cout << str << std::endl; // 與下列三行等價
for(int i = 0; str[i] != '\0'; i++)
  std::cout << str[i];
std::cout << std::endl;
```

## 輸入

```cpp
char str[11];
std::cin >> str;// 輸入:abc bba sadad
std::cout << str << std::endl;// 輸出:abc
// str === {'a', 'b', 'c', '\0'}
```

# Exercise

## Prob.

輸入一行字串，計算她的長度並輸出他。

輸入的字串由小寫英文字母組成，長度最多$1000$。

## Sol.

```cpp
int ans = 0;
for(int i = 0; str[i] != '\0'; i++) ans++;
```

## Sol. 2

請先 `#include <cstring>`

```cpp
int ans = strlen(str);
```

# 一堆字串怎麼辦

## $char$的多維陣列

輸入$n$代表有$n$行字串要輸入。

```cpp
int n;
char str[111][111];
std::cin >> n;
for(int i = 0; i < n; i++)
  std::cin >> str[i];
for(int i = 0; i < n; i++)
  std::cout << str[i] << std::endl;
```

# ASCII

## 字元都是整數

因為現代電腦儲存資料都是二進位，就連字元也是。

所以需要一個把字元對應到整數的方法。

## examples

`'A' == 65, 'B' == 66,,,, 'Z' == 90`

`'a' == 97, 'b' == 98,,,, 'z' == 122`

`'0' == 48,,,, '9' == 57`

`'\0' == 0`

注意到某種神祕的連續關係

## 判斷英文字母

```cpp
if('a' <= str[i] && str[i] <= 'z')
  blahblahblah;
```

```cpp
if('A' <= str[i] && str[i] <= 'Z')
  blahblahblah;
```

## 判斷數字

```cpp
if('0' <= str[i] && str[i] <= '9')
  blahblahblah;
```

## 判斷字串結尾

```cpp
if(str[i] == 0)
  blahblahblah;
```

# 對字串做事情

## Caesar Cipher

傳說是古老西方神祕半島的老大隱藏軍令的方法。

把`a -> d, b -> e, c -> f,,,, x -> a, y -> b, z -> c`

輸入一個明文，請把他加密後輸出。

## Sol

```cpp
for(int i = 0; str[i] != '\0'; i++) {
  int nowCh = str[i]-'a';
  int newCh = (nowCh + 3) % 26;
  str[i] = newCh + 'a';
}
```


# 字串比較

## strcmp

請先`#include <cstring>`

用法 :

```cpp
char a[], b[];
strcmp(a, b); // > 0 如果a的字典序比b大
              // == 0 如果兩個字串一樣
              // < 0 如果a的字典序比b小
```

# 總結

##

- 字串是$char$的陣列
- 字串的後面要有結尾字元`'\0'`
- ASCII碼有神祕的連續性質
- `strcmp`回傳0代表兩個字串一樣
- `#include<cstring>`有很多東東可以用

