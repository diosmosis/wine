/*
 * Graphics driver management functions
 *
 * Copyright 1994 Bob Amstadt
 * Copyright 1996, 2001 Alexandre Julliard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "config.h"
#include "wine/port.h"

#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "windef.h"
#include "winbase.h"
#include "winreg.h"
#include "ddrawgdi.h"
#include "wine/winbase16.h"

#include "gdi_private.h"
#include "wine/unicode.h"
#include "wine/list.h"
#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(driver);

struct graphics_driver
{
    struct list             entry;
    HMODULE                 module;  /* module handle */
    DC_FUNCTIONS            funcs;
};

static struct list drivers = LIST_INIT( drivers );
static struct graphics_driver *display_driver;

static CRITICAL_SECTION driver_section;
static CRITICAL_SECTION_DEBUG critsect_debug =
{
    0, 0, &driver_section,
    { &critsect_debug.ProcessLocksList, &critsect_debug.ProcessLocksList },
      0, 0, { (DWORD_PTR)(__FILE__ ": driver_section") }
};
static CRITICAL_SECTION driver_section = { &critsect_debug, -1, 0, 0, 0, 0 };

/**********************************************************************
 *	     create_driver
 *
 * Allocate and fill the driver structure for a given module.
 */
static struct graphics_driver *create_driver( HMODULE module )
{
    struct graphics_driver *driver;

    if (!(driver = HeapAlloc( GetProcessHeap(), 0, sizeof(*driver)))) return NULL;
    driver->module = module;

    /* fill the function table */
    if (module)
    {
#define GET_FUNC(name) driver->funcs.p##name = (void*)GetProcAddress( module, #name )
        GET_FUNC(AbortDoc);
        GET_FUNC(AbortPath);
        GET_FUNC(AlphaBlend);
        GET_FUNC(AngleArc);
        GET_FUNC(Arc);
        GET_FUNC(ArcTo);
        GET_FUNC(BeginPath);
        GET_FUNC(ChoosePixelFormat);
        GET_FUNC(Chord);
        GET_FUNC(CloseFigure);
        GET_FUNC(CreateBitmap);
        GET_FUNC(CreateDC);
        GET_FUNC(CreateDIBSection);
        GET_FUNC(DeleteBitmap);
        GET_FUNC(DeleteDC);
        GET_FUNC(DescribePixelFormat);
        GET_FUNC(DeviceCapabilities);
        GET_FUNC(Ellipse);
        GET_FUNC(EndDoc);
        GET_FUNC(EndPage);
        GET_FUNC(EndPath);
        GET_FUNC(EnumDeviceFonts);
        GET_FUNC(EnumICMProfiles);
        GET_FUNC(ExcludeClipRect);
        GET_FUNC(ExtDeviceMode);
        GET_FUNC(ExtEscape);
        GET_FUNC(ExtFloodFill);
        GET_FUNC(ExtSelectClipRgn);
        GET_FUNC(ExtTextOut);
        GET_FUNC(FillPath);
        GET_FUNC(FillRgn);
        GET_FUNC(FlattenPath);
        GET_FUNC(FrameRgn);
        GET_FUNC(GdiComment);
        GET_FUNC(GetBitmapBits);
        GET_FUNC(GetCharWidth);
        GET_FUNC(GetDIBits);
        GET_FUNC(GetDeviceCaps);
        GET_FUNC(GetDeviceGammaRamp);
        GET_FUNC(GetICMProfile);
        GET_FUNC(GetNearestColor);
        GET_FUNC(GetPixel);
        GET_FUNC(GetPixelFormat);
        GET_FUNC(GetSystemPaletteEntries);
        GET_FUNC(GetTextExtentExPoint);
        GET_FUNC(GetTextMetrics);
        GET_FUNC(IntersectClipRect);
        GET_FUNC(InvertRgn);
        GET_FUNC(LineTo);
        GET_FUNC(MoveTo);
        GET_FUNC(ModifyWorldTransform);
        GET_FUNC(OffsetClipRgn);
        GET_FUNC(OffsetViewportOrgEx);
        GET_FUNC(OffsetWindowOrgEx);
        GET_FUNC(PaintRgn);
        GET_FUNC(PatBlt);
        GET_FUNC(Pie);
        GET_FUNC(PolyBezier);
        GET_FUNC(PolyBezierTo);
        GET_FUNC(PolyDraw);
        GET_FUNC(PolyPolygon);
        GET_FUNC(PolyPolyline);
        GET_FUNC(Polygon);
        GET_FUNC(Polyline);
        GET_FUNC(PolylineTo);
        GET_FUNC(RealizeDefaultPalette);
        GET_FUNC(RealizePalette);
        GET_FUNC(Rectangle);
        GET_FUNC(ResetDC);
        GET_FUNC(RestoreDC);
        GET_FUNC(RoundRect);
        GET_FUNC(SaveDC);
        GET_FUNC(ScaleViewportExtEx);
        GET_FUNC(ScaleWindowExtEx);
        GET_FUNC(SelectBitmap);
        GET_FUNC(SelectBrush);
        GET_FUNC(SelectClipPath);
        GET_FUNC(SelectFont);
        GET_FUNC(SelectPalette);
        GET_FUNC(SelectPen);
        GET_FUNC(SetArcDirection);
        GET_FUNC(SetBitmapBits);
        GET_FUNC(SetBkColor);
        GET_FUNC(SetBkMode);
        GET_FUNC(SetDCBrushColor);
        GET_FUNC(SetDCPenColor);
        GET_FUNC(SetDIBColorTable);
        GET_FUNC(SetDIBits);
        GET_FUNC(SetDIBitsToDevice);
        GET_FUNC(SetDeviceClipping);
        GET_FUNC(SetDeviceGammaRamp);
        GET_FUNC(SetLayout);
        GET_FUNC(SetMapMode);
        GET_FUNC(SetMapperFlags);
        GET_FUNC(SetPixel);
        GET_FUNC(SetPixelFormat);
        GET_FUNC(SetPolyFillMode);
        GET_FUNC(SetROP2);
        GET_FUNC(SetRelAbs);
        GET_FUNC(SetStretchBltMode);
        GET_FUNC(SetTextAlign);
        GET_FUNC(SetTextCharacterExtra);
        GET_FUNC(SetTextColor);
        GET_FUNC(SetTextJustification);
        GET_FUNC(SetViewportExtEx);
        GET_FUNC(SetViewportOrgEx);
        GET_FUNC(SetWindowExtEx);
        GET_FUNC(SetWindowOrgEx);
        GET_FUNC(SetWorldTransform);
        GET_FUNC(StartDoc);
        GET_FUNC(StartPage);
        GET_FUNC(StretchBlt);
        GET_FUNC(StretchDIBits);
        GET_FUNC(StrokeAndFillPath);
        GET_FUNC(StrokePath);
        GET_FUNC(SwapBuffers);
        GET_FUNC(UnrealizePalette);
        GET_FUNC(WidenPath);

        /* OpenGL32 */
        GET_FUNC(wglCreateContext);
        GET_FUNC(wglCreateContextAttribsARB);
        GET_FUNC(wglDeleteContext);
        GET_FUNC(wglGetProcAddress);
        GET_FUNC(wglGetPbufferDCARB);
        GET_FUNC(wglMakeContextCurrentARB);
        GET_FUNC(wglMakeCurrent);
        GET_FUNC(wglSetPixelFormatWINE);
        GET_FUNC(wglShareLists);
        GET_FUNC(wglUseFontBitmapsA);
        GET_FUNC(wglUseFontBitmapsW);
#undef GET_FUNC
    }
    else memset( &driver->funcs, 0, sizeof(driver->funcs) );

