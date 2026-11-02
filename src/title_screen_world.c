#include "global.h"
#include "clear_save_data_menu.h"
#include "decompress.h"
#include "event_data.h"
#include "graphics.h"
#include "gpu_regs.h"
#include "intro.h"
#include "m4a.h"
#include "main.h"
#include "main_menu.h"
#include "palette.h"
#include "quickstart.h"
#include "reset_rtc_screen.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "title_screen.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#if ALL_REGIONS

// The 240x160 title contains no prompt; reuse the original World blinking sprite.
#define MOSAIC_SCREEN_BLOCK 30
#define MOSAIC_TITLE_TILES_RAW_BYTES (232 * 64)
#define MOSAIC_PRESS_START_TAG 1001
#define MOSAIC_PRESS_START_PIECES 5
#define CLEAR_SAVE_COMBO (B_BUTTON | SELECT_BUTTON | DPAD_UP)
#define RESET_RTC_COMBO (B_BUTTON | SELECT_BUTTON | DPAD_LEFT)

static const struct OamData sMosaicPressStartOam =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x8),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sMosaicPromptFrame0[] = { ANIMCMD_FRAME(1, 4), ANIMCMD_END };
static const union AnimCmd sMosaicPromptFrame1[] = { ANIMCMD_FRAME(5, 4), ANIMCMD_END };
static const union AnimCmd sMosaicPromptFrame2[] = { ANIMCMD_FRAME(9, 4), ANIMCMD_END };
static const union AnimCmd sMosaicPromptFrame3[] = { ANIMCMD_FRAME(13, 4), ANIMCMD_END };
static const union AnimCmd sMosaicPromptFrame4[] = { ANIMCMD_FRAME(17, 4), ANIMCMD_END };

static const union AnimCmd *const sMosaicPromptAnims[] =
{
    sMosaicPromptFrame0,
    sMosaicPromptFrame1,
    sMosaicPromptFrame2,
    sMosaicPromptFrame3,
    sMosaicPromptFrame4,
};

static void SpriteCB_MosaicPressStart(struct Sprite *sprite)
{
    sprite->invisible = !(++sprite->data[0] & 16);
}

static const struct SpriteTemplate sMosaicPressStartTemplate =
{
    .tileTag = MOSAIC_PRESS_START_TAG,
    .paletteTag = MOSAIC_PRESS_START_TAG,
    .oam = &sMosaicPressStartOam,
    .anims = sMosaicPromptAnims,
    .callback = SpriteCB_MosaicPressStart,
};

static const struct CompressedSpriteSheet sMosaicPressStartSheet =
{
    .data = gTitleScreenPressStartGfx,
    .size = 0x520,
    .tag = MOSAIC_PRESS_START_TAG,
};

static const struct SpritePalette sMosaicPressStartPalette =
{
    .data = gTitleScreenPressStartPal,
    .tag = MOSAIC_PRESS_START_TAG,
};

static void CreateMosaicPressStart(void)
{
    u8 i;
    for (i = 0; i < MOSAIC_PRESS_START_PIECES; i++)
    {
        u8 spriteId = CreateSprite(&sMosaicPressStartTemplate, 65 + i * 32, 145, 0);
        if (spriteId != MAX_SPRITES)
            StartSpriteAnim(&gSprites[spriteId], i);
    }
}

static const u32 sMosaicTiles[] = INCBIN_U32("graphics/title_screen/world/anthology_title_tiles.bin");
static const u16 sMosaicPalette[] = INCBIN_U16("graphics/title_screen/world/anthology_title_palette.bin");
static const u16 sMosaicMap[] = INCBIN_U16("graphics/title_screen/world/anthology_title_map.bin");

STATIC_ASSERT(MOSAIC_TITLE_TILES_RAW_BYTES <= MOSAIC_SCREEN_BLOCK * 0x800, MosaicTitleTilesFit);
STATIC_ASSERT(sizeof(sMosaicTiles) == MOSAIC_TITLE_TILES_RAW_BYTES, MosaicTitleTilesLength);
STATIC_ASSERT(sizeof(sMosaicPalette) == BG_PLTT_SIZE, MosaicTitlePaletteSize);
STATIC_ASSERT(sizeof(sMosaicMap) == 0x800, MosaicTitleMapSize);

static void MainCB2_WorldTitleScreen(void);
static void Task_WorldTitleScreen(u8 taskId);
static void CB2_LeaveWorldTitleScreen(void);

