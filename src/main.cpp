#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {

    void customSetup() override {
        PauseLayer::customSetup();

        auto playLayer = PlayLayer::get();
        if (playLayer == nullptr) {return;}
        auto level = playLayer->m_level;

        int center = 45;

        setup_difficulty(level, -40, center);
        setup_time(level, playLayer, -80, center);
        setup_stats(level, -125, center);
        setup_creator(level, -175, center);
        //setup_rewards(level, -225, center);
    }

    private:

    // Set Up Info

    //Difficulty
    void setup_difficulty(GJGameLevel* level, int offsetY, int offsetX) {
        //Difficulty
        GJDifficultyName diffType = GJDifficultyName::Short;

        int difficulty;
        if (level->m_demon > 0) {
            difficulty = level->demonIconForDifficulty((DemonDifficultyType) level->m_demonDifficulty);
        } else {
            difficulty = level->getAverageDifficulty();
        }

        auto diffSprite = GJDifficultySprite::create(difficulty, diffType);

        diffSprite->updateDifficultyFrame(difficulty, diffType);
        diffSprite->updateFeatureStateFromLevel(level);

        diffSprite->setPosition(getPosition(offsetX - 1, offsetY));
        diffSprite->setScale(0.7f);
        this->addChild(diffSprite);

        //Stars
        if (level->m_stars > 0) {
            // Star sprite
            auto starSprite = CCSprite::createWithSpriteFrameName("star_small01_001.png");
            starSprite->setPosition(getPosition(offsetX - 6, offsetY - 22));
            starSprite->setScale(0.8f);
            this->addChild(starSprite);

            // Star count
            auto starsLabel = CCLabelBMFont::create(
                fmt::format("{}", level->m_stars).c_str(),
                "bigFont.fnt"
            );
            starsLabel->setPosition(getPosition(offsetX + 4, offsetY - 22));
            starsLabel->setScale(0.3f);
            this->addChild(starsLabel);
        }
    }

    //Time
    void setup_time(GJGameLevel* level, PlayLayer* playLayer, int offsetY, int offsetX) {
        //Time Header
        auto timelabel = CCLabelBMFont::create("Time:", "goldFont.fnt");
        timelabel->setPosition(getPosition(offsetX, offsetY));
        timelabel->setScale(0.7f);
        this->addChild(timelabel);

        //Time
        CCPoint endPos = CCPoint(playLayer->m_levelLength, 0);
        int a = playLayer->timeForPos(endPos, 0, 0, false, 0);

        int b = (level->m_timestamp) / 240;

        int totalSeconds = std::max(a, b);

        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;
        std::string v_time = std::to_string(minutes) + "m " + std::to_string(seconds) + "s";

        auto time = CCLabelBMFont::create(v_time.c_str(), "bigFont.fnt");
        time->setPosition(getPosition(offsetX, offsetY - 25));
        time->setScale(0.3f);
        this->addChild(time);

        //Time Stamp
        std::string v_timeLabel = level->lengthKeyToString(level->m_levelLength);

        auto timePlaceholder = CCLabelBMFont::create(v_timeLabel.c_str(), "bigFont.fnt");
        timePlaceholder->setPosition(getPosition(offsetX, offsetY - 15));
        timePlaceholder->setScale(0.4f);
        this->addChild(timePlaceholder);
    }

    //Stats
    void setup_stats(GJGameLevel* level, int offsetY, int offsetX) {
        //Stats Header
        auto likelabel = CCLabelBMFont::create("Stats:", "goldFont.fnt");
        likelabel->setPosition(getPosition(offsetX, offsetY));
        likelabel->setScale(0.7f);
        this->addChild(likelabel);

        //Downloads
        std::string strDownloads = condence(level->m_downloads);
        int dowOffset = strDownloads.length() - 1;

        auto downloads = CCLabelBMFont::create(strDownloads.c_str(), "bigFont.fnt");
        downloads->setPosition(getPosition(offsetX - (4 + dowOffset*2), offsetY - 17));
        downloads->setAnchorPoint({0.0f, 0.5f});
        downloads->setScale(0.4f);
        this->addChild(downloads);

        //Downloads Sprite
        auto downloadsSprite = CCSprite::createWithSpriteFrameName("GJ_downloadsIcon_001.png");
        downloadsSprite->setPosition(getPosition(offsetX - (10 + dowOffset*2), offsetY - 17));
        downloadsSprite->setScale(0.5f);
        this->addChild(downloadsSprite);

        //Likes
        std::string strLikes = condence(level->m_likes);
        int likeOffset = strLikes.length() - 1;

        auto likes = CCLabelBMFont::create(strLikes.c_str(), "bigFont.fnt");
        likes->setPosition(getPosition(offsetX - (4 + likeOffset*2), offsetY - 30));
        likes->setAnchorPoint({0.0f, 0.5f});
        likes->setScale(0.4f);
        this->addChild(likes);

        //Likes Sprite
        const char* spriteLocation = level->m_likes < 0 ? "GJ_dislikesIcon_001.png" : "GJ_likesIcon_001.png";
        auto likeSprite = CCSprite::createWithSpriteFrameName(spriteLocation);
        likeSprite->setPosition(getPosition(offsetX - (10 + likeOffset*2), offsetY - 30));
        likeSprite->setScale(0.5f);
        this->addChild(likeSprite);
    }

    //Creator
    void setup_creator(GJGameLevel* level, int offsetY, int offsetX) {
        //Creator Header
        auto creatorlabel = CCLabelBMFont::create("Creator:", "goldFont.fnt");
        creatorlabel->setPosition(getPosition(offsetX, offsetY));
        creatorlabel->setScale(0.6f);
        this->addChild(creatorlabel);

        auto creator = CCLabelBMFont::create(level->m_creatorName.c_str(), "bigFont.fnt");
        creator->setPosition(getPosition(offsetX, offsetY - 15));
        creator->setScale(0.3f);
        this->addChild(creator);

        //Creator Points
        int intCreatorPoints = getCreatorPoints(level->m_accountID);

        if (intCreatorPoints > 0) {
            //CreatorPoints
            std::string stringCreatorPoints = std::to_string(intCreatorPoints);
            int lengthOffset = stringCreatorPoints.length() - 1;

            auto creatorPoints = CCLabelBMFont::create(stringCreatorPoints.c_str(), "bigFont.fnt");
            creatorPoints->setPosition(getPosition(offsetX - (1 + lengthOffset*3), offsetY - 29));
            creatorPoints->setAnchorPoint({0.0f, 0.5f});
            creatorPoints->setScale(0.4f);
            this->addChild(creatorPoints);

            //CreatorPoints Sprite
            auto creatorPointSprite = CCSprite::createWithSpriteFrameName("GJ_hammerIcon_001.png");
            creatorPointSprite->setPosition(getPosition(offsetX - (7 + lengthOffset*3), offsetY - 29));
            creatorPointSprite->setScale(0.5f);
            this->addChild(creatorPointSprite);
        }
    }

    //Rewards
    void setup_rewards(GJGameLevel* level, int offsetY, int offsetX) {
        //Rewards Header
        auto rewardslabel = CCLabelBMFont::create("Rewards:", "goldFont.fnt");
        rewardslabel->setPosition(getPosition(offsetX, offsetY));
        rewardslabel->setScale(0.6f);
        this->addChild(rewardslabel);
    }

    // Helper Functions

    CCPoint getPosition(int xmod, int ymod) {
        return CCPoint(
            (CCDirector::get()->getScreenLeft() + CCDirector::get()->getScreenScaleFactorW() * xmod),
            (CCDirector::get()->getScreenTop() + CCDirector::get()->getScreenScaleFactorH() * ymod)
        );
    }

    std::string condence(int val) {
        if (val >= 1000000) {
            return std::to_string(val/1000000) + "m";
        }
        if (val >= 1000) {
            return std::to_string(val/1000) + "k";
        }
        return std::to_string(val);
    }

    int getCreatorPoints(int id) {
        auto GLM = GameLevelManager::sharedState();
        GLM->getGJUserInfo(id);
        GJUserScore* userInfo = GLM->userInfoForAccountID(id);

        if (!userInfo) {return -1;}

        return userInfo->m_creatorPoints;
    }
};

class $modify(MyPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

        GameLevelManager::sharedState()->getGJUserInfo(level->m_accountID);
        return true;
    }
};