#include "../BetterPause.h"

// Difficulty
void MyPauseLayer::setup_difficulty(const GJFeatureState feature_state, const int difficulty, int stars, const bool is_platformer, const int offsetY, const int offsetX) {
    constexpr auto diffType = GJDifficultyName::Short;

    const auto diffSprite = GJDifficultySprite::create(difficulty, diffType);

    diffSprite->updateDifficultyFrame(difficulty, diffType);
    diffSprite->updateFeatureState(feature_state);
    diffSprite->setPosition(getPosition(offsetX - 1, offsetY));
    diffSprite->setScale(0.7f);
    this->addChild(diffSprite);

    if (stars > 0) {
        std::string starOrMoon;
        if (is_platformer)
            starOrMoon = "moon_small01_001.png";
        else
            starOrMoon = "star_small01_001.png";

        const auto starSprite = CCSprite::createWithSpriteFrameName(starOrMoon.c_str());
        starSprite->setPosition(getPosition(offsetX - 6, offsetY - 22));
        starSprite->setScale(0.8f);
        this->addChild(starSprite);

        const auto starsLabel = CCLabelBMFont::create(
            fmt::format("{}", stars).c_str(),
            "bigFont.fnt"
        );
        starsLabel->setPosition(getPosition(offsetX + 4, offsetY - 22));
        starsLabel->setScale(0.3f);
        this->addChild(starsLabel);
    }
}

// Time
void MyPauseLayer::setup_time(const std::string v_time, const std::string v_timeLabel, const int offsetY, const int offsetX) {
    const auto timelabel = CCLabelBMFont::create("Time:", "goldFont.fnt");
    timelabel->setPosition(getPosition(offsetX, offsetY));
    timelabel->setScale(0.7f);
    this->addChild(timelabel);

    const auto time = CCLabelBMFont::create(v_time.c_str(), "bigFont.fnt");
    time->setPosition(getPosition(offsetX, offsetY - 25));
    time->setScale(0.3f);
    this->addChild(time);

    const auto timePlaceholder = CCLabelBMFont::create(v_timeLabel.c_str(), "bigFont.fnt");
    timePlaceholder->setPosition(getPosition(offsetX, offsetY - 15));
    timePlaceholder->setScale(0.4f);
    this->addChild(timePlaceholder);
}

// Stats
void MyPauseLayer::setup_stats(const int intDownloads, const int intLikes, const int offsetY, const int offsetX) {
    const auto likelabel = CCLabelBMFont::create("Stats:", "goldFont.fnt");
    likelabel->setPosition(getPosition(offsetX, offsetY));
    likelabel->setScale(0.7f);
    this->addChild(likelabel);

    const std::string strDownloads = condence(intDownloads);
    const int dowOffset = static_cast<int>(strDownloads.length()) - 1;

    const auto downloads = CCLabelBMFont::create(strDownloads.c_str(), "bigFont.fnt");
    downloads->setPosition(getPosition(offsetX - (4 + dowOffset*2), offsetY - 17));
    downloads->setAnchorPoint({0.0f, 0.5f});
    downloads->setScale(0.4f);
    this->addChild(downloads);

    const auto downloadsSprite = CCSprite::createWithSpriteFrameName("GJ_downloadsIcon_001.png");
    downloadsSprite->setPosition(getPosition(offsetX - (10 + dowOffset*2), offsetY - 17));
    downloadsSprite->setScale(0.5f);
    this->addChild(downloadsSprite);

    const std::string strLikes = condence(intLikes);
    const int likeOffset = static_cast<int>(strLikes.length()) - 1;

    const auto likes = CCLabelBMFont::create(strLikes.c_str(), "bigFont.fnt");
    likes->setPosition(getPosition(offsetX - (4 + likeOffset*2), offsetY - 30));
    likes->setAnchorPoint({0.0f, 0.5f});
    likes->setScale(0.4f);
    this->addChild(likes);

    const char* spriteLocation = intLikes < 0 ? "GJ_dislikesIcon_001.png" : "GJ_likesIcon_001.png";

    const auto likeSprite = CCSprite::createWithSpriteFrameName(spriteLocation);
    likeSprite->setPosition(getPosition(offsetX - (10 + likeOffset*2), offsetY - 30));
    likeSprite->setScale(0.5f);
    this->addChild(likeSprite);
}

