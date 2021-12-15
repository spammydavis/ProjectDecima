#pragma once


#include "decima/serializable/object/object.hpp"
#include "decima/serializable/object/common/bbox.hpp"
#include "decima/serializable/reference.hpp"
#include "decima/serializable/array.hpp"
#include "decima/serializable/string.hpp"
#include "decima/serializable/guid.hpp"

namespace Decima {


    class SRTBindingCache  {
    public:
        void parse(ash::buffer& buffer, CoreFile& file);
        void draw();

    private:
        Array<std::uint16_t> BindingDataIndices;
        Array<std::uint64_t> SRTEntryHandles;
    };

    class SamplerBindings {
    public:
        void parse(ash::buffer& buffer, CoreFile& file);
        void draw();

    private:
        std::uint32_t BindingNameHash;
        std::uint32_t SamplerData;
        std::uint64_t SamplerBindingHandle;
    };

    class TextureBindings {
    public:
        void parse(ash::buffer& buffer, CoreFile& file);
        void draw();

    private:
        std::uint32_t BindingNameHash;
        std::uint32_t BindingSwizzleNameHash;
        std::uint32_t SamplerNameHash;
        std::uint32_t PackedData;
        Ref TextureResource;
        std::uint64_t TextureBindingHandle;
        std::uint64_t SwizzleBindingHandle;
    };

    class VariableBindings {
    public:
        void parse(ash::buffer& buffer, CoreFile& file);
        void draw();

    private:
        std::uint32_t VariableData0;
        std::uint32_t VariableData1;
        std::uint32_t VariableData2;
        std::uint32_t VariableData3;
        std::uint32_t BindingNameHash;
        std::uint32_t VariableIDHash;
        std::uint8_t VariableType;
        Ref Animator;
        std::uint64_t VarBindingHandle;
    };
    class RenderTechnique {
    public:
        void parse(ash::buffer& buffer, CoreFile& file);
        void draw();

    private:
        std::vector<std::uint8_t> RTState;
        SRTBindingCache SRTBCache;
        std::uint32_t TechniqueType;
        std::uint8_t GPUSkinned;
        std::uint8_t WriteGlobalVertexCache;
        std::uint8_t CameraFacing;
        std::uint8_t InitiallyEnabled;
        std::uint32_t MaterialLayerID;
        std::vector<SamplerBindings> SB;
        std::vector<TextureBindings> TB;
        std::vector<VariableBindings> VB;
        Ref ShaderRef;
        std::uint64_t ID;
        std::uint8_t ForceLODFadeEmulation;
    };

    class RenderTechniqueSet {
    public:
        void parse(ash::buffer& buffer, CoreFile& file);
        void draw();

    private:
        std::vector<RenderTechnique> RTech;
        std::uint32_t Type;
        std::uint32_t EffectType;
        std::uint32_t TechMask;
        std::uint32_t InitEnabledMask;
    };

    class RenderEffectResource : public CoreObject {
    public:
        void parse(ArchiveManager& manager, ash::buffer& buffer, CoreFile& file) override;
        void draw() override;

    private:
        Ref ObjectAttributeAnimatorResource;
        std::vector<RenderTechniqueSet> TechniqueSets;
        std::uint32_t SortMode;
        std::uint32_t SortOrder;
        std::uint32_t EffectType;
        std::uint8_t MakeAccumulationBufferCopy;
        std::uint8_t ForwardIgonoreLocalIndirectLighting;
        std::uint32_t EnvironmentInteractionTargets;
    };


    class MeshHierarchyInfo {
    public:
        void parse(ash::buffer& buffer, CoreFile& file);
        void draw();

    private:
        std::uint32_t mit_node_size;
        std::uint32_t primitive_count;
        std::uint16_t mesh_count;
        std::uint16_t static_mesh_count;
        std::uint16_t lod_mesh_count;
        std::uint16_t packed_data;
    };
	
    class MeshResourceBase : public CoreObject {
    public:

        void parse(ArchiveManager& manager, ash::buffer& buffer, CoreFile& file) override;
        void draw() override;

    private:
        std::uint32_t static_datablock_size;	
		BBox3 bounding_box;
		std::uint32_t cull_info;
		MeshHierarchyInfo mesh_hier_info;
		
    };


    class MultiMeshResourcePart : public CoreSerializable {
    public:
        void parse(ash::buffer& buffer, CoreFile& file);
        void draw();

    private:
        Ref mesh;
        double transform_pX;
        double transform_pY;
        double transform_pZ;
        Vec3 transform_OCol0;
        Vec3 transform_OCol1;
        Vec3 transform_OCol2;
    };
		
    class MultiMeshResource : public MeshResourceBase {
    public:
        void parse(ArchiveManager& manager, ash::buffer& buffer, CoreFile& file) override;
        void draw() override;
    private:
        Array<MultiMeshResourcePart> parts;
    };

    class LodMeshResourcePart : public CoreSerializable {
    public:
        void parse(ash::buffer& buffer, CoreFile& file);
        void draw();
    private:
      Ref mesh;
	  float distance;
    };
		
    class LodMeshResource : public MeshResourceBase {
    public:

        void parse(ArchiveManager& manager, ash::buffer& buffer, CoreFile& file) override;
        void draw() override;

    private:
        //void draw_preview(float preview_width, float preview_height, float zoom_region, float zoom_scale);
    private:
	  float max_distance;
	  Array<LodMeshResourcePart> meshes;

    };

    class SkinnedMeshResource : public MeshResourceBase {
    public:
        void parse(ArchiveManager& manager, ash::buffer& buffer, CoreFile& file) override;
        void draw() override;

    private:
        Ref skeleton;
        Ref orientation_helpers;
    };


    class RegularSkinnedMeshResourceBase : public SkinnedMeshResource {
    public:
        void parse(ArchiveManager& manager, ash::buffer& buffer, CoreFile& file) override;
        void draw() override;

    private:
        // these might be incorrect
        std::uint32_t view_layer;
        std::uint32_t shadow_cull_mode;
        /*
  ubyte CastDynamicShadows;
  ubyte CastShadows;
  uint32 RenderType;
  ubyte VoxelizeBaking;
  DrawFlags DF;
  uint DeformerType;
*/
        Ref skinned_mesh_joint_bindings;
        Ref skinned_mesh_bone_bounding_boxes;
    };

    class RegularSkinnedMeshResource : public RegularSkinnedMeshResourceBase {
    public:
        void parse(ArchiveManager& manager, ash::buffer& buffer, CoreFile& file) override;
        void draw() override;

    private:
      Vec3 position_bounds_scale;
      Vec3 position_bounds_offset;
      Ref skin_info;
      Array<Ref> primitives;
      Array<Ref> shading_groups;
      Ref render_effect_swapper;
      String stream_name;
      GUID stream_handle_guid;
      std::uint32_t stream_handle_unk1;
      std::uint32_t stream_handle_unk2;
      std::uint32_t stream_handle_unk3;
    };



	
}


