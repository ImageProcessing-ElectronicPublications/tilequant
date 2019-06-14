/**************************************/
#pragma once
/**************************************/
#include <stdint.h>
/**************************************/
#include "Bitmap.h"
#include "PxType.h"
/**************************************/

union TilePx_t {
	struct YUVAf_t *PxYUVA;
	struct BGR8_t  *PxBGRA;
	uint8_t  PxIdx;
};

struct TilesData_t {
	int TileW,  TileH;
	int TilesX, TilesY;
	union TilePx_t *TilePxPtr;  //! Tile pixel pointers
	struct YUVAf_t *TileValue;  //! Tile values
	struct YUVAf_t *PxData;     //! Tile pixel data
	struct YUVAf_t *PxTemp;     //! Temporary processing data
	int32_t        *PxTempIdx;  //! Temporary processing data (palette entry indices)
	int32_t        *TilePalIdx; //! Tile palette indices
};

/**************************************/

//! Convert bitmap to tiles
//! NOTE: To destroy, call free() on the returned pointer
struct TilesData_t *TilesData_FromBitmap(const struct BmpCtx_t *Ctx, int TileW, int TileH, const struct BGRA8_t *BitRange);

//! Create quantized palette
//! NOTE: PalUnusedEntries is used for 'padding', such as on
//! the GBA/NDS where index 0 of every palette is transparent
int TilesData_QuantizePalettes(struct TilesData_t *TilesData, struct YUVAf_t *Palette, int MaxTilePals, int MaxPalSize, int PalUnusedEntries);

/**************************************/
//! EOF
/**************************************/