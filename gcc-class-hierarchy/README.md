# g++ 查看类内存布局

----

## 编译  
g++ -fdump-class-hierarchy main.cpp

生成文件main.cpp.002t.class
```c++
(省略系统库的类结构。。。。)
Vtable for Base
Base::_ZTV4Base: 3u entries
0     (int (*)(...))0
8     (int (*)(...))(& _ZTI4Base)
16    (int (*)(...))Base::Func

Class Base
   size=8 align=8
   base size=8 base align=8
Base (0x0x7f6c4e65cd80) 0 nearly-empty
    vptr=((& Base::_ZTV4Base) + 16u)

Vtable for Derive
Derive::_ZTV6Derive: 3u entries
0     (int (*)(...))0
8     (int (*)(...))(& _ZTI6Derive)
16    (int (*)(...))Derive::Func

Class Derive
   size=8 align=8
   base size=8 base align=8
Derive (0x0x7f6c4e4b42d8) 0 nearly-empty
    vptr=((& Derive::_ZTV6Derive) + 16u)
  Base (0x0x7f6c4e65cde0) 0 nearly-empty
      primary-for Derive (0x0x7f6c4e4b42d8)
```