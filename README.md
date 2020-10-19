# LogoCompiler
程序设计基础大作业，实现仿Logo语言的一个编译器。

## 功能描述

通过一种称为 Logo 语言的东西，汇出一张 bmp 格式的图像。

类似：

```asm
@SIZE 1000 1000
@BACKGROUND 30 30 30
@POSITION 500	500  
COLOR 255 255 255
DEF step 1
LOOP 1000
	MOVE step
	TURN 9
	ADD step 1
END LOOP
```

输出：

![demo](https://github.com/TianhuaTao/LogoCompiler/blob/master/demo.png?raw=true)

更多例子请看 `testcases` 中的内容。