    return driver;
}


/**********************************************************************
 *	     DRIVER_get_display_driver
 *
 * Special case for loading the display driver: get the name from the config file
 */
const DC_FUNCTIONS *DRIVER_get_display_driver(void)
{
    struct graphics_driver *driver;
    char buffer[MAX_PATH], libname[32], *name, *next;
    HMODULE module = 0;
    HKEY hkey;

    if (display_driver) return &display_driver->funcs;  /* already loaded */

    strcpy( buffer, "x11" );  /* default value */
    /* @@ Wine registry key: HKCU\Software\Wine\Drivers */
    if (!RegOpenKeyA( HKEY_CURRENT_USER, "Software\\Wine\\Drivers", &hkey ))
    {
        DWORD type, count = sizeof(buffer);
        RegQueryValueExA( hkey, "Graphics", 0, &type, (LPBYTE) buffer, &count );
        RegCloseKey( hkey );
    }

    name = buffer;
    while (name)
    {
        next = strchr( name, ',' );
        if (next) *next++ = 0;

        snprintf( libname, sizeof(libname), "wine%s.drv", name );
        if ((module = LoadLibraryA( libname )) != 0) break;
        name = next;
    }

    if (!(driver = create_driver( module )))
    {
        MESSAGE( "Could not create graphics driver '%s'\n", buffer );
        FreeLibrary( module );
        ExitProcess(1);
    }
    if (InterlockedCompareExchangePointer( (void **)&display_driver, driver, NULL ))
    {
        /* somebody beat us to it */
        FreeLibrary( driver->module );
        HeapFree( GetProcessHeap(), 0, driver );
    }
    return &display_driver->funcs;
}


/**********************************************************************
 *	     DRIVER_load_driver
 */
const DC_FUNCTIONS *DRIVER_load_driver( LPCWSTR name )
{
    HMODULE module;
    struct graphics_driver *driver, *new_driver;
    static const WCHAR displayW[] = { 'd','i','s','p','l','a','y',0 };
    static const WCHAR display1W[] = {'\\','\\','.','\\','D','I','S','P','L','A','Y','1',0};

    /* display driver is a special case */
    if (!strcmpiW( name, displayW ) || !strcmpiW( name, display1W )) return DRIVER_get_display_driver();

    if ((module = GetModuleHandleW( name )))
    {
        if (display_driver && display_driver->module == module) return &display_driver->funcs;
        EnterCriticalSection( &driver_section );
        LIST_FOR_EACH_ENTRY( driver, &drivers, struct graphics_driver, entry )
        {
            if (driver->module == module) goto done;
        }
        LeaveCriticalSection( &driver_section );
    }

    if (!(module = LoadLibraryW( name ))) return NULL;

    if (!(new_driver = create_driver( module )))
    {
        FreeLibrary( module );
        return NULL;
    }

    /* check if someone else added it in the meantime */
    EnterCriticalSection( &driver_section );
    LIST_FOR_EACH_ENTRY( driver, &drivers, struct graphics_driver, entry )
    {
        if (driver->module != module) continue;
        FreeLibrary( module );
        HeapFree( GetProcessHeap(), 0, new_driver );
        goto done;
    }
    driver = new_driver;
    list_add_head( &drivers, &driver->entry );
    TRACE( "loaded driver %p for %s\n", driver, debugstr_w(name) );
done:
    LeaveCriticalSection( &driver_section );
    return &driver->funcs;
}


static INT CDECL nulldrv_AbortDoc( PHYSDEV dev )
{
    return 0;
}

static BOOL CDECL nulldrv_AlphaBlend( PHYSDEV dst_dev, INT x_dst, INT y_dst, INT width_dst, INT height_dst,
                                      PHYSDEV src_dev, INT x_src, INT y_src, INT width_src, INT height_src,
                                      BLENDFUNCTION func)
{
    return TRUE;
}

static BOOL CDECL nulldrv_Arc( PHYSDEV dev, INT left, INT top, INT right, INT bottom,
                               INT xstart, INT ystart, INT xend, INT yend )
{
    return TRUE;
}

static INT CDECL nulldrv_ChoosePixelFormat( PHYSDEV dev, const PIXELFORMATDESCRIPTOR *descr )
{
    return 0;
}

static BOOL CDECL nulldrv_Chord( PHYSDEV dev, INT left, INT top, INT right, INT bottom,
                                 INT xstart, INT ystart, INT xend, INT yend )
{
    return TRUE;
}

static BOOL CDECL nulldrv_CreateBitmap( PHYSDEV dev, HBITMAP bitmap, LPVOID bits )
{
    return TRUE;
}

