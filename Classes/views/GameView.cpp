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
    // 1. ��������� Label
    _statusLabel = cocos2d::Label::createWithSystemFont(u8"����", "Microsoft YaHei", 36); // ȷ��·����ȷ
    _statusLabel->setPosition(900, 400);  // ����λ��
    _statusLabel->setTextColor(cocos2d::Color4B::WHITE);  // �ı���ɫ
    this->addChild(_statusLabel, 100);     // ��ӵ���ͼ��zOrder=10 ȷ���ڶ���

    // ��ӡ Label �ĳߴ��λ��
    CCLOG("Label size: %f, %f", _statusLabel->getContentSize().width, _statusLabel->getContentSize().height);
    CCLOG("Label position: %f, %f", _statusLabel->getPositionX(), _statusLabel->getPositionY());

    // 2. ע�ᴥ���¼�
    registerTouchEvents();
    return true;
}

void GameView::generateCardViews(GameModel& model) {
    // ���� playfield ��Ӧ�� CardView ����
    const auto& playfield = model.getPlayfield();
    for (auto cardModel : playfield) {
        CardView* cardView = CardView::create(cardModel, Vec2(0, 0));
        if (cardView) {
            _playfieldCardViews.push_back(cardView);
            this->addChild(cardView);
        }
    }

    // ���� stackfield ��Ӧ�� CardView ����
    const auto& stackfield = model.getStackfield();
    for (auto cardModel : stackfield) {
        CardView* cardView = CardView::create(cardModel, Vec2(0, 0));
        if (cardView) {
            _stackfieldCardViews.push_back(cardView);
            this->addChild(cardView);
        }
    }
    // Ϊ���п������õ���ص�
    auto handleCardClick = [this](CardView* cardView) {
        // ʾ�����ı俨��͸����
        cardView->setOpacity(180);
        // ���� GameController �����Ƶ���߼�
        CardModel& cardModel = cardView->_cardManager->getModel();
        CCLOG(u8"CardView �����Ƶ���߼�");
        if (cardModel.getZone() == CardZone::Playfield) {
            _gameController->selectCardFromPlayefieldAndMatch(cardModel);
        }
        else if (cardModel.getZone() == CardZone::Stack) {
            _gameController->clickStackCard(cardModel);
        }  
    };

    // Ϊ Playfield �������ûص�
    for (auto cardView : _playfieldCardViews) {
        cardView->setClickCallback(handleCardClick);
    }

    // Ϊ Stackfield �������ûص�
    for (auto cardView : _stackfieldCardViews) {
        cardView->setClickCallback(handleCardClick);
    }
}


void GameView::registerTouchEvents() {
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    // ������ʼ������Ƿ��� Label
    touchListener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        cocos2d::Vec2 touchPos = this->convertToNodeSpace(touch->getLocation());
        if (_statusLabel->getBoundingBox().containsPoint(touchPos)) {
            // ����Ч�����Ŵ�
            _statusLabel->setScale(1.2f);
            return true;  // ���� true ��ʾ����ô����¼�
        }
        return false;
    };

    // ������������������߼�
    touchListener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        _statusLabel->setScale(1.0f);  // �ָ�ԭ��С
        cocos2d::Vec2 touchPos = this->convertToNodeSpace(touch->getLocation());
        if (_statusLabel->getBoundingBox().containsPoint(touchPos)) {
            onLabelClicked();  // ���õ��������
        }
    };

    // ����ȡ�����ָ�״̬
    touchListener->onTouchCancelled = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        _statusLabel->setScale(1.0f);
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameView::onLabelClicked() {
    CCLOG(u8"Label �����");
    _gameController->handleLabelClick();
}