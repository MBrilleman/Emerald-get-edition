#include "global.h"
#include "blit.h"
#include "window.h"
#include "menu.h"
#include "palette.h"
#include "event_data.h"
#include "constants/mugshots.h"

#define MUGSHOT_PALETTE_NUM 13

struct Mugshot{
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    const u32* image;
    const u16* palette;
};

void DrawMugshot(void); //VAR_0x8000 = mugshot id
void DrawMugshotAtPos(void); //VAR_0x8000 = mugshot id, VAR_0x8001 = x, VAR_0x8002 = y
void ClearMugshot(void);
void DrawMugshot2(void);

static const u32 sMugshotImg_intromin1[] = INCBIN_U32("graphics/mugshots/intromin1.4bpp.lz");
static const u32 sMugshotImg_intro0[] = INCBIN_U32("graphics/mugshots/intro0.4bpp.lz");
static const u32 sMugshotImg_intro1[] = INCBIN_U32("graphics/mugshots/intro1.4bpp.lz");
static const u32 sMugshotImg_intro2[] = INCBIN_U32("graphics/mugshots/intro2.4bpp.lz");
static const u32 sMugshotImg_intro3[] = INCBIN_U32("graphics/mugshots/intro3.4bpp.lz");
static const u32 sMugshotImg_intro4[] = INCBIN_U32("graphics/mugshots/intro4.4bpp.lz");
static const u32 sMugshotImg_intro5[] = INCBIN_U32("graphics/mugshots/intro5.4bpp.lz");
static const u32 sMugshotImg_intro6[] = INCBIN_U32("graphics/mugshots/intro6.4bpp.lz");
static const u16 sMugshotPal_intro[] = INCBIN_U16("graphics/mugshots/intro.gbapal");

static const u32 sMugshotImg_appear1[] = INCBIN_U32("graphics/mugshots/appear1.4bpp.lz");
static const u32 sMugshotImg_appear2[] = INCBIN_U32("graphics/mugshots/appear2.4bpp.lz");
static const u32 sMugshotImg_appear3[] = INCBIN_U32("graphics/mugshots/appear3.4bpp.lz");
static const u32 sMugshotImg_appear4[] = INCBIN_U32("graphics/mugshots/appear4.4bpp.lz");
static const u32 sMugshotImg_appear5[] = INCBIN_U32("graphics/mugshots/appear5.4bpp.lz");
static const u32 sMugshotImg_appear6[] = INCBIN_U32("graphics/mugshots/appear6.4bpp.lz");
static const u32 sMugshotImg_appear7[] = INCBIN_U32("graphics/mugshots/appear7.4bpp.lz");
static const u32 sMugshotImg_appear7b[] = INCBIN_U32("graphics/mugshots/appear7b.4bpp.lz");
static const u16 sMugshotPal_appear[] = INCBIN_U16("graphics/mugshots/appear.gbapal");

