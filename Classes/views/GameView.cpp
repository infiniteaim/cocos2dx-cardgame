#include "GameView.h"

GameView* GameView::create(GameModel& model) {
    GameView* pRet = new(std::nothrow) GameView();
    if (pRet && pRet->init(model)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool GameView::init(GameModel& model) {
    if (!Node::init()) {
        return false;
    }

    _gameController = new GameController(model);
    generateCardViews(model);
    // 1. 创建并添加 Label
    _statusLabel = cocos2d::Label::createWithSystemFont(u8"回退", "Microsoft YaHei", 36); // 确保路径正确
    _statusLabel->setPosition(900, 400);  // 设置位置
    _statusLabel->setTextColor(cocos2d::Color4B::WHITE);  // 文本颜色
    this->addChild(_statusLabel, 100);     // 添加到视图，zOrder=10 确保在顶层

    // 打印 Label 的尺寸和位置
    CCLOG("Label size: %f, %f", _statusLabel->getContentSize().width, _statusLabel->getContentSize().height);
    CCLOG("Label position: %f, %f", _statusLabel->getPositionX(), _statusLabel->getPositionY());

    // 2. 注册触摸事件
    registerTouchEvents();
    return true;
}

void GameView::generateCardViews(GameModel& model) {
    // 生成 playfield 对应的 CardView 数组
    const auto& playfield = model.getPlayfield();
    for (auto cardModel : playfield) {
        CardView* cardView = CardView::create(cardModel, Vec2(0, 0));
        if (cardView) {
            _playfieldCardViews.push_back(cardView);
            this->addChild(cardView);
        }
    }

    // 生成 stackfield 对应的 CardView 数组
    const auto& stackfield = model.getStackfield();
    for (auto cardModel : stackfield) {
        CardView* cardView = CardView::create(cardModel, Vec2(0, 0));
        if (cardView) {
            _stackfieldCardViews.push_back(cardView);
            this->addChild(cardView);
        }
    }
    // 为所有卡牌设置点击回调
    auto handleCardClick = [this](CardView* cardView) {
        // 示例：改变卡牌透明度
        cardView->setOpacity(180);
        // 调用 GameController 处理卡牌点击逻辑
        CardModel& cardModel = cardView->_cardManager->getModel();
        CCLOG(u8"CardView 处理卡牌点击逻辑");
        if (cardModel.getZone() == CardZone::Playfield) {
            _gameController->selectCardFromPlayefieldAndMatch(cardModel);
        }
        else if (cardModel.getZone() == CardZone::Stack) {
            _gameController->clickStackCard(cardModel);
        }  
    };

    // 为 Playfield 卡牌设置回调
    for (auto cardView : _playfieldCardViews) {
        cardView->setClickCallback(handleCardClick);
    }

    // 为 Stackfield 卡牌设置回调
    for (auto cardView : _stackfieldCardViews) {
        cardView->setClickCallback(handleCardClick);
    }
}


void GameView::registerTouchEvents() {
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    // 触摸开始：检查是否点击 Label
    touchListener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 touchPos = this->convertToNodeSpace(touch->getLocation());
        if (_statusLabel->getBoundingBox().containsPoint(touchPos)) {
            // 高亮效果（放大）
            _statusLabel->setScale(1.2f);
            return true;  // 返回 true 表示处理该触摸事件
        }
        return false;
    };

    // 触摸结束：触发点击逻辑
    touchListener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        _statusLabel->setScale(1.0f);  // 恢复原大小
        cocos2d::Vec2 touchPos = this->convertToNodeSpace(touch->getLocation());
        if (_statusLabel->getBoundingBox().containsPoint(touchPos)) {
            onLabelClicked();  // 调用点击处理函数
        }
    };

    // 触摸取消：恢复状态
    touchListener->onTouchCancelled = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        _statusLabel->setScale(1.0f);
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameView::onLabelClicked() {
    CCLOG(u8"Label 被点击");
    _gameController->handleLabelClick();
}