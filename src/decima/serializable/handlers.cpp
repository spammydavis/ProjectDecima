#include "decima/serializable/handlers.hpp"

#include "decima/serializable/object/object.hpp"
#include "decima/serializable/object/object_dummy.hpp"
#include "decima/serializable/object/collection.hpp"
#include "decima/serializable/object/translation.hpp"
#include "decima/serializable/object/prefetch.hpp"
#include "decima/serializable/object/texture.hpp"
#include "decima/serializable/object/texture_set.hpp"
#include "decima/serializable/object/resource/vertex_array_resource.hpp"
#include "decima/serializable/object/resource/index_array_resource.hpp"
#include "decima/serializable/object/resource/primitive_resource.hpp"
#include "decima/serializable/object/mesh.hpp"

#include "utils.hpp"

class FileMagics {
};

class DeathStranding_FileMagics : public FileMagics {
public:
    // clang-format off
    static constexpr uint64_t Armature                            = 0x11e1d1a40b933e66;
    static constexpr uint64_t Texture                             = 0xa664164d69fd2b38;
    static constexpr uint64_t TextureSet                          = 0xa321e8c307328d2e;
    static constexpr uint64_t Translation                         = 0x31be502435317445;
    static constexpr uint64_t Shader                              = 0x16bb69a9e5aa0d9e;
    static constexpr uint64_t Collection                          = 0xf3586131b4f18516;
    static constexpr uint64_t Prefetch                            = 0xd05789eae3acbf02;
    static constexpr uint64_t VertexArrayResource                 = 0x3ac29a123faabab4;
    static constexpr uint64_t IndexArrayResource                  = 0x5fe633b37cedbf84;
    static constexpr uint64_t PrimitiveResource                   = 0xee49d93da4c1f4b8;
    static constexpr uint64_t MeshResourceBase                    = 0x2879C7EF5EAF5865;
    static constexpr uint64_t LodMeshResource                     = 0x36B88667B0A33134;
    static constexpr uint64_t MultiMeshResource                   = 0x9FC36C15337A680A; 
    static constexpr uint64_t SkinnedMeshResource                 = 0xC8D223289354D443;
    static constexpr uint64_t RegularSkinnedMeshResourceBase      = 0xD40C19AE1D16D98E;
    static constexpr uint64_t RegularSkinnedMeshResource          = 0xE2A812418ABC2172;
    static constexpr uint64_t SkinnedMeshIndexedJointBindings     = 0xBCE84D96052C041E;
    static constexpr uint64_t SkinnedMeshBoneBoundingBoxes        = 0x118378C2F191097A;
    static constexpr uint64_t ShadingGroup                        = 0xFE2843D4AAD255E7;
    static constexpr uint64_t RenderEffectResource                = 0xE844B010BF3CFD73;
    static constexpr uint64_t RegularSkinnedMeshResourceSkinInfo  = 0x8EB29E71F97E460F;
    static constexpr uint64_t StaticMeshResource                  = 0xB36C3ADC211AB947;

    // clang-format on
};

class ZeroDawn_FileMagics : public FileMagics {
public:
    static constexpr uint64_t Texture = 0xf2e1afb7052b3866;
};

