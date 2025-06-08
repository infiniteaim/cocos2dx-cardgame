#include "CardView.h"
#include <iostream>

CardView* CardView::create(const CardModel& model, const Vec2& offset) {
    auto view = new CardView();
    if (view && view->init(model, offset)) {
        view->autorelease(); // 交给内存管理池自动释放
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}


void CardView::setClickCallback(const ClickCallback& callback) {
    _clickCallback = callback;
    _cardManager->setCardClickedCallback([this, callback](CardModel& model) {
        if (callback) {
            callback(this);
        }
    });
}

bool CardView::isTouchInside(const Vec2& touchPos) {
    if (!_background) return false;
    
    return _background->getBoundingBox().containsPoint(touchPos);
}

bool CardView::init(const CardModel& model, const Vec2& offset) {
    if (!Node::init()) {
        return false;
    }

    // 1. 加载背景（必须优先加载，确定卡牌尺寸）
    loadBackground();
    if (!_background) {
        CCLOG("CardView: 背景图加载失败！");
        return false;
    }
    // 创建 CardManager 实例
    _cardManager = new CardManager(model);
    // 2. 加载子元素
    loadSmallNumber(model);
    loadBigNumber(model);
    loadSuitIcon(model);
    this->setPosition(model.getPosition() + offset);
    
    // 设置卡片和视图到 CardManager
    _cardManager->setCard(model, this);
    return true;
}


void CardView::loadBackground() {
    // 假设背景图资源名为 "card_bg.png"，需确保资源存在
    _background = Sprite::create(CardResConfig::getBackGround());
    if (_background) {
        _background->setAnchorPoint(Vec2::ANCHOR_MIDDLE); // 背景锚点设为中心
        this->addChild(_background);
        // 同步CardView的尺寸与背景图一致
        this->setContentSize(_background->getContentSize());
    }
}

void CardView::loadSmallNumber(const CardModel& model) {
    // 1. 获取资源路径
    auto suit = model.getSuit();
    auto face = model.getFace();
    std::string res = CardResConfig::getSmallNumberRes(suit, face);

    // 2. 创建Sprite（资源不存在时返回nullptr，避免崩溃）
    _smallNumber = Sprite::create(res);
    if (_smallNumber) {
        _smallNumber->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT); // 左上角对齐
        _smallNumber->setPosition(_smallNumberPos);          // 相对背景中心的位置
        this->addChild(_smallNumber);
    }
    else {
        CCLOG("CardView: 小数字资源缺失: %s", res.c_str());
    }
}

void CardView::loadBigNumber(const CardModel& model) {
    // 1. 获取资源路径
    auto suit = model.getSuit();
    auto face = model.getFace();
    std::string res = CardResConfig::getBigNumberRes(suit, face);

    // 2. 创建Sprite
    _bigNumber = Sprite::create(res);
    if (_bigNumber) {
        _bigNumber->setAnchorPoint(Vec2::ANCHOR_MIDDLE); // 中心对齐
        _bigNumber->setPosition(_bigNumberPos);          // 背景中心位置
        this->addChild(_bigNumber);
    }
    else {
        CCLOG("CardView: 大数字资源缺失: %s", res.c_str());
    }
}

void CardView::loadSuitIcon(const CardModel& model) {
    // 1. 获取资源路径
    auto suit = model.getSuit();
    std::string res = CardResConfig::getSuitRes(suit);

    // 2. 创建Sprite
    _suitIcon = Sprite::create(res);
    if (_suitIcon) {
        _suitIcon->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT); // 右上角对齐
        _suitIcon->setPosition(_suitIconPos);              // 相对背景中心的位置
        this->addChild(_suitIcon);
    }
    else {
        CCLOG("CardView: 花色图标资源缺失: %s", res.c_str());
    }
}