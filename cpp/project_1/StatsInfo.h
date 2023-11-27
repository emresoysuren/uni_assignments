#pragma once

/// @brief A struct to represent the stats info to be shown in the stats tables
struct StatsInfo
{
    int goals = 0, wins = 0, draws = 0, losses = 0;

    /// @brief Checks if all the stats are zero
    bool isAllZero() const
    {
        return goals == 0 && wins == 0 && draws == 0 && losses == 0;
    }
};