#include <iso646.h>

#include "../BetterPause.h"

void MyPauseLayer::checkMainLevels(Params* params, GJGameLevel* level) {
    const int id = level->m_levelID;
    const int percentage = level->m_normalPercent.value();

    switch (id) {
        case 1:
            // Stereo Madness
            constructRobtopLevelParam(params, "easy", percentage, 50, "1.0");
            break;
        case 2:
            // Back On Track
            constructRobtopLevelParam(params, "easy", percentage, 75, "1.0");
            break;
        case 3:
            // Polargeist
            constructRobtopLevelParam(params, "medium", percentage, 100, "1.0");
            break;
        case 4:
            // Dry Out
            constructRobtopLevelParam(params, "medium", percentage, 125, "1.0");
            break;
        case 5:
            // Base After Base
            constructRobtopLevelParam(params, "hard", percentage, 150, "1.0");
            break;
        case 6:
            // Can't Let Go
            constructRobtopLevelParam(params, "hard", percentage, 175, "1.0");
            break;
        case 7:
            // Jumper
            constructRobtopLevelParam(params, "harder", percentage, 200, "1.0");
            break;
        case 8:
            // Time Machine
            constructRobtopLevelParam(params, "harder", percentage, 225, "1.1");
            break;
        case 9:
            // Cycles
            constructRobtopLevelParam(params, "harder", percentage, 250, "1.2");
            break;
        case 10:
            // xStep
            constructRobtopLevelParam(params, "insane", percentage, 275, "1.3");
            break;
        case 11:
            // Clutterfunk
            constructRobtopLevelParam(params, "insane", percentage, 300, "1.4");
            break;
        case 12:
            // Theory Of Everything
            constructRobtopLevelParam(params, "insane", percentage, 325, "1.5");
            break;
        case 13:
            // Electroman Adventures
            constructRobtopLevelParam(params, "insane", percentage, 275, "1.6");
            break;
        case 14:
            // Clubstep
            constructRobtopLevelParam(params, "demon", percentage, 500, "1.6");
            break;
        case 15:
            // Electrodynamics
            constructRobtopLevelParam(params, "insane", percentage, 325, "1.7");
            break;
        case 16:
            // Hexagon Force
            constructRobtopLevelParam(params, "insane", percentage, 325, "1.8");
            break;
        case 17:
            // Blast Processing
            constructRobtopLevelParam(params, "harder", percentage, 275, "1.9");
            break;
        case 18:
            // Theory Of Everything 2
            constructRobtopLevelParam(params, "demon", percentage, 500, "1.9");
            break;
        case 19:
            // Geometrical Dominator
            constructRobtopLevelParam(params, "harder", percentage, 275, "2.0");
            break;
        case 20:
            // Deadlocked
            constructRobtopLevelParam(params, "demon", percentage, 500, "2.0");
            break;
        case 21:
            // Fingerdash
            constructRobtopLevelParam(params, "insane", percentage, 325, "2.1");
            break;
        case 22:
            // Dash
            constructRobtopLevelParam(params, "insane", percentage, 325, "2.2");
            break;
        case 5001:
            // The Tower
            constructRobtopPlatformerParam(params, "hard", percentage, 125, "2.2");
            break;
        case 5002:
            // The Sewers
            constructRobtopPlatformerParam(params, "harder", percentage, 225, "2.2");
            break;
        case 5003:
            // The Cellar
            constructRobtopPlatformerParam(params, "insane", percentage, 275, "2.2");
            break;
        case 5004:
            // The Secret Hollow
            constructRobtopPlatformerParam(params, "insane", percentage, 275, "2.2");
            break;
        case 3001:
            // The Secret Hollow
            constructRobtopLevelParam(params, "normal", percentage, 75, "2.1");
            params->timeLabel = "Tiny";
            break;
    }
}

void MyPauseLayer::constructRobtopLevelParam(Params* params, std::string difficulty, int percentage, int max_orbs, std::string update) {
    params->feature_state = GJFeatureState::Featured;
    params->timeLabel = "Long";
    params->creator = "Robtop";
    params->creator_points = 1;

    params->difficulty = convertDifficulty(difficulty);

    int orbs = getCurrentOrbs(percentage, max_orbs);
    params->orbs = std::to_string(orbs) + "/" + std::to_string(max_orbs);
    params->hasOrbs = true;
    params->hasDiamonds = false;

    params->update = "Update: " + update;
}

void MyPauseLayer::constructRobtopPlatformerParam(Params* params, std::string difficulty, int percentage, int max_orbs, std::string update) {
    params->feature_state = GJFeatureState::Featured;
    params->time = "N/A";
    params->creator = "Robtop";
    params->creator_points = 1;

    params->difficulty = convertDifficulty(difficulty);

    int orbs = getCurrentOrbs(percentage, max_orbs);
    params->orbs = std::to_string(orbs) + "/" + std::to_string(max_orbs);
    params->hasOrbs = true;
    params->hasDiamonds = false;

    params->update = "Update: " + update;
}

int MyPauseLayer::convertDifficulty(std::string difficulty) {
    if (difficulty == "easy") {
        return 1;
    } if (difficulty == "medium") {
        return 2;
    } if (difficulty == "hard") {
        return 3;
    } if (difficulty == "harder") {
        return 4;
    } if (difficulty == "insane") {
        return 5;
    } if (difficulty == "demon") {
        return 6;
    }
    return -1;
}

void MyPauseLayer::checkEasterEggs(Params* params, GJGameLevel* level) {
    const int id = level->m_levelID;

    switch (id) {
        case 97253886:
            params->feature_state = GJFeatureState::Mythic;
            break;
        case 3001:
            params->difficulty = 10;
    }
}