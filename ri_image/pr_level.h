//  ----------------------------------------------------------------------------
//  MODULE    : PResolutionLevel 
//  LANGUAGE  : C 
//  CREATOR   : Philippe BOSSUT 
//  CREAT. DATE : Wednesday, March 13, 1996 
//  DESCRIPTION :  
//  COMMENTS  : 
//  SCCSID      : @(#)pr_level.h  1.1 11:46:42 18 Dec 1996
//  ----------------------------------------------------------------------------
//  Copyright (c) 1999 Digital Imaging Group, Inc.
//  For conditions of distribution and use, see copyright notice
//  in Flashpix.h
//  ----------------------------------------------------------------------------
  #ifndef PResolutionLevel_h
  #define PResolutionLevel_h
  #ifndef Commun_h
    #include  "common.h"
  #endif
//  ----------------------------------------------------------------------------

//  Includes
//  --------

#ifndef SystemIVUE_h
  #include  "ri_sys.h"
#endif

#ifndef CombinMat_h
  #include  "matrix.h"
#endif

#ifndef FPXBaselineIO_h
  #include "fpxlibio.h"
#endif

  // to avoid include CorrectLut.h
  struct CorrectLut;

//  Constants
//  ---------

//  Types Declarations
//  ------------------

//  Types Definitions
//  -----------------

//  Classes Declarations
//  --------------------

  class PHierarchicalImage;
  class PFileIVUEIO;
  class PFileFlashPixIO;
  class PResolutionLevel;
  class PTile;
  class PTileIVUE;
  class PTileFlashPix;

//  Classes Definitions
//  -------------------

  // Resolution Level class. A resolution level is composed of several tiles of pixels.
  // Each resolution level points to the next resolution level which resolution is 1/2.

  class PResolutionLevel : public PToolkitObject {

    friend class PHierarchicalImage;
    friend class PFileIVUEIO;
    friend class PFileFlashPixIO;
    friend class PTile;
    friend class PTileIVUE;
    friend class PTileFlashPix;

  public:
      // Constructors and destructor :
      
               // Create resolution and next resolution in write mode
               PResolutionLevel (PHierarchicalImage* father, int width, int height, int* quelImage);
               // Create resolution and next resolution in read mode
               PResolutionLevel (PHierarchicalImage* father, int* offset, int id);

      virtual     ~PResolutionLevel();
              
      // Public interface: File specific implementation of a Resolution Level:
      // ---------------------------------------------------------------------
      // These methods must be derived in most of the cases

      // Writing tools:
      virtual FPXStatus WriteLine (Pixel* pix, short plan = -1);
      virtual FPXStatus   WriteRectangle (int x0, int y0, int x1, int y1, Pixel* pix, short plan = -1);

      // Reading pixels tools:
      virtual FPXStatus   ReadRectangle (int x0, int y0, int x1, int y1, Pixel* pix);
      virtual FPXStatus ReadSampledRectangle(int x0, int y0,int x1, int y1, Pixel* map, short pixelsPerLine, int mapWidth, int mapHeight, Boolean showAlphaChannel = false, float ratio = 0.0);
      virtual FPXStatus Read (int* px, int* py, Pixel* table);
      virtual FPXStatus ReadInterpolated (int* px, int* py, Pixel* table);
      virtual FPXStatus ReadMean (int xi, int yi, Pixel& pixel);
      virtual FPXStatus ReadMeanInterpolated (int xi, int yi, Pixel& pixel);

      // Get information tools
      virtual FPXStatus GetHistogram (int* alpha, int* red, int* green, int* blue, int* brightness, const CorrectLut* correctLut = NULL);
      virtual FPXStatus InverseAlpha();           // Inverse alpha channel in all opened tiles
      virtual Boolean   IsOnTheBorder (int xi, int yi);
      virtual FPXStatus SearchPixelTopLeftCorner(int* x1, int* y1, float ratio);
      virtual FPXStatus GetResolutionSizeInfo (int* width, int* height, int* nbTilesWidth, int* nbTilesHeight);
      virtual Boolean   HasBeenUsed ();

  protected:
      // Protected interface: Methods used by the derived classes to customize the behavior of a Resolution Level:
      // ---------------------------------------------------------------------------------------------------------
      
      // Subimages management
      virtual void    InitWhenCreate();
      virtual void    InitWhenReading();
          FPXStatus Allocation ();
      virtual FPXStatus AllocTilesArray ();
          FPXStatus CloseSubImage ();
      
      // Reading tools:
      virtual FPXStatus Read ();    // Read the resolution specific information
      virtual FPXStatus ReadInARectangle(Pixel* bufferOut, short pixelsPerLine, short width, short height,
                       const CorrectLut* correctLut = NULL, Boolean useAlphaChannel = false, const CombinMat* combinaisonMatrix = NULL);

      // Writing tools:
      virtual FPXStatus Write ();   // Write the resolution specific information
      virtual FPXStatus Convolution (int x, int y, Pixel* pix, int width, int height);
      virtual FPXStatus FlushModifiedTiles ();
      virtual FPXStatus DecimateLevel ();
      
      // Error management:
          long  Status();
        
  protected:
      // Data of the PResolutionLevel object
      // -----------------------------------
      
      PHierarchicalImage*   fatherFile;       // Pointer to the father FileIVUEIO
      int           posFic;         // Position in the file
      int32         identifier;       // Sub-Image identifier (i.e. sub image number)

      short         nbTilesH;       // Height of the sub-image in tiles
      short         nbTilesW;       // Width of the sub-image in tiles
      int           realHeight;       // Height of the sub-image in pixels
      int           realWidth;        // Width of the sub-image in pixels
      PTile*          tiles;          // Tiles list
      
      Boolean         isAlpha;        // true if there is an alpha channel
      Boolean         premultiplied;      // true if the data are premultiplied by the alpha
      unsigned char     alphaOffset;      // position of the alpha channel in a 32 bits pixel

      int           currentLine;      // Current line number
      long          imageStatus;
      
      PResolutionLevel*     next;         // Point to the next sub-image
      PResolutionLevel*     Previous();       // Get the pointer to the previous sub-image
};



//  'inline' Functions
//  ------------------

inline FPXStatus PResolutionLevel::WriteLine (Pixel* pix, short plan)

{
  FPXStatus status;
  
  status = WriteRectangle (0, currentLine, realWidth - 1, currentLine, pix, plan);
  if (!status) currentLine++;
  return status;
}

inline long PResolutionLevel::Status()

{
  return imageStatus;
}

//  'extern' Functions
//  ------------------

//  'extern' Variables
//  ------------------

//  ----------------------------------------------------------------------------
  #endif // PResolutionLevel_h
//  ----------------------------------------------------------------------------
