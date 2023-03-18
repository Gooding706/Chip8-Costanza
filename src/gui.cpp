#include <imgui.h>
#include <imgui-SFML.h>
#include "fileStructure.h"
#include <iostream>
#include "gui.h"
#include "CPU.h"

Gui::Gui(Chip8& Cpu, sf::RenderWindow& window) : Cpu(Cpu), window(window)
{

}

void Gui::Popup()
{
  if (show_popup)
      ImGui::OpenPopup("My Popup Window");
  if (ImGui::BeginPopupModal("My Popup Window", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_Popup))
  {
      ImGui::Text("Select a file:");

      std::vector<std::string> files = get_files("Roms/");

      if (files.size() == 0)
      {
          ImGui::Text("No files found in directory.");
      }
      else
      {
          const char* current_item = files[selected_file_index].c_str();
          if (ImGui::BeginCombo("##combo", current_item))
          {
              for (int i = 0; i < files.size(); i++)
              {
                  bool is_selected = (selected_file_index == i);
                  if (ImGui::Selectable(files[i].c_str(), is_selected))
                      selected_file_index = i;
                  if (is_selected)
                      ImGui::SetItemDefaultFocus();
              }
              ImGui::EndCombo();
          }

          if (ImGui::Button("Open"))
          {
              Cpu.loadRom(files[selected_file_index].c_str());
              show_popup = false;
              ImGui::CloseCurrentPopup();
          }
      }

      if(ImGui::CollapsingHeader("Settings"))
      {
        ImGui::SliderInt("Instruction Speed", &instructionsPerFrame, 10, 100);
        ImGui::ColorEdit3("Background Color", backgroundColor);
        ImGui::ColorEdit3("Pixel Color", pixelColor);
      }

      if (ImGui::Button("Cancel"))
      {

          show_popup = false;
          ImGui::CloseCurrentPopup();
          window.close();
      }

      ImGui::EndPopup();
  }
}
