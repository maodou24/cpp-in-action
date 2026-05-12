# The C++ Programming Language Specification

## Types

A declaration is a statement that introduces a name into the program. It specifies a type for the
named entity

### Fundamental Types

| Type | Keyword |
| - | - |
| Boolean | bool |
| Character | char |
| Integer | int |
| 浮点数 | float |
| 双浮点型 | double |
| 无类型 | void |
| 宽字符型 | wchar_t |

### 类型修饰符

| 修饰符 | 描述 |
| - | - |
| signed | 符号类型 |
| unsigned | 无符号类型 |
| short | 短整型 |
| long | 长整型 |
| const | 常量，值不可修改 |
| volatile | 变量可能被意外修改，禁止编译器优化 |
| mutable | 类成员可以在 const 对象中修改 |

## 声明


`type var_name;`

| 声明修饰符 | 描述 | 示例 |
| - | - | - |
| * | 指针 | `char* name = "Njal";` |
| & | 引用 | `int& ref = x;` |
| *const | 指针常量 | - |
| *volatile | | |
| auto |  | `auto count = 1;` |
| [] | 数组 | `int arr[5] = {1, 2, 3, 4, 5};` |
| () | 函数 | `int func(int a, int b);` |
| -> |  | `ptr->name` |

```cpp
char ch;

auto count = 1;

const double pi {3.1415926535897};

const char* name = ""
```
