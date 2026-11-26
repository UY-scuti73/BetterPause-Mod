#include "../BetterPause.h"

bool MyPlayLayer::init(GJGameLevel* level, bool dontCreateObjects) {
    if (!PlayLayer::init(level, dontCreateObjects))
        return false;

    GameLevelManager::sharedState()->getGJUserInfo(level->m_accountID);
    return true;
}