static BOOL CDECL nulldrv_CreateDC( HDC hdc, PHYSDEV *dev, LPCWSTR driver, LPCWSTR device,
                                    LPCWSTR output, const DEVMODEW *devmode )
{
    assert(0);  /* should never be called */
    return FALSE;
}

static HBITMAP CDECL nulldrv_CreateDIBSection( PHYSDEV dev, HBITMAP bitmap,
                                               const BITMAPINFO *info, UINT usage )
{
    return bitmap;
}

static BOOL CDECL nulldrv_DeleteBitmap( HBITMAP bitmap )
{
    return TRUE;
}

static BOOL CDECL nulldrv_DeleteDC( PHYSDEV dev )
{
    assert(0);  /* should never be called */
    return TRUE;
}

static BOOL CDECL nulldrv_DeleteObject( PHYSDEV dev, HGDIOBJ obj )
{
    return TRUE;
}

static INT CDECL nulldrv_DescribePixelFormat( PHYSDEV dev, INT format,
                                              UINT size, PIXELFORMATDESCRIPTOR * descr )
{
    return 0;
}

static DWORD CDECL nulldrv_DeviceCapabilities( LPSTR buffer, LPCSTR device, LPCSTR port,
                                               WORD cap, LPSTR output, DEVMODEA *devmode )
{
    return -1;
}

static BOOL CDECL nulldrv_Ellipse( PHYSDEV dev, INT left, INT top, INT right, INT bottom )
{
    return TRUE;
}

static INT CDECL nulldrv_EndDoc( PHYSDEV dev )
{
    return 0;
}

static INT CDECL nulldrv_EndPage( PHYSDEV dev )
{
    return 0;
}

static BOOL CDECL nulldrv_EnumDeviceFonts( PHYSDEV dev, LOGFONTW *logfont,
                                           FONTENUMPROCW proc, LPARAM lParam )
{
    return FALSE;
}

static INT CDECL nulldrv_EnumICMProfiles( PHYSDEV dev, ICMENUMPROCW func, LPARAM lparam )
{
    return -1;
}

static INT CDECL nulldrv_ExtDeviceMode( LPSTR buffer, HWND hwnd, DEVMODEA *output, LPSTR device,
                                        LPSTR port, DEVMODEA *input, LPSTR profile, DWORD mode )
{
    return -1;
}

static INT CDECL nulldrv_ExtEscape( PHYSDEV dev, INT escape, INT in_size, const void *in_data,
                                    INT out_size, void *out_data )
{
    return 0;
}

static BOOL CDECL nulldrv_ExtFloodFill( PHYSDEV dev, INT x, INT y, COLORREF color, UINT type )
{
    return TRUE;
}

static BOOL CDECL nulldrv_ExtTextOut( PHYSDEV dev, INT x, INT y, UINT flags, const RECT *rect,
                                      LPCWSTR str, UINT count, const INT *dx )
{
    return TRUE;
}

static BOOL CDECL nulldrv_GdiComment( PHYSDEV dev, UINT size, const BYTE *data )
{
    return FALSE;
}

static BOOL CDECL nulldrv_GetCharWidth( PHYSDEV dev, UINT first, UINT last, INT *buffer )
{
    return FALSE;
}

static INT CDECL nulldrv_GetDeviceCaps( PHYSDEV dev, INT cap )
{
    switch (cap)  /* return meaningful values for some entries */
    {
    case HORZRES:     return 640;
    case VERTRES:     return 480;
    case BITSPIXEL:   return 1;
    case PLANES:      return 1;
    case NUMCOLORS:   return 2;
    case ASPECTX:     return 36;
    case ASPECTY:     return 36;
    case ASPECTXY:    return 51;
    case LOGPIXELSX:  return 72;
    case LOGPIXELSY:  return 72;
    case SIZEPALETTE: return 2;
    case TEXTCAPS:    return (TC_OP_CHARACTER | TC_OP_STROKE | TC_CP_STROKE |
                              TC_CR_ANY | TC_SF_X_YINDEP | TC_SA_DOUBLE | TC_SA_INTEGER |
                              TC_SA_CONTIN | TC_UA_ABLE | TC_SO_ABLE | TC_RA_ABLE | TC_VA_ABLE);
    default:          return 0;
    }
}

static BOOL CDECL nulldrv_GetDeviceGammaRamp( PHYSDEV dev, void *ramp )
{
    return FALSE;
}

static BOOL CDECL nulldrv_GetICMProfile( PHYSDEV dev, LPDWORD size, LPWSTR filename )
{
    return FALSE;
}

static COLORREF CDECL nulldrv_GetPixel( PHYSDEV dev, INT x, INT y )
{
    return 0;
}

static INT CDECL nulldrv_GetPixelFormat( PHYSDEV dev )
{
    return 0;
}

static UINT CDECL nulldrv_GetSystemPaletteEntries( PHYSDEV dev, UINT start,
                                                   UINT count, PALETTEENTRY *entries )
{
    return 0;
}

static BOOL CDECL nulldrv_GetTextExtentExPoint( PHYSDEV dev, LPCWSTR str, INT count, INT max_ext,
                                                INT *fit, INT *dx, SIZE *size )
{
    return FALSE;
}

static BOOL CDECL nulldrv_GetTextMetrics( PHYSDEV dev, TEXTMETRICW *metrics )
{
    return FALSE;
}

static BOOL CDECL nulldrv_LineTo( PHYSDEV dev, INT x, INT y )
{
    return TRUE;
}

static BOOL CDECL nulldrv_MoveTo( PHYSDEV dev, INT x, INT y )
{
    return TRUE;
}

static BOOL CDECL nulldrv_PaintRgn( PHYSDEV dev, HRGN rgn )
{
    return TRUE;
}

static BOOL CDECL nulldrv_PatBlt( PHYSDEV dev, INT x, INT y, INT width, INT height, DWORD rop )
{
    return TRUE;
}

static BOOL CDECL nulldrv_Pie( PHYSDEV dev, INT left, INT top, INT right, INT bottom,
                               INT xstart, INT ystart, INT xend, INT yend )
{
    return TRUE;
}

static BOOL CDECL nulldrv_PolyPolygon( PHYSDEV dev, const POINT *points, const INT *counts, UINT polygons )
{
    /* FIXME: could be implemented with Polygon */
    return TRUE;
}

