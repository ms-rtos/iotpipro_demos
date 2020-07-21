##### 1. 工程目录结构说明

* /src/TouchGFX  该目录下的文件为 TouchGFX Designer 工具生成的代码；在编译 MS-RTOS APP 工程时，需要删除掉 Makefile 中 target/simulator/APP 这些目录下的.c文件（不编译这些文件）。
* /src/System  该目录用于存放系统服务相关的源码文件，这些文件为 TouchGFX 的 Model 提供基于操作系统的服务接口，如：传感器数据采集、时间信息获取、文件存储、网络通信等服务。
* /src/* 该目录下的其它文件为移植相关的源码文件，对于基于 MS-RTOS 的 TouchGFX 应用程序来说，这些文件是通用文件，您在创建新的工程时可以直接拷贝使用。



##### 2. 基于 TouchGFX 的 MS-RTOS UI 应用程序开发流程

(1) 在 TouchGFX 中新建一个 UI 工程，并设置好 Model 相关的数据接口，并仿真运行，查看UI的显示效果。

(2) 新建 MS-RTOS 应用程序工程，将 TouchGFX 工程所生成的代码的 TouchGFX 目录拷贝到应用程序工程中。

(3) 处理 Makefile 中要编译的源码文件、头文件搜索路径、依赖库路径等，编译应用程序

(4) 实现 Model 中相关接口，然后下载程序到开发板进行实际测试



##### 3. 在开发过程中修改应用程序的界面

* 方法一：可以直接双击 /src/TouchGFX 目录下的 touchgfx_app.touchgfx 文件，打开工程后可以直接修改 UI ，然后生成代码，但是此方式在编译时可能会报错，因为工程环境变化了。
* 方法二：在原始的 TouchGFX UI 工程中修改 UI, 用 VisualStudio 修改 UI 相关的代码，然后将修改后的代码同步到当前 MS-RTOS 的应用程序代码中。



##### 4. 在 VisualStudio 中添加自定义 UI 相关的源码文件

(1) 将包含源码的文件夹(或文件)分别拷贝到 gui/inc 和 gui/src 目录下 

(2) 使用 VisualStudio 打开工程，然后在对应的目录下新建 Flite ，然后右键导入已存在的 item

(3) 使用 VisualStudio 编辑代码，但编译时还是通过 TouchGFX 的 Run Simulator 来编译并预览效果


##### 5. 注意事项

使用 TouchGFX 创建工程时，需要选择目标板，在选择目标板时，需要正确选择分辨率和颜色深度与实际板卡一致的目标板。

