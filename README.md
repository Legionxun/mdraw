# mdraw - 天津大学《计算机语言实习》绘图程序改进版

mdraw is a simple drawing application based on MFC (Microsoft Foundation Classes) that allows users to create and edit various geometric shapes.

## Features

- Draw basic shapes:
  - Line
  - Rectangle
  - Square
  - Ellipse
  - Circle
  - Triangle (multiple types)

- Shape editing functions:
  - Move
  - Rotate
  - Scale
  - Fill
  - Set border width
  - Set colors (fill color, border color, intersection color)

- Support for standard file operations (New, Open, Save)
- Support for printing functionality

## Technical Implementation

- Uses MFC (Microsoft Foundation Classes) framework
- Uses GDI+ for graphics rendering
- Single Document Interface (SDI) application
- Supports mouse interaction for drawing and editing shapes

## Main Components

- [CShape](file://f:\Cpp%20Source\mdraw\mdraw\CShape.h#L12-L157) class: Base class for all shapes, defining basic properties and operations of shapes
- [CmdrawView](file://f:\Cpp%20Source\mdraw\mdraw\mdrawView.h#L9-L82) class: View class, handling user interaction and graphics display
- [CmdrawDoc](file://f:\Cpp%20Source\mdraw\mdraw\mdrawDoc.h#L8-L47) class: Document class, managing graphics data
- [CMainFrame](file://f:\Cpp%20Source\mdraw\mdraw\MainFrm.h#L6-L53) class: Main frame window class, containing menus and toolbars

## Usage

1. Select the shape type to draw from the menu or toolbar
2. Press and hold the left mouse button in the drawing area and drag to draw the shape
3. Select editing tools to modify drawn shapes
4. Access more options through the right-click menu, such as setting colors, border width, etc.

## Development Environment

- Microsoft Visual Studio
- MFC (Microsoft Foundation Classes)
- Windows SDK
- GDI+

## Project Structure

```
mdraw/
├── mdraw.cpp # Application entry point and main class implementation
├── mdraw.h # Application main class declaration
├── mdrawDoc.cpp # Document class implementation
├── mdrawDoc.h # Document class declaration
├── mdrawView.cpp # View class implementation
├── mdrawView.h # View class declaration
├── CShape.cpp # Shape class implementation
├── CShape.h # Shape class declaration
├── MainFrm.cpp # Main frame window implementation
├── MainFrm.h # Main frame window declaration
├── resource.h # Resource identifier definitions
└── mdraw.rc # Resource definition file
```

## Compilation and Execution

1. Open the `mdraw.sln` solution file using Visual Studio
2. Configure the project to use MFC and GDI+
3. Compile the project to generate the executable file
4. Run `mdraw.exe`

## Notes

- This is a teaching example project primarily used to demonstrate basic usage of MFC and GDI+

- The project may require Visual Studio and Windows SDK environment to compile and run correctly

- The current implementation may not include error handling and boundary condition checks, and is for learning reference only

  

## 中文教程

mdraw 是一个基于 MFC (Microsoft Foundation Classes) 的简单绘图应用程序，允许用户创建和编辑各种几何图形。

## 功能特点

- 绘制基本图形：
  - 直线 (Line)
  - 矩形 (Rectangle)
  - 正方形 (Square)
  - 椭圆 (Ellipse)
  - 圆形 (Circle)
  - 三角形 (多种类型)

- 图形编辑功能：
  - 移动 (Move)
  - 旋转 (Rotate)
  - 缩放 (Scale)
  - 填充 (Fill)
  - 设置边框宽度
  - 设置颜色（填充色、边框色、交集色）

- 支持标准文件操作（新建、打开、保存）
- 支持打印功能

## 技术实现

- 使用 MFC (Microsoft Foundation Classes) 框架
- 使用 GDI+ 进行图形渲染
- 单文档界面 (SDI) 应用程序
- 支持鼠标交互绘制和编辑图形

## 主要组件

- [CShape](file://f:\Cpp%20Source\mdraw\mdraw\CShape.h#L12-L157) 类：所有图形的基类，定义了图形的基本属性和操作
- [CmdrawView](file://f:\Cpp%20Source\mdraw\mdraw\mdrawView.h#L9-L82) 类：视图类，处理用户交互和图形显示
- [CmdrawDoc](file://f:\Cpp%20Source\mdraw\mdraw\mdrawDoc.h#L8-L47) 类：文档类，管理图形数据
- [CMainFrame](file://f:\Cpp%20Source\mdraw\mdraw\MainFrm.h#L6-L53) 类：主框架窗口类，包含菜单和工具栏

## 使用方法

1. 从菜单或工具栏选择要绘制的图形类型
2. 在绘图区域按住鼠标左键并拖动以绘制图形
3. 选择编辑工具对已绘制的图形进行修改
4. 可以通过右键菜单访问更多选项，如设置颜色、边框宽度等

## 开发环境

- Microsoft Visual Studio
- MFC (Microsoft Foundation Classes)
- Windows SDK
- GDI+

## 项目结构

```
mdraw/ 
├── mdraw.cpp # 应用程序入口点和主类实现 
├── mdraw.h # 应用程序主类声明 
├── mdrawDoc.cpp # 文档类实现 
├── mdrawDoc.h # 文档类声明 
├── mdrawView.cpp # 视图类实现 
├── mdrawView.h # 视图类声明 
├── CShape.cpp # 图形类实现 
├── CShape.h # 图形类声明 
├── MainFrm.cpp # 主框架窗口实现 
├── MainFrm.h # 主框架窗口声明 
├── resource.h # 资源标识符定义 
└── mdraw.rc # 资源定义文件
```



## 编译和运行

1. 使用 Visual Studio 打开 `mdraw.sln` 解决方案文件
2. 配置项目以使用 MFC 和 GDI+
3. 编译项目生成可执行文件
4. 运行 `mdraw.exe`

## 注意事项

- 这是一个教学示例项目，主要用于演示 MFC 和 GDI+ 的基本用法
- 项目可能需要 Visual Studio 和 Windows SDK 环境才能正确编译和运行
- 当前实现可能不包含错误处理和边界条件检查，仅供学习参考