static BOOL CDECL nulldrv_PolyPolyline( PHYSDEV dev, const POINT *points, const DWORD *counts, DWORD lines )
{
    /* FIXME: could be implemented with Polyline */
    return TRUE;
}

static BOOL CDECL nulldrv_Polygon( PHYSDEV dev, const POINT *points, INT count )
{
    return TRUE;
}

static BOOL CDECL nulldrv_Polyline( PHYSDEV dev, const POINT *points, INT count )
{
    return TRUE;
}

static UINT CDECL nulldrv_RealizeDefaultPalette( PHYSDEV dev )
{
    return 0;
}

static UINT CDECL nulldrv_RealizePalette( PHYSDEV dev, HPALETTE palette, BOOL primary )
{
    return 0;
}

static BOOL CDECL nulldrv_Rectangle( PHYSDEV dev, INT left, INT top, INT right, INT bottom )
{
    return TRUE;
}

static HDC CDECL nulldrv_ResetDC( PHYSDEV dev, const DEVMODEW *devmode )
{
    return 0;
}

static BOOL CDECL nulldrv_RoundRect( PHYSDEV dev, INT left, INT top, INT right, INT bottom,
                                     INT ell_width, INT ell_height )
{
    return TRUE;
}

static HBITMAP CDECL nulldrv_SelectBitmap( PHYSDEV dev, HBITMAP bitmap )
{
    return bitmap;
}

static HBRUSH CDECL nulldrv_SelectBrush( PHYSDEV dev, HBRUSH brush )
{
    return brush;
}

static HFONT CDECL nulldrv_SelectFont( PHYSDEV dev, HFONT font, HANDLE gdi_font )
{
    return 0;
}

static HPALETTE CDECL nulldrv_SelectPalette( PHYSDEV dev, HPALETTE palette, BOOL bkgnd )
{
    return palette;
}

static HPEN CDECL nulldrv_SelectPen( PHYSDEV dev, HPEN pen )
{
    return pen;
}

static INT CDECL nulldrv_SetArcDirection( PHYSDEV dev, INT dir )
{
    return dir;
}

static COLORREF CDECL nulldrv_SetBkColor( PHYSDEV dev, COLORREF color )
{
    return color;
}

static INT CDECL nulldrv_SetBkMode( PHYSDEV dev, INT mode )
{
    return mode;
}

static COLORREF CDECL nulldrv_SetDCBrushColor( PHYSDEV dev, COLORREF color )
{
    return color;
}

static COLORREF CDECL nulldrv_SetDCPenColor( PHYSDEV dev, COLORREF color )
{
    return color;
}

static UINT CDECL nulldrv_SetDIBColorTable( PHYSDEV dev, UINT pos, UINT count, const RGBQUAD *colors )
{
    return 0;
}

static INT CDECL nulldrv_SetDIBitsToDevice( PHYSDEV dev, INT x_dst, INT y_dst, DWORD width, DWORD height,
                                            INT x_src, INT y_src, UINT start, UINT lines,
                                            const void *bits, const BITMAPINFO *info, UINT coloruse )
{
    return 0;
}

static void CDECL nulldrv_SetDeviceClipping( PHYSDEV dev, HRGN vis_rgn, HRGN clip_rgn )
{
}

static DWORD CDECL nulldrv_SetLayout( PHYSDEV dev, DWORD layout )
{
    return layout;
}

static BOOL CDECL nulldrv_SetDeviceGammaRamp( PHYSDEV dev, void *ramp )
{
    return FALSE;
}

static DWORD CDECL nulldrv_SetMapperFlags( PHYSDEV dev, DWORD flags )
{
    return flags;
}

static COLORREF CDECL nulldrv_SetPixel( PHYSDEV dev, INT x, INT y, COLORREF color )
{
    return color;
}

static BOOL CDECL nulldrv_SetPixelFormat( PHYSDEV dev, INT format, const PIXELFORMATDESCRIPTOR *descr )
{
    return FALSE;
}

static INT CDECL nulldrv_SetPolyFillMode( PHYSDEV dev, INT mode )
{
    return mode;
}

static INT CDECL nulldrv_SetROP2( PHYSDEV dev, INT rop )
{
    return rop;
}

static INT CDECL nulldrv_SetRelAbs( PHYSDEV dev, INT mode )
{
    return mode;
}

static INT CDECL nulldrv_SetStretchBltMode( PHYSDEV dev, INT mode )
{
    return mode;
}

static UINT CDECL nulldrv_SetTextAlign( PHYSDEV dev, UINT align )
{
    return align;
}

static INT CDECL nulldrv_SetTextCharacterExtra( PHYSDEV dev, INT extra )
{
    return extra;
}

static COLORREF CDECL nulldrv_SetTextColor( PHYSDEV dev, COLORREF color )
{
    return color;
}

static BOOL CDECL nulldrv_SetTextJustification( PHYSDEV dev, INT extra, INT breaks )
{
    return TRUE;
}

static INT CDECL nulldrv_StartDoc( PHYSDEV dev, const DOCINFOW *info )
{
    return 0;
}

static INT CDECL nulldrv_StartPage( PHYSDEV dev )
{
    return 1;
}

static BOOL CDECL nulldrv_SwapBuffers( PHYSDEV dev )
{
    return TRUE;
}

static BOOL CDECL nulldrv_UnrealizePalette( HPALETTE palette )
{
    return FALSE;
}

static BOOL CDECL nulldrv_wglCopyContext( HGLRC ctx_src, HGLRC ctx_dst, UINT mask )
{
    return FALSE;
}

static HGLRC CDECL nulldrv_wglCreateContext( PHYSDEV dev )
{
    return 0;
}

static HGLRC CDECL nulldrv_wglCreateContextAttribsARB( PHYSDEV dev, HGLRC share_ctx, const int *attribs )
{
    return 0;
}

static BOOL CDECL nulldrv_wglDeleteContext( HGLRC ctx )
{
    return FALSE;
}

static PROC CDECL nulldrv_wglGetProcAddress( LPCSTR name )
{
    return NULL;
}

