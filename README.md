# InputStream 类

这是一个用于处理串行通信的类，提供了接收和解析数据的函数。它定义了以下主要功能：

1. **接收缓冲区管理**：
   - `_rec_buf` 结构体用于管理接收缓冲区，包括缓冲区大小、写指针、读指针和缓冲区中的数据长度。

2. **接收函数**：
   - `available()`: 返回缓冲区中可用的数据长度。
   - `read()`: 从缓冲区中读取一个字节。
   - `readString()`: 从缓冲区中读取一个字符串。
   - `peek()`: 查看缓冲区中的下一个字节，但不从缓冲区中移除它。
   - `getc()`: 从缓冲区中读取下一个字节，如果当前没有数据可读，则阻塞直到有数据。
   - `scanNumber()`: 从缓冲区中读取一个长整型数字。
   - `scanFloat()`: 从缓冲区中读取一个浮点数。
   - `scan()`: 读取不同类型的数据到指定的变量中。

3. **模板操作符重载**：
   - 支持 `>>` 操作符的重载，用于方便地从缓冲区中读取数据。

# OutputStream 类

这是一个用于处理串行通信的类，提供了发送数据的函数。它定义了以下主要功能：

1. **发送缓冲区管理**：
   - 使用 `tx_Buff` 数组作为发送缓冲区。

2. **发送函数**：
   - `write()`: 发送一个字节。
   - `write()`: 发送一个字符串。
   - `print()`: 发送格式化输出。
   - `println()`: 发送格式化输出并换行。
   - `operator<<()`: 支持 `<<` 操作符的重载，用于方便地发送数据。

3. **格式化打印函数**：
   - 提供了一系列的 `print` 和 `println` 函数，用于发送整数、浮点数、字符串等不同类型的数据，并支持不同进制和精度。

**仿写知名框架，让其不使用该框架也能方便的进行数据的输出输入，目前仅支持串口，理论上来说支持iic spi 音频等一切可以抽象为数据流的事物**
---
**该库支持在hal库中方便的进行数据的输出与输入，如果想要在别的单片机（该单片机不包含该库的功能）使用，重写write函数与read函数即可**
## todo 添加iic spi等