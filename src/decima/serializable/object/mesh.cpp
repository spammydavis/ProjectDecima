#include "decima/serializable/object/mesh.hpp"


void Decima::MeshHierarchyInfo::parse(ash::buffer& buffer, Decima::CoreFile& file) {
     mit_node_size= buffer.get<decltype(mit_node_size)>();
     primitive_count= buffer.get<decltype(primitive_count)>();
     mesh_count= buffer.get<decltype(mesh_count)>();
     static_mesh_count= buffer.get<decltype(static_mesh_count)>();
     lod_mesh_count= buffer.get<decltype(lod_mesh_count)>();
     packed_data= buffer.get<decltype(packed_data)>();
}


void Decima::MeshResourceBase::parse(Decima::ArchiveManager& manager, ash::buffer& buffer, Decima::CoreFile& file) {
    CoreObject::parse(manager, buffer, file);
    static_datablock_size = buffer.get<decltype(static_datablock_size)>();
    bounding_box = buffer.get<decltype(bounding_box)>();
    cull_info = buffer.get<decltype(cull_info)>();
	mesh_hier_info.parse(buffer,file);
}


void Decima::MultiMeshResourcePart::parse(ash::buffer& buffer, Decima::CoreFile& file) {
    mesh.parse(buffer, file);
    transform_pX = buffer.get<decltype(transform_pX)>();
    transform_pY = buffer.get<decltype(transform_pY)>();
    transform_pZ = buffer.get<decltype(transform_pZ)>();
    transform_OCol0 = buffer.get<decltype(transform_OCol0)>();
    transform_OCol1 = buffer.get<decltype(transform_OCol1)>();
    transform_OCol2 = buffer.get<decltype(transform_OCol2)>();
}

void Decima::MultiMeshResource::parse(Decima::ArchiveManager& manager, ash::buffer& buffer, Decima::CoreFile& file) {
    MeshResourceBase::parse(manager, buffer, file);
    parts.parse(buffer, file);
}

void Decima::LodMeshResourcePart::parse(ash::buffer& buffer, Decima::CoreFile& file) {
    mesh.parse(buffer, file);
    distance = buffer.get<decltype(distance)>();
}

void Decima::LodMeshResource::parse(Decima::ArchiveManager& manager, ash::buffer& buffer, Decima::CoreFile& file) {
    MeshResourceBase::parse(manager, buffer, file);
    max_distance = buffer.get<decltype(max_distance)>();
    meshes.parse(buffer, file);
}

void Decima::SkinnedMeshResource::parse(Decima::ArchiveManager& manager, ash::buffer& buffer, Decima::CoreFile& file) {
    MeshResourceBase::parse(manager, buffer, file);
    skeleton.parse(buffer, file);
    orientation_helpers.parse(buffer, file);
}

void Decima::RegularSkinnedMeshResourceBase::parse(Decima::ArchiveManager& manager, ash::buffer& buffer, Decima::CoreFile& file) {
    SkinnedMeshResource::parse(manager, buffer, file);
    view_layer = buffer.get<decltype(view_layer)>();
    shadow_cull_mode = buffer.get<decltype(shadow_cull_mode)>();
    skinned_mesh_joint_bindings.parse(buffer, file);
    skinned_mesh_bone_bounding_boxes.parse(buffer, file);
}

void Decima::RegularSkinnedMeshResource::parse(Decima::ArchiveManager& manager, ash::buffer& buffer, Decima::CoreFile& file) {
    RegularSkinnedMeshResourceBase::parse(manager, buffer, file);
    position_bounds_scale = buffer.get<decltype(position_bounds_scale)>();
    position_bounds_offset = buffer.get<decltype(position_bounds_offset)>();
    skin_info.parse(buffer, file);
    primitives.parse(buffer, file);
    shading_groups.parse(buffer, file);
    render_effect_swapper.parse(buffer, file);
    stream_name.parse(buffer, file);
    stream_handle_guid.parse(buffer, file);
    stream_handle_unk1 = buffer.get<decltype(stream_handle_unk1)>();
    stream_handle_unk2 = buffer.get<decltype(stream_handle_unk2)>();
    stream_handle_unk3 = buffer.get<decltype(stream_handle_unk3)>();
}



