# LogoCompiler
程序设计基础大作业，实现仿Logo语言的一个编译器。

## 功能描述

通过一种称为 Logo 语言的东西，汇出一张 bmp 格式的图像。

类似：

```asm
@SIZE 1000 1000
@BACKGROUND 20 20 20
@POSITION 700 500  
COLOR 1 2 3

DEF x 100
DEF r 255
DEF g 255
DEF b 0
FUNC magic(step)
    DEF y 90
    LOOP 4
        MOVE step
        TURN y
    END LOOP
END FUNC

LOOP 15
    COLOR r g b
    CALL magic(x)
    TURN 20
    ADD x 30
    ADD r -3
    ADD g -12
    ADD b 13
END LOOP
```

输出：

![demo](https://github.com/TianhuaTao/LogoCompiler/blob/master/demo.png?raw=true)

更多例子请看 `testcases` 中的内容。
