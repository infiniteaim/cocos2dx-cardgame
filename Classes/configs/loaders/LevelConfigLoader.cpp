#include "LevelConfigLoader.h"


int LevelConfigLoader::currentId = 0;

LevelConfig* LevelConfigLoader::loadLevelConfig(std::string fileName) {
        std::string jsonStr = cocos2d::FileUtils::getInstance()->getStringFromFile(fileName);
        rapidjson::Document d;
        d.Parse<rapidjson::kParseDefaultFlags>(jsonStr.c_str());
        if (d.HasParseError()) {
            CCLOG("GetParseError %s\n", d.GetParseError());
            return nullptr;
        }
        auto config = new LevelConfig();
        if (!d.IsObject()) {
            CCLOG("LevelConfigLoader: Root node is not an object.");
            return nullptr; // ���ؿ����ݵ� config����������󷵻� nullptr��
        }

        // �������� id
        currentId = 0;

        // 4. ���� Playfield ����
        if (d.HasMember("Playfield") && d["Playfield"].IsArray()) {
            const rapidjson::Value& playfieldArray = d["Playfield"];
            for (SizeType i = 0; i < playfieldArray.Size(); ++i) {
                const rapidjson::Value& cardNode = playfieldArray[i];
                if (!parseCardModel(cardNode, config->_playfieldCards, CardZone::Playfield)) {
                    CCLOG("LevelConfigLoader: Invalid Playfield card at index %zu", i);
                }
            }
        }

        // 5. ���� Stack ����
        if (d.HasMember("Stack") && d["Stack"].IsArray()) {
            const rapidjson::Value& stackArray = d["Stack"];
            for (SizeType i = 0; i < stackArray.Size(); ++i) {
                const rapidjson::Value& cardNode = stackArray[i];
                if (!parseCardModel(cardNode, config->_stackCards, CardZone::Stack)) {
                    CCLOG("LevelConfigLoader: Invalid Stack card at index %zu", i);
                }
            }
        }
        return config;
}

bool LevelConfigLoader::parseCardModel(const rapidjson::Value& cardNode, std::vector<CardModel>& target, CardZone zone) {
    if (!cardNode.IsObject()) return false;

    // У���Ҫ�ֶδ�����������ȷ
    if (!cardNode.HasMember("CardFace") || !cardNode["CardFace"].IsInt()) return false;
    if (!cardNode.HasMember("CardSuit") || !cardNode["CardSuit"].IsInt()) return false;
    if (!cardNode.HasMember("Position") || !cardNode["Position"].IsObject()) return false;

    const rapidjson::Value& posNode = cardNode["Position"];
    if (!posNode.HasMember("x") || !posNode["x"].IsInt() ||
        !posNode.HasMember("y") || !posNode["y"].IsInt()) {
        return false;
    }

    // ��ȡԭʼֵ
    int faceInt = cardNode["CardFace"].GetInt();
    int suitInt = cardNode["CardSuit"].GetInt();
    float x = posNode["x"].GetFloat();
    float y = posNode["y"].GetFloat();

    // У��ö�ٷ�Χ������ CardFace: 1~13��CardSuit: 0~3��
    if (faceInt < 0 || faceInt > 12) return false;
    if (suitInt < 0 || suitInt > 3) return false;

    // ת��Ϊö�ٲ����� CardModel
    CardFaceType face = static_cast<CardFaceType>(faceInt);
    CardSuitType suit = static_cast<CardSuitType>(suitInt);
    cocos2d::Vec2 pos(x, y);

    // ��ȡ��ǰ id ������
    int id = currentId++;
    if(zone == CardZone::Stack)  pos += Vec2(300, 400);
    else pos += Vec2(0, 600);
    target.emplace_back(face, suit, pos, id, zone); // ֱ�ӹ��죬���⿽��
    return true;
}