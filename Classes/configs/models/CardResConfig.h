
#ifndef CARD_RES_CONFIG_H
#define CARD_RES_CONFIG_H
#include <string>
#include <array>
#include "LevelConfig.h"
#include "models/CardModel.h"

/**
 * @brief 卡牌资源配置类（遵循MVC架构的configs层规范）
 *
 * 该类负责提供卡牌相关的所有资源路径配置，包括背景、花色图标、数字等资源的路径生成逻辑。
 * 设计上符合程序设计架构要求中的"静态配置相关类"职责（），将资源路径集中管理，
 * 便于后续扩展新卡牌资源或修改资源路径规则，同时避免硬编码问题，提升代码可维护性。
 *
 * @note 依赖CardSuitType和CardFaceType枚举定义（），
 * 所有方法均为静态方法，无需实例化即可调用，符合"工具类提供通用功能"的编码规范（）。
 */

class CardResConfig {
public:
    /**
     * @brief 获取卡片背景路径
     * @param suit 花色枚举
     * @return 资源文件路径（如"club.png"）
     */
    static std::string getBackGround() {
        return "res/card_general.png";
    }

    /**
     * @brief 获取花色图标资源路径（右上角）
     * @param suit 花色枚举
     * @return 资源文件路径（如"club.png"）
     */
    static std::string getSuitRes(CardSuitType suit) {
        switch (suit) {
        case CardSuitType::CST_CLUBS:    return "res/suits/club.png";
        case CardSuitType::CST_DIAMONDS: return "res/suits/diamond.png";
        case CardSuitType::CST_HEARTS:   return "res/suits/heart.png";
        case CardSuitType::CST_SPADES:   return "res/suits/spade.png";
        default: return ""; // 处理非法枚举
        }
    }

    /**
     * @brief 获取左上角小数字资源路径
     * @param suit 花色（决定颜色：黑/红）
     * @param face 点数
     * @return 资源文件路径（如"small_black_3.png"）
     */
    static std::string getSmallNumberRes(CardSuitType suit, CardFaceType face) {
        std::string color = suitToColor(suit);
        std::string faceStr = faceToString(face);
        if (color.empty() || faceStr.empty()) {
            return ""; // 非法参数，返回空
        }
        return "res/number/small_" + color + "_" + faceStr + ".png";
    }

    /**
     * @brief 获取中间大数字资源路径
     * @param suit 花色（决定颜色：黑/红）
     * @param face 点数
     * @return 资源文件路径（如"big_red_3.png"）
     */
    static std::string getBigNumberRes(CardSuitType suit, CardFaceType face) {
        std::string color = suitToColor(suit);
        std::string faceStr = faceToString(face);
        if (color.empty() || faceStr.empty()) {
            return ""; // 非法参数，返回空
        }
        return "res/number/big_" + color + "_" + faceStr + ".png";
    }

private:
    /**
     * @brief 将点数枚举转换为字符串（如CardFaceType::Three → "3"）
     * @param face 点数枚举
     * @return 点数字符串
     */
    static std::string faceToString(CardFaceType face) {
        const std::string faceNames[] = {
        "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"
        };

        int index = static_cast<int>(face);
        // 校验枚举范围（排除CFT_NONE和CFT_NUM_CARD_FACE_TYPES）
        if (index < 0 || index >= static_cast<int>(CardFaceType::CFT_NUM_CARD_FACE_TYPES)) {
            return ""; // 非法枚举，返回空
        }
        return faceNames[index];
    }

     /**
     * @brief 根据花色判断颜色（黑/红）
     * @param suit 花色枚举
     * @return 颜色字符串（"black" 或 "red"）
     */
    static std::string suitToColor(CardSuitType suit) {
        if (suit == CardSuitType::CST_CLUBS || suit == CardSuitType::CST_SPADES) {
            return "black";
        }
        else {
            return "red";
        }
    }
};

#endif // CARD_RES_CONFIG_H