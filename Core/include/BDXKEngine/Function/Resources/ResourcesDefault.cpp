﻿#include "ResourcesDefault.h"

#include <filesystem>

#include "BDXKEngine/Platform/GL/Mesh/MeshImport.h"
#include "BDXKEngine/Platform/GL/Shader/ShaderImport.h"

namespace BDXKEngine
{
    ObjectPtr<Material> ResourcesDefault::fallbackMaterial = nullptr;
    ObjectPtr<Material> ResourcesDefault::unlitMaterial = nullptr;
    ObjectPtr<Material> ResourcesDefault::standardMaterial = nullptr;
    ObjectPtr<Material> ResourcesDefault::skyboxMaterial = nullptr;
    ObjectPtr<Mesh> ResourcesDefault::cubeMesh = nullptr;
    ObjectPtr<Mesh> ResourcesDefault::sphereMesh = nullptr;
    ObjectPtr<Mesh> ResourcesDefault::blenderMesh = nullptr;
    ObjectPtr<Texture2D> ResourcesDefault::whiteTexture = nullptr;

    ObjectPtr<Material>& ResourcesDefault::GetFallbackMaterial()
    {
        return fallbackMaterial;
    }
    ObjectPtr<Material>& ResourcesDefault::GetUnlitMaterial()
    {
        return unlitMaterial;
    }
    ObjectPtr<Material>& ResourcesDefault::GetStandardMaterial()
    {
        return standardMaterial;
    }
    ObjectPtr<Material>& ResourcesDefault::GetSkyboxMaterial()
    {
        return skyboxMaterial;
    }
    ObjectPtr<Texture2D>& ResourcesDefault::GetWhiteTexture2D()
    {
        return whiteTexture;
    }
    ObjectPtr<Texture2D>& ResourcesDefault::GetFallbackTexture2D()
    {
        return GetWhiteTexture2D();
    }
    ObjectPtr<Mesh>& ResourcesDefault::GetCubeMesh()
    {
        return cubeMesh;
    }
    ObjectPtr<Mesh>& ResourcesDefault::GetSphereMesh()
    {
        return sphereMesh;
    }
    ObjectPtr<Mesh>& ResourcesDefault::GetBlenderMesh()
    {
        return blenderMesh;
    }

    void ResourcesDefault::Initialize()
    {
        if (std::filesystem::exists("ResourcesDefault") == false)
            throw std::exception("无法获取到默认资源");

# define ParsePath(path) "ResourcesDefault/"#path
        //网格
        cubeMesh = MeshImport::Glb(ParsePath(Meshes/Cube.glb));
        sphereMesh = MeshImport::Glb(ParsePath(Meshes/Sphere.glb));
        blenderMesh = MeshImport::Glb(ParsePath(Meshes/Blender.glb));
        //贴图
        whiteTexture = Texture2D::Create(Color::white);
        //着色器
        ObjectPtr<Shader> fallbackShader = ShaderImport::Hlsl(ParsePath(Shaders/Fallback.hlsl));
        ObjectPtr<Shader> shadowMapShader = ShaderImport::Hlsl(ParsePath(Shaders/ShadowMap.hlsl));
        ObjectPtr<Shader> unlitShader = ShaderImport::Hlsl(ParsePath(Shaders/Unlit.hlsl));
        ObjectPtr<Shader> standardShader = ShaderImport::Hlsl(ParsePath(Shaders/Standard.hlsl));
        ObjectPtr<Shader> skyboxShader = ShaderImport::Hlsl(ParsePath(Shaders/Skybox.hlsl));
        //材质球
        fallbackMaterial = Material::Create({
            {PassType::ForwardBase, fallbackShader},
        });
        skyboxMaterial = Material::Create({
            {PassType::ForwardBase, skyboxShader}
        });
        skyboxMaterial->SetPassZTest(0, ZTest::Background);
        unlitMaterial = Material::Create({
            {PassType::ForwardBase, unlitShader},
            {PassType::ForwardAdd, unlitShader},
            {PassType::ShadowCaster, shadowMapShader}
        });
        unlitMaterial->SetPassBlend(1, Blend::Additive);
        unlitMaterial->SetTexture2D(0, whiteTexture);
        standardMaterial = Material::Create({
            {PassType::ForwardBase, standardShader},
            {PassType::ForwardAdd, standardShader},
            {PassType::ShadowCaster, shadowMapShader}
        });
        standardMaterial->SetPassBlend(1, Blend::Additive);
        standardMaterial->SetTexture2D(0, whiteTexture);
    }
}
