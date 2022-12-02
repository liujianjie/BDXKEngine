﻿#pragma once
#include <unordered_set>
#include "BDXKEngine/Base/Object/Core/Object.h"
#include "BDXKEngine/Base/Reflection/Reflection.h"

namespace BDXKEngine
{
    class ScriptableObject;

    class AwakeHandler
    {
        friend ScriptableObject;
    public:
        virtual ~AwakeHandler() = default;
    protected:
        virtual void OnAwake() = 0;
    };

    class DestroyHandler
    {
        friend ScriptableObject;
    public:
        virtual ~DestroyHandler() = default;
    protected:
        virtual void OnDestroy() = 0;
    };

    class EnableHandler
    {
        friend ScriptableObject;
    public:
        virtual ~EnableHandler() = default;
    protected:
        virtual void OnEnable() = 0;
    };

    class DisableHandler
    {
        friend ScriptableObject;
    public:
        virtual ~DisableHandler() = default;
    protected:
        virtual void OnDisable() = 0;
    };

    //脚本能力有两层含义，1.提供基本的脚本事件，2.提供被其他脚本搜索的功能
    class ScriptableObject : public Object
    {
    public:
        template <class TObject, class TResult = TObject>
        static std::vector<ObjectPtr<TResult>> FindScriptableObjectsOfType()
        {
            std::vector<ObjectPtr<TResult>> result{};
            for (const auto& item : allScriptableObjects)
            {
                TObject* object = dynamic_cast<TObject*>(item);
                if (object != nullptr)result.emplace_back(dynamic_cast<TResult*>(object));
            }

            return result;
        }

        virtual bool GetIsActivating() const;
        bool GetIsEnabling() const;
        void SetIsActivating(bool state);
        void SetIsEnabling(bool state);

        bool IsActivatingAndEnabling() const;

        void Transfer(Transferer& transferer) override;
    protected:
        virtual void Enable();
        virtual void Disable();
        void Awake() override;
        void Destroy() override;
    private:
        static std::unordered_set<ScriptableObject*> allScriptableObjects;

        bool isAwakened = false;
        bool isActivating = false;
        bool isEnabling = true;
    };

    CustomReflection(ScriptableObject)
}
