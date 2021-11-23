#include <Cesium/MathReflect.h>
#include <AzCore/Serialization/Json/RegistrationContext.h>

namespace Cesium
{
    void MathSerialization::Reflect(AZ::ReflectContext* context)
    {
        auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context);
        if (serializeContext)
        {
            serializeContext->Class<glm::dvec2>()->Serializer<GlmVecSerializer<glm::dvec2>>();
            serializeContext->Class<glm::dvec3>()->Serializer<GlmVecSerializer<glm::dvec3>>();
            serializeContext->Class<glm::dvec4>()->Serializer<GlmVecSerializer<glm::dvec4>>();
            serializeContext->Class<glm::dquat>()->Serializer<GlmVecSerializer<glm::dquat>>();
        }

        AZ::JsonRegistrationContext* jsonRegistrationContext = azrtti_cast<AZ::JsonRegistrationContext*>(context);
        if (jsonRegistrationContext)
        {
            jsonRegistrationContext->Serializer<GlmDVec2JsonSerializer>()->HandlesType<glm::dvec2>();
            jsonRegistrationContext->Serializer<GlmDVec3JsonSerializer>()->HandlesType<glm::dvec3>();
            jsonRegistrationContext->Serializer<GlmDVec4JsonSerializer>()->HandlesType<glm::dvec4>();
            jsonRegistrationContext->Serializer<GlmDQuatJsonSerializer>()->HandlesType<glm::dquat>();
        }

        if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            ReflectGlmVecBehavior<glm::dvec2>(behaviorContext, "DVector2");
            ReflectGlmVecBehavior<glm::dvec3>(behaviorContext, "DVector3");
            ReflectGlmVecBehavior<glm::dvec4>(behaviorContext, "DVector4");
            ReflectGlmQuatBehavior(behaviorContext);

        }
    }

    template<typename VecType>
    void MathSerialization::ReflectGlmVecBehavior(AZ::BehaviorContext* behaviorContext, const AZStd::string& name)
    {
        behaviorContext->Class<VecType>(name.c_str())
            ->Attribute(AZ::Script::Attributes::Category, "Cesium/Math")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value)
            ->Method(
                "Add",
                [](const VecType& lhs, const VecType& rhs)
                {
                    return lhs + rhs;
                })
            ->Method(
                "Subtract",
                [](const VecType& lhs, const VecType& rhs)
                {
                    return lhs - rhs;
                })
            ->Attribute(AZ::Script::Attributes::Operator, AZ::Script::Attributes::OperatorType::Sub)
            ->Method(
                "Multiply",
                [](const VecType& lhs, const VecType& rhs)
                {
                    return lhs * rhs;
                })
            ->Method(
                "Divide",
                [](const VecType& lhs, const VecType& rhs)
                {
                    return lhs / rhs;
                })
            ->Method(
                "MultiplyByConstant",
                [](const VecType& lhs, double rhs)
                {
                    return lhs * rhs;
                })
            ->Method(
                "DivideByConstant",
                [](const VecType& lhs, double rhs)
                {
                    return lhs / rhs;
                })
            ->Method(
                "Normalized",
                [](const VecType& vec)
                {
                    return glm::normalize(vec);
                })
            ->Method(
                "Length",
                [](const VecType& vec)
                {
                    return glm::length(vec);
                })
            ->Method(
                "LengthSq",
                [](const VecType& vec)
                {
                    return glm::dot(vec, vec);
                })
            ->Method(
                "Distance",
                [](const VecType& lhs, const VecType& rhs)
                {
                    return glm::distance(lhs, rhs);
                })
            ->Method(
                "Dot",
                [](const VecType& lhs, const VecType& rhs)
                {
                    return glm::dot(lhs, rhs);
                })
            ->Method(
                "Abs",
                [](const VecType& vec)
                {
                    return glm::abs(vec);
                })
            ->Method(
                "Min",
                [](const VecType& lhs, const VecType& rhs)
                {
                    return glm::min(lhs, rhs);
                })
            ->Method(
                "Max",
                [](const VecType& lhs, const VecType& rhs)
                {
                    return glm::max(lhs, rhs);
                })
            ->Method(
                "Clamp",
                [](const VecType& x, const VecType& min, const VecType& max)
                {
                    return glm::clamp(x, min, max);
                },
                { AZ::BehaviorParameterOverrides("Value"), AZ::BehaviorParameterOverrides("Min"), AZ::BehaviorParameterOverrides("Max") })
            ->Method(
                "Equal",
                [](const VecType& lhs, const VecType& rhs)
                {
                    return lhs == rhs;
                })
            ;
    }

    void MathSerialization::ReflectGlmQuatBehavior(AZ::BehaviorContext* behaviorContext)
    {
        behaviorContext->Class<glm::dquat>("DQuaternion")
            ->Attribute(AZ::Script::Attributes::Category, "Cesium/Math")
            ->Attribute(AZ::Script::Attributes::Storage, AZ::Script::Attributes::StorageType::Value);
    }

} // namespace Cesium
