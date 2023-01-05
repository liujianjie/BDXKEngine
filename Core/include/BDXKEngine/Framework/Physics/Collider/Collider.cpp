﻿#include "Collider.h"

#include "BDXKEngine/Framework/Physics/Rigidbody/Rigidbody.h"

namespace BDXKEngine
{
    void Collider::OnEnable()
    {
        rightbody = GetGameObject()->GetComponent<Rigidbody>();
        if (rightbody == nullptr)
        {
            rightbody = Create<Rigidbody>(GetGameObject());
            rightbody->SetIsKinematic(true);
        }

        shape->setGeometry(GetPxGeometry());
        rightbody->GetPxRigidbody().attachShape(*shape);
        rightbody->ResetCenterOfMassAndInertiaTensor();
    }
    void Collider::OnDisable()
    {
        if (rightbody.IsNotNull())
        {
            rightbody->GetPxRigidbody().detachShape(*shape);
            rightbody->ResetCenterOfMassAndInertiaTensor();
        }
    }
    void Collider::OnAwake()
    {
        shape = Phys::GetPhysics().createShape(GetPxGeometry(), material.IsNotNull() ? material->GetPxMaterial() : Phys::GetMaterial());
        shape->userData = this;
    }
    void Collider::OnDestroy()
    {
        shape->release();
    }

    void Collider::Transfer(Transferer& transferer)
    {
        Behavior::Transfer(transferer);

        TransferFieldInfo(material);
    }
    void Collider::Awake()
    {
        Behavior::Awake();
    }
}
