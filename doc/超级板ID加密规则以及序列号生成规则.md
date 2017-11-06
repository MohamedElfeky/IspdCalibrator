### 超级板ID加密规则
#### 加密字符集

```
/// 34进制加密顺序(此顺序不可改变)
static const std::map<int, std::string> tenTo34 = {
    {0, "0"},
    {1, "1"},
    {2, "2"},
    {3, "3"},
    {4, "4"},
    {5, "5"},
    {6, "6"},
    {7, "7"},
    {8, "8"},
    {9, "9"},
    {10, "A"},
    {11, "B"},
    {12, "C"},
    {13, "E"},
    {14, "D"},
    {15, "F"},
    {16, "G"},
    {17, "J"},
    {18, "H"},
    {19, "K"},
    {20, "L"},
    {21, "N"},
    {22, "M"},
    {23, "P"},
    {24, "Q"},
    {25, "R"},
    {26, "T"},
    {27, "S"},
    {28, "U"},
    {29, "V"},
    {30, "W"},
    {31, "Y"},
    {32, "X"},
    {33, "Z"},
};
```
#### `c++`算法实现
```
static std::string intToString(int32_t x) {
    std::stringstream ss;
    ss << x;

    std::string out;
    ss >> out;

    return out;
}

std::string decimalToAny(int32_t num, int32_t n) {
    std::string new_num_str = "";
    int32_t remainder;
    std::string remainder_str;
    while (num != 0) {
        remainder = num % n;
        if (remainder < 34 && remainder > 9) {
            remainder_str = tenTo34.at(remainder);
        } else {
            remainder_str = intToString(remainder);
        }
        new_num_str = remainder_str + new_num_str;
        num = num / n;
    }
    return new_num_str;
}

int32_t findKey(const std::string & value) {
    int32_t result = -1;
    for (auto elem : tenTo34) {
        if (elem.second == value) {
            result = elem.first;
        }
    }
    return result;
}

static std::string charToString(const char & ch) {
    std::stringstream ss;
    ss << ch;
    std::string res;
    ss >> res;
    return res;
}

int32_t anyToDecimal(const std::string & num, int32_t n) {
    double new_num = 0.0;
    int32_t nNum = num.length() - 1;
    for (auto elem = num.begin(); elem != num.end(); elem++) {
        int32_t tmp = double(findKey(charToString(*elem)));
        if (tmp != -1) {
            new_num = new_num + tmp*std::pow(double(n), double(nNum));
            nNum -= 1;

        } else {
            break;
        }
    }

    return static_cast<int32_t>(new_num);
}
```
#### 算法使用示例
```
std::cout << "encrypt: " << decimalToAny(1216889114, 34) << std::endl;
std::cout << "decrypt: " << anyToDecimal(decimalToAny(1216889114, 34), 34) << std::endl;
```

### 序列号生成规则：
|年    |周| 星期|版本|颜色|大小|ID  |
|:-----|---:|---:|---:|---:|---:|---:|
|2位|  2位| 1位  |2位 |2位 |2位 |[6,10]位|
|从2017开始|当年的第几周|周几（1-7）|见超级板类型定义|见超级板颜色定义|见超级板大小定义|见超级板ID加密规则|
:如：`01313000001A21NGB`
>表示：`2017`年的第`31`周的周`3`，版本类型为`D1`，颜色为`黑红`，大小为`M`，ID为`A21NGB`



