#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

class ScoreSystem
{
public:

	std::string* leaderboardNames = nullptr;
	std::string* leaderboardScores = nullptr;

	~ScoreSystem();

	static ScoreSystem* Instance();

	void AddMarioScore(int scoreToAdd) { m_MarioScore += scoreToAdd; }
	void AddLuigiScore(int scoreToAdd) { m_LuigiScore += scoreToAdd; }
	
	void RemoveMarioScore(int scoreToRemove) { m_MarioScore -= scoreToRemove; }
	void RemoveLuigiScore(int scoreToRemove) { m_LuigiScore -= scoreToRemove; }

	void ResetScores();

	int GetMarioScore() { return m_MarioScore; }
	int GetLuigiScore() { return m_LuigiScore; }

	bool LoadHighscores(std::string* leaderboardNames, std::string* leaderboardScores);

	void UpdateLeaderBoard(std::string playerName);

private:

	ScoreSystem();
	static ScoreSystem* m_instance;

	int m_MarioScore;
	int m_LuigiScore;
};

