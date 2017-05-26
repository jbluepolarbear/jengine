#include <windows.h>
#include "Display.h"

Display::Display( int owidth, int oheight )
{
  originalwidth = owidth;
  originalheight = oheight;

  FullScreen = false;
  changed = false;
  GetDisplays();
}

void Display::Resolution::Set()
{
  width = mode.dmPelsWidth;
  height = mode.dmPelsHeight;
}

std::vector< Display::Resolution > Display::GetResolutions()
{
  return resolutions;
}

void Display::ChangeResolution( int index )
{
  if ( !FullScreen )
    return;

  changed = true;

  current.mode = resolutions[index].mode;
  current.Set();
  if ( ChangeDisplaySettings( &current.mode, CDS_FULLSCREEN ) == DISP_CHANGE_SUCCESSFUL ) 
  {
    SetFullScreenContext();
    //InvalidateRect( NULL, NULL, TRUE );
    //ChangeDisplaySettings( &original, CDS_FULLSCREEN );
  }
}

void Display::RestoreOriginal()
{
  if ( !changed )
    return;

  current = original;
  if ( ChangeDisplaySettings( &original.mode, CDS_FULLSCREEN ) == DISP_CHANGE_SUCCESSFUL )
  {
    SetWindowContext();
  }
  changed = false;
}

void Display::SetFullScreenContext()
{
  SetWindowLong( GetActiveWindow(), GWL_STYLE, WS_POPUP );
  SetWindowPos( GetActiveWindow(), HWND_TOP, 0, 0, current.width, current.height, SWP_SHOWWINDOW );

  FullScreen = true;
}

void Display::SetWindowContext()
{
  SetWindowLong( GetActiveWindow(), GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX );
  SetWindowPos( GetActiveWindow(), HWND_TOP, 0, 0, originalwidth, originalheight, SWP_SHOWWINDOW );

  FullScreen = false;
}

Display::Resolution Display::GetCurrentResolution()
{
  return current;
}

int Display::ChangeResolutionTo( int width, int height )
{
  int index = 0;
  bool found = false;
  for ( ; index < resolutions.size(); ++index )
  {
    if ( width == resolutions[index].width && height == resolutions[index].height )
    {
      found = true;
      break;
    }
  }

  if ( !found )
    return -1;

  SetFullScreenContext();
  ChangeResolution( index );
  return index;
}

bool Display::GetFullScreen()
{
  return FullScreen;
}

void Display::GetDisplays()
{
  device.cb = sizeof( device );
  if ( EnumDisplayDevices( NULL, 0, &device, EDD_GET_DEVICE_INTERFACE_NAME ) )
  {
    DEVMODE mode;
    mode.dmSize = sizeof( mode );
    mode.dmDriverExtra = 0;

    EnumDisplaySettings( device.DeviceName, ENUM_CURRENT_SETTINGS, &original.mode );
    original.Set();
    current = original;

    for ( int setting = 0; EnumDisplaySettings( device.DeviceName, setting, &mode ); ++setting )
    {
      if ( mode.dmBitsPerPel != 32 ||
        mode.dmDisplayOrientation != 0 ||
        mode.dmDisplayFrequency != 60 ||
        mode.dmDefaultSource != 0 ||
        mode.dmPelsWidth / mode.dmPelsHeight > 2.0 )
        continue;
      Resolution r;
      r.mode = mode;
      r.Set();
      resolutions.push_back( r );
    }
  }
}