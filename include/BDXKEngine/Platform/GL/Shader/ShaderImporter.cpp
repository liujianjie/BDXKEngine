﻿#include "ShaderImporter.h"
#include <d3dcompiler.h>
#include "BDXKEngine/Base/Extension/String.h"

namespace BDXKEngine
{
    void CompileShaderFromFile(const std::string& path, const char* entrypoint, const char* target, ID3DBlob** blob)
    {
        CComPtr<ID3DBlob> compileError;
        const HRESULT result = D3DCompileFromFile(String::to_wstring(path).c_str(),
                                                  nullptr,
                                                  D3D_COMPILE_STANDARD_FILE_INCLUDE,
                                                  entrypoint,
                                                  target,
                                                  D3DCOMPILE_DEBUG,
                                                  0,
                                                  blob,
                                                  &compileError.p
        );

        if (FAILED(result))
        {
            // ReSharper disable once CppDeclaratorNeverUsed
            char* errorInfo = static_cast<char*>(compileError->GetBufferPointer());
            throw std::exception("编译着色器失败");
        }
    }

    ObjectPtr<Shader> ShaderImporter::Import(const std::string& fileName)
    {
        //编译顶点着色器
        CComPtr<ID3DBlob> vertexBlob;
        CompileShaderFromFile(fileName, "VertexPass", "vs_5_0", &vertexBlob.p);
        //编译像素着色器
        CComPtr<ID3DBlob> pixelBlob;
        CompileShaderFromFile(fileName, "PixelPass", "ps_5_0", &pixelBlob.p);

        return Shader::Create(vertexBlob, pixelBlob);
    }
}
