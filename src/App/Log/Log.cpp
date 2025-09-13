#include "Log.h"

#include <imgui.h>

#include <format>

void Log::Draw()
{
	ImGui::Begin("Log", nullptr, ImGuiWindowFlags_NoTitleBar);
	ImGui::BeginChild("##content", ImVec2(0, 0), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);

	for (int i = 0; i < entries.size(); ++i)
	{
		Entry e = entries[i];
		ImGui::PushID(i);

		ImVec2 startPos = ImGui::GetCursorScreenPos();

		ImGui::BeginGroup();
		{
			if (ImGui::BeginTable("Test Table", 2))
			{
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("Instruction:");
				ImGui::TableSetColumnIndex(1);
				ImGui::Text(e.instruction.c_str());
				
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("OP:");
				ImGui::TableSetColumnIndex(1);
				ImGui::Text(std::format("{:#02X}", e.OP).c_str());

				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("PC:");
				ImGui::TableSetColumnIndex(1);
				ImGui::Text(std::format("{:#04X}", e.PC).c_str());

				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("SP:");
				ImGui::TableSetColumnIndex(1);
				ImGui::Text(std::format("{:#04X}", e.SP).c_str());

				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("AF:");
				ImGui::TableSetColumnIndex(1);
				ImGui::Text(std::format("{:#04X}", e.AF).c_str());

				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("BC:");
				ImGui::TableSetColumnIndex(1);
				ImGui::Text(std::format("{:#04X}", e.BC).c_str());

				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("DE:");
				ImGui::TableSetColumnIndex(1);
				ImGui::Text(std::format("{:#04X}", e.DE).c_str());

				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("HL:");
				ImGui::TableSetColumnIndex(1);
				ImGui::Text(std::format("{:#04X}", e.HL).c_str());

				ImGui::EndTable();
			}
		}
		ImGui::EndGroup();

		ImVec2 endPos = ImGui::GetCursorScreenPos();
		float height = endPos.y - startPos.y;

		ImGui::SetCursorScreenPos(startPos);
		bool selected = ImGui::Selectable("##entry", false, ImGuiSelectableFlags_AllowDoubleClick, ImVec2(0, height));

		ImGui::SetCursorScreenPos(endPos);

		ImGui::PopID();
	}

	ImGui::EndChild();
	ImGui::End();
}

void Log::Add(Entry entry)
{
	entries.push_back(entry);
}