static HDC CDECL nulldrv_wglGetPbufferDCARB( PHYSDEV dev, void *pbuffer )
{
    return 0;
}

static BOOL CDECL nulldrv_wglMakeCurrent( PHYSDEV dev, HGLRC ctx )
{
    return FALSE;
}

static BOOL CDECL nulldrv_wglMakeContextCurrentARB( PHYSDEV dev_draw, PHYSDEV dev_read, HGLRC ctx )
{
    return FALSE;
}

static BOOL CDECL nulldrv_wglSetPixelFormatWINE( PHYSDEV dev, INT format,
                                                 const PIXELFORMATDESCRIPTOR *descr )
{
    return FALSE;
}

static BOOL CDECL nulldrv_wglShareLists( HGLRC ctx1, HGLRC ctx2 )
{
    return FALSE;
}

static BOOL CDECL nulldrv_wglUseFontBitmapsA( PHYSDEV dev, DWORD start, DWORD count, DWORD base )
{
    return FALSE;
}

static BOOL CDECL nulldrv_wglUseFontBitmapsW( PHYSDEV dev, DWORD start, DWORD count, DWORD base )
{
    return FALSE;
}

const DC_FUNCTIONS null_driver =
{
    nulldrv_AbortDoc,                   /* pAbortDoc */
    nulldrv_AbortPath,                  /* pAbortPath */
    nulldrv_AlphaBlend,                 /* pAlphaBlend */
    nulldrv_AngleArc,                   /* pAngleArc */
    nulldrv_Arc,                        /* pArc */
    nulldrv_ArcTo,                      /* pArcTo */
    nulldrv_BeginPath,                  /* pBeginPath */
    nulldrv_ChoosePixelFormat,          /* pChoosePixelFormat */
    nulldrv_Chord,                      /* pChord */
    nulldrv_CloseFigure,                /* pCloseFigure */
    nulldrv_CreateBitmap,               /* pCreateBitmap */
    nulldrv_CreateDC,                   /* pCreateDC */
    nulldrv_CreateDIBSection,           /* pCreateDIBSection */
    nulldrv_DeleteBitmap,               /* pDeleteBitmap */
    nulldrv_DeleteDC,                   /* pDeleteDC */
    nulldrv_DeleteObject,               /* pDeleteObject */
    nulldrv_DescribePixelFormat,        /* pDescribePixelFormat */
    nulldrv_DeviceCapabilities,         /* pDeviceCapabilities */
    nulldrv_Ellipse,                    /* pEllipse */
    nulldrv_EndDoc,                     /* pEndDoc */
    nulldrv_EndPage,                    /* pEndPage */
    nulldrv_EndPath,                    /* pEndPath */
    nulldrv_EnumDeviceFonts,            /* pEnumDeviceFonts */
    nulldrv_EnumICMProfiles,            /* pEnumICMProfiles */
    nulldrv_ExcludeClipRect,            /* pExcludeClipRect */
    nulldrv_ExtDeviceMode,              /* pExtDeviceMode */
    nulldrv_ExtEscape,                  /* pExtEscape */
    nulldrv_ExtFloodFill,               /* pExtFloodFill */
    nulldrv_ExtSelectClipRgn,           /* pExtSelectClipRgn */
    nulldrv_ExtTextOut,                 /* pExtTextOut */
    nulldrv_FillPath,                   /* pFillPath */
    nulldrv_FillRgn,                    /* pFillRgn */
    nulldrv_FlattenPath,                /* pFlattenPath */
    nulldrv_FrameRgn,                   /* pFrameRgn */
    nulldrv_GdiComment,                 /* pGdiComment */
    nulldrv_GetBitmapBits,              /* pGetBitmapBits */
    nulldrv_GetCharWidth,               /* pGetCharWidth */
    nulldrv_GetDIBits,                  /* pGetDIBits */
    nulldrv_GetDeviceCaps,              /* pGetDeviceCaps */
    nulldrv_GetDeviceGammaRamp,         /* pGetDeviceGammaRamp */
    nulldrv_GetICMProfile,              /* pGetICMProfile */
    nulldrv_GetNearestColor,            /* pGetNearestColor */
    nulldrv_GetPixel,                   /* pGetPixel */
    nulldrv_GetPixelFormat,             /* pGetPixelFormat */
    nulldrv_GetSystemPaletteEntries,    /* pGetSystemPaletteEntries */
    nulldrv_GetTextExtentExPoint,       /* pGetTextExtentExPoint */
    nulldrv_GetTextMetrics,             /* pGetTextMetrics */
    nulldrv_IntersectClipRect,          /* pIntersectClipRect */
    nulldrv_InvertRgn,                  /* pInvertRgn */
    nulldrv_LineTo,                     /* pLineTo */
    nulldrv_ModifyWorldTransform,       /* pModifyWorldTransform */
    nulldrv_MoveTo,                     /* pMoveTo */
    nulldrv_OffsetClipRgn,              /* pOffsetClipRgn */
    nulldrv_OffsetViewportOrgEx,        /* pOffsetViewportOrg */
    nulldrv_OffsetWindowOrgEx,          /* pOffsetWindowOrg */
    nulldrv_PaintRgn,                   /* pPaintRgn */
    nulldrv_PatBlt,                     /* pPatBlt */
    nulldrv_Pie,                        /* pPie */
    nulldrv_PolyBezier,                 /* pPolyBezier */
    nulldrv_PolyBezierTo,               /* pPolyBezierTo */
    nulldrv_PolyDraw,                   /* pPolyDraw */
    nulldrv_PolyPolygon,                /* pPolyPolygon */
    nulldrv_PolyPolyline,               /* pPolyPolyline */
    nulldrv_Polygon,                    /* pPolygon */
    nulldrv_Polyline,                   /* pPolyline */
    nulldrv_PolylineTo,                 /* pPolylineTo */
    nulldrv_RealizeDefaultPalette,      /* pRealizeDefaultPalette */
    nulldrv_RealizePalette,             /* pRealizePalette */
    nulldrv_Rectangle,                  /* pRectangle */
    nulldrv_ResetDC,                    /* pResetDC */
    nulldrv_RestoreDC,                  /* pRestoreDC */
    nulldrv_RoundRect,                  /* pRoundRect */
    nulldrv_SaveDC,                     /* pSaveDC */
    nulldrv_ScaleViewportExtEx,         /* pScaleViewportExt */
    nulldrv_ScaleWindowExtEx,           /* pScaleWindowExt */
    nulldrv_SelectBitmap,               /* pSelectBitmap */
    nulldrv_SelectBrush,                /* pSelectBrush */
    nulldrv_SelectClipPath,             /* pSelectClipPath */
    nulldrv_SelectFont,                 /* pSelectFont */
    nulldrv_SelectPalette,              /* pSelectPalette */
    nulldrv_SelectPen,                  /* pSelectPen */
    nulldrv_SetArcDirection,            /* pSetArcDirection */
    nulldrv_SetBitmapBits,              /* pSetBitmapBits */
    nulldrv_SetBkColor,                 /* pSetBkColor */
    nulldrv_SetBkMode,                  /* pSetBkMode */
    nulldrv_SetDCBrushColor,            /* pSetDCBrushColor */
    nulldrv_SetDCPenColor,              /* pSetDCPenColor */
    nulldrv_SetDIBColorTable,           /* pSetDIBColorTable */
    nulldrv_SetDIBits,                  /* pSetDIBits */
    nulldrv_SetDIBitsToDevice,          /* pSetDIBitsToDevice */
    nulldrv_SetDeviceClipping,          /* pSetDeviceClipping */
    nulldrv_SetDeviceGammaRamp,         /* pSetDeviceGammaRamp */
    nulldrv_SetLayout,                  /* pSetLayout */
    nulldrv_SetMapMode,                 /* pSetMapMode */
    nulldrv_SetMapperFlags,             /* pSetMapperFlags */
    nulldrv_SetPixel,                   /* pSetPixel */
    nulldrv_SetPixelFormat,             /* pSetPixelFormat */
    nulldrv_SetPolyFillMode,            /* pSetPolyFillMode */
    nulldrv_SetROP2,                    /* pSetROP2 */
    nulldrv_SetRelAbs,                  /* pSetRelAbs */
    nulldrv_SetStretchBltMode,          /* pSetStretchBltMode */
    nulldrv_SetTextAlign,               /* pSetTextAlign */
    nulldrv_SetTextCharacterExtra,      /* pSetTextCharacterExtra */
    nulldrv_SetTextColor,               /* pSetTextColor */
    nulldrv_SetTextJustification,       /* pSetTextJustification */
    nulldrv_SetViewportExtEx,           /* pSetViewportExt */
    nulldrv_SetViewportOrgEx,           /* pSetViewportOrg */
    nulldrv_SetWindowExtEx,             /* pSetWindowExt */
    nulldrv_SetWindowOrgEx,             /* pSetWindowOrg */
    nulldrv_SetWorldTransform,          /* pSetWorldTransform */
    nulldrv_StartDoc,                   /* pStartDoc */
    nulldrv_StartPage,                  /* pStartPage */
    nulldrv_StretchBlt,                 /* pStretchBlt */
    nulldrv_StretchDIBits,              /* pStretchDIBits */
    nulldrv_StrokeAndFillPath,          /* pStrokeAndFillPath */
    nulldrv_StrokePath,                 /* pStrokePath */
    nulldrv_SwapBuffers,                /* pSwapBuffers */
    nulldrv_UnrealizePalette,           /* pUnrealizePalette */
    nulldrv_WidenPath,                  /* pWidenPath */
    nulldrv_wglCopyContext,             /* pwglCopyContext */
    nulldrv_wglCreateContext,           /* pwglCreateContext */
    nulldrv_wglCreateContextAttribsARB, /* pwglCreateContextAttribsARB */
    nulldrv_wglDeleteContext,           /* pwglDeleteContext */
    nulldrv_wglGetProcAddress,          /* pwglGetProcAddress */
    nulldrv_wglGetPbufferDCARB,         /* pwglGetPbufferDCARB */
    nulldrv_wglMakeCurrent,             /* pwglMakeCurrent */
    nulldrv_wglMakeContextCurrentARB,   /* pwglMakeContextCurrentARB */
    nulldrv_wglSetPixelFormatWINE,      /* pwglSetPixelFormatWINE */
    nulldrv_wglShareLists,              /* pwglShareLists */
    nulldrv_wglUseFontBitmapsA,         /* pwglUseFontBitmapsA */
    nulldrv_wglUseFontBitmapsW,         /* pwglUseFontBitmapsW */
};