template <class T, typename... Args>
inline static std::shared_ptr<Decima::CoreObject> construct(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

static const std::unordered_map<std::uint64_t, Decima::Handler<Decima::CoreObject>> handlers {
    // clang-format off
    { DeathStranding_FileMagics::Translation,         construct<Decima::Translation>         },
    { DeathStranding_FileMagics::Texture,             construct<Decima::Texture>             },
    { DeathStranding_FileMagics::TextureSet,          construct<Decima::TextureSet>          },
    { DeathStranding_FileMagics::Collection,          construct<Decima::Collection>          },
    { DeathStranding_FileMagics::Prefetch,            construct<Decima::Prefetch>            },
    { DeathStranding_FileMagics::VertexArrayResource, construct<Decima::VertexArrayResource> },
    { DeathStranding_FileMagics::IndexArrayResource,  construct<Decima::IndexArrayResource>  },
    { DeathStranding_FileMagics::PrimitiveResource,   construct<Decima::PrimitiveResource>   },
    { DeathStranding_FileMagics::LodMeshResource,     construct<Decima::LodMeshResource>     },
    { DeathStranding_FileMagics::MultiMeshResource,   construct<Decima::MultiMeshResource>   },
    { DeathStranding_FileMagics::SkinnedMeshResource, construct<Decima::SkinnedMeshResource> },
    { DeathStranding_FileMagics::RegularSkinnedMeshResourceBase, construct<Decima::RegularSkinnedMeshResourceBase>   },
    { DeathStranding_FileMagics::RegularSkinnedMeshResource,     construct<Decima::RegularSkinnedMeshResource>       },
    { DeathStranding_FileMagics::RenderEffectResource,           construct<Decima::RenderEffectResource>             },
    // clang-format on
};

static const std::unordered_map<uint64_t, std::string> names = {
    // clang-format off
    { DeathStranding_FileMagics::Armature,                                 "Armature"                             },
    { DeathStranding_FileMagics::Texture,                                  "Texture"                              },
    { DeathStranding_FileMagics::TextureSet,                               "TextureSet"                           },
    { DeathStranding_FileMagics::Translation,                              "Translation"                          },
    { DeathStranding_FileMagics::Shader,                                   "Shader"                               },
    { DeathStranding_FileMagics::Collection,                               "Collection"                           },
    { DeathStranding_FileMagics::Prefetch,                                 "Prefetch"                             },
    { DeathStranding_FileMagics::VertexArrayResource,                      "VertexArrayResource"                  },
    { DeathStranding_FileMagics::IndexArrayResource,                       "IndexArrayResource"                   },
    { DeathStranding_FileMagics::PrimitiveResource,                        "PrimitiveResource"                    },
    { DeathStranding_FileMagics::MeshResourceBase,                         "MeshResourceBase"                     },
    { DeathStranding_FileMagics::LodMeshResource,                          "LodMeshResource"                      },
    { DeathStranding_FileMagics::MultiMeshResource,                        "MultiMeshResource"                    },
    { DeathStranding_FileMagics::SkinnedMeshResource,                      "SkinnedMeshResource"                  },
    { DeathStranding_FileMagics::RegularSkinnedMeshResourceBase,           "RegularSkinnedMeshResourceBase"       },
    { DeathStranding_FileMagics::RegularSkinnedMeshResource,               "RegularSkinnedMeshResource"           },
    { DeathStranding_FileMagics::SkinnedMeshIndexedJointBindings,          "SkinnedMeshIndexedJointBindings"      },
    { DeathStranding_FileMagics::SkinnedMeshBoneBoundingBoxes,             "SkinnedMeshBoneBoundingBoxes"         },
    { DeathStranding_FileMagics::ShadingGroup,                             "ShadingGroup"                         },
    { DeathStranding_FileMagics::RenderEffectResource,                     "RenderEffectResource"                 },
    { DeathStranding_FileMagics::RegularSkinnedMeshResourceSkinInfo,       "RegularSkinnedMeshResourceSkinInfo"   },
    { DeathStranding_FileMagics::StaticMeshResource,                       "StaticMeshResource"                   },
    // clang-format on
};

std::invoke_result_t<Decima::Handler<Decima::CoreObject>> Decima::get_type_handler(std::uint64_t hash) {
    const auto handler = handlers.find(hash);
    return handler != handlers.end() ? handler->second() : construct<Decima::Dummy>();
}

std::string Decima::get_type_name(uint64_t hash) {
    const auto name = names.find(hash);
    return name != names.end() ? name->second : "Unknown '" + uint64_to_hex(hash) + "'";
}