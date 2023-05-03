#include "ScoreSystem.h"

ScoreSystem* ScoreSystem::m_instance = nullptr;

ScoreSystem::ScoreSystem()
{
	m_MarioScore = 0;
	m_LuigiScore = 0;
}

ScoreSystem::~ScoreSystem()
{
	m_instance = nullptr;
}

ScoreSystem* ScoreSystem::Instance()
{
	if (!m_instance) {
		m_instance = new ScoreSystem;
	}

	return m_instance;
}

bool ScoreSystem::LoadHighscores(std::string* leaderboardNames, std::string* leaderboardScores)
{
	std::ifstream fileIn;
	
	fileIn.open("txt/LeaderBoard.txt");

	if (!fileIn.good())
	{
		std::cout << "Failed to load leaderboard!\n";
		return false;
	}

	std::string currentLine;
	std::string name;
	std::string score;
	std::stringstream lineStream(currentLine);
	std::vector<std::string> namesIn;
	std::vector<std::string> scoresIn;


	while (!fileIn.eof())
	{
		std::getline(fileIn, currentLine, '\n');
		std::getline(lineStream, name, ' ');
		std::getline(lineStream, score, ' ');

		namesIn.push_back(name);
		scoresIn.push_back(score);
	}

	for (int i = 0; i < namesIn.size(); i++)
	{
		leaderboardNames[i] = namesIn[i];
		leaderboardScores[i] = scoresIn[i];
	}

	for (int i = namesIn.size(); i < 5; i++)
	{
		leaderboardNames[i] = "---";
		leaderboardScores[i] = "---";
	}

	
	return true;
}
