#include "decima/serializable/object/mesh.hpp"

#include <imgui.h>

void Decima::MeshHierarchyInfo::draw() {
    ImGui::Columns(2);

    {
        ImGui::Text("Property");
        ImGui::NextColumn();

        ImGui::Text("Value");
        ImGui::NextColumn();

        ImGui::Separator();
    }

    ImGui::SetColumnWidth(0, 200);
    ImGui::SetColumnWidth(1, ImGui::GetWindowWidth() - 200);

    {
        ImGui::Text("mit_node_size");
        ImGui::NextColumn();

        ImGui::Text("%u", mit_node_size);
        ImGui::NextColumn();

        ImGui::Separator();
    }

    {
        ImGui::Text("primitive_count");
        ImGui::NextColumn();

        ImGui::Text("%u", primitive_count);
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("mesh_count");
        ImGui::NextColumn();

        ImGui::Text("%u", mesh_count);
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("lod_mesh_count");
        ImGui::NextColumn();

        ImGui::Text("%u", lod_mesh_count);
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("packed_data");
        ImGui::NextColumn();

        ImGui::Text("%u", packed_data);
        ImGui::NextColumn();

        ImGui::Separator();
    }


}


void Decima::MeshResourceBase::draw() {
    ImGui::Columns(2);

    {
        ImGui::Text("Property");
        ImGui::NextColumn();

        ImGui::Text("Value");
        ImGui::NextColumn();

        ImGui::Separator();
    }

    ImGui::SetColumnWidth(0, 200);
    ImGui::SetColumnWidth(1, ImGui::GetWindowWidth() - 200);


    {
        ImGui::Text("static_datablock_size");
        ImGui::NextColumn();

        ImGui::Text("%u", static_datablock_size);
        ImGui::NextColumn();

        ImGui::Separator();
    }

    {
        ImGui::Text("Bounding Box");
        ImGui::NextColumn();

        ImGui::Text("%s", Decima::to_string(bounding_box).c_str());
        ImGui::NextColumn();

        ImGui::Separator();
    }

    {
        ImGui::Text("cull_info");
        ImGui::NextColumn();

        ImGui::Text("%u", cull_info);
        ImGui::NextColumn();

        ImGui::Separator();
    }
    ImGui::Columns(1);
    if (ImGui::TreeNodeEx("MeshHierarchyInfo", ImGuiTreeNodeFlags_SpanFullWidth)) {
        mesh_hier_info.draw();
        ImGui::TreePop();
    }

    ImGui::Separator();

}

