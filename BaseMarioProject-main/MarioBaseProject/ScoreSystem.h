#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class ScoreSystem
{
public:

	~ScoreSystem();

	static ScoreSystem* Instance();

	void AddMarioScore(int scoreToAdd) { m_MarioScore += scoreToAdd; }
	void AddLuigiScore(int scoreToAdd) { m_LuigiScore += scoreToAdd; }
	
	void RemoveMarioScore(int scoreToRemove) { m_MarioScore -= scoreToRemove; }
	void RemoveLuigiScore(int scoreToRemove) { m_LuigiScore -= scoreToRemove; }

	int GetMarioScore() { return m_MarioScore; }
	int GetLuigiScore() { return m_LuigiScore; }

	bool LoadHighscores(std::string* leaderboardNames, std::string* leaderboardScores);

private:

	ScoreSystem();
	static ScoreSystem* m_instance;

	int m_MarioScore;
	int m_LuigiScore;
};