/*****************************************************************************
 *      DRIVER_GetDriverName
 *
 */
BOOL DRIVER_GetDriverName( LPCWSTR device, LPWSTR driver, DWORD size )
{
    static const WCHAR displayW[] = { 'd','i','s','p','l','a','y',0 };
    static const WCHAR devicesW[] = { 'd','e','v','i','c','e','s',0 };
    static const WCHAR display1W[] = {'\\','\\','.','\\','D','I','S','P','L','A','Y','1',0};
    static const WCHAR empty_strW[] = { 0 };
    WCHAR *p;

    /* display is a special case */
    if (!strcmpiW( device, displayW ) ||
        !strcmpiW( device, display1W ))
    {
        lstrcpynW( driver, displayW, size );
        return TRUE;
    }

    size = GetProfileStringW(devicesW, device, empty_strW, driver, size);
    if(!size) {
        WARN("Unable to find %s in [devices] section of win.ini\n", debugstr_w(device));
        return FALSE;
    }
    p = strchrW(driver, ',');
    if(!p)
    {
        WARN("%s entry in [devices] section of win.ini is malformed.\n", debugstr_w(device));
        return FALSE;
    }
    *p = 0;
    TRACE("Found %s for %s\n", debugstr_w(driver), debugstr_w(device));
    return TRUE;
}


/***********************************************************************
 *           GdiConvertToDevmodeW    (GDI32.@)
 */
