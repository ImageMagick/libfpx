//  ----------------------------------------------------------------------------
//  MODULE    : PRIImage 
//  LANGUAGE  : C++
//  CREATOR   : Philippe BOSSUT 
//  CREAT. DATE : Tuesday, March 12, 1996 
//  DESCRIPTION : Portable Resolution Independent Image
//  COMMENTS  : This package is a part of the IVUE Toolkit I/O and of
//                the FlashPix Baseline I/O Toolkit
//  SCCSID      : @(#)priimage.h  1.1 11:46:42 18 Dec 1996
//  ----------------------------------------------------------------------------
//  Copyright (c) 1999 Digital Imaging Group, Inc.
//  For conditions of distribution and use, see copyright notice
//  in Flashpix.h
//  ----------------------------------------------------------------------------
  #ifndef PRIImage_h
  #define PRIImage_h
  #ifndef Commun_h
    #include  "common.h"
  #endif
//  ----------------------------------------------------------------------------

//  Includes
//  --------

#ifndef SystemIVUE_h
  #include  "ri_sys.h"
#endif
#ifndef FicNomSearchIVUE_h
  #include  "fn_srch.h"
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
//
// A 4x4 sample is defined as follows :
//
//  2>  .       .<3     if (x0,y0) are the coordinates of the center of P00, (x1,y1), (x2,y2) and (x3,y3) are
//    P03 P13 P23 P33       the coordinates of the center of the surrounding pixels. They are outside the sample.
//    P02 P12 P22 P32       The middle of (0,3) segment is then P22, the middle of (0,1) is P20, etcÉ
//    P01 P11 P21 P31
//    P00 P10 P20 P30 .
//     ^        ^
//     0        1
//
  #define SAMPLE_WIDTH  4

  #define P00 0
  #define P10 1
  #define P20 2
  #define P30 3
  #define P01 4
  #define P11 5
  #define P21 6
  #define P31 7
  #define P02 8
  #define P12 9
  #define P22 10
  #define P32 11
  #define P03 12
  #define P13 13
  #define P23 14
  #define P33 15

//  Types Declarations
//  ------------------

//  Types Definitions
//  -----------------

//  Classes Declarations
//  --------------------

  class PRIImage;
  class PResolutionLevel;
  class PTile;
  class PageImage;
  class PImageFile;
  class ViewImage;
  class PFlashPixImageView;

