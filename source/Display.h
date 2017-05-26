#pragma once
#include <vector>

class Display
{
  public:
    Display( int owidth, int oheight );

    struct Resolution
    {
      int width, height;
      DEVMODE mode;
      void Set();
    };

    std::vector< Resolution > GetResolutions();

    void ChangeResolution( int index );

    void RestoreOriginal();

    void SetFullScreenContext();

    void SetWindowContext();

    Resolution GetCurrentResolution();

    int ChangeResolutionTo( int width, int height );
    
    bool GetFullScreen();

  private:
    void GetDisplays();

    DISPLAY_DEVICE device;
    std::vector< Resolution > resolutions;
    int originalwidth;
    int originalheight;
    Resolution original;
    Resolution current;
    bool FullScreen;
    bool changed;
};
