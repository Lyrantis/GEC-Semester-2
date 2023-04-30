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
