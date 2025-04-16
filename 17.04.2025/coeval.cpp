#include <iostream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>

struct Date
{
    int day;
    int month;
    int year;

    Date() {}
    Date(int day, int month, int year) : day{day}, month{month}, year{year} {}

    Date add_years(int years)
    {
        Date new_date(day, month, year);
        new_date.year += years;
        return new_date;
    }

    bool operator<(const Date date) const
    {
        if (year == date.year)
        {
            if (month == date.month)
                return day < date.day;
            return month < date.month;
        }
        return year < date.year;
    }

    bool operator>(const Date date) const
    {
        return !(*this < date || *this == date);
    }

    bool operator==(const Date date) const
    {
        return day == date.day && month == date.month && year == date.year;
    }
};

size_t solution(std::vector<std::pair<Date, Date>> people)
{
    std::priority_queue<Date, std::vector<Date>, std::greater<Date>> ends;

    // выделяем период, когда человек мог быть на собрании
    
    std::vector<std::pair<Date, Date>> new_people;
    for (int i = 0; i < people.size(); ++i)
    {
        std::pair<Date, Date> new_date;
        new_date.first = people[i].first.add_years(18);
        new_date.second = std::min(people[i].second, people[i].first.add_years(80));
        if (new_date.first < new_date.second)
            new_people.push_back(new_date);
    }

    std::sort(new_people.begin(), new_people.end());
    size_t result = 0;
    for (int i = 0; i < new_people.size(); ++i)
    {
        if (!ends.empty())
        {
            Date top = ends.top();
            while (top < new_people[i].first)
            {
                ends.pop();
                top = ends.top();
            }
        }
        ends.push(new_people[i].second);
        result = std::max(result, ends.size());
    }
    return result;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::pair<Date, Date>> dates;
    for (int i = 0; i < n; ++i)
    {
        std::pair<Date, Date> pair;
        int day, month, year;

        std::cin >> day >> month >> year;
        pair.first = Date(day, month, year);
        std::cin >> day >> month >> year;
        pair.second = Date(day, month, year);

        dates.push_back(pair);
    }

    std::cout << solution(dates);
}