#pragma once

#include <vector>

struct AutomationPoint
{
    float time = 0.0f;

    float value = 0.0f;
};

class AutomationLane
{
public:

    void addPoint(
        float time,
        float value)
    {
        points.push_back(
            { time, value });
    }

    float evaluate(
        float time) const
    {
        if (points.empty())
            return 0.0f;

        if (time <= points.front().time)
            return points.front().value;

        for (std::size_t i = 1;
             i < points.size();
             ++i)
        {
            if (time < points[i].time)
            {
                const auto& a =
                    points[i - 1];

                const auto& b =
                    points[i];

                float t =
                    (time - a.time) /
                    (b.time - a.time);

                return
                    a.value +
                    t *
                    (b.value -
                     a.value);
            }
        }

        return
            points.back().value;
    }

    void clear()
    {
        points.clear();
    }

private:

    std::vector<
        AutomationPoint>
            points;
};