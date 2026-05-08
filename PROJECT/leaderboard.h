#pragma once
#include <wx/wx.h>
#include <vector>
#include <algorithm>
#include <fstream>

struct LeaderboardEntry {
    wxString name;
    int      score;
    wxString difficulty;
};

class Leaderboard {
public:
    static const int MAX_ENTRIES = 5;

    void Load() {
        myentries.clear();
        std::ifstream file("leaderboard.txt");
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            wxString wx(line);
            wxArrayString parts = wxSplit(wx, ',');
            if (parts.size() != 3) continue;

            LeaderboardEntry entry;
            entry.name = parts[0].Trim();
            entry.score = wxAtoi(parts[1].Trim());
            entry.difficulty = parts[2].Trim();
            myentries.push_back(entry);
        }

        SortAndTrim();
    }

    void Save() {
        std::ofstream file("leaderboard.txt", std::ios::trunc);
        if (!file.is_open()) return;

        for (const auto& entry : myentries)
            file << entry.name.ToStdString() << ","
            << entry.score << ","
            << entry.difficulty.ToStdString() << "\n";
    }

    // Add a new score, keep only top 5
    void AddEntry(const wxString& name, int score, const wxString& difficulty) {
        LeaderboardEntry entry;
        entry.name = name.IsEmpty() ? "Anonymous" : name;
        entry.score = score;
        entry.difficulty = difficulty;
        myentries.push_back(entry);
        SortAndTrim();
        Save();
    }

    const std::vector<LeaderboardEntry>& GetEntries() const { return myentries; }

    static wxString DifficultyLabel(int d) {
        const wxString labels[] = { "Easy", "Medium", "Hard", "Insane" };
        if (d >= 0 && d < 4) return labels[d];
        return "Unknown";
    }

private:
    std::vector<LeaderboardEntry> myentries;

    void SortAndTrim() {
        std::sort(myentries.begin(), myentries.end(),
            [](const LeaderboardEntry& a, const LeaderboardEntry& b) {
                return a.score > b.score;
            });
        if ((int)myentries.size() > MAX_ENTRIES)
            myentries.resize(MAX_ENTRIES);
    }
};