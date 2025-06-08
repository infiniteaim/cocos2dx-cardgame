# cocos2dx-cardgame

这是一个基于 Cocos2d-x 3.17 开发的纸牌游戏示例项目。项目采用 MVC（Model-View-Controller）架构模式，展示了如何使用 Cocos2d-x 引擎开发一个简单的纸牌游戏。

## 目录
1. [项目介绍](#项目介绍)
2. [前置要求](#前置要求)
3. [项目结构](#项目结构)
4. [配置说明](#配置说明)
5. [运行方法](#运行方法)
6. [功能特性](#功能特性)

## 项目介绍
此纸牌游戏示例构建于 Cocos2d-x 游戏引擎 3.17 版本之上，展示了一个简单纸牌游戏的实现，具备从 JSON 文件加载纸牌数据、处理触摸事件以及撤销操作等功能。

## 前置要求
- **Cocos2d-x**：确保你的系统已安装 Cocos2d-x 3.17 版本。你可以从 Cocos2d-x 官方网站下载。
- **CMake**：用于构建项目。根据你的操作系统从官方网站安装 CMake。


## 项目结构
项目主要目录和文件如下：
- **Classes**：包含游戏的主要源代码，按功能模块组织，如模型、视图、控制器、管理器和配置加载器。
  - **models**：定义游戏中使用的数据模型，如 `CardModel`、`GameModel` 和 `UndoModel`。
  - **views**：实现游戏的视觉组件，包括 `CardView` 和 `GameView`。
  - **controllers**：处理游戏逻辑和交互，例如 `GameController`。
  - **managers**：管理游戏的各个方面，如 `CardManager` 和 `UndoManager`。
  - **configs/loaders**：从 JSON 文件加载游戏配置，如 `LevelConfigLoader`。
- **Resources**：包含游戏资源，如图像和 JSON 配置文件。
- **proj.win32**：Windows 特定的项目文件和配置。
- **CMakeLists.txt**：CMake 配置文件，用于构建项目。

## 配置说明
游戏使用 JSON 文件进行关卡配置。例如，`Resources/level_1.json` 定义了游戏中纸牌的初始状态，包括面值、花色和位置。

## 运行方法
1. **构建项目**
2. **运行可执行文件**：
   - **Windows 系统**：在 `proj.win32/Debug.win32` 目录下找到生成的可执行文件并运行。
   - **其他平台**：按照相应的步骤运行构建好的应用程序。

## 功能特性
- **关卡加载**：从 JSON 文件加载游戏关卡，便于自定义游戏状态。
- **纸牌交互**：支持纸牌的触摸事件，包括点击和拖动交互。
- **撤销功能**：允许玩家撤销操作，通过 `UndoManager` 和 `UndoModel` 实现。
- **MVC 架构**：遵循 MVC 模式，提高代码的组织性和可维护性。
