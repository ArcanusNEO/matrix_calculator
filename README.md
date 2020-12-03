# 关于Matrix类
1. 宏定义
    + _MATRIX_H 用于判断matrix.h头文件是否已被包含
    
    + _MATRIX_EPS 规定浮点运算精度，输出精度为 -1 - lg(_MATRIX_EPS) 位小数

2. 成员变量
    + maxSize_定义行列最大大小

    + row_, col_定义行列大小

    + 二维数组a存储矩阵

3. 成员函数
    + 重载了 + - * = () 运算符，* 支持内积和外积，() 支持以matrix(x, y)引用形式访问元素，带越界检查，越界返回0或a[0][0]的引用。

    + inverse() 返回矩阵的逆矩阵。

    + self_inverse() 修改当前矩阵为逆矩阵，并返回当前矩阵的引用。

    + determinant() 返回当前矩阵的行列式。

    + reset(unsigned rowSize, unsigned colSize, double num) 会将矩阵初始化为行数rowSize，列数colSize，对角线上的数为num，其余为0的矩阵。默认rowSize = 0, colSize = 0, num = 0。
    
    + 构造函数支持与reset函数相同的参数，也接受另一个矩阵并复制。

    + transpose() 返回矩阵的转置矩阵。

    + row_size() 和 col_size() 分别返回行列大小

    + print() 使用std::cout向标准输出打印矩阵，第一行打印row_size col_size，接下来row_size行每行打印col_size 个矩阵元素，第i行第j个数对应matrix(i, j)。

    + read() 使用std::cin从标准输入读取矩阵，格式同print函数。

4. 错误处理
    + 使用std::cerr向标准错误打印错误信息并返回EXIT_FAILURE。

# 关于matrix_calculator
#### matrix_calculator是Matrix类的一个简单的启动器，仅支持命令行运行，配合选项-ASMmITD使用，不支持多选项。直接运行或传入错误的参数即可打印内置说明。

##### 示例：
> 1:
>> 输入  

>> matrix_calculator -I  
>>  4 4  
>>  1 2 3 4  
>>  5 6 7 8  
>>  9 8 7 6  
>>  5 4 3 2  

>> 将会得到输出  

>> 0  

> 2:
>> 输入  

>> matrix_calculator -M  
>>  4 4  
>>  1 2 1 0  
>>  0 2 0 1  
>>  4 0 0 0  
>>  5 1 1 2  
>>  4 4  
>>  0 0 0.25 0  
>>  0.2 0.4 0.2 -0.2  
>>  0.6 -0.8 -0.65 0.4  
>>  -0.4 0.2 -0.4 0.4  

>> 将会得到输出  

>>  1 0 0 0  
>>  0 1 0 0  
>>  0 0 1 0  
>>  0 0 -0 1  