#pragma once

#include <AzCore/Math/Transform.h>
#include <AzCore/Math/Vector3.h>
#include <AzCore/Math/Vector4.h>
#include <AzCore/Math/Quaternion.h>
#include <glm/glm.hpp>

namespace Cesium
{
    struct MathHelper
    {
        static glm::dmat4 ConvertTransformAndScaleToDMat4(const AZ::Transform& transform, const AZ::Vector3& nonUniformScale);

        /***
         * Converts mat4 transformation matrix into AZ::Transform and non-uniform scaling factors
         * 
         * @param mat4 Input transformation
         * @param o3deTransform Output - AZ::Transform
         * @param o3deScale Output - AZ::Vector3 of scaling factors in x/y/z dimension
        */
        static void ConvertMat4ToTransformAndScale(const glm::dmat4& mat4, AZ::Transform& o3deTransform, AZ::Vector3& o3deScale);

        static glm::dquat ToDQuaternion(const AZ::Quaternion& quat);

        static glm::dvec3 ToDVec3(const AZ::Vector3& vec);

        static glm::dvec4 ToDVec4(const AZ::Vector3& vec, double w);

        static glm::dvec4 ToDVec4(const AZ::Vector4& vec);

        static bool IsIdentityMatrix(const glm::dmat4& mat);

        static glm::dvec3 CalculatePitchRollHead(const glm::dvec3& direction);

        static std::size_t Align(std::size_t location, std::size_t align);
    };
} // namespace Cesium
