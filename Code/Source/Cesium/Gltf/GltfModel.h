#pragma once

#include <Atom/Feature/Mesh/MeshFeatureProcessorInterface.h>
#include <Atom/RPI.Public/Material/Material.h>
#include <AzCore/std/containers/vector.h>
#include <AzFramework/Physics/Common/PhysicsTypes.h>
#include <glm/glm.hpp>

namespace Cesium
{
    struct GltfLoadModel;

    struct GltfMaterial
    {
        GltfMaterial() = default;

        AZ::Data::Instance<AZ::RPI::Material> m_material;
    };

    struct GltfPrimitive
    {
        GltfPrimitive();

        AZ::Render::MeshFeatureProcessorInterface::MeshHandle m_meshHandle;
        AZStd::vector<AzPhysics::SimulatedBodyHandle> m_colliderHandles; // TODO: Needs to be destroyed at end of lifetime
        std::int32_t m_materialIndex;
    };

    struct GltfMesh
    {
        GltfMesh();

        AZStd::vector<GltfPrimitive> m_primitives;
        glm::dmat4 m_transform;
    };

    class GltfModel
    {
    public:
        GltfModel(AZ::Render::MeshFeatureProcessorInterface* meshFeatureProcessor, const GltfLoadModel& loadModel);

        GltfModel(const GltfModel&) = delete;

        GltfModel(GltfModel&&) noexcept;

        GltfModel& operator=(const GltfModel&) = delete;

        GltfModel& operator=(GltfModel&&) noexcept;

        ~GltfModel() noexcept;

        const AZStd::vector<GltfMesh>& GetMeshes() const;

        AZStd::vector<GltfMesh>& GetMeshes();

        const AZStd::vector<GltfMaterial>& GetMaterials() const;

        AZStd::vector<GltfMaterial>& GetMaterials();

        void UpdateMaterialForPrimitive(GltfPrimitive& primitive);

        bool IsVisible() const;

        void SetVisible(bool visible);

        void SetTransform(const glm::dmat4& transform);

        const glm::dmat4& GetTransform() const;

        void Destroy() noexcept;

    private:
        void SetUpPhysicsCollidersForPrimitive(AZ::Data::Instance<AZ::RPI::Model> visualModel, GltfPrimitive& primitive);

        AZ::Render::MeshFeatureProcessorInterface::ModelChangedEvent::Handler makeModelChangeEventHandlerForPrimitive(GltfPrimitive& primitive)
        {
            return AZ::Render::MeshFeatureProcessorInterface::ModelChangedEvent::Handler
            {
                [&](AZ::Data::Instance<AZ::RPI::Model> model) { 
                    SetUpPhysicsCollidersForPrimitive(model, primitive); 
                }
            };
        };

        // TODO: Set up handler for non-uniform scaling. Cf. MeshComponentController.cpp
        // AZ::NonUniformScaleChangedEvent::Handler m_nonUniformScaleChangedHandler
        // {
        //     [&](const AZ::Vector3& nonUniformScale) { HandleNonUniformScaleChange(nonUniformScale); }
        // };

        const AZ::Name m_position = AZ::Name("POSITION");
        bool m_visible;
        glm::dmat4 m_transform;
        AZ::Render::MeshFeatureProcessorInterface* m_meshFeatureProcessor;
        AZStd::vector<GltfMesh> m_meshes;
        AZStd::vector<GltfMaterial> m_materials;
        // AzPhysics::SceneHandle m_sceneHandle;
    };
} // namespace Cesium
