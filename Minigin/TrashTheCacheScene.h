//#pragma once
//#include "Scene.h"
//
//struct Transform
//{
//	float matrix[16] = {
//		1,0,0,0,
//		0,1,0,0,
//		0,0,1,0,
//		0,0,0,1
//	};
//};
//
//class GameObject3D
//{
//public:
//	Transform transform;
//	int ID;
//};
//
//class GameObject3DAlt
//{
//public:
//	int ID;
//	Transform* transform;
//};
//
//
//class TrashTheCacheScene final : public dae::Scene
//{
//public:
//	explicit TrashTheCacheScene(const std::string& scenename);
//	void RenderImGui();
//
//private:
//	bool m_exercise1_active;
//	bool m_isCalculatingEx1;
//	int m_numSamplesEx1;
//	std::vector<float> m_averageEx1;
//	
//	bool m_exercise2_active;
//	bool m_isCalculatingEx2;
//	int m_numSamplesEx2;
//	std::vector<float> m_averageEx2Part1;
//	std::vector<float> m_averageEx2Part2;
//
//	void Exercise1();
//	void Exercise2();
//	std::vector<float> GetAverage(const std::vector<std::vector<long long>>& samples) const;
//
//	void RenderExercise1();
//	void RenderExercise2();
//};
//