static EWRAM_DATA MainCallback sWorldTitleNextCallback = NULL;

static void VBlankCB_WorldTitleScreen(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_InitWorldTitleScreen(void)
{
    u32 i;

    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        SetHBlankCallback(NULL);
        ScanlineEffect_Stop();
        ScanlineEffect_Clear();
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_FORCED_BLANK);
        for (i = REG_OFFSET_BG0CNT; i <= REG_OFFSET_BG3VOFS; i += 2)
            SetGpuReg(i, 0);
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WIN1H, 0);
        SetGpuReg(REG_OFFSET_WIN1V, 0);
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_MOSAIC, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        DmaFill16(3, 0, (void *)VRAM, VRAM_SIZE);
        DmaFill32(3, 0, (void *)OAM, OAM_SIZE);
        DmaFill16(3, 0, (void *)PLTT, PLTT_SIZE);
        ResetPaletteFade();
        ResetTasks();
        ResetSpriteData();
        FreeAllSpritePalettes();
        gReservedSpritePaletteCount = 0;
        sWorldTitleNextCallback = NULL;
        gMain.state++;
        break;
    case 1:
        // A direct aligned DMA copy avoids VRAM LZ10 halfword decoding differences.
        // The art is only 38 KiB raw, so ROM overhead is small.
        DmaCopy32(3, sMosaicTiles, (void *)VRAM, sizeof(sMosaicTiles));
        DmaCopy16(3, sMosaicMap, (void *)BG_SCREEN_ADDR(MOSAIC_SCREEN_BLOCK), sizeof(sMosaicMap));
        LoadPalette(sMosaicPalette, 0, sizeof(sMosaicPalette));
        LoadCompressedSpriteSheet(&sMosaicPressStartSheet);
        LoadSpritePalette(&sMosaicPressStartPalette);
        if (QUICKSTART && QUICKSTART_HUD)
            CreateQuickstartHud();
        BuildOamBuffer();
        gMain.state++;
        break;
    default:
        SetGpuReg(REG_OFFSET_BG0CNT, BGCNT_PRIORITY(0) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(MOSAIC_SCREEN_BLOCK) | BGCNT_256COLOR | BGCNT_TXT256x256);
        CreateMosaicPressStart();
        CreateTask(Task_WorldTitleScreen, 0);
        BeginNormalPaletteFade(PALETTES_ALL, 1, 16, 0, RGB_WHITEALPHA);
        SetVBlankCallback(VBlankCB_WorldTitleScreen);
        EnableInterrupts(INTR_FLAG_VBLANK);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG0_ON | DISPCNT_OBJ_ON);
        m4aSongNumStart(MUS_TITLE);
        SetMainCallback2(MainCB2_WorldTitleScreen);
        break;
    }
}

static void MainCB2_WorldTitleScreen(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void LeaveWorldTitleScreen(MainCallback nextCallback, u16 fadeColor)
{
    ScanlineEffect_Stop();
    FadeOutBGM(4);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, fadeColor);
    sWorldTitleNextCallback = nextCallback;
    SetMainCallback2(CB2_LeaveWorldTitleScreen);
}

static void CB2_LeaveWorldTitleScreen(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(sWorldTitleNextCallback);
}

static void Task_WorldTitleScreen(u8 taskId)
{
    (void)taskId;
    if (gPaletteFade.active)
        return;

    if (JOY_HELD(CLEAR_SAVE_COMBO) == CLEAR_SAVE_COMBO)
        LeaveWorldTitleScreen(CB2_InitClearSaveDataScreen, RGB_WHITEALPHA);
    else if (JOY_HELD(RESET_RTC_COMBO) == RESET_RTC_COMBO)
    {
        if (CanResetRTC())
            LeaveWorldTitleScreen(CB2_InitResetRtcScreen, RGB_BLACK);
    }
    else if (JOY_NEW(A_BUTTON | START_BUTTON))
        LeaveWorldTitleScreen(CB2_InitMainMenu, RGB_WHITEALPHA);
    else if (QUICKSTART && JOY_NEW(SELECT_BUTTON))
        Quickstart();
    else if ((gMPlayInfo_BGM.status & 0xFFFF) == 0)
        LeaveWorldTitleScreen(CB2_InitCopyrightScreenAfterTitleScreen, RGB_WHITEALPHA);
}

#endif // ALL_REGIONS