DEVMODEW * WINAPI GdiConvertToDevmodeW(const DEVMODEA *dmA)
{
    DEVMODEW *dmW;
    WORD dmW_size, dmA_size;

    dmA_size = dmA->dmSize;

    /* this is the minimal dmSize that XP accepts */
    if (dmA_size < FIELD_OFFSET(DEVMODEA, dmFields))
        return NULL;

    if (dmA_size > sizeof(DEVMODEA))
        dmA_size = sizeof(DEVMODEA);

    dmW_size = dmA_size + CCHDEVICENAME;
    if (dmA_size >= FIELD_OFFSET(DEVMODEA, dmFormName) + CCHFORMNAME)
        dmW_size += CCHFORMNAME;

    dmW = HeapAlloc(GetProcessHeap(), 0, dmW_size + dmA->dmDriverExtra);
    if (!dmW) return NULL;

    MultiByteToWideChar(CP_ACP, 0, (const char*) dmA->dmDeviceName, -1,
                                   dmW->dmDeviceName, CCHDEVICENAME);
    /* copy slightly more, to avoid long computations */
    memcpy(&dmW->dmSpecVersion, &dmA->dmSpecVersion, dmA_size - CCHDEVICENAME);

    if (dmA_size >= FIELD_OFFSET(DEVMODEA, dmFormName) + CCHFORMNAME)
    {
        if (dmA->dmFields & DM_FORMNAME)
            MultiByteToWideChar(CP_ACP, 0, (const char*) dmA->dmFormName, -1,
                                       dmW->dmFormName, CCHFORMNAME);
        else
            dmW->dmFormName[0] = 0;

        if (dmA_size > FIELD_OFFSET(DEVMODEA, dmLogPixels))
            memcpy(&dmW->dmLogPixels, &dmA->dmLogPixels, dmA_size - FIELD_OFFSET(DEVMODEA, dmLogPixels));
    }

    if (dmA->dmDriverExtra)
        memcpy((char *)dmW + dmW_size, (const char *)dmA + dmA_size, dmA->dmDriverExtra);

    dmW->dmSize = dmW_size;

    return dmW;
}


/*****************************************************************************
 *      @ [GDI32.100]
 *
 * This should thunk to 16-bit and simply call the proc with the given args.
 */
INT WINAPI GDI_CallDevInstall16( FARPROC16 lpfnDevInstallProc, HWND hWnd,
                                 LPSTR lpModelName, LPSTR OldPort, LPSTR NewPort )
{
    FIXME("(%p, %p, %s, %s, %s)\n", lpfnDevInstallProc, hWnd, lpModelName, OldPort, NewPort );
    return -1;
}

/*****************************************************************************
 *      @ [GDI32.101]
 *
 * This should load the correct driver for lpszDevice and calls this driver's
 * ExtDeviceModePropSheet proc.
 *
 * Note: The driver calls a callback routine for each property sheet page; these
 * pages are supposed to be filled into the structure pointed to by lpPropSheet.
 * The layout of this structure is:
 *
 * struct
 * {
 *   DWORD  nPages;
 *   DWORD  unknown;
 *   HPROPSHEETPAGE  pages[10];
 * };
 */
INT WINAPI GDI_CallExtDeviceModePropSheet16( HWND hWnd, LPCSTR lpszDevice,
                                             LPCSTR lpszPort, LPVOID lpPropSheet )
{
    FIXME("(%p, %s, %s, %p)\n", hWnd, lpszDevice, lpszPort, lpPropSheet );
    return -1;
}

/*****************************************************************************
 *      @ [GDI32.102]
 *
 * This should load the correct driver for lpszDevice and call this driver's
 * ExtDeviceMode proc.
 *
 * FIXME: convert ExtDeviceMode to unicode in the driver interface
 */
INT WINAPI GDI_CallExtDeviceMode16( HWND hwnd,
                                    LPDEVMODEA lpdmOutput, LPSTR lpszDevice,
                                    LPSTR lpszPort, LPDEVMODEA lpdmInput,
                                    LPSTR lpszProfile, DWORD fwMode )
{
    WCHAR deviceW[300];
    WCHAR bufW[300];
    char buf[300];
    HDC hdc;
    DC *dc;
    INT ret = -1;

    TRACE("(%p, %p, %s, %s, %p, %s, %d)\n",
          hwnd, lpdmOutput, lpszDevice, lpszPort, lpdmInput, lpszProfile, fwMode );

    if (!lpszDevice) return -1;
    if (!MultiByteToWideChar(CP_ACP, 0, lpszDevice, -1, deviceW, 300)) return -1;

    if(!DRIVER_GetDriverName( deviceW, bufW, 300 )) return -1;

    if (!WideCharToMultiByte(CP_ACP, 0, bufW, -1, buf, 300, NULL, NULL)) return -1;

    if (!(hdc = CreateICA( buf, lpszDevice, lpszPort, NULL ))) return -1;

    if ((dc = get_dc_ptr( hdc )))
    {
        PHYSDEV physdev = GET_DC_PHYSDEV( dc, pExtDeviceMode );
        ret = physdev->funcs->pExtDeviceMode( buf, hwnd, lpdmOutput, lpszDevice, lpszPort,
                                              lpdmInput, lpszProfile, fwMode );
	release_dc_ptr( dc );
    }
    DeleteDC( hdc );
    return ret;
}

/****************************************************************************
 *      @ [GDI32.103]
 *
 * This should load the correct driver for lpszDevice and calls this driver's
 * AdvancedSetupDialog proc.
 */
INT WINAPI GDI_CallAdvancedSetupDialog16( HWND hwnd, LPSTR lpszDevice,
                                          LPDEVMODEA devin, LPDEVMODEA devout )
{
    TRACE("(%p, %s, %p, %p)\n", hwnd, lpszDevice, devin, devout );
    return -1;
}

/*****************************************************************************
 *      @ [GDI32.104]
 *
 * This should load the correct driver for lpszDevice and calls this driver's
 * DeviceCapabilities proc.
 *
 * FIXME: convert DeviceCapabilities to unicode in the driver interface
 */
