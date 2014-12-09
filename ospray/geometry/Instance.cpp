/********************************************************************* *\
 * INTEL CORPORATION PROPRIETARY INFORMATION                            
 * This software is supplied under the terms of a license agreement or  
 * nondisclosure agreement with Intel Corporation and may not be copied 
 * or disclosed except in accordance with the terms of that agreement.  
 * Copyright (C) 2014 Intel Corporation. All Rights Reserved.           
 ********************************************************************* */

#undef NDEBUG

// ospray
#include "Instance.h"
#include "ospray/common/Model.h"
// ispc-generated files
#include "Instance_ispc.h"

namespace ospray {

  Instance::Instance()
  {
    this->ispcEquivalent = ispc::InstanceGeometry_create(this);
  }

  void Instance::finalize(Model *model) 
  {
    xfm.l.vx = getParam3f("xfm.l.vx",vec3f(1.f,0.f,0.f));
    xfm.l.vy = getParam3f("xfm.l.vy",vec3f(0.f,1.f,0.f));
    xfm.l.vz = getParam3f("xfm.l.vz",vec3f(0.f,0.f,1.f));
    xfm.p   = getParam3f("xfm.p",vec3f(0.f,0.f,0.f));

    instancedScene = (Model *)getParamObject("model",NULL);
    embreeGeomID = rtcNewInstance(model->embreeSceneHandle,
                                  instancedScene->embreeSceneHandle);

    assert(instancedScene);
    
    const vec3f mesh_center  = xfm.p == vec3f(0.f, 0.f, 0.f)
      ? embree::center(instancedScene->geometry[0]->bounds)
      : xfm.p;
    const vec3f model_center = model->getParam3f("explosion.center", mesh_center);
    const vec3f dir = mesh_center - model_center;
    xfm.p += dir * model->getParam1f("explosion.factor", 0.f);

    rtcSetTransform(model->embreeSceneHandle,embreeGeomID,
                    RTC_MATRIX_COLUMN_MAJOR,
                    (const float *)&xfm);
    rtcEnable(model->embreeSceneHandle,embreeGeomID);
    AffineSpace3f rcp_xfm = rcp(xfm);
    ispc::InstanceGeometry_set(getIE(),
                               (ispc::AffineSpace3f&)xfm,
                               (ispc::AffineSpace3f&)rcp_xfm,
                               instancedScene->getIE());
  }

  OSP_REGISTER_GEOMETRY(Instance,instance);
}