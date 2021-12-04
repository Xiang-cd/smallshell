# 程序设计基础大作业说明文档



根据需求文档, 进行以下架构的设计:

1. 框架整体是一个死循环，不断等待通过getline来阻塞监听用户的输入，每读取输入的一行，则处理相应的用户输入，处理为命令和参数的形式。
2. 对于读取到到每一行，先用正则表达式进行指令的分割（面向复合指令），再一次进行指令的选择调用。
3. 到一行指令执行完毕，再将strout输出到标准输出流中。
4. 







## 测试部分文档：

为了进行验证功能验证，我们严格按照作业要求文档进行测试样例的生成，以下一一介绍：

### 用户初始化部分：

1. 计算机名，用户名，根目录长度不超过固定长度100，如果超过，则报错，要求重新输入。
2. 由于根目录点存在性由用户保证，初始化阶段不对文件路径存在性进行验证。
3. 文件路径和文件名合法验证，如果出现非法字符，则报错，要求重新输入。
4. 由于作业要求文档对计算机名和用户名的格式没有进行限制，这里按照常规程序变量命名的规则，即标识符只能以字母和下划线开头，并且以字母，下划线，数字三种类型的字符组成。

为此我们进行以下样例点测试(同样类型的测试只进行一次)：

```shell
Machine Name:aaaaaaaaaabbbbbbbbbbaaaaaaaaaabbbbbbbbbbaaaaaaaaaabbbbbbbbbbaaaaaaaaaabbbbbbbbbbaaaaaaaaaabbbbbbbbbbc # 此时应当因为长度过长而报错
Machine Name:2abc # 因字母开头报错
Machine Name:a.bc # 因非法字符报错
Machine Name:a bc # 因包含空格报错
Machine Name:mac1_ # 合法,进入下一个输入
Root Directory:?_ # 非法字符报错
Root Directory:abc/ls # 非绝对路径报错
Root Directory:/xxy2.s-r # 合法输入,进入下一个输入
Login:usr #合法输入,进入命令行,等待指令
```

### echo命令验证:

不识别转义字符, 不识别引号, 通过直接输出相应的参数, 同时要验证`-n`和`--help`以及`--version`参数, 并且`-n`只识别紧跟`echo`的位置, 其他位置输入`-n`认为是字符串。`--help`识别后, 后续的字符不再输出, `--version`同理。为此我们进行以下样例的测试:

```shell
echo --help
echo --help -n hello # 不识别后续参数, 只输出帮助内容
echo hello world! #正常输出
echo -n hello  #不输出换行符
echo -n -n # 输出-n,带空行
echo --version # 输出 "homework for basic programming,version 0.1"
```

### 单指令参数分割部分:

通过识别指令内容, 调用相应的指令函数, 在个人版本的实现部分, 所有未实现的单个指令会依次输出所有参数以及`strin`以及`strout`的内容(`pwd`进行了单独处理, 详见下一节), 以此来验证输出的正确性, 如果没有指令match, 则报错。接下来以此遍历所有要求的指令:

```shell
diff --help -b -i a.txt b.txt
grep *B a.txt
tee -a a.txt
cat -b a.md
cp --help -n a.md b.txt
cd ..
pwd
la #报错
```

### 符合指令部分:

通过`echo`向`strout`中写入相应的字符, 在执行下一条指令时将`strout`的内容复制到`strin`中, 由每个指令中测试部分输出所有的参数和标注输入输出的情况来进行程序有效性的验证, 为了进行连续的输入输出转换, 执行`pwd`后会向`strout`中写入"pwd output"。

```shell
echo hello | echo hi # 应当输出"hi"
echo hello | tee  a.txt # tee 的strin中应该有"hello"
echo hello | pwd | grep ir - # 应当在pwd的strin中看到hello, 在grep 的strin 中看到"pwd output"
echo hello | pw | echo hello? # 根据老师建议,中途出错依旧继续执行指令
```

### 额外指令部分:

1. `cls`或者`clear`指令, 执行后会直接清空当前屏幕, 不考虑后续的参数。
2. `change` 指令, 改变shell的主题, 0为默认主题, 1为块状主题, 2为粉色主题。
3. `exit`指令, 不考虑后续参数, 退出程序。
4. `vim`指令, 通过系统调用打开vim编辑器, 可以接受和判断合法的文件名。

```shell
clear # 清空屏幕
change 1 # 切换为主题1
change 2 # 切换为主题2
vim a.txt # 进入vim
vim a?.txt # 错误文件名报错
```





