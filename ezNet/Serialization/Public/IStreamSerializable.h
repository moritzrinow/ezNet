// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include "Common/Public/Defines.h"
#include "Stream/Public/IStream.h"

EZNET_BEGIN

class IStreamSerializable;

/*
* Interface to work with objects, that can be serialized to streams.
*/
class IStreamSerializable {

public:

  /*
  * Virtual deconstructor.
  */
  virtual ~IStreamSerializable() {}

  /*
  * This should serialize the current instance behind the interface to a stream.
  */
  virtual void Serialize(IStream* stream) = 0;
};

EZNET_END