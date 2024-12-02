# Basic-Interpreter-2024

## 目录

- [简介](#1)
  - [背景](#2)
  - [作业目标](#3)
- [作业要求](#4)
  - [基础任务](#5)
      - [下发文件](#6)
      - [解释器实现步骤及待实现文件介绍](#7)
      - [实现要求](#8)
  - [bonus:构造测试点](#9)
      - [测试点成功攻击他人程序](#11)
  - [bonus:增强程序鲁棒性](#10)
  - [bonus:四则运算计算器](#12)
- [须知](#13)
  - [Deadline](#14)
  - [本地评测](#15)
  - [OJ评测](#16)
  - [评分细则](#17)
- [负责助教](#18)
- [Special Thanks](#19)
- [Q&A](#20)


<a name="1"></a>
##  简介

<a name="2"></a>
### 背景

BASIC 是一门**解释性**编程语言，本次大作业要求你用 C++ 实现这个语言中的一些功能，来完成一个 Minimal 版本的 BASIC 解释器。

该解释器具有的功能有：

- **立即解释**某些语句并运行
- 执行特定控制语句
- 按照行数升序依次运行的大程序

<a name="3"></a>
### 作业目标

- 锻炼文档的阅读能力
- 初步了解解释器的设计
- 锻炼 git 的使用

<a name="4"></a>
## 作业要求

<a name="5"></a>
### 基础任务

<a name="6"></a>
#### 下发文件

```plain
├── Basic
│   ├── Basic.cpp
│   ├── Utils
│   │   ├── error.cpp
│   │   ├── error.hpp
│   │   ├── strlib.cpp
│   │   ├── strlib.hpp
│   │   ├── tokenScanner.cpp
│   │   └── tokenScanner.hpp
│   ├── evalstate.cpp
│   ├── evalstate.hpp
│   ├── exp.cpp
│   ├── exp.hpp
│   ├── parser.cpp
│   ├── parser.hpp
│   ├── program.cpp
│   ├── program.hpp
│   ├── statement.cpp
│   └── statement.hpp
├── StanfordCPPLib
├── Test
├── Basic-Demo-64bit
├── CMakeLists.txt
├── .gitignore
├── Minimal BASIC Interpreter - 2023.pdf
├── README.md
└── score.cpp
```

##### 需要学习使用的部分

```plain
├── Basic
│   ├── Utils
│   │   ├── error.cpp
│   │   ├── error.hpp
│   │   ├── strlib.cpp
│   │   ├── strlib.hpp
│   │   ├── tokenScanner.cpp
│   │   └── tokenScanner.hpp
```

这部分文件正常情况下你**不应修改**，如确信这部分文件有问题，请找出问题后向助教反馈。

`Basic/Utils/strlib.hpp` 和 `Basic/Utils/tokenScanner.hpp` 源于 StanfordCPPLib，是在 StanfordCPPLib 基础上进行过修改的版本，基本排除了由于编译器版本导致的问题，同时也基本修复了原代码的 memory leak 问题，使用方法与 StanfordCPPLib 中对应文件相同，请通过阅读文件中的注释，以及查阅官方文档 [The StanfordCPPLib package](https://cs.stanford.edu/people/eroberts/StanfordCPPLib/doc/index.html) 自行学习。

一般来说，你只需要使用 `Basic/Utils/strlib.hpp` 和 `Basic/Utils/tokenScanner.hpp` 。当然，如果你愿意的话，也可以自己使用 StanfordCPPLib 的其它文件(但请务必在使用前仔细阅读说明，并检查是否会造成内存泄漏)。

`error.hpp` 的使用请参考 [C++ 异常处理 - 菜鸟教程](https://www.runoob.com/cplusplus/cpp-exceptions-handling.html)。请务必熟悉代码中的异常处理方法，包括助教给出的代码。

注意：这是助教实现上的设计建议，你可以完全抛开现有框架自己实现，只需在 code review 时与助教说明即可。

##### 需要补充代码的部分

```plain
├── Basic
│   ├── Basic.cpp
│   ├── evalstate.cpp
│   ├── evalstate.hpp
│   ├── exp.cpp
│   ├── exp.hpp
│   ├── parser.cpp
│   ├── parser.hpp
│   ├── program.cpp
│   ├── program.hpp
│   ├── statement.cpp
│   └── statement.hpp
```

一般来讲，你只需补充 `Basic/Basic.cpp` `Basic/program.hpp` `Basic/program.cpp` `Basic/statement.hpp` `Basic/statement.cpp` 中的代码即可完成作业要求。当然，你也可以根据自己的需要修改其他文件。同时，你也应该仔细学习使用其他文件。

<a name="7"></a>
#### 解释器实现步骤及待实现文件介绍

**对于指令的介绍和要求详见 `Minimal-BASIC-Interpreter-2023.pdf`** 。

- ##### 读入指令并切片

目的： 将指令按照一定规律划分，以便于使用

实现方法： 学习使用 `Basic/Utils/tokenscanner` 来帮助你完成这一步

实现位置： `Basic/Basic.cpp`

- #####  指令合法性检查

目的： 检查获得的切片是否满足类型要求以及切片的组合方式是否满足指令格式

实现方法：学习使用 `Basic/Utils/tokenscanner` 来帮助你完成这一步

实现位置：`Basic/Basic.cpp`

e.g.

```
111         --> a valid integer
1a1         --> an invalid integer
```

```
END         --> a valid END command
END Hahaha  --> an invalid END command
```

- ##### 指令存储

目的：  用于实现大程序中的跳转指令，指令打印等等

实现方法： 使用数据结构，如 map， set 等，请自行设计

实现位置： `Basic/program.cpp, Basic/program.hpp`

- ##### 指令运行

目的： 执行指令

实现方法： 完成 `Basic/statment.hpp`中的类的设计和实现，在 `Basic/Basic.cpp` 中通过调用 `Basic/statment` 及其子类的 `execute` 函数实现

实现位置： `Basic/statment.cpp, Basic/statment.hpp`

【注：表达式的计算过程：

1.  `Basic/parser.hpp` 对表达式进行正确性检查，并将其解释成一棵表达式树
2.  `Basic/exp.hpp` 对表达式进行求值
3.  `Basic/evalstate.hpp` 存储程序运行过程的变量与值】


<a name="8"></a>
#### 实现要求

我们会进行基本的**鲁棒性检测**和**内存泄漏检测**，但是不进行性能检测，你只需要通过下发的数据点即可。

<a name="9"></a>
### Bonus:构造测试点

在本次作业中，我们要求各位同学在第 11 周周六 (11.30) 23:50 前向助教提供一份自己构造的数据输入。你要做的，是在**不看到**他人代码的情况下，尝试构造边界情况，攻破他人的程序。这份数据提交之后，原则上不应当再次修改。各位所提交的数据将会在标程中得到相应的输出，并且将作为该测试点的标准答案。各位所出的测试点我们将**不会**公开。关于各位构造的数据点，我们要求在 onlinejudge 上在 1s 内可以得到结果。为了防止出现可能的性能波动，我们并不希望各位构造较大的数据点。如果出现这种情况，助教可能会联系构造者重新构造。如果仍旧不符合要求，那么该测试点就不会在 onlinejudge 上进行测试。总结一下，我们希望测试点：

- 大小不超过 1M
- 不出现除了空格和换行符以外的不可见字符
- 不出现合法的HELP指令
- 在oj运行时间不超过 500ms
- 构造者可以通过自己的测试点


<a name="11"></a>
#### 测试点成功攻击他人程序

本部分共占 2% 的分数。你所构造的测试点每成功攻击一位同学的程序，就获得 0.5% 的分数，直到获得 2% 为止。此外，你必须保证能够通过自己构造的测试点。否则，成功攻击他人程序的这一部分得分为 0 分。

<a name="10"></a>
#### 增强程序鲁棒性

由于源库是祖传的，其鲁棒性远低于助教的想象。大家可以在CR时提出程序的缺陷，并且说明自己程序中的改进。这一部分占 1% 的分数。

<a name="12"></a>
### Bonus: 四则运算计算器

该作业在[Calculator](Bonus%2FCalculator)文件夹下，要求大家完成一个简单的四则运算计算器，同时大家也会对 std::any 这个语言特性，和 antlr 中的 visitor 方法有一个较为直观的理解。后者将大大有助于各位在之后的编译器项目中快速上手。

<a name="13"></a>
## 须知

<a name="14"></a>
### Deadline

第 12 周 周四 （12.5）18:30

<a name="15"></a>
### 本地评测

```
├── Basic-Demo-64bit
├── CMakeLists.txt
├── Test
└── score.cpp
```

#### 评测数据

`Test` 文件中的 100 个数据点，这些文件和oj中测评的数据点是相同的。

#### 评测原理

与标程对拍 （指进行相同输入看输出是否相同）

#### 标程

如果你用的是 wsl 或 linux ，请删除 `Basic-Demo-64bit_for_mac_to_be_rename` 。

如果你用的是 mac ，请删除 `Basic-Demo-64bit` ，并将 `Basic-Demo-64bit_for_mac_to_be_rename` 改名为 `Basic-Demo-64bit` 。

之后的步骤中我们认为你完成了此操作。

`Basic-Demo-64bit ` 是标程的可执行文件，你可以用命令行输入 `./Basic-Demo-64bit` 来运行它，看看 BASIC 解释器是如何工作的。

【注：

如果你用的不是 wsl ，而是 mac 或 linux ，在运行 `./Basic-Demo-64bit` 的时候，可能会出现 Permission denied 错误。这时候运行 `chmod +x Basic-Demo-64bit` 应当可以解决此问题。

如果你在wsl下运行 `./Basic-Demo-64bit` 的时候出现 Permission denied 错误，可以先运行 `chmod +x Basic-Demo-64bit` 来修改权限。】

#### 评测脚本使用方法

编译 `score.cpp`，然后运行编译产生的文件，即可。

e.g. 命令行中输入：

```
g++ -o score score.cpp
./score -f
```

即可进行本地测试。

你可以输入 `./score -h` 来查看帮助。

【注意：如果你修改了仓库中给出框架的文件结构，请相应修改 `score.cpp` 中的 `main` 函数中的相关文件路径，否则无法正常进行本地测试。】

<a name="16"></a>
### OJ 评测

你需要使用git进行版本管理和代码提交。比如，你的git仓库地址是 `Your_profile/Your_repo`，你只需要在OJ的提交页面中输入 `https://github.com/Your_profile/Your_repo` 即可。

**注意，你的可执行文件的名字必须为 `code`（如果你修改了Cmake，请务必保证可执行文件名仍为 `code` ）。**

测评文件内容默认是 Test 文件夹下提供的文件。这些文件和 oj 中测评的数据点是相同的。在这些测试点下，你的程序需要输出与标程相同的结果。

<a name="17"></a>
### 评分细则

- 基础任务 80%
  - 按 OJ 得分给分
- Code Review 20%
- 增强程序鲁棒性(bonus) 1%
- 测试点成功攻击他人程序 2% (bonus)
- 四则运算计算器 3% (bonus)

总得分大于 105% 按 105% 计。

<a name="18"></a>
## 负责助教

[@李林璋](https://github.com/Seven-Streams)，[@王思瀚](https://github.com/leowang000)，[@李方可](https://github.com/algebraic-arima)

<a name="19"></a>
## Special Thanks

感谢 22' ACM HenryHe0123, 22' ACM Irfnfnkemed 提供的文档 `Minimal-BASIC-Interpreter-2023.pdf` 。

<a name="20"></a>
## Q&A

### 构造测试点时允许数据溢出吗？
不允许超过int范围。如果出现，那么你的构造数据点bonus不会得分。

### "10 INPUT 10"是合法的吗？
合法。在这里第二个"10"被视作为一个变量名。但是，假设我们输入了5，**20 PRINT 10**的结果还会是**10**.也就是说，对于完全由数字组成的变量名，我们还是会优先将其解释为数字本身。

### 数字范围是多少？
int范围。不支持浮点数。输入浮点数也是不合法的。

### "010 INPUT 10"语句，在LIST指令时行号是否保持前导零？
要求保持原有格式。无需对行号格式做进一步修改。

### "PRINT-1+1"是合法的吗？
原则上是合法的。但是，考虑到同学们的工作量，在形如**PRINT**,**INPUT**等之后紧跟着表达式的行为是**未定义**的，也就是说形如**PRINTA**这样的语句，你可以选择解释成**PRINT A**，也可以认为这是个语法错误。
各位在构造数据点时，不应当使自己构造的数据点中包含这种情况。

### LET 后面的var = exp之间不加空格是合法的吗？
这类情况属于未定义行为。大家在构造测试点时要求这之间一定有空格。

### 行号和语句之间不加空格是...？
未定义。处理同上。

### 关于行首和行末空格？
未定义行为。处理同上。此外，手册上要求加空格的地方必须加空格，否则也是未定义行为。

### 变量命名规范？
必须由一个或多个数字、大小写字母组成，且不能是关键字（REM，LET，PRINT，INPUT，END，GOTO，IF，THEN，RUN，LIST，CLEAR，QUIT，HELP）。出现其他字符是未定义行为。变量名包含关键字也被视为是未定义行为。