//  Classes Definitions
//  -------------------

  // PRIImage stands for Portable Resolution Independent Image

  class PRIImage : public PToolkitObject {
  
  friend class PResolutionLevel;
  friend class PTile;
  friend class PageImage;
  friend class ViewImage;
  friend class PFlashPixImageView;
  
  public:
        // Constructors and destructor :
        
                 // Image constructors
                 PRIImage ();
                 PRIImage (int width, int height, float resolution);
                 
        virtual     ~PRIImage ();

        // Public interface: Methods used by the application to read a RI Image:
        // ---------------------------------------------------------------------
        // These methods must be derived in most of the cases

        // Global flag: read with interpolation between levels when true, simple subsampling when false 
        static  Boolean readInterpolated;

        // Read a buffer of pixels methods:
        virtual FPXStatus ReadRectangle (int x0, int y0, int x1, int y1, Pixel* rect, int resolution = -1);
        virtual FPXStatus ReadInARectangle(Pixel* bufferOut, short pixelsParLigne, short largeur, short hauteur, 
                         const CorrectLut* correctLut = NULL, Boolean useAlphaChannel = FALSE, const CombinMat* matDeCombinaison = NULL);
        virtual FPXStatus Read4Points (int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, Pixel* table, int levelSubImage = -1);
        virtual FPXStatus ReadMean (int xi, int yi, Pixel& pix, int levelSubImage);

        // Return true if the alpha channel is not flat in the neighborhood
            Boolean   DispersionAlphaChannel (int xNW, int yNW, int xNE, int yNE, int xSW, int ySW, int xSE, int ySE, int levelSubImage);

        // Get information tools
        virtual FPXStatus GetFileName (FicNom& refNom);
            FPXStatus GetDimensions (int* width, int* height);      // Get pixel dimensions of the high res after cropping (if any)
        virtual FPXStatus GetTrueDimensions (int* width, int* height);    // Get pixel dimensions of the high res without cropping
            FPXStatus GetResolution (float* resol);
        virtual FPXStatus GetHistogram (int* alpha, int* red, int* green, int* blue, int* brightness, const CorrectLut* correctLut = NULL);
        virtual FPXStatus GetCropRectangle (int* x0, int* y0, int* x1, int* y1);
        virtual FPXStatus GetHotSpot (int* x0, int* y0);

        // Set information tools
        virtual FPXStatus SetCropRectangle (int x0, int y0, int x1, int y1);
        virtual FPXStatus ResetCropRectangle ();
            void    SetImageParameter (ViewImage* viewImage);
            void    SetApplyParameter (Boolean applyParameter);

        // Alpha channel management
            Boolean   ExistAlphaChannel();
        virtual Boolean   SetAlphaChannel(Boolean exist);
        virtual FPXStatus UseAlphaChannel (Boolean useAlpha);
        virtual FPXStatus InvertAlphaChannel (Boolean inverseAlpha);

        // Path management
        virtual OSErr ReadPaths  (data_Record** thePath, int* nbRecords, int* theClipPathNum);
        virtual OSErr ReleasePaths  ();

        // Error management
        virtual FPXStatus Status ();

        // Reference management
            void  IncrementReference()        { nbRefs++; }
            void  DecrementReference()        { nbRefs--; }
            Boolean NoMoreReference()           { return (nbRefs == 0); }
            
            void  ResetMagicNumber()        { magicNumber = 0; }
            void  SetMagicNumber()        { magicNumber = (unsigned long)(this); }
            Boolean ChallengeMagicNumber()      { return (magicNumber == (unsigned long)(this)); }
            void  SetMagicNumber(unsigned long id)    { magicNumber = id; }
            Boolean ChallengeMagicNumber(unsigned long id)  { return (magicNumber == id); }
            unsigned long GetMagicNumber()        { return magicNumber; }
  protected:
        // Protected interface: Methods used by the derived classes to customize the behavior of a RI Image:
        // -------------------------------------------------------------------------------------------------
        
        // Read a buffer of pixels methods:
        virtual FPXStatus ReadSampledRectangle(int x0, int y0, int x1, int y1, Pixel* map, short pixelsPerLine, int mapWidth, int mapHeight, Boolean showAlphaChannel = FALSE, float ratio = 0.0);
        virtual FPXStatus SearchPixelTopLeftCorner(int* x1, int* y1, float ratio);

        // Set information tools
        virtual FPXStatus SetHotSpot (int x0, int y0);
        virtual FPXStatus SetImageSize (int theWidth, int theHeight, float theResolution);

        // Alpha channel management
        virtual FPXStatus InverseAlpha();           // Inverse alpha channel in all opened sub-images

        // Error management
        virtual void    UpdateErrorCount();
            void    RaiseError (FPXStatus err)      { error = err; }

        // Data of the Resolution Independent Image object
        // -----------------------------------------------

        int      height, width;      // Full resolution image size in pixels
        float     resolution;       // Scanning resolution in dot per mm
        Boolean     useAlphaChannel;    // Use the alpha channel when reading
        Boolean     existAlphaChannel;    // Existence of an alpha channel in the image file
        Boolean     inverseAlphaChannel;  // Inverse alpha channel when reading
        int      hotSpotX, hotSpotY;   // Hot Spot position within the full resolution image

        int      cropX0, cropY0;     // Top left crop point position
        int      cropX1, cropY1;     // Bottom right crop point position
        data_Record*  path;         // Path handle
        int32       nbPaths;        // Number of path records
        int32     clipPathNum;      // Number of the clip path in the path list

        // Pointer to the View Image object (if any) and application flag
        ViewImage*    imageParam;
        Boolean     applyParam;

  private:
        // Private init of a PRIImage -> this is not a virtual method
            void  Init();

        // Data of the Resolution Independent Image
        // ----------------------------------------

        // Reference management
        unsigned long magicNumber;      // Used to reference a PRIImage object used by several composition objects
        int      nbRefs;         // Number of existing references to this PRIImage object

        // Error management
        FPXStatus   error;          // Correctness of the PRIImage : error == 0 when all is OK
        int      nbError;        // Count number of errors reading the image
  };


//  'inline' Functions
//  ------------------

// PRIImage inline functions : Obtaining usefull information tools : 

inline FPXStatus  PRIImage::GetDimensions (int* width, int* height)
{
  *height = cropY1 - cropY0;
  *width  = cropX1 - cropX0;
  if (!(*height)) *height = this->height;
  if (!(*width))  *width  = this->width;
  return FPX_OK;
}

// Return resolution in dot per mm
inline FPXStatus  PRIImage::GetResolution (float* resol)
{
  *resol = resolution;
  return FPX_OK;
}

inline Boolean  PRIImage::ExistAlphaChannel ()
{
  return existAlphaChannel;
}
  
inline void PRIImage::SetImageParameter (ViewImage* viewImage) 
{
  imageParam = viewImage;
}

inline void PRIImage::SetApplyParameter (Boolean applyParameter)
{
  applyParam = applyParameter;
}
  
//  'extern' Functions
//  ------------------

//  'extern' Variables
//  ------------------

//  ----------------------------------------------------------------------------
  #endif // PRIImage_h
//  ----------------------------------------------------------------------------
