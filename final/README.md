# LogoCompiler

THU homework project

小组成员：
陶天骅(组长)2017010255 计 81
左博伟 2019012025 数 92
周海刚 2019012058 数 93

基本功能完成情况：
功能完美实现能够实现以下语句并且符合题目说明文档的要求，例如：
DEF ADD MOVE TURN COLOR CLOAK
以及 循环语句：
LOOP [Value] ... END LOOP
函数调用语句：
CALL [NAME]([PARA 1],...,[PARA n])
函数定义语句：
FUNC [Name]([para 1],...,[para n])
...
END FUNC
各函数的功能符合题目文档中阐述的要求

拓展功能：
一.拓展函数：
调整画笔的粗细：PENWIDTH [Value]

说明：[Value]应该替换为一个数值常量或者是变量名，单位为像素。每次执行该语句时，画笔的粗细变为相应的粗细
例如
PENWIDTH 1
PENWIDTH X 其中 X 为已经定义的变量，否则会报错

二：程序特色（为什么选择我们！）

1.简洁的执行方式，没有制作简陋的图形界面，有的只有直接从命令行执行的程序本身，纯净可靠，专为了解计算机热爱极简主义的的您准备！

2.更高的自由度：我们允许您在进行 logo 语言的编辑当中插入单行注释，便于您的团队协作编译！

3.专业的回显设计，方便您在执行程序的同时能够看到程序的进行过程，使您产生前所未有的自豪感！

4.专业准确的报错信息，帮助您排查可能出现的错误，并且给您提供相应的可能错误提示，使得错误远离您的 logo 程序！

5.专业快速的绘图，使得您快速绘制工业级\*准确的图形变为可能！

6.我们是开源的！这会使得我们的受众变得更多，我们也欢迎您给我们的程序提出您的宝贵建议！

7.利用我们的内置函数，我们使用循环绘制了很多好看的图形可以作为您的参考！它们被放置在 outputs 文件夹下。

（\*实验数据表明：logocompiler 能够轻松应对市场上 90%以上的绘图需求，实际程序效果与执行的电脑有关）

三.说明： 1.对于输入的说明：
i)输入文件【代码内容】（即需要程序识别的内容）不允许输入非大小写字母，空格，回车，数字，下划线以外的文本，否则可能会报错
ii)输入文件名需要以.logo 结尾，否则会报错
iii)输入文件的操作：在终端处执行程序并在命令行后添加文件的位置，否则会报错
iv)输入文件中可以通过添加//来提供单行注释,但是当最后一行是注释的时候需要以换行结尾，否则会报错
v) 输入文件名不区分大小写字母
vi)输出文件储存于 src 上一层的 outputs 里面，输出文件名默认为 output.bmp

2.对于语法的说明：
i)代码前几行必须规定 size 等信息，否则会报错
ii)代码各单词之间只需要空格隔开即可
iii)代码不支持括号(在调用函数的时候除外)，甚至可能会报错，例如：(20)和 20 并不等价
iv)如果在文件中非必须的位置(例如 DEF 后面的两个位置)出现非关键词的大小写单词，会报错
v)变量名称区分大小写，并且不允许重复定义
vi)在主函数区域定义的变量属于全局变量，可以在 FUNC 定义当中使用，但是请注意以下事项：在 FUNC 里面定义的变量会屏蔽全局变量；在退出函数后局部变量将需要全局定义

3.对于句法的说明：
i)在 loop 循环语句当中，循环次数不能使用变量名,否则会报错
ii)在定义函数的语句当中可以定义在函数以外已经定义过的函数；并且定义函数的形式参数的名称可以在函数外部曾被定义
iii)LOOP 函数和 FUNC 函数都需要对应的 END 函数来结束运行，否则会报错
iv)程序不允许在定义函数当中定义函数
v)理论上来说可以定义无限多个函数

4.对于报错的说明：
i)NO INPUT FILE：没有在命令行后发现文件路径
ii)CANNOT OPEN THE FILE：文件名未输入正确或者是后缀错误
iii)cannot find variable X：表示无法找到名为 X 的变量
iv)Variable X is already defined：表示名为 x 的变量已经被定义过
v) Error at line 7: [ 说明在第 7 行出现了不合法的符号[
vi)Unexpected symbol at line 6: 出现了非法的字符
v)WTF R U TALKING'BOUT：nonsense:说明出现了无法识别的语句 nonsense,系统对于 nonsense 的出现零容忍，因此口吐芬芳（逃
vi)Runtime error: 一般是没有结束 loop 循环导致的或者是没有定义变量导致的

5.对于正常回显的说明：
i)pc[7]: TURN 100 degree
表示程序执行至第 7 个操作，第七步的内容是顺时针方向转动 100 度(注意如果此时操作的语句当中写的是 TURN X 其中 X 为已经定义的变量名，在回显中会自动变成其数值)
ii)degree state: 150
表示当前的角度为 150 度
iii)logical_location:[214.279,138.666]
当前的逻辑位置为[214.279,138.666]
iv)write file return value: 1
表示写文件成功
v)write to file output.bmp
写文件成功至 output.bmp
vi)ONE loop finished
表示一次循环完成
vii)return from 0global
主函数返回值为 0

分工情况：
陶天骅： 负责整个工程的框架设计并且亲自为另外两名成员讲解了有关知识；负责了解码器相关的代码设计；负责了变量相关代码的设计工作；以及 bug 的调试工作
左博伟：负责了画笔移动相关的代码设计；负责视频的制作工作
周海刚：负责了函数调用与定义有关代码设计；文档的撰写工作；bug 测试工作；