void Decima::SkinnedMeshResource::draw() {
    MeshResourceBase::draw();
    ImGui::Separator();
    ImGui::Columns(2);
    {
        ImGui::Text("Skeleton");
        ImGui::NextColumn();

        skeleton.draw();
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("Orientation Helpers");
        ImGui::NextColumn();

        orientation_helpers.draw();
        ImGui::NextColumn();

        ImGui::Separator();
    }
}
void Decima::RegularSkinnedMeshResourceBase::draw() {
    SkinnedMeshResource::draw();
    ImGui::Separator();
    ImGui::Columns(2);
    {
        ImGui::Text("view_layer");
        ImGui::NextColumn();

        ImGui::Text("%u", view_layer);
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("shadow_cull_mode");
        ImGui::NextColumn();

        ImGui::Text("%u", shadow_cull_mode);
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("skinned_mesh_joint_bindings");
        ImGui::NextColumn();

        skinned_mesh_joint_bindings.draw();
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("skinned_mesh_bone_bounding_boxes");
        ImGui::NextColumn();

        skinned_mesh_bone_bounding_boxes.draw();
        ImGui::NextColumn();

        ImGui::Separator();
    }
}
void Decima::RegularSkinnedMeshResource::draw() {
    RegularSkinnedMeshResourceBase::draw();
    ImGui::Separator();
    ImGui::Columns(2);


    {
        ImGui::Text("position_bounds_scale");
        ImGui::NextColumn();

        ImGui::Text("%s", Decima::to_string(position_bounds_scale).c_str());
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("position_bounds_offset");
        ImGui::NextColumn();

        ImGui::Text("%s", Decima::to_string(position_bounds_offset).c_str());
        ImGui::NextColumn();

        ImGui::Separator();
    }

    {
        ImGui::Text("skin_info");
        ImGui::NextColumn();

        skin_info.draw();
        ImGui::NextColumn();

        ImGui::Separator();
    }


    ImGui::Columns(1);
    if (ImGui::TreeNodeEx("primitives", ImGuiTreeNodeFlags_SpanFullWidth)) {
        for (std::size_t entry_index = 0; entry_index < primitives.data().size(); entry_index++) {
            const auto entry_name = "primitive #" + std::to_string(entry_index);

            if (ImGui::TreeNodeEx(entry_name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth)) {
                primitives.data().at(entry_index).draw();
                ImGui::TreePop();
            }
        }

        ImGui::TreePop();
    }
    ImGui::Separator();
    ImGui::Columns(1);
    if (ImGui::TreeNodeEx("shading_groups", ImGuiTreeNodeFlags_SpanFullWidth)) {
        for (std::size_t entry_index = 0; entry_index < shading_groups.data().size(); entry_index++) {
            const auto entry_name = "shading_group #" + std::to_string(entry_index);

            if (ImGui::TreeNodeEx(entry_name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth)) {
                shading_groups.data().at(entry_index).draw();
                ImGui::TreePop();
            }
        }

        ImGui::TreePop();
    }
    ImGui::Separator();
    ImGui::Columns(2);

    {
        ImGui::Text("render_effect_swapper");
        ImGui::NextColumn();

        render_effect_swapper.draw();
        ImGui::NextColumn();

        ImGui::Separator();
    }

    {
        ImGui::Text("stream_name");
        ImGui::NextColumn();
        std::string sname = stream_name.data() + ".core.stream";
        ImGui::TextWrapped("%s", sname.c_str());

        if (ImGui::BeginPopupContextItem(sname.c_str())) {
            if (ImGui::Selectable("Copy to clipboard"))
                ImGui::SetClipboardText(sname.c_str());
            ImGui::EndPopup();
        }
        ImGui::NextColumn();
    } 

    ImGui::Separator();
    {
        ImGui::Text("stream_handle_guid");
        ImGui::NextColumn();

        ImGui::Text("%s", Decima::to_string(stream_handle_guid).c_str());
        ImGui::NextColumn();
    }

    ImGui::Separator();
    {
        ImGui::Text("stream_handle_unk1");
        ImGui::NextColumn();

        ImGui::Text("%u", stream_handle_unk1);
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("stream_handle_unk2");
        ImGui::NextColumn();

        ImGui::Text("%u", stream_handle_unk2);
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("stream_handle_unk3");
        ImGui::NextColumn();

        ImGui::Text("%u", stream_handle_unk3);
        ImGui::NextColumn();

        ImGui::Separator();
    }
}