static const u32 sMugshotImg_encounter1[] = INCBIN_U32("graphics/mugshots/encounter1.4bpp.lz");
static const u32 sMugshotImg_encounter2[] = INCBIN_U32("graphics/mugshots/encounter2.4bpp.lz");
static const u32 sMugshotImg_encounter3[] = INCBIN_U32("graphics/mugshots/encounter3.4bpp.lz");
static const u32 sMugshotImg_encounter4[] = INCBIN_U32("graphics/mugshots/encounter4.4bpp.lz");
static const u32 sMugshotImg_encounter5[] = INCBIN_U32("graphics/mugshots/encounter5.4bpp.lz");
static const u32 sMugshotImg_encounter6[] = INCBIN_U32("graphics/mugshots/encounter6.4bpp.lz");
static const u32 sMugshotImg_encounter7[] = INCBIN_U32("graphics/mugshots/encounter7.4bpp.lz");
static const u32 sMugshotImg_encounter8[] = INCBIN_U32("graphics/mugshots/encounter8.4bpp.lz");
static const u32 sMugshotImg_encounter8a1[] = INCBIN_U32("graphics/mugshots/encounter8a1.4bpp.lz");
static const u32 sMugshotImg_encounter8a2[] = INCBIN_U32("graphics/mugshots/encounter8a2.4bpp.lz");
static const u32 sMugshotImg_encounter9[] = INCBIN_U32("graphics/mugshots/encounter9.4bpp.lz");
static const u32 sMugshotImg_encounter10[] = INCBIN_U32("graphics/mugshots/encounter10.4bpp.lz");
static const u32 sMugshotImg_encounter11[] = INCBIN_U32("graphics/mugshots/encounter11.4bpp.lz");
static const u32 sMugshotImg_encounter12[] = INCBIN_U32("graphics/mugshots/encounter12.4bpp.lz");
static const u32 sMugshotImg_encounter13[] = INCBIN_U32("graphics/mugshots/encounter13.4bpp.lz");
static const u32 sMugshotImg_encounter14[] = INCBIN_U32("graphics/mugshots/encounter14.4bpp.lz");
static const u32 sMugshotImg_encounter15[] = INCBIN_U32("graphics/mugshots/encounter15.4bpp.lz");
static const u32 sMugshotImg_encounter16[] = INCBIN_U32("graphics/mugshots/encounter16.4bpp.lz");
static const u32 sMugshotImg_encounter17[] = INCBIN_U32("graphics/mugshots/encounter17.4bpp.lz");
static const u32 sMugshotImg_encounter18[] = INCBIN_U32("graphics/mugshots/encounter18.4bpp.lz");
static const u32 sMugshotImg_encounter19[] = INCBIN_U32("graphics/mugshots/encounter19.4bpp.lz");
static const u32 sMugshotImg_encounter20[] = INCBIN_U32("graphics/mugshots/encounter20.4bpp.lz");
static const u32 sMugshotImg_encounter21[] = INCBIN_U32("graphics/mugshots/encounter21.4bpp.lz");
static const u32 sMugshotImg_encounter22[] = INCBIN_U32("graphics/mugshots/encounter22.4bpp.lz");
static const u32 sMugshotImg_encounter23[] = INCBIN_U32("graphics/mugshots/encounter23.4bpp.lz");
static const u32 sMugshotImg_encounter24[] = INCBIN_U32("graphics/mugshots/encounter24.4bpp.lz");
static const u32 sMugshotImg_encounter25[] = INCBIN_U32("graphics/mugshots/encounter25.4bpp.lz");
static const u16 sMugshotPal_encounter[] = INCBIN_U16("graphics/mugshots/encounter.gbapal");

static const struct Mugshot sMugshots[] = {
    [MUGSHOT_INTROMIN1] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_intromin1, .palette = sMugshotPal_intro},
    [MUGSHOT_INTRO0] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_intro0, .palette = sMugshotPal_intro},
    [MUGSHOT_INTRO1] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_intro1, .palette = sMugshotPal_intro},
    [MUGSHOT_INTRO2] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_intro2, .palette = sMugshotPal_intro},
    [MUGSHOT_INTRO3] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_intro3, .palette = sMugshotPal_intro},
    [MUGSHOT_INTRO4] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_intro4, .palette = sMugshotPal_intro},
    [MUGSHOT_INTRO5] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_intro5, .palette = sMugshotPal_intro},
    [MUGSHOT_INTRO6] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_intro6, .palette = sMugshotPal_intro},
    [MUGSHOT_APPEAR1] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_appear1, .palette = sMugshotPal_appear},
    [MUGSHOT_APPEAR2] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_appear2, .palette = sMugshotPal_appear},
    [MUGSHOT_APPEAR3] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_appear3, .palette = sMugshotPal_appear},
    [MUGSHOT_APPEAR4] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_appear4, .palette = sMugshotPal_appear},
    [MUGSHOT_APPEAR5] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_appear5, .palette = sMugshotPal_appear},
    [MUGSHOT_APPEAR6] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_appear6, .palette = sMugshotPal_appear},
    [MUGSHOT_APPEAR7] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_appear7, .palette = sMugshotPal_appear},
    [MUGSHOT_APPEAR7B] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_appear7b, .palette = sMugshotPal_appear},
    [MUGSHOT_ENCOUNTER1] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter1, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER2] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter2, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER3] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter3, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER4] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter4, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER5] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter5, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER6] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter6, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER7] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter7, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER8] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter8, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER8A1] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter8a1, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER8A2] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter8a2, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER9] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter9, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER10] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter10, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER11] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter11, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER12] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter12, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER13] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter13, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER14] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter14, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER15] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter15, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER16] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter16, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER17] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter17, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER18] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter18, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER19] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter19, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER20] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter20, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER21] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter21, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER22] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter22, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER23] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter23, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER24] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter24, .palette = sMugshotPal_encounter},
    [MUGSHOT_ENCOUNTER25] {.x = 0, .y = 0, .width = 240, .height =176, .image = sMugshotImg_encounter25, .palette = sMugshotPal_encounter},
};


