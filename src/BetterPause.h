#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <string>

using namespace geode::prelude;

// Forward declarations
class MyPauseLayer;
class MyPlayLayer;

// MyPauseLayer declaration
class $modify(MyPauseLayer, PauseLayer) {
    public:
    void customSetup() override;

    private:
    struct Params {
        GJFeatureState feature_state;
        int difficulty;
        int stars;
        bool is_platformer;
        std::string time;
        std::string timeLabel;
        int downloads;
        int likes;
        std::string creator;
        int creator_points;
        std::string id;
        std::string update;
        std::string orbs;
        std::string diamonds;
        bool hasOrbs;
        bool hasDiamonds;
        Params();
    };

    struct Config {
        bool difficultySet;
        bool timeSet;
        bool statsSet;
        bool creatorSet;
        bool idSet;
        bool rewardsSet;
        float x_offset;
        bool easterEggs;
        Config();
    };

    void setup(const Params& params, Config config);
    Params getParams(GJGameLevel* level, PlayLayer* playLayer);

    // Setup sections
    void setup_difficulty(GJFeatureState feature_state, int difficulty, int stars, bool is_platformer, int offsetY, int offsetX);
    void setup_time(std::string v_time, std::string v_timeLabel, int offsetY, int offsetX);
    void setup_stats(int intDownloads, int intLikes, int offsetY, int offsetX);
    void setup_creator(std::string creatorName, int intCreatorPoints, int offsetY, int offsetX);
    void setup_id(std::string stringID, std::string stringUpdate, int offsetY, int offsetX);
    void setup_rewards(bool hasOrbs, bool hasDiamonds, std::string orbs, std::string diamonds, int offsetY, int offsetX);

    // Helper functions
    int calculateOffset(float offset);
    cocos2d::CCPoint getPosition(int xmod, int ymod);
    std::string condence(int val);
    int getCreatorPoints(int id);
    std::string getUpdate(int id);

    // Reward helpers
    int getCurrentOrbs(int percentage, int max_orbs);
    int getCurrentDiamonds(int percentage, int max_diamonds);
    void getRewards(int stars, int& max_orbs, int& max_diamonds);
    bool hasDiamonds(GJGameLevel* level);

    // Exceptions
    void checkMainLevels(Params* params, GJGameLevel* level);
    void constructRobtopLevelParam(Params* params, std::string difficulty, int percentage, int max_orbs, std::string update);
    void constructRobtopPlatformerParam(Params* params, std::string difficulty, int percentage, int max_orbs, std::string update);
    int convertDifficulty(std::string difficulty);

    void checkEasterEggs(Params* params, GJGameLevel* level);
};

// MyPlayLayer declaration
class $modify(MyPlayLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects);
};