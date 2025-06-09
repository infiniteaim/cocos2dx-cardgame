# cocos2dx-cardgame

这是一个基于 Cocos2d-x 3.17 开发的纸牌游戏示例项目。项目采用 MVC（Model-View-Controller）架构模式，展示了如何使用 Cocos2d-x 引擎开发一个简单的纸牌游戏。

## 目录
1. [项目介绍](#项目介绍)
2. [前置要求](#前置要求)
3. [项目结构](#项目结构)
4. [配置说明](#配置说明)
5. [运行方法](#运行方法)
6. [功能特性](#功能特性)
7. [项目扩展](#项目扩展)

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
1. **构建项目**：先使用cocos命令创建项目，再将其中的对应部分替换为本仓库的内容。
2. **运行可执行文件**：
   - **Windows 系统**：在 `proj.win32/Debug.win32` 目录下找到生成的可执行文件并运行。
   - **其他平台**：按照相应的步骤运行构建好的应用程序。

## 功能特性
- **关卡加载**：从 JSON 文件加载游戏关卡，便于自定义游戏状态。
- **纸牌交互**：支持纸牌的触摸事件，包括点击和拖动交互。
- **撤销功能**：允许玩家撤销操作，通过 `UndoManager` 和 `UndoModel` 实现。
- **MVC 架构**：遵循 MVC 模式，提高代码的组织性和可维护性。

## 项目扩展

### 添加卡牌类型

#### 1. 扩展卡牌配置文件
首先在 `Resources/level_1.json` 等配置文件中添加新的卡牌定义。例如：
```json
{
  "Playfield": [
    {  "CardFace": "...", "CardSuit": "Joker", "x": 100, "y": 200 },
  ]
}
```

#### 2. 修改卡牌模型类
在 `Classes/models/CardModel.h` 中扩展卡牌属性：
```cpp
enum CardSuitType {
        CST_HEARTS, CST_DIAMONDS, CST_CLUBS, CST_SPADES, CST_JOKERS // 添加 CST_JOKERS 类型
    };
class CardModel {
public:
    // 添加新的初始化方法或修改现有方法
    CardModel(CardFaceType face, CardSuitType suit, const cocos2d::Vec2& position, int id, CardZone zone): 
        _face(face)
        , _suit(suit)
        , _position(position)
        , _id(id)
        , _zone(zone){}
    ...
};
```

#### 3. 更新卡牌视图渲染
在 `Classes/configs/models/CardResConfig.h` 中根据新的卡牌类型加载不同路径的纹理：
```cpp
static std::string getSuitRes(CardSuitType suit) {
        switch (suit) {
        case CardSuitType::CST_CLUBS:    return "res/suits/club.png";
        case CardSuitType::CST_DIAMONDS: return "res/suits/diamond.png";
        case CardSuitType::CST_HEARTS:   return "res/suits/heart.png";
        case CardSuitType::CST_SPADES:   return "res/suits/spade.png";
        case CardSuitType::CST_JOKERS:   return "...";
        default: return "";
        }
    }
```

#### 4. 添加新的卡牌纹理资源
确保在 `Resources/cards/` 目录下添加新卡牌类型对应的图片资源，例如：
- `Joker.png`


#### 5. 处理特殊卡牌逻辑
如果新卡牌有特殊行为，需要在控制器或管理器中添加相应逻辑：
```cpp
// 在 GameController.cpp 中
void GameController::onCardClicked(CardModel* card) {
    if (card->getSuit() == CardSuitType::CST_JOKERS) {
        // 处理 Joker 卡牌的特殊逻辑
        handleJokerCard(card);
    } else {
        // 常规卡牌逻辑
        handleNormalCard(card);
    }
}
```

#### 6. 测试新卡牌
完成上述步骤后，重新编译并运行游戏，验证新卡牌是否正常显示和工作。

### 添加新的Undo操作
以添加一个仅回退stack区域的卡牌操作为例

#### 1. 为UndoModel添加新的接口，使其能返回最顶端的stack区域卡牌：
```cpp
    bool UndoModel::undoStack(UndoCardState& outState) {
        if (_history.empty()) {
            return false; 
        }
        for(int i = _history.size() - 1; i >= 0 ; i++){
            if(_history[i].zone == CardZone::Stack){
                outState = _history[i];
                _history.erase(_history.begin() + i);
                return true;
            }
        }
        return false;
    }
```

#### 2. 为UndoManager添加对应的方法
```cpp
    bood undoStack(UndoCardState& outState){
        return _undoModel.undoStack(outState);
    }
```

### 3. 在GameController中添加对应的逻辑
```cpp
    bool GameController::undoStack() {
        ......
    }
```

### 4. 在GameView中添加新的label并绑定点击事件，同时设置回调函数

### 5. 进行测试