//WindowId + 1, 0 if window is not open
static EWRAM_DATA u8 sMugshotWindow = 0;
static EWRAM_DATA u8 sMugshotWindow2 = 0;

void ClearMugshot(void){
    while(sMugshotWindow != 0){
        ClearStdWindowAndFrameToTransparent(sMugshotWindow - 1, 0);
        CopyWindowToVram(sMugshotWindow - 1, 3);
        RemoveWindow(sMugshotWindow - 1);
        sMugshotWindow = sMugshotWindow - 1;
    }
}

void ClearMugshot2(void){
    while(sMugshotWindow2 != 0){
        ClearStdWindowAndFrameToTransparent(sMugshotWindow2 - 1, 0);
        CopyWindowToVram(sMugshotWindow2 - 1, 3);
        RemoveWindow(sMugshotWindow2 - 1);
        sMugshotWindow2 = sMugshotWindow2 - 1;
    }
}

static void DrawMugshotCore(const struct Mugshot* const mugshot, int x, int y){
    struct WindowTemplate t;
    u16 windowId;
    
    // if(sMugshotWindow != 0){
    //     ClearMugshot();
    // }
    if (sMugshotWindow == 0){
        #if GAME_VERSION==VERSION_EMERALD
        SetWindowTemplateFields(&t, 0, x, y, mugshot->width/8, mugshot->height/8, MUGSHOT_PALETTE_NUM, 0x40);
        #else
        t = SetWindowTemplateFields(0, x, y, mugshot->width/8, mugshot->height/8, MUGSHOT_PALETTE_NUM, 0x40);
        #endif
        windowId = AddWindow(&t);
        sMugshotWindow = windowId + 1;
    } 

    else { 
        windowId = sMugshotWindow - 1;
    }
        
    
    LoadPalette(mugshot->palette, 16 * MUGSHOT_PALETTE_NUM, 32);
    CopyToWindowPixelBuffer(windowId, (const void*)mugshot->image, 0, 0);
    PutWindowRectTilemap(windowId, 0, 0, mugshot->width/8, mugshot->height/8);
    CopyWindowToVram(windowId, 3);
}

static void DrawMugshotCore2(const struct Mugshot* const mugshot, int x, int y){
    struct WindowTemplate t;
    u16 windowId2;
    
    // if(sMugshotWindow2 != 0){
    //     ClearMugshot2();
    // }
    
    #if GAME_VERSION==VERSION_EMERALD
    SetWindowTemplateFields(&t, 0, x, y, mugshot->width/8, mugshot->height/8, MUGSHOT_PALETTE_NUM, 0x40);
    #else
    t = SetWindowTemplateFields(0, x, y, mugshot->width/8, mugshot->height/8, MUGSHOT_PALETTE_NUM, 0x40);
    #endif
    windowId2 = AddWindow(&t);
    sMugshotWindow2 = windowId2 + 1;
    
    LoadPalette(mugshot->palette, 16 * MUGSHOT_PALETTE_NUM, 32);
    CopyToWindowPixelBuffer(windowId2, (const void*)mugshot->image, 0, 0);
    PutWindowRectTilemap(windowId2, 0, 0, mugshot->width/8, mugshot->height/8);
    CopyWindowToVram(windowId2, 3);
}

void DrawMugshot(void){
    const struct Mugshot* const mugshot = sMugshots + VarGet(VAR_0x8000);
    DrawMugshotCore(mugshot, mugshot->x, mugshot->y);
}

void DrawMugshot2(void){
    const struct Mugshot* const mugshot = sMugshots + VarGet(VAR_0x8003);
    DrawMugshotCore2(mugshot, mugshot->x, mugshot->y);
}

void DrawMugshotAtPos(void){
    DrawMugshotCore(sMugshots + VarGet(VAR_0x8000), VarGet(VAR_0x8001), VarGet(VAR_0x8002));
}