void Decima::SRTBindingCache::parse(ash::buffer& buffer, Decima::CoreFile& file) {
    BindingDataIndices.parse(buffer, file);
    SRTEntryHandles.parse(buffer, file);
    std::cout << "BD size " << BindingDataIndices.data().size() << "\n";
}
void Decima::SamplerBindings::parse(ash::buffer& buffer, Decima::CoreFile& file) {
    BindingNameHash = buffer.get<decltype(BindingNameHash)>();
    SamplerData = buffer.get<decltype(SamplerData)>();
    SamplerBindingHandle = buffer.get<decltype(SamplerBindingHandle)>();
}
void Decima::TextureBindings::parse(ash::buffer& buffer, Decima::CoreFile& file) {
    BindingNameHash = buffer.get<decltype(BindingNameHash)>();
    BindingSwizzleNameHash = buffer.get<decltype(BindingSwizzleNameHash)>();
    SamplerNameHash = buffer.get<decltype(SamplerNameHash)>();
    PackedData = buffer.get<decltype(PackedData)>();
    TextureResource.parse(buffer, file);
    TextureBindingHandle = buffer.get<decltype(TextureBindingHandle)>();
    SwizzleBindingHandle = buffer.get<decltype(SwizzleBindingHandle)>();
}

void Decima::VariableBindings::parse(ash::buffer& buffer, Decima::CoreFile& file) {
    VariableData0 = buffer.get<decltype(VariableData0)>();
    VariableData1 = buffer.get<decltype(VariableData1)>();
    VariableData2 = buffer.get<decltype(VariableData2)>();
    VariableData3 = buffer.get<decltype(VariableData3)>();
    BindingNameHash = buffer.get<decltype(BindingNameHash)>();
    VariableIDHash = buffer.get<decltype(VariableIDHash)>();
    VariableType = buffer.get<decltype(VariableType)>();
    Animator.parse(buffer,file);
    VarBindingHandle = buffer.get<decltype(VarBindingHandle)>();
}
void Decima::RenderTechnique::parse(ash::buffer& buffer, Decima::CoreFile& file) {
    for (int i = 0; i < 19; i++) { 
        //unsigned int b;
        RTState.push_back(buffer.get<std::uint8_t>());
        //b = RTState.at(i);
        //std::cout << "rtstate " << std::dec << i << " " << std::hex << b << "\n";
    }
    
    SRTBCache.parse(buffer, file);
    TechniqueType = buffer.get<decltype(TechniqueType)>();
    GPUSkinned = buffer.get<decltype(GPUSkinned)>();
    WriteGlobalVertexCache = buffer.get<decltype(WriteGlobalVertexCache)>();
    CameraFacing = buffer.get<decltype(CameraFacing)>();
    InitiallyEnabled = buffer.get<decltype(InitiallyEnabled)>();
    MaterialLayerID = buffer.get<decltype(MaterialLayerID)>();
    SB.resize(buffer.get<std::uint32_t>());
    for (auto& entry : SB)
        entry.parse(buffer, file);
    TB.resize(buffer.get<std::uint32_t>());
    for (auto& entry : TB)
        entry.parse(buffer, file);
    VB.resize(buffer.get<std::uint32_t>());
    for (auto& entry : VB)
        entry.parse(buffer, file);
    ShaderRef.parse(buffer,file);
    ID = buffer.get<std::uint32_t>();
    std::cout << "ID " << std::hex << ID << "\n";
    ID = buffer.get<std::uint32_t>();
    std::cout << "ID " << std::hex << ID << "\n";
    ForceLODFadeEmulation = buffer.get<decltype(ForceLODFadeEmulation)>();
 
}

void Decima::RenderTechniqueSet::parse(ash::buffer& buffer, Decima::CoreFile& file) {
    RTech.resize(buffer.get<std::uint32_t>());
    for (auto& entry : RTech)
        entry.parse(buffer, file);
    Type = buffer.get<decltype(Type)>();
    EffectType = buffer.get<decltype(EffectType)>();
    TechMask = buffer.get<decltype(TechMask)>();
    InitEnabledMask = buffer.get<decltype(InitEnabledMask)>();
}



void Decima::RenderEffectResource::parse(Decima::ArchiveManager& manager, ash::buffer& buffer, Decima::CoreFile& file) {
    CoreObject::parse(manager, buffer, file);
    ObjectAttributeAnimatorResource.parse(buffer, file);
    TechniqueSets.resize(buffer.get<std::uint32_t>());
    for (auto& entry : TechniqueSets)
        entry.parse(buffer, file);
    SortMode = buffer.get<decltype(SortMode)>();
    SortOrder = buffer.get<decltype(SortOrder)>();
    EffectType = buffer.get<decltype(EffectType)>();
    MakeAccumulationBufferCopy = buffer.get<decltype(MakeAccumulationBufferCopy)>();
    ForwardIgonoreLocalIndirectLighting = buffer.get<decltype(ForwardIgonoreLocalIndirectLighting)>();
    EnvironmentInteractionTargets = buffer.get<decltype(EnvironmentInteractionTargets)>();
}