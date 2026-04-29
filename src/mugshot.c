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

static const u32 sMugshotImg_test[] = INCBIN_U32("graphics/mugshots/test.4bpp.lz");
static const u16 sMugshotPal_test[] = INCBIN_U16("graphics/mugshots/test.gbapal");
static const u32 sMugshotImg_test2[] = INCBIN_U32("graphics/mugshots/test2.4bpp.lz");
static const u16 sMugshotPal_test2[] = INCBIN_U16("graphics/mugshots/test2.gbapal");
static const u32 sMugshotImg_test3[] = INCBIN_U32("graphics/mugshots/test3.4bpp.lz");
static const u16 sMugshotPal_test3[] = INCBIN_U16("graphics/mugshots/test3.gbapal");
static const u32 sMugshotImg_test4[] = INCBIN_U32("graphics/mugshots/test4.4bpp.lz");
static const u16 sMugshotPal_test4[] = INCBIN_U16("graphics/mugshots/test4.gbapal");
static const u32 sMugshotImg_peace1[] = INCBIN_U32("graphics/mugshots/peace1.4bpp.lz");
static const u16 sMugshotPal_peace1[] = INCBIN_U16("graphics/mugshots/peace1.gbapal");
static const u32 sMugshotImg_peace2[] = INCBIN_U32("graphics/mugshots/peace2.4bpp.lz");
static const u16 sMugshotPal_peace2[] = INCBIN_U16("graphics/mugshots/peace2.gbapal");
static const u32 sMugshotImg_peace3[] = INCBIN_U32("graphics/mugshots/peace3.4bpp.lz");
static const u16 sMugshotPal_peace3[] = INCBIN_U16("graphics/mugshots/peace3.gbapal");
static const u32 sMugshotImg_peace4[] = INCBIN_U32("graphics/mugshots/peace4.4bpp.lz");
static const u16 sMugshotPal_peace4[] = INCBIN_U16("graphics/mugshots/peace4.gbapal");

static const struct Mugshot sMugshots[] = {
    [MUGSHOT_TEST] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_test, .palette = sMugshotPal_test},
    [MUGSHOT_TEST2] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_test2, .palette = sMugshotPal_test2},
    [MUGSHOT_TEST3] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_test3, .palette = sMugshotPal_test3},
    [MUGSHOT_TEST4] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_test4, .palette = sMugshotPal_test4},
    [MUGSHOT_PEACE1] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_peace1, .palette = sMugshotPal_peace1},
    [MUGSHOT_PEACE2] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_peace2, .palette = sMugshotPal_peace2},
    [MUGSHOT_PEACE3] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_peace3, .palette = sMugshotPal_peace3},
    [MUGSHOT_PEACE4] = {.x = 0, .y = 0, .width = 200, .height = 136, .image = sMugshotImg_peace4, .palette = sMugshotPal_peace4},
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