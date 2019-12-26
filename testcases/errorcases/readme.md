这些都是含有错误的logo文件，用来测试程序的错误检查和错误提示功能。
   
一些测例会提示error，不能生成bmp文件。
一些测例会提示warning，但可以继续生成bmp文件。

testcase_1.logo:
    多余字符 "\"
testcase_2.logo:
    空文件
testcase_3.logo:
    多余字符
testcase_4.logo:
    无 END LOOP
testcase_5.logo:
    无 END FUNC，有提示
testcase_6.logo:
    参数不匹配
testcase_7.logo:
    数值超限，警告
testcase_8.logo:
    虽然忽略空白字符，但END LOOP和END FUNC不可以在两行
