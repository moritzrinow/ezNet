// Copyright (c) 2018 - 2018, Moritz Rinow. All rights reserved.

#pragma once

#include "Common/Public/Defines.h"
#include "Stream/Public/MemoryStream.h"

EZNET_BEGIN

class ZipStream;

#define ZIP_MIN_IN_BUFFER_SIZE 16 // Minimum in buffer size in bytes
#define ZIP_MIN_OUT_BUFFER_COMPARED_TO_IN 1.05 // Output buffer at least 5% larger than in buffer
#define ZIP_MIN_OUT_BUFFER_SIZE 66 // Minimum out buffer size in bytes

/*
* Defines wether the stream should be compressed or decompressed.
*/
enum class ECompressionMode {

  Compress = 0,
  Decompress = 1
};

/*
* Defines the level of compression.
*/
enum class ECompressionLevel {
  
  None = 0, // For decompression
  Fast = 1, // For smaller data (speed)
  Strong = 2 // For huge data (more compression, slightly slower)
};

/*
* Provides functionality to compress / decompress streams.
*/
class ZipStream : public IStream {

public:

  ZipStream(IStream* stream, ECompressionLevel level); // Compressing
  ZipStream(IStream* stream, ECompressionMode mode, int32 originalSize); // Decompressing / Compressing (level 1)
  ~ZipStream();

  /*
  * Returns wether the current instance is used for compression or decompression.
  */
  ECompressionMode Mode();

  /*
  * Returns the level of the current compression.
  */
  ECompressionLevel Level();

  /*
  * This is only relevant in decompress mode.
  * Determines wether the given compressed input stream was decompressed well internally.
  */
  bool DecompressedWell();

  /*
  * Returns a pointer to the underlying stream.
  */
  IStream* BaseStream();

  /*
  * Not supported.
  * Always false.
  */
  bool EndOfStream() override;

  /*
  * Not supported.
  * Always returns -1.
  */
  int32 Length() override;

  /*
  * Not supported.
  * Always returns -1;
  */
  int32 GetPosition() override;

  /*
  * Not supported.
  * Always returns -1;
  */
  void SetPosition(int32 position) override;

  /*
  * Closes the underlying stream.
  */
  void Close(int32 waitMs) override;

  /*
  * Supported by default.
  */
  void CopyTo(IStream* destination) override;

  /*
  * Only supported for decompression mode.
  * Returns -1 if unsupported.
  */
  int32 Read(byte* buffer, int32 offset, int32 count) override;

  /*
  * Only supported for decompression mode.
  * Returns -1 if not supported.
  */
  int32 ReadByte() override;

  /*
  * Only supported for compression mode.
  * Does nothing if not supported.
  *
  * NOTES:
  * Input buffer has to be at least 16 bytes long (count too).
  * If not, this method wont do anything.
  */
  void Write(byte* buffer, int32 offset, int32 count) override;

  /*
  * Not supported.
  * This method does nothing.
  */
  void WriteByte(byte value) override;

private:

  bool DecompressToInternalBuffer();

  int32 m_originalSize;
  bool m_decompressedWell;
  MemoryStream m_readStream;
  IStream* m_baseStream;
  ECompressionMode m_mode;
  ECompressionLevel m_level;
};

EZNET_END