//#include "TrashTheCacheScene.h"
//#include <imgui.h>
//#include <chrono>
//#include <imgui_plot.h>
//
//
//TrashTheCacheScene::TrashTheCacheScene(const std::string& scenename)
//	:dae::Scene(scenename)
//	, m_exercise1_active{ true }
//	, m_exercise2_active{ true }
//	, m_isCalculatingEx1{ false }
//	, m_isCalculatingEx2{ false }
//	, m_numSamplesEx1{ 10 }
//	, m_numSamplesEx2{ 10 }
//	, m_averageEx1{}
//{
//}
//
//void TrashTheCacheScene::RenderImGui()
//{
//	RenderExercise1();
//	RenderExercise2();
//}
//
//void TrashTheCacheScene::RenderExercise1()
//{
//	ImGui::Begin("Exercise 1", &m_exercise1_active);
//	ImGui::SliderInt("# samples", &m_numSamplesEx1, 0, 20);
//	if (m_isCalculatingEx1)
//	{
//		ImGui::Text("Processing...");
//	}
//	else
//	{
//		if (ImGui::Button("Trash the cache"))
//		{
//			m_isCalculatingEx1 = true;
//			Exercise1();
//			m_isCalculatingEx1 = false;
//		}
//	}
//
//	if (m_averageEx1.size() > 0)
//	{
//		//ImGui::PlotLines("Samples", m_averageEx1.data(), int(m_averageEx1.size()), 0, nullptr, 0.0f, 1.0f, ImVec2(0, 80));
//		//ImGui::Text("Draw Plot...");
//
//		ImGui::PlotConfig conf;
//		//conf.values.xs = x_data; // this line is optional
//		conf.values.ys = m_averageEx1.data();
//		conf.values.count = int(m_averageEx1.size());
//		conf.scale.min = 0;
//		conf.scale.max = m_averageEx1[0];
//		conf.tooltip.show = true;
//		conf.tooltip.format = "x=%.0f, y=%.2f";
//		//conf.grid_x.show = true;
//		conf.grid_y.show = true;
//		conf.frame_size = ImVec2(200, 200);
//		conf.line_thickness = 1.f;
//
//		ImGui::Plot("Ex 1", conf);
//
//	}
//	ImGui::End();
//}
//
//void TrashTheCacheScene::RenderExercise2()
//{
//	ImGui::Begin("Exercise 2", &m_exercise2_active);
//	ImGui::SliderInt("# samples", &m_numSamplesEx2, 0, 100);
//	if (m_isCalculatingEx2)
//	{
//		ImGui::Text("Processing...");
//	}
//	else
//	{
//		if (ImGui::Button("Trash the cache"))
//		{
//			m_isCalculatingEx2 = true;
//			Exercise2();
//			m_isCalculatingEx2 = false;
//		}
//	}
//	
//	if (m_averageEx2Part2.size() > 0 && m_averageEx2Part1.size() > 0 && m_averageEx2Part2.size() == m_averageEx2Part1.size())
//	{
//		static ImU32 colors[2] = { ImColor(0, 255, 0), ImColor(255, 0, 0)};
//		const float* y_data[] = { m_averageEx2Part1.data(), m_averageEx2Part2.data() };
//
//		ImGui::PlotConfig conf;
//		//conf.values.xs = x_data; // this line is optional
//		conf.values.ys_list = y_data;
//		//conf.values.ys = m_averageEx2Part2.data();
//		conf.values.count = int(m_averageEx2Part2.size());
//		conf.scale.min = 0;
//		conf.scale.max = m_averageEx2Part2[0];
//		conf.values.colors = colors;
//		conf.tooltip.show = true;
//		conf.tooltip.format = "x=%.0f, y=%.2f";
//		conf.grid_y.show = true;
//		conf.frame_size = ImVec2(200, 200);
//		conf.line_thickness = 1.f;
//
//		ImGui::Plot("Combined", conf);
//	}
//	ImGui::End();
//}
//
//void TrashTheCacheScene::Exercise1()
//{
//	const uint32_t size = int(powf(2, 26));
//	const uint32_t iterations = 11;
//	const uint32_t sampleSize = m_numSamplesEx1;
//
//	std::unique_ptr<int[]> pInts = std::make_unique<int[]>(size);
//
//	
//	std::vector<std::vector<long long>> samples;
//
//	for (size_t sampleIndex = 0; sampleIndex < sampleSize; sampleIndex++)
//	{
//		samples.emplace_back(std::vector<long long>());
//		uint32_t stepsize = 1;
//		for (size_t it = 0; it < iterations; it++)
//		{
//			auto start = std::chrono::high_resolution_clock::now();
//			for (size_t i = 0; i < size; i += stepsize)
//			{
//				pInts.get()[i] *= 2;
//			}
//			auto end = std::chrono::high_resolution_clock::now();
//			auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//
//			samples[sampleIndex].emplace_back(elapsed);
//			stepsize *= 2;
//		}
//	}
//	m_averageEx1.clear();
//	m_averageEx1 = GetAverage(samples);
//}
//
//void TrashTheCacheScene::Exercise2()
//{
//	const uint32_t size = int(powf(2, 24));
//	const uint32_t iterations = 11;
//	const uint32_t sampleSize = m_numSamplesEx2;
//
//	std::unique_ptr<GameObject3D*> pGameObjects = std::make_unique<GameObject3D*>(size);
//
//	std::vector<std::vector<long long>> samples;
//
//	for (size_t sampleIndex = 0; sampleIndex < sampleSize; sampleIndex++)
//	{
//		samples.emplace_back(std::vector<long long>());
//		uint32_t stepsize = 1;
//		for (size_t it = 0; it < iterations; it++)
//		{
//			auto start = std::chrono::high_resolution_clock::now();
//			for (size_t i = 0; i < size; i += stepsize)
//			{
//				pGameObjects.get()[i]->ID *= 2;
//			}
//			auto end = std::chrono::high_resolution_clock::now();
//			auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//
//			samples[sampleIndex].emplace_back(elapsed);
//			stepsize *= 2;
//		}
//	}
//	m_averageEx2Part1.clear();
//	m_averageEx2Part1 = GetAverage(samples);
//
//	std::unique_ptr<GameObject3DAlt*> pGameObjectsAlt = std::make_unique<GameObject3DAlt*>(size);
//
//	samples.clear();
//
//	for (size_t sampleIndex = 0; sampleIndex < sampleSize; sampleIndex++)
//	{
//		samples.emplace_back(std::vector<long long>());
//		uint32_t stepsize = 1;
//		for (size_t it = 0; it < iterations; it++)
//		{
//			auto start = std::chrono::high_resolution_clock::now();
//			for (size_t i = 0; i < size; i += stepsize)
//			{
//				pGameObjectsAlt.get()[i]->ID *= 2;
//			}
//			auto end = std::chrono::high_resolution_clock::now();
//			auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//
//			samples[sampleIndex].emplace_back(elapsed);
//			stepsize *= 2;
//		}
//	}
//	m_averageEx2Part2.clear();
//	m_averageEx2Part2 = GetAverage(samples);
//}
//
//std::vector<float> TrashTheCacheScene::GetAverage(const std::vector<std::vector<long long>>& samples) const
//{
//	std::vector<float> averages;
//	uint32_t stepsize = 1;
//	for (size_t it = 0; it < samples[0].size(); it++)
//	{
//		long long sum{ 0 };
//		long long biggest{ 0 };
//		long long smallest{ LONG_MAX };
//		for (size_t sampleIndex = 0; sampleIndex < samples.size(); sampleIndex++)
//		{
//			sum += samples[sampleIndex][it];
//			if (samples[sampleIndex][it] > biggest)
//			{
//				biggest = samples[sampleIndex][it];
//			}
//			if (samples[sampleIndex][it] < smallest)
//			{
//				smallest = samples[sampleIndex][it];
//			}
//		}
//		sum -= biggest;
//		sum -= smallest;
//		averages.emplace_back(sum / samples.size() / 1000.f);
//		stepsize *= 2;
//	}
//	return averages;
//}