DWORD WINAPI GDI_CallDeviceCapabilities16( LPCSTR lpszDevice, LPCSTR lpszPort,
                                           WORD fwCapability, LPSTR lpszOutput,
                                           LPDEVMODEA lpdm )
{
    WCHAR deviceW[300];
    WCHAR bufW[300];
    char buf[300];
    HDC hdc;
    DC *dc;
    INT ret = -1;

    TRACE("(%s, %s, %d, %p, %p)\n", lpszDevice, lpszPort, fwCapability, lpszOutput, lpdm );

    if (!lpszDevice) return -1;
    if (!MultiByteToWideChar(CP_ACP, 0, lpszDevice, -1, deviceW, 300)) return -1;

    if(!DRIVER_GetDriverName( deviceW, bufW, 300 )) return -1;

    if (!WideCharToMultiByte(CP_ACP, 0, bufW, -1, buf, 300, NULL, NULL)) return -1;

    if (!(hdc = CreateICA( buf, lpszDevice, lpszPort, NULL ))) return -1;

    if ((dc = get_dc_ptr( hdc )))
    {
        PHYSDEV physdev = GET_DC_PHYSDEV( dc, pDeviceCapabilities );
        ret = physdev->funcs->pDeviceCapabilities( buf, lpszDevice, lpszPort,
                                                   fwCapability, lpszOutput, lpdm );
        release_dc_ptr( dc );
    }
    DeleteDC( hdc );
    return ret;
}


/************************************************************************
 *             Escape  [GDI32.@]
 */
INT WINAPI Escape( HDC hdc, INT escape, INT in_count, LPCSTR in_data, LPVOID out_data )
{
    INT ret;
    POINT *pt;

    switch (escape)
    {
    case ABORTDOC:
        return AbortDoc( hdc );

    case ENDDOC:
        return EndDoc( hdc );

    case GETPHYSPAGESIZE:
        pt = out_data;
        pt->x = GetDeviceCaps( hdc, PHYSICALWIDTH );
        pt->y = GetDeviceCaps( hdc, PHYSICALHEIGHT );
        return 1;

    case GETPRINTINGOFFSET:
        pt = out_data;
        pt->x = GetDeviceCaps( hdc, PHYSICALOFFSETX );
        pt->y = GetDeviceCaps( hdc, PHYSICALOFFSETY );
        return 1;

    case GETSCALINGFACTOR:
        pt = out_data;
        pt->x = GetDeviceCaps( hdc, SCALINGFACTORX );
        pt->y = GetDeviceCaps( hdc, SCALINGFACTORY );
        return 1;

    case NEWFRAME:
        return EndPage( hdc );

    case SETABORTPROC:
        return SetAbortProc( hdc, (ABORTPROC)in_data );

    case STARTDOC:
        {
            DOCINFOA doc;
            char *name = NULL;

            /* in_data may not be 0 terminated so we must copy it */
            if (in_data)
            {
                name = HeapAlloc( GetProcessHeap(), 0, in_count+1 );
                memcpy( name, in_data, in_count );
                name[in_count] = 0;
            }
            /* out_data is actually a pointer to the DocInfo structure and used as
             * a second input parameter */
            if (out_data) doc = *(DOCINFOA *)out_data;
            else
            {
                doc.cbSize = sizeof(doc);
                doc.lpszOutput = NULL;
                doc.lpszDatatype = NULL;
                doc.fwType = 0;
            }
            doc.lpszDocName = name;
            ret = StartDocA( hdc, &doc );
            HeapFree( GetProcessHeap(), 0, name );
            if (ret > 0) ret = StartPage( hdc );
            return ret;
        }

    case QUERYESCSUPPORT:
        {
            const INT *ptr = (const INT *)in_data;
            if (in_count < sizeof(INT)) return 0;
            switch(*ptr)
            {
            case ABORTDOC:
            case ENDDOC:
            case GETPHYSPAGESIZE:
            case GETPRINTINGOFFSET:
            case GETSCALINGFACTOR:
            case NEWFRAME:
            case QUERYESCSUPPORT:
            case SETABORTPROC:
            case STARTDOC:
                return TRUE;
            }
            break;
        }
    }

    /* if not handled internally, pass it to the driver */
    return ExtEscape( hdc, escape, in_count, in_data, 0, out_data );
}


/******************************************************************************
 *		ExtEscape	[GDI32.@]
 *
 * Access capabilities of a particular device that are not available through GDI.
 *
 * PARAMS
 *    hdc         [I] Handle to device context
 *    nEscape     [I] Escape function
 *    cbInput     [I] Number of bytes in input structure
 *    lpszInData  [I] Pointer to input structure
 *    cbOutput    [I] Number of bytes in output structure
 *    lpszOutData [O] Pointer to output structure
 *
 * RETURNS
 *    Success: >0
 *    Not implemented: 0
 *    Failure: <0
 */
INT WINAPI ExtEscape( HDC hdc, INT nEscape, INT cbInput, LPCSTR lpszInData,
                      INT cbOutput, LPSTR lpszOutData )
{
    INT ret = 0;
    DC * dc = get_dc_ptr( hdc );

    if (dc)
    {
        PHYSDEV physdev = GET_DC_PHYSDEV( dc, pExtEscape );
        ret = physdev->funcs->pExtEscape( physdev, nEscape, cbInput, lpszInData, cbOutput, lpszOutData );
        release_dc_ptr( dc );
    }
    return ret;
}


/*******************************************************************
 *      DrawEscape [GDI32.@]
 *
 *
 */
INT WINAPI DrawEscape(HDC hdc, INT nEscape, INT cbInput, LPCSTR lpszInData)
{
    FIXME("DrawEscape, stub\n");
    return 0;
}

/*******************************************************************
 *      NamedEscape [GDI32.@]
 */
INT WINAPI NamedEscape( HDC hdc, LPCWSTR pDriver, INT nEscape, INT cbInput, LPCSTR lpszInData,
                        INT cbOutput, LPSTR lpszOutData )
{
    FIXME("(%p, %s, %d, %d, %p, %d, %p)\n",
          hdc, wine_dbgstr_w(pDriver), nEscape, cbInput, lpszInData, cbOutput,
          lpszOutData);
    return 0;
}

/*******************************************************************
 *      DdQueryDisplaySettingsUniqueness [GDI32.@]
 *      GdiEntry13                       [GDI32.@]
 */
ULONG WINAPI DdQueryDisplaySettingsUniqueness(VOID)
{
    static int warn_once;

    if (!warn_once++)
        FIXME("stub\n");
    return 0;
}
