#include <xor.hpp>
#include <vector>

#include "../dependencies.h"
#include "configs.h"

namespace menu
{
	std::vector<std::string> tabs{
		"RAGE",
		"VISUALS",
		"MISC",
		"CFG",
	};

	int selected_tab{ 0 };

	void render()
	{
		if (!cfg::get().ui.opened)
			return;

		ImGui::SetNextWindowSize({ 590, 424 }, ImGuiCond_Once);
		ImGui::Begin("CONQUEST", &cfg::get().ui.opened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		{
			ImGui::BeginChild("Tabs", { 145, 385 }, true);
			{
				for (int i = 0; i < tabs.size(); ++i)
				{
					if (ImGui::Selectable(tabs[i].c_str(), selected_tab == i))
						selected_tab = i;
				}
			}
			ImGui::EndChild();

			ImGui::SameLine();

			ImGui::BeginChild("Contents", { 422, 385 }, true);
			{
				switch (selected_tab)
				{
				case 0:
					break;
				case 1:
					break;
				case 2:
				{
					ImGui::Checkbox("Auto jump", &cfg::get().auto_jump);
					ImGui::Checkbox("Auto strafe", &cfg::get().auto_strafe);
				}
				break;
				case 3:
				{
					if (ImGui::SmallButton("Save"))
						configs::save("test.txt");

					if (ImGui::SmallButton("Load"))
						configs::load("test.txt");
				}					
				break;
				}
			}
			ImGui::EndChild();
		}
		ImGui::End();
	}
}
