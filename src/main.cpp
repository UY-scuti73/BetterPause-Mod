#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <string>

using namespace geode::prelude;

class $modify(MyPauseLayer, PauseLayer) {

    void customSetup() override {
        PauseLayer::customSetup();

        auto playLayer = PlayLayer::get();
        if (playLayer == nullptr) {return;}
        auto level = playLayer->m_level;

        bool difficultySet = Mod::get()->getSettingValue<bool>("difficulty");
        bool timeSet = Mod::get()->getSettingValue<bool>("time");
        bool statsSet = Mod::get()->getSettingValue<bool>("stats");
        bool creatorSet = Mod::get()->getSettingValue<bool>("creator");
        bool idSet = Mod::get()->getSettingValue<bool>("id");
        bool rewardsSet = Mod::get()->getSettingValue<bool>("rewards");

        float x_offset = Mod::get()->getSettingValue<float>("x_offset");

        int center = calculateOffset(x_offset);
        int yoffset = -40;

        if (difficultySet) {
            setup_difficulty(level, yoffset, center);
            yoffset -= 39;
        }
        if (timeSet) {
            setup_time(level, playLayer, yoffset, center);
            yoffset -= 44;
        }
        if (statsSet) {
            setup_stats(level, yoffset, center);
            yoffset -= 49;
        }
        if (creatorSet) {
            setup_creator(level, yoffset, center);
            yoffset -= 47;
        }
        if (idSet) {
            setup_id(level, yoffset, center);
            yoffset -= 49;
        }
        if (rewardsSet)
        {
            setup_rewards(level, yoffset, center);
        }
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
            std::string starOrMoon;
            if (level->isPlatformer()) {starOrMoon = "moon_small01_001.png";}
            else {starOrMoon = "star_small01_001.png";}

            auto starSprite = CCSprite::createWithSpriteFrameName(starOrMoon.c_str());
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

    //Level ID
    void setup_id(GJGameLevel* level, int offsetY, int offsetX) {
        //ID Header
        auto IDlabel = CCLabelBMFont::create("Level ID:", "goldFont.fnt");
        IDlabel->setPosition(getPosition(offsetX, offsetY));
        IDlabel->setScale(0.6f);
        this->addChild(IDlabel);

        std::string stringID = std::to_string(level->m_levelID.value());

        // ID
        auto ID = CCLabelBMFont::create(stringID.c_str(), "bigFont.fnt");
        ID->setPosition(getPosition(offsetX, offsetY - 15));
        ID->setScale(0.4f);
        this->addChild(ID);

        std::string stringUpdate = "Update: " + getUpdate(level->m_levelID.value());

        // Update
        auto update = CCLabelBMFont::create(stringUpdate.c_str(), "bigFont.fnt");
        update->setPosition(getPosition(offsetX, offsetY - 30));
        update->setScale(0.4f);
        this->addChild(update);
    }

    //Rewards
    void setup_rewards(GJGameLevel* level, int offsetY, int offsetX) {
        //Rewards Header
        auto rewardslabel = CCLabelBMFont::create("Rewards:", "goldFont.fnt");
        rewardslabel->setPosition(getPosition(offsetX, offsetY));
        rewardslabel->setScale(0.6f);
        this->addChild(rewardslabel);

        if (level->m_stars <= 1) {
            auto creator = CCLabelBMFont::create("N/A", "bigFont.fnt");
            creator->setPosition(getPosition(offsetX, offsetY - 15));
            creator->setScale(0.4f);
            this->addChild(creator);
            return;
        }

        int max_orbs;
        int max_diamonds;

        getRewards(level->m_stars, max_orbs, max_diamonds);

        int current_orbs = getCurrentOrbs(level->m_normalPercent.value(), max_orbs);
        int current_diamonds = getCurrentDiamonds(level->m_normalPercent.value(), max_diamonds);

        std::string orbs = std::to_string(current_orbs) + "/" + std::to_string(max_orbs);
        std::string diamonds = std::to_string(current_diamonds) + "/" + std::to_string(max_diamonds);

        int lengthOffsetOrbs = orbs.length() - 1;
        int lengthOffsetDiamonds = diamonds.length() - 1;

        //Orbs Text
        auto orbText = CCLabelBMFont::create(orbs.c_str(), "bigFont.fnt");
        orbText->setPosition(getPosition(offsetX - (1 + lengthOffsetOrbs*3), offsetY - 15));
        orbText->setAnchorPoint({0.0f, 0.5f});
        orbText->setScale(0.4f);
        this->addChild(orbText);

        //Orbs Sprite
        auto orbSprite = CCSprite::createWithSpriteFrameName("currencyOrbIcon_001.png");
        orbSprite->setPosition(getPosition(offsetX - (7 + lengthOffsetOrbs*3), offsetY - 15));
        orbSprite->setScale(0.5f);
        this->addChild(orbSprite);

        if (!hasDiamonds(level)) {return;}

        //Diamonds Text
        auto diamondText = CCLabelBMFont::create(diamonds.c_str(), "bigFont.fnt");
        diamondText->setPosition(getPosition(offsetX - (1 + lengthOffsetDiamonds*3), offsetY - 30));
        diamondText->setAnchorPoint({0.0f, 0.5f});
        diamondText->setScale(0.4f);
        this->addChild(diamondText);

        //Diamonds Sprite
        auto diamondSprite = CCSprite::createWithSpriteFrameName("GJ_diamondsIcon_001.png");
        diamondSprite->setPosition(getPosition(offsetX - (7 + lengthOffsetDiamonds*3), offsetY - 30));
        diamondSprite->setScale(0.5f);
        this->addChild(diamondSprite);
    }

    // Helper Functions

    int calculateOffset(float offset) {
        int left_offset = 45;
        float constant = 195;

        offset = offset + 1;

        return static_cast<int>((offset * constant) + left_offset);
    }

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

    // Get Update
    std::string getUpdate(int id) {
        if (id < 1000) {
            return "1.0";
        } else if (id < 1800) {
            return "1.1";
        } else if (id < 10000) {
            return "1.2";
        } else if (id < 20000) {
            return "1.3";
        } else if (id < 100000) {
            return "1.4";
        } else if (id < 426309) {
            return "1.5";
        } else if (id < 835854) {
            return "1.6";
        } else if (id < 1629780) {
            return "1.7";
        } else if (id < 2814868) {
            return "1.8";
        } else if (id < 11000000) {
            return "1.9";
        } else if (id < 28600000) {
            return "2.0";
        } else if (id < 97500000) {
            return "2.1";
        } else {
            return "2.2";
        }
    }

    // Reward Helper Functions
    int getCurrentOrbs(int percentage, int max_orbs) {
        if (percentage < 100) {
            double temp = max_orbs * 0.8 * percentage;
            return std::floor(temp/100);
        } else {
            return max_orbs;
        }
    }

    int getCurrentDiamonds(int percentage, int max_diamonds) {
        return std::floor((percentage/100.0) * max_diamonds);
    }

    void getRewards(int stars, int& max_orbs, int& max_diamonds) {
        switch (stars) {
            case 2:
                max_orbs = 50;
                max_diamonds = 4;
                break;
            case 3:
                max_orbs = 75;
                max_diamonds = 5;
                break;
            case 4:
                max_orbs = 125;
                max_diamonds = 6;
                break;
            case 5:
                max_orbs = 175;
                max_diamonds = 7;
                break;
            case 6:
                max_orbs = 225;
                max_diamonds = 8;
                break;
            case 7:
                max_orbs = 275;
                max_diamonds = 9;
                break;
            case 8:
                max_orbs = 350;
                max_diamonds = 10;
                break;
            case 9:
                max_orbs = 425;
                max_diamonds = 11;
                break;
            case 10:
                max_orbs = 500;
                max_diamonds = 12;
                break;
            default:
                max_orbs = -1;
                max_diamonds = -1;
        }
    }

    bool hasDiamonds(GJGameLevel* level) {
        if (level->m_dailyID > 0 || level->m_gauntletLevel || level->m_gauntletLevel2) {return true;}
        return false;
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