void Decima::MultiMeshResourcePart::draw() {
    ImGui::Columns(2);

    {
        ImGui::Text("Property");
        ImGui::NextColumn();

        ImGui::Text("Value");
        ImGui::NextColumn();

        ImGui::Separator();
    }

    ImGui::SetColumnWidth(0, 200);
    ImGui::SetColumnWidth(1, ImGui::GetWindowWidth() - 200);

    {
        ImGui::Text("Mesh");
        ImGui::NextColumn();

        mesh.draw();
        ImGui::NextColumn();

        ImGui::Separator();
    }

    {
        ImGui::Text("transform_pX");
        ImGui::NextColumn();
        ImGui::SetNextItemWidth(-1.0f);
        ImGui::InputDouble("##", &transform_pX, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("transform_pY");
        ImGui::NextColumn();
        ImGui::SetNextItemWidth(-1.0f);
        ImGui::InputDouble("##", &transform_pY, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("transform_pZ");
        ImGui::NextColumn();
        ImGui::SetNextItemWidth(-1.0f);
        ImGui::InputDouble("##", &transform_pZ, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("transform_OCol0");
        ImGui::NextColumn();

        ImGui::Text("%s", Decima::to_string(transform_OCol0).c_str());
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("transform_OCol1");
        ImGui::NextColumn();

        ImGui::Text("%s", Decima::to_string(transform_OCol1).c_str());
        ImGui::NextColumn();

        ImGui::Separator();
    }
    {
        ImGui::Text("transform_OCol2");
        ImGui::NextColumn();

        ImGui::Text("%s", Decima::to_string(transform_OCol2).c_str());
        ImGui::NextColumn();

        ImGui::Separator();
    }

    ImGui::Columns(1);
}

void Decima::MultiMeshResource::draw() {

    MeshResourceBase::draw();
    ImGui::Separator();

    ImGui::Columns(1);
    if (ImGui::TreeNodeEx("Parts", ImGuiTreeNodeFlags_SpanFullWidth)) {
        for (std::size_t entry_index = 0; entry_index < parts.data().size(); entry_index++) {
            const auto entry_name = "Part #" + std::to_string(entry_index);

            if (ImGui::TreeNodeEx(entry_name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth)) {
                parts.data().at(entry_index).draw();
                ImGui::TreePop();
            }
        }

        ImGui::TreePop();
    }
}


void Decima::LodMeshResourcePart::draw() {
    ImGui::Columns(2);

    {
        ImGui::Text("Property");
        ImGui::NextColumn();

        ImGui::Text("Value");
        ImGui::NextColumn();

        ImGui::Separator();
    }

    ImGui::SetColumnWidth(0, 200);
    ImGui::SetColumnWidth(1, ImGui::GetWindowWidth() - 200);

    {
        ImGui::Text("Mesh");
        ImGui::NextColumn();

        mesh.draw();
        ImGui::NextColumn();

        ImGui::Separator();
    }

    {
        ImGui::Text("distance");
        ImGui::NextColumn();
        ImGui::SetNextItemWidth(-1.0f);
        ImGui::InputFloat("##", &distance, 0, 0, "%.3f", ImGuiInputTextFlags_ReadOnly);
        ImGui::NextColumn();

        ImGui::Separator();
    }

    ImGui::Columns(1);
}

void Decima::LodMeshResource::draw() {


    MeshResourceBase::draw();
    ImGui::Separator();
    ImGui::Columns(2);
    {
        ImGui::Text("max_distance");
        ImGui::NextColumn();
        ImGui::SetNextItemWidth(-1.0f);
        ImGui::InputFloat("##", &max_distance,0,0, "%.3f", ImGuiInputTextFlags_ReadOnly);
        ImGui::NextColumn();

        ImGui::Separator();
    }

    ImGui::Columns(1);
    if (ImGui::TreeNodeEx("Meshes", ImGuiTreeNodeFlags_SpanFullWidth)) {
        for (std::size_t entry_index = 0; entry_index < meshes.data().size(); entry_index++) {
            const auto entry_name = "Mesh #" + std::to_string(entry_index);

            if (ImGui::TreeNodeEx(entry_name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth)) {
                meshes.data().at(entry_index).draw();
                ImGui::TreePop();
            }
        }

        ImGui::TreePop();
    }
}


void Decima::SRTBindingCache::draw() {
    ImGui::Columns(1);
    if (ImGui::TreeNodeEx("BindingDataIndices", ImGuiTreeNodeFlags_SpanFullWidth)) {
        ImGui::Columns(2);
        for (std::size_t entry_index = 0; entry_index < BindingDataIndices.data().size(); entry_index++) {
            ImGui::Text("%u", entry_index);
            ImGui::NextColumn();
            ImGui::Text("%u", BindingDataIndices.data().at(entry_index));
            ImGui::NextColumn();
        }
        ImGui::TreePop();
    }
    ImGui::Columns(1);
    if (ImGui::TreeNodeEx("SRTEntryHandles", ImGuiTreeNodeFlags_SpanFullWidth)) {
        ImGui::Columns(2);
        for (std::size_t entry_index = 0; entry_index < SRTEntryHandles.data().size(); entry_index++) {
            ImGui::Text("%u", entry_index);
            ImGui::NextColumn();
            ImGui::Text("%u", SRTEntryHandles.data().at(entry_index));
            ImGui::NextColumn();
        }
        ImGui::TreePop();
    }
}

void Decima::SamplerBindings::draw() {
    ImGui::Columns(2);
    ImGui::Text("BindingNameHash");
    ImGui::NextColumn();
    ImGui::Text("%u", BindingNameHash);
    ImGui::NextColumn();
    ImGui::Separator();

    ImGui::Text("SamplerData");
    ImGui::NextColumn();
    ImGui::Text("%u", SamplerData);
    ImGui::NextColumn();
    ImGui::Separator();

    ImGui::Text("SamplerBindingHandle");
    ImGui::NextColumn();
    ImGui::Text("%u", SamplerBindingHandle);
    ImGui::NextColumn();
    ImGui::Separator();
}
void Decima::TextureBindings::draw() {
    ImGui::Columns(2);
    /* BindingNameHash
BindingSwizzleNameHash
SamplerNameHash
PackedData*/
    {
        ImGui::Text("TextureResource");
        ImGui::NextColumn();

        TextureResource.draw();
        ImGui::NextColumn();

        ImGui::Separator();
    }
                    
/* TextureBindingHandle
SwizzleBindingHandle */

}
void Decima::VariableBindings::draw() {
    ImGui::Columns(2);
    /*
    VariableData0
    VariableData1
    VariableData2
    VariableData3
    BindingNameHash
    VariableIDHash
    VariableType */

    {
        ImGui::Text("Animator");
        ImGui::NextColumn();

        Animator.draw();
        ImGui::NextColumn();

        ImGui::Separator();
    }

    //VarBindingHandle

}
void Decima::RenderTechnique::draw() {
    ImGui::Columns(2);
    //RTState
    SRTBCache.draw();
    ImGui::Separator();
    /* TechniqueType
    GPUSkinned
    WriteGlobalVertexCache
    CameraFacing
    InitiallyEnabled
    MaterialLayerID */
    ImGui::Columns(1);
        for (std::size_t entry_index = 0; entry_index < SB.size(); entry_index++) {
            const auto entry_name = "SamplerBinding #" + std::to_string(entry_index);
            ImGui::Columns(1);
            if (ImGui::TreeNodeEx(entry_name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth)) {
                ImGui::Columns(2);
                SB.at(entry_index).draw();
                ImGui::TreePop();
            }
            ImGui::Separator();
    }
    ImGui::Columns(1);
        for (std::size_t entry_index = 0; entry_index < TB.size(); entry_index++) {
            const auto entry_name = "TextureBinding #" + std::to_string(entry_index);
            ImGui::Columns(1);
            if (ImGui::TreeNodeEx(entry_name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth)) {
                ImGui::Columns(2);
                TB.at(entry_index).draw();
                ImGui::TreePop();
            }
            ImGui::Separator();
    }
    ImGui::Columns(1);
        for (std::size_t entry_index = 0; entry_index < VB.size(); entry_index++) {
            const auto entry_name = "VariableBinding #" + std::to_string(entry_index);
            ImGui::Columns(1);
            if (ImGui::TreeNodeEx(entry_name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth)) {
                ImGui::Columns(2);
                VB.at(entry_index).draw();
                ImGui::TreePop();
            }
            ImGui::Separator();
    }
    ImGui::Columns(2);
    {
        ImGui::Text("ShaderRef");
        ImGui::NextColumn();

        ShaderRef.draw();
        ImGui::NextColumn();

        ImGui::Separator();
    }


    //ID
    //ForceLODFadeEmulation
}
void Decima::RenderTechniqueSet::draw() {
    ImGui::Columns(1);
    for (std::size_t entry_index = 0; entry_index < RTech.size(); entry_index++) {
            const auto entry_name = "RenderTechnique #" + std::to_string(entry_index);
        ImGui::Columns(1);
            if (ImGui::TreeNodeEx(entry_name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth)) {
            ImGui::Columns(2);
                RTech.at(entry_index).draw();
                ImGui::TreePop();
            }
            ImGui::Separator();
    }
    ImGui::Separator();
    /* Type
    EffectType
    TechMask
    InitEnabledMask */
}
void Decima::RenderEffectResource::draw() {
    ImGui::Columns(2);

    {
        ImGui::Text("Property");
        ImGui::NextColumn();

        ImGui::Text("Value");
        ImGui::NextColumn();

        ImGui::Separator();
    }

    ImGui::SetColumnWidth(0, 200);
    ImGui::SetColumnWidth(1, ImGui::GetWindowWidth() - 200);


    {
        ImGui::Text("ObjectAttributeAnimatorResource");
        ImGui::NextColumn();

        ObjectAttributeAnimatorResource.draw();
        ImGui::NextColumn();

        ImGui::Separator();
    }
    ImGui::Columns(1);
    for (std::size_t entry_index = 0; entry_index < TechniqueSets.size(); entry_index++) {
            const auto entry_name = "RenderTechniqueSet #" + std::to_string(entry_index);
            ImGui::Columns(1);
            if (ImGui::TreeNodeEx(entry_name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth)) {
                ImGui::Columns(2);
                TechniqueSets.at(entry_index).draw();
                ImGui::TreePop();
            }
            ImGui::Separator();
    }
    ImGui::Separator();
    /*
    SortMode
    SortOrder
    EffectType
    MakeAccumulationBufferCopy;
   ForwardIgonoreLocalIndirectLighting 
    EnvironmentInteractionTargets
    */


}










