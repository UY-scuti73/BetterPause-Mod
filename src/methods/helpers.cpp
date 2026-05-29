#include "../BetterPause.h"

int MyPauseLayer::calculateOffset(float offset) {
    int left_offset = 45;
    float constant = 195;
    offset = offset + 1;
    return static_cast<int>((offset * constant) + left_offset);
}

cocos2d::CCPoint MyPauseLayer::getPosition(int xmod, int ymod) {
    return cocos2d::CCPoint(
        (CCDirector::get()->getScreenLeft() +
         CCDirector::get()->getScreenScaleFactorW() * xmod),
        (CCDirector::get()->getScreenTop() +
         CCDirector::get()->getScreenScaleFactorH() * ymod)
    );
}

std::string MyPauseLayer::condence(int val) {
    if (val >= 1000000) {
        return std::to_string(val / 1000000) + "m";
    }
    if (val >= 1000) {
        return std::to_string(val / 1000) + "k";
    }
    return std::to_string(val);
}

int MyPauseLayer::getCreatorPoints(int id) {
    auto GLM = GameLevelManager::sharedState();
    GLM->getGJUserInfo(id);
    GJUserScore* userInfo = GLM->userInfoForAccountID(id);
    if (!userInfo) return -1;
    return userInfo->m_creatorPoints;
}

int MyPauseLayer::getCurrentOrbs(int percentage, int max_orbs) {
    if (percentage < 100) {
        double temp = max_orbs * 0.8 * percentage;
        return static_cast<int>(std::floor(temp / 100));
    }
    return max_orbs;
}

int MyPauseLayer::getCurrentDiamonds(int percentage, int max_diamonds) {
    return static_cast<int>(std::floor((percentage / 100.0) * max_diamonds));
}

void MyPauseLayer::getRewards(int stars, int& max_orbs, int& max_diamonds) {
    switch (stars) {
        case 2:  max_orbs = 50;  max_diamonds = 4;  break;
        case 3:  max_orbs = 75;  max_diamonds = 5;  break;
        case 4:  max_orbs = 125; max_diamonds = 6;  break;
        case 5:  max_orbs = 175; max_diamonds = 7;  break;
        case 6:  max_orbs = 225; max_diamonds = 8;  break;
        case 7:  max_orbs = 275; max_diamonds = 9;  break;
        case 8:  max_orbs = 350; max_diamonds = 10; break;
        case 9:  max_orbs = 425; max_diamonds = 11; break;
        case 10: max_orbs = 500; max_diamonds = 12; break;
        default:
            max_orbs = -1;
            max_diamonds = -1;
    }
}

bool MyPauseLayer::hasDiamonds(GJGameLevel* level) {
    if (level->m_dailyID > 0 || level->m_gauntletLevel || level->m_gauntletLevel2)
        return true;
    return false;
}