// Creator
void MyPauseLayer::setup_creator(const std::string creatorName, const int intCreatorPoints, const int offsetY, const int offsetX) {
    const auto creatorlabel = CCLabelBMFont::create("Creator:", "goldFont.fnt");
    creatorlabel->setPosition(getPosition(offsetX, offsetY));
    creatorlabel->setScale(0.6f);
    this->addChild(creatorlabel);

    const auto creator = CCLabelBMFont::create(creatorName.c_str(), "bigFont.fnt");
    creator->setPosition(getPosition(offsetX, offsetY - 15));
    creator->setScale(0.3f);
    this->addChild(creator);

    if (intCreatorPoints > 0) {
        const std::string stringCreatorPoints = std::to_string(intCreatorPoints);
        const int lengthOffset = static_cast<int>(stringCreatorPoints.length()) - 1;

        const auto creatorPoints = CCLabelBMFont::create(stringCreatorPoints.c_str(), "bigFont.fnt");
        creatorPoints->setPosition(getPosition(offsetX - (1 + lengthOffset*3), offsetY - 29));
        creatorPoints->setAnchorPoint({0.0f, 0.5f});
        creatorPoints->setScale(0.4f);
        this->addChild(creatorPoints);

        const auto creatorPointSprite = CCSprite::createWithSpriteFrameName("GJ_hammerIcon_001.png");
        creatorPointSprite->setPosition(getPosition(offsetX - (7 + lengthOffset*3), offsetY - 29));
        creatorPointSprite->setScale(0.5f);
        this->addChild(creatorPointSprite);
    }
}

// Level ID
void MyPauseLayer::setup_id(const std::string stringID, const std::string stringUpdate, const int offsetY, const int offsetX) {
    const auto IDlabel = CCLabelBMFont::create("Level ID:", "goldFont.fnt");
    IDlabel->setPosition(getPosition(offsetX, offsetY));
    IDlabel->setScale(0.6f);
    this->addChild(IDlabel);

    const auto ID = CCLabelBMFont::create(stringID.c_str(), "bigFont.fnt");
    ID->setPosition(getPosition(offsetX, offsetY - 15));
    ID->setScale(0.4f);
    this->addChild(ID);

    const auto update = CCLabelBMFont::create(stringUpdate.c_str(), "bigFont.fnt");
    update->setPosition(getPosition(offsetX, offsetY - 30));
    update->setScale(0.4f);
    this->addChild(update);
}

// Rewards
void MyPauseLayer::setup_rewards(const bool hasOrbs, const bool hasDiamonds, const std::string orbs, const std::string diamonds, const int offsetY, const int offsetX) {
    const auto rewardslabel = CCLabelBMFont::create("Rewards:", "goldFont.fnt");
    rewardslabel->setPosition(getPosition(offsetX, offsetY));
    rewardslabel->setScale(0.6f);
    this->addChild(rewardslabel);

    if (!hasOrbs) {
        const auto creator = CCLabelBMFont::create("N/A", "bigFont.fnt");
        creator->setPosition(getPosition(offsetX, offsetY - 15));
        creator->setScale(0.4f);
        this->addChild(creator);
        return;
    }

    const int lengthOffsetOrbs = static_cast<int>(orbs.length()) - 1;
    const int lengthOffsetDiamonds = static_cast<int>(diamonds.length()) - 1;

    const auto orbText = CCLabelBMFont::create(orbs.c_str(), "bigFont.fnt");
    orbText->setPosition(getPosition(offsetX - (1 + lengthOffsetOrbs*3), offsetY - 15));
    orbText->setAnchorPoint({0.0f, 0.5f});
    orbText->setScale(0.4f);
    this->addChild(orbText);

    const auto orbSprite = CCSprite::createWithSpriteFrameName("currencyOrbIcon_001.png");
    orbSprite->setPosition(getPosition(offsetX - (7 + lengthOffsetOrbs*3), offsetY - 15));
    orbSprite->setScale(0.5f);
    this->addChild(orbSprite);

    if (!hasDiamonds) return;

    const auto diamondText = CCLabelBMFont::create(diamonds.c_str(), "bigFont.fnt");
    diamondText->setPosition(getPosition(offsetX - (1 + lengthOffsetDiamonds*3), offsetY - 30));
    diamondText->setAnchorPoint({0.0f, 0.5f});
    diamondText->setScale(0.4f);
    this->addChild(diamondText);

    const auto diamondSprite = CCSprite::createWithSpriteFrameName("GJ_diamondsIcon_001.png");
    diamondSprite->setPosition(getPosition(offsetX - (7 + lengthOffsetDiamonds*3), offsetY - 30));
    diamondSprite->setScale(0.5f);
    this->addChild(diamondSprite);
}