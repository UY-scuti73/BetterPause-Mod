#include "../BetterPause.h"

void MyPauseLayer::customSetup() {
    PauseLayer::customSetup();

    Config config = Config();

    auto playLayer = PlayLayer::get();
    if (playLayer == nullptr) return;

    auto level = playLayer->m_level;

    Params params = getParams(level, playLayer);
    checkMainLevels(&params, level);

    if (config.easterEggs) {
        checkEasterEggs(&params, level);
    }

    setup(params, config);
}

void MyPauseLayer::setup(const Params& params, Config config) {
    const int center = calculateOffset(config.x_offset);
    int yoffset = -40;

    if (config.difficultySet) {
        setup_difficulty(params.feature_state, params.difficulty, params.stars, params.is_platformer, yoffset, center);
        yoffset -= 39;
    }
    if (config.timeSet) {
        setup_time(params.time, params.timeLabel, yoffset, center);
        yoffset -= 44;
    }
    if (config.statsSet) {
        setup_stats(params.downloads, params.likes, yoffset, center);
        yoffset -= 49;
    }
    if (config.creatorSet) {
        setup_creator(params.creator, params.creator_points, yoffset, center);
        yoffset -= 47;
    }
    if (config.idSet) {
        setup_id(params.id, params.update, yoffset, center);
        yoffset -= 49;
    }
    if (config.rewardsSet) {
        setup_rewards(params.hasOrbs, params.hasDiamonds, params.orbs, params.diamonds, yoffset, center);
    }
}

MyPauseLayer::Params MyPauseLayer::getParams(GJGameLevel* level, PlayLayer* playLayer) {
    Params params = Params();

    // Difficulty
    GJDifficultyName diffType = GJDifficultyName::Short;
    int difficulty;
    if (level->m_demon > 0) {
        difficulty = level->demonIconForDifficulty(
            static_cast<DemonDifficultyType>(level->m_demonDifficulty)
        );
    } else {
        difficulty = level->getAverageDifficulty();
    }

    const auto diffSprite = GJDifficultySprite::create(difficulty, diffType);
    diffSprite->updateDifficultyFrame(difficulty, diffType);
    diffSprite->updateFeatureStateFromLevel(level);

    params.feature_state = diffSprite->m_featureState;
    params.difficulty = difficulty;
    params.stars = level->m_stars;
    params.is_platformer = level->isPlatformer();

    // Time
    const auto endPos = CCPoint(playLayer->m_levelLength, 0);
    const int a = playLayer->timeForPos(endPos, 0, 0, false, 0);
    const int b = (level->m_timestamp) / 240;
    const int totalSeconds = std::max(a, b);
    const int minutes = totalSeconds / 60;
    const int seconds = totalSeconds % 60;

    const std::string v_time = std::to_string(minutes) + "m " + std::to_string(seconds) + "s";
    const std::string v_timeLabel = level->lengthKeyToString(level->m_levelLength);

    params.time = v_time;
    params.timeLabel = v_timeLabel;

    // Stats
    const int downloads = level->m_downloads;
    const int likes = level->m_likes;

    params.downloads = downloads;
    params.likes = likes;

    // Creator
    params.creator = level->m_creatorName;
    params.creator_points = getCreatorPoints(level->m_accountID);

    // ID
    std::string stringID = std::to_string(level->m_levelID.value());

    double versionVal = static_cast<double>(level->m_gameVersion)/10;
    std::string stringUpdate = "Update: " + std::format("{:.1f}", versionVal);

    params.id = stringID;
    params.update = stringUpdate;

    // Rewards
    int max_orbs;
    int max_diamonds;
    getRewards(level->m_stars, max_orbs, max_diamonds);

    const int current_orbs = getCurrentOrbs(level->m_normalPercent.value(), max_orbs);
    const int current_diamonds = getCurrentDiamonds(level->m_normalPercent.value(), max_diamonds);

    const std::string orbs = std::to_string(current_orbs) + "/" + std::to_string(max_orbs);
    const std::string diamonds = std::to_string(current_diamonds) + "/" + std::to_string(max_diamonds);

    bool hasOrbs;
    if (level->m_stars <= 1) {hasOrbs = false;} else {hasOrbs = true;}

    const bool hasDiamond = hasDiamonds(level);

    params.orbs = orbs;
    params.diamonds = diamonds;
    params.hasOrbs = hasOrbs;
    params.hasDiamonds = hasDiamond;

    return params;
}

MyPauseLayer::Params::Params() {
    feature_state = GJFeatureState::None;
    difficulty = -1;
    stars = 0;
    is_platformer = false;
    time = "";
    timeLabel = "";
    downloads = 0;
    likes = 0;
    creator = "";
    creator_points = 0;
    id = "";
    update = "";
    orbs = "";
    diamonds = "";
    hasOrbs = false;
    hasDiamonds = false;
}

MyPauseLayer::Config::Config() {
    difficultySet = Mod::get()->getSettingValue<bool>("difficulty");
    timeSet       = Mod::get()->getSettingValue<bool>("time");
    statsSet      = Mod::get()->getSettingValue<bool>("stats");
    creatorSet    = Mod::get()->getSettingValue<bool>("creator");
    idSet         = Mod::get()->getSettingValue<bool>("id");
    rewardsSet    = Mod::get()->getSettingValue<bool>("rewards");

    x_offset = Mod::get()->getSettingValue<float>("x_offset");

    easterEggs = Mod::get()->getSettingValue<bool>("easter_eggs");
}