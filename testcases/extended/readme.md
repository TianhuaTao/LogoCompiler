这些是额外的一些测例，测试了程序的各方面功能。
这些测例都是合法的，并且可能用到了程序的拓展功能。

测试用途：
testcase_1.logo:
    MOVE, TURN, COLOR基本测试
testcase_2.logo:
    MOVE, TURN, COLOR基本测试
testcase_3.logo:
    LOOP基本测试
testcase_4.logo:
    注释测试
testcase_5.logo:
    CLOAK测试
testcase_6.logo:
    ADD, DEF测试，负数支持
testcase_7.logo:
    变量测试
testcase_8.logo:
    函数测试
testcase_9.logo:
    画笔粗细调节
testcase_10.logo:
    函数互相调用测试
testcase_11.logo:
    综合测试
testcase_12.logo:
    前端分词测试，可以支持灵活的写法，忽略空白字符，不受换行限制(END FUNC和END LOOP除外)

此外，在logoGen文件夹中，有一个辅助工具logoGenerator.py，它可以把任意一张图片，转变为合法的logo文件。把该logo文件作为输入，LogoCompiler可以生成完全相同的图片。logo文件可能很大，但是LogoCompiler可以高效地执行它。

具体用法：
python3 logoGenerator.py Lenna.png > Lenna.logo
./logoCompiler Lenna.logo


