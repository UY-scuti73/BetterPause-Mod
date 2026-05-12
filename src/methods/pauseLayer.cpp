#include "../BetterPause.h"

bool MyPlayLayer::init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
    if (!PlayLayer::init(level, useReplay, dontCreateObjects))
        return false;

    GameLevelManager::sharedState()->getGJUserInfo(level->m_accountID);
    return true;
}