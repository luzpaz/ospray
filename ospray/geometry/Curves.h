// ======================================================================== //
// Copyright 2009-2018 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#include "Geometry.h"

namespace ospray {
  /*! \brief A geometry for curves

    Implements the \ref geometry_curves geometry

  */
  struct OSPRAY_SDK_INTERFACE Curves : public Geometry
  {
    Curves();
    virtual ~Curves() override = default;
    virtual std::string toString() const override;
    virtual void finalize(Model *model) override;

    // Data members //

    Ref<Data> vertexData; //!< refcounted data array for vertex data
    Ref<Data> indexData; //!< refcounted data array for segment data
    Ref<Data> normalData; //!< refcounted data array for normal data
    Ref<Data> tangentData; //!< refcounted data array for tangent data
  };
  /*! @} */

} // ::ospray

