#pragma once

#include <ctime>
#include <optional>

#include "util/Utils.h"

/// @brief A struct that represents a date constraint.
struct DateConstraint
{
    /// @brief The date from which the constraint starts
    std::optional<std::tm> from = std::nullopt;

    /// @brief The date to which the constraint ends
    std::optional<std::tm> to = std::nullopt;

    /// @brief Checks if the given date is in the constraint. If the from or to values are ommited, they will be ignored.
    /// @param date The date to check
    /// @return Whether the date is in the constraint or not
    bool isDateInConstraint(std::tm date) const
    {
        if (from.has_value())
        {
            if (Utils::isDateBefore(date, from.value()))
            {
                return false;
            }
        }

        if (to.has_value())
        {
            if (Utils::isDateBefore(to.value(), date))
            {
                return false;
            }
        }

        return true;
    }
};