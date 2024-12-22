#pragma once
#include <Banshee/Components/Transform.hpp>

class CameraController final : public Banshee::ComponentBase {
    f32 m_TranslationSpeed = 8.f;
    f32 m_RotationSpeed = 64.f;

    Ref<Banshee::Transform> m_Transform{};

public:
    CameraController() = default;
    ~CameraController() override = default;

    void OnCreate() override {
        PROFILE_SCOPE();
        m_Transform = GetOwner()->GetComponent<Banshee::Transform>();
    }

    void OnTick(f64 delta) override;
    void OnRender(Banshee::Camera *camera) const override {}
    void OnDestroy() override {}
    void OnImGui() override;

    [[nodiscard]] String GetName() const override { return "CameraController"; }
};
