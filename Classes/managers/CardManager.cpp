// CardManager.cpp
#include "managers/CardManager.h"
#include <iostream>
#include "views/CardView.h"  
#include "services/CardIdManagerMap.h"



CardManager::CardManager(const CardModel& model) : _model(model), _view(nullptr), _isSelected(false) {
    CardIdManagerMap::getInstance().addCardManager(model._id, this);
}

CardManager::~CardManager() {}

void CardManager::setCard(const CardModel& model, CardView* view) {
    _model = model;
    _view = view;
    CardIdManagerMap::getInstance().addCardManager(model._id, this);
    setupTouchEvents();
}

void CardManager::setupTouchEvents() {
    if (!_view) return;
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(CardManager::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(CardManager::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(CardManager::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(CardManager::onTouchCancelled, this);

    _view->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, _view);
}

bool CardManager::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return false;
    cocos2d::Vec2 touchPos = _view->convertToNodeSpace(touch->getLocation());
    if (!_view->isTouchInside(touchPos)) return false;
    CCLOG(u8"点击开始，卡片放大！");
    // 点击开始，卡片放大
    _view->setScale(1.1f);
    _isSelected = true;
    return true;
}

void CardManager::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    // 触摸移动，可添加拖动逻辑
}

void CardManager::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return;
    cocos2d::Vec2 touchPos = _view->convertToNodeSpace(touch->getLocation());
    _view->setScale(1.0f);  // 恢复原大小
    CCLOG(u8"点击结束，恢复原大小！");
    if (_cardClickedCallback) {
        CCLOG(u8"CardManager 触摸结束在卡片内，触发点击回调");
        _cardClickedCallback(_model);
    }
    _isSelected = false;
}

void CardManager::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return;
    _view->setScale(1.0f);  // 恢复原大小
    _isSelected = false;
}

void CardManager::setCardClickedCallback(const std::function<void(CardModel&)>& callback) {
    _cardClickedCallback = callback;
}
