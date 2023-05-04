#include "ScoreSystem.h"

ScoreSystem* ScoreSystem::m_instance = nullptr;

ScoreSystem::ScoreSystem()
{
	m_MarioScore = 300;
	m_LuigiScore = 800;

	leaderboardNames = new std::string[5];
	leaderboardScores = new std::string[5];

	LoadHighscores(leaderboardNames, leaderboardScores);

	for (int i = 0; i < 5; i++)
	{
		std::cout << leaderboardNames[i] << " " << leaderboardScores[i] << std::endl;
	}

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
	std::vector<std::string> namesIn;
	std::vector<std::string> scoresIn;


	while (!fileIn.eof())
	{
		std::getline(fileIn, currentLine, '\n');
		std::stringstream lineStream(currentLine);
		std::getline(lineStream, name, ' ');
		std::getline(lineStream, score, ' ');


		namesIn.push_back(name.c_str());
		scoresIn.push_back(score.c_str());
	}

	for (int i = 0; i < namesIn.size(); i++)
	{
		leaderboardNames[i] = namesIn[i].c_str();
		leaderboardScores[i] = scoresIn[i].c_str();
	}

	for (int i = namesIn.size(); i < 5; i++)
	{
		leaderboardNames[i] = "---";
		leaderboardScores[i] = "---";
	}

	fileIn.close();

	return true;
}

void ScoreSystem::UpdateLeaderBoard(std::string playerName)
{
	int playerScoreTotal = m_MarioScore + m_LuigiScore;
	int playerPos = 0;

	for (int i = 0; i < 5; i++)
	{
		if (stoi(leaderboardScores[i]) >= playerScoreTotal)
		{
			playerPos++;
		}
	}

	if (playerPos < 5)
	{

		for (int i = 3; i > playerPos - 1; i--)
		{
			leaderboardNames[i + 1] = leaderboardNames[i];
			leaderboardScores[i + 1] = leaderboardScores[i];
		}

		leaderboardNames[playerPos] = playerName;
		leaderboardScores[playerPos] = std::to_string(playerScoreTotal);
	}

	std::ofstream fileOut;
	fileOut.open("txt/LeaderBoard.txt");

	for (int i = 0; i < 5; i++)
	{
		if (leaderboardNames[i] != "---")
		{
			fileOut << leaderboardNames[i] << " " << leaderboardScores[i];

			if (i != 4)
			{
				fileOut << "\n";
			}
		}

	}

	fileOut.close();
}
