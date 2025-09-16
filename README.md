# mdraw - ����ѧ�����������ʵϰ����ͼ����Ľ���

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
������ mdraw.cpp # Application entry point and main class implementation
������ mdraw.h # Application main class declaration
������ mdrawDoc.cpp # Document class implementation
������ mdrawDoc.h # Document class declaration
������ mdrawView.cpp # View class implementation
������ mdrawView.h # View class declaration
������ CShape.cpp # Shape class implementation
������ CShape.h # Shape class declaration
������ MainFrm.cpp # Main frame window implementation
������ MainFrm.h # Main frame window declaration
������ resource.h # Resource identifier definitions
������ mdraw.rc # Resource definition file
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

  

## ���Ľ̳�

mdraw ��һ������ MFC (Microsoft Foundation Classes) �ļ򵥻�ͼӦ�ó��������û������ͱ༭���ּ���ͼ�Ρ�

## �����ص�

- ���ƻ���ͼ�Σ�
  - ֱ�� (Line)
  - ���� (Rectangle)
  - ������ (Square)
  - ��Բ (Ellipse)
  - Բ�� (Circle)
  - ������ (��������)

- ͼ�α༭���ܣ�
  - �ƶ� (Move)
  - ��ת (Rotate)
  - ���� (Scale)
  - ��� (Fill)
  - ���ñ߿���
  - ������ɫ�����ɫ���߿�ɫ������ɫ��

- ֧�ֱ�׼�ļ��������½����򿪡����棩
- ֧�ִ�ӡ����

## ����ʵ��

- ʹ�� MFC (Microsoft Foundation Classes) ���
- ʹ�� GDI+ ����ͼ����Ⱦ
- ���ĵ����� (SDI) Ӧ�ó���
- ֧����꽻�����ƺͱ༭ͼ��

## ��Ҫ���

- [CShape](file://f:\Cpp%20Source\mdraw\mdraw\CShape.h#L12-L157) �ࣺ����ͼ�εĻ��࣬������ͼ�εĻ������ԺͲ���
- [CmdrawView](file://f:\Cpp%20Source\mdraw\mdraw\mdrawView.h#L9-L82) �ࣺ��ͼ�࣬�����û�������ͼ����ʾ
- [CmdrawDoc](file://f:\Cpp%20Source\mdraw\mdraw\mdrawDoc.h#L8-L47) �ࣺ�ĵ��࣬����ͼ������
- [CMainFrame](file://f:\Cpp%20Source\mdraw\mdraw\MainFrm.h#L6-L53) �ࣺ����ܴ����࣬�����˵��͹�����

## ʹ�÷���

1. �Ӳ˵��򹤾���ѡ��Ҫ���Ƶ�ͼ������
2. �ڻ�ͼ����ס���������϶��Ի���ͼ��
3. ѡ��༭���߶��ѻ��Ƶ�ͼ�ν����޸�
4. ����ͨ���Ҽ��˵����ʸ���ѡ���������ɫ���߿��ȵ�

## ��������

- Microsoft Visual Studio
- MFC (Microsoft Foundation Classes)
- Windows SDK
- GDI+

## ��Ŀ�ṹ

```
mdraw/ 
������ mdraw.cpp # Ӧ�ó�����ڵ������ʵ�� 
������ mdraw.h # Ӧ�ó����������� 
������ mdrawDoc.cpp # �ĵ���ʵ�� 
������ mdrawDoc.h # �ĵ������� 
������ mdrawView.cpp # ��ͼ��ʵ�� 
������ mdrawView.h # ��ͼ������ 
������ CShape.cpp # ͼ����ʵ�� 
������ CShape.h # ͼ�������� 
������ MainFrm.cpp # ����ܴ���ʵ�� 
������ MainFrm.h # ����ܴ������� 
������ resource.h # ��Դ��ʶ������ 
������ mdraw.rc # ��Դ�����ļ�
```



## ���������

1. ʹ�� Visual Studio �� `mdraw.sln` ��������ļ�
2. ������Ŀ��ʹ�� MFC �� GDI+
3. ������Ŀ���ɿ�ִ���ļ�
4. ���� `mdraw.exe`

## ע������

- ����һ����ѧʾ����Ŀ����Ҫ������ʾ MFC �� GDI+ �Ļ����÷�
- ��Ŀ������Ҫ Visual Studio �� Windows SDK ����������ȷ���������
- ��ǰʵ�ֿ��ܲ�����������ͱ߽�������飬����ѧϰ�ο