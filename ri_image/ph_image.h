//  ----------------------------------------------------------------------------
//  MODULE    : PHierarchicalImage 
//  LANGUAGE  : C++
//  CREATOR   : Philippe BOSSUT 
//  CREAT. DATE : Tuesday, March 12, 1996 
//  DESCRIPTION :  
//  COMMENTS  : 
//  SCCSID      : @(#)ph_image.h  1.1 11:46:41 18 Dec 1996
//  ----------------------------------------------------------------------------
//  Copyright (c) 1999 Digital Imaging Group, Inc.
//  For conditions of distribution and use, see copyright notice
//  in Flashpix.h
//  ----------------------------------------------------------------------------
  #ifndef PHierarchicalImage_h
  #define PHierarchicalImage_h
  #ifndef Commun_h
    #include  "common.h"
  #endif
//  ----------------------------------------------------------------------------

//  Includes
//  --------

#ifndef PRIImage_h
  #include  "priimage.h"
#endif
#ifndef Fichier_h
  #include  "a_file.h"  // just for Mode
#endif
#ifndef Compresseur_h
  #include  "fpxcompress.h"
#endif

#ifndef FPXBaselineIO_h
  #include "fpxlibio.h"
#endif

//  Constants
//  ---------

//  Types Declarations
//  ------------------

//  Types Definitions
//  -----------------

//  Classes Declarations
//  --------------------

  class PResolutionIVUE;
  class PResolutionFlashPix;
  class PTileIVUE;
  class PTileFlashPix;
  class PHierarchicalImage;

//  Classes Definitions
//  -------------------

  // Implementation of Resolution Independent Image with Hierarchy (IVUE and FlashPix)

  class PHierarchicalImage : public PRIImage {
  
  friend class PResolutionLevel;
  friend class PResolutionIVUE;
  friend class PResolutionFlashPix;
  friend class PTile;
  friend class PTileIVUE;
  friend class PTileFlashPix;
  friend class PageImage;
  
  public:
        // Constructors and destructor :
        
                 // Open the file in Create Mode 
                 PHierarchicalImage (FicNom& refNom, int width, int height, float resolution);
                 PHierarchicalImage (int fd, int width, int height, float resolution);
                 // Open the file in Read Mode only
                 PHierarchicalImage (FicNom& refNom);
                 PHierarchicalImage (int fd);
                 // Open the file in Read/Write mode (but not Create)
                 PHierarchicalImage (FicNom& refNom, mode_Ouverture openMode);
                 PHierarchicalImage (int fd, mode_Ouverture openMode);

        virtual     ~PHierarchicalImage ();

        // Public interface: Customize a RI Image:
        // ---------------------------------------

        // Read a buffer of pixels methods:
        virtual FPXStatus ReadRectangle (int x0, int y0, int x1, int y1, Pixel* rect, int resolution = -1);
        virtual FPXStatus ReadInARectangle(Pixel* bufferOut, short pixelsParLigne, short largeur, short hauteur, 
                         const CorrectLut* correctLut = NULL, Boolean useAlphaChannel = FALSE, const CombinMat* matDeCombinaison = NULL);
        virtual FPXStatus Read4Points (int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, Pixel* table, int levelSubImage = -1);
        virtual FPXStatus ReadMean (int xi, int yi, Pixel& pix, int levelSubImage);

        // Return true if the alpha channel is not flat in the neighborhood
            Boolean DispersionAlphaChannel (int xNW, int yNW, int xNE, int yNE, int xSW, int ySW, int xSE, int ySE, int levelSubImage);

        // Get information tools
        virtual FPXStatus GetTileSize (int* tileSize);
        virtual FPXStatus GetFileName (FicNom& refNom);
        virtual FPXStatus GetHistogram (int* alpha, int* red, int* green, int* blue, int* brightness, const CorrectLut* correctLut = NULL);

        // Set information tools
        virtual void  SetConvolution (Typ_Convolution newConvolution);
        virtual void  SetAutomaticDecimation (Boolean automaticDecimationOn);

        // Set compression 
        virtual void  SetCompression (Typ_Compression theCompression);

        // Alpha channel management
        virtual Boolean SetAlphaChannel(Boolean exist);

        // Path management :
        virtual OSErr ReadPaths  (data_Record** thePath, int* nbRecords, int* theClipPathNum);
        virtual OSErr WritePaths (data_Record*  thePath, int  nbRecords, int  theClipPathNum);

        // Public interface: Methods used by the application to use a Hierarchical Image:
        // ------------------------------------------------------------------------------
        // These methods must be derived in most of the cases

        // File management:
        virtual FPXStatus OpenImage();        // Open an Image in read, write or create mode
        virtual void    DoNotCloseFileWhenDelete();
        virtual void*   GetCurrentFile();     // return the file descriptor filePtr
        virtual Boolean   EnoughDiskSpace ();     // Test if there is enough space on disk to create the file

        // Write a buffer of pixels methods:
        virtual FPXStatus WriteLine (Pixel* line, short plan = -1);
        virtual FPXStatus WriteRectangle (int x0, int y0, int x1, int y1, Pixel* rect, short plan = -1, short resolution = 0);
        virtual FPXStatus RegenerateHierarchy ();

        // Get information tools
            long    GetNbResolutions ();
        virtual FPXStatus GetInfo (int* width, int* height, int* tileWidth, int* tileHeight, Typ_Compression* compr);

        // Color space & background color management
    FPXBaselineColorSpace   GetBaselineSpace();
    FPXBaselineColorSpace GetUsedColorSpace ();
            void  SetUsedColorSpace (FPXBaselineColorSpace colorSpace);
            void  SetBaseColorSpace (FPXBaselineColorSpace colorSpace);
            void  ResetUsedColorSpace ();
            void  SetBackgroundColor (FPXBaselineColorSpace colorSpace, Pixel backgroundColor);
            void  SetUncalibratedFlag(Boolean isUncalibrated);
            Boolean GetUncalibratedFlag();

  protected:
        // Protected interface: Customize a RI Image:
        // ------------------------------------------
        
        virtual FPXStatus ReadSampledRectangle(int x0, int y0,int x1, int y1, Pixel* map, short pixelsPerLine, int mapWidth, int mapHeight, Boolean showAlphaChannel = FALSE, float ratio = 0.0);
        virtual FPXStatus SearchPixelTopLeftCorner(int* x1, int* y1, float ratio);

        // Alpha channel management
        virtual FPXStatus InverseAlpha();     // Inverse alpha channel in all opened sub-images

        // Error management
        virtual void    UpdateErrorCount();   // Increment counter and invalid the image if necessary

        // Protected interface: Methods used by the derived classes to customize the behavior of a Hierarchical Image:
        // -----------------------------------------------------------------------------------------------------------
        
        // Set information tools
        virtual FPXStatus SetTileParameter (int width, int height);

        // File management:
        virtual FPXStatus OpenFile();         // Read or Init header file information
        virtual FPXStatus CloseFile();                              // End sub images computation and writing before closing the file
        virtual void    CloseFileWhenDelete();

        // Resolution hierarchy management:
        virtual FPXStatus InitResolutionLevelsTable();                      // Update pointers array of sub images
        virtual FPXStatus CreateInitResolutionLevelList();                    // Make a sub image list in read or write mode
        virtual FPXStatus CreateEmptyResolutionLevelList();                   // Make a sub image list in create mode
    virtual PResolutionLevel* CreateEmptyResolutionLevel(int width, int height, int* quelImage); // Make a sub image in create mode 
    virtual PResolutionLevel* CreateInitResolutionLevel(int* offset, long id);           // Make a sub image in read or write mode 

        // Protected data of the Hierarchical Image object
        // -----------------------------------------------

        FicNomSearchIVUE  fileName;     // Name of the image file
        PImageFile*     filePtr;        // The image file descriptor
        int         fd;           // The standard file descriptor (if provided by the user)
        mode_Ouverture    mode;         // The opening mode
        int32       posFic;         // Position of the header in the file
        int32       version;        // Version of the file

        PResolutionLevel* firstSubImage;      // This first resolution level is the full resolution image.
        long        nbSubImages;      // Number of sub-images
        PResolutionLevel**  subImages;        // Copy of the sub-image list
      
        int32       posPath;        // Position of the paths in the file
        Boolean       isFlatFile;

  protected:
        // Private init of a PHierarchicalmage -> this is not a virtual method
            void  Init();                 

        // Private data of the Hierarchical Image object
        // ---------------------------------------------

    FPXBaselineColorSpace     baseSpace;        // Base color space used natively in the file
        Boolean       baseUncalibrated;   // True if the colors are not calibrated in the file 
    FPXBaselineColorSpace     usedSpace;        // Color space used by the user when reading or writing 
        unsigned char   alphaOffset;      // position of the alpha channel in a 32 bits pixel for the usedSpace
        Pixel       backgroundBase;     // Color of the background in the base color space (used when writing)
        Pixel       backgroundUsed;     // Color of the background in the used color space (used when reading)

        Typ_Convolution   convolution;      // Convolution used in this image file
        Typ_Filter      filter;         // Convolution function used in this image file
        Boolean       automaticDecimation;  // Convolution of subimages done automatically if true

        Typ_Compression   compression;      // Compression mode used in this image file
        void*       compressionHandle;    // Compression/decompression handle
        int         handleSize;       // Size (in bytes) on this handle

        int         tileWidth;        // Width in pixels of a tile
        int         tileSize;       // = tileWidth * tileWidth * Sizeof(Pixel)
        int         tileLineSize;     // = tileWidth * Sizeof(Pixel)
        int         log2TileWidth;      // When doing ">>" instead of "/" (fast integer computation)
        int         maskTileWidth;      // When doing "&"  instead of "%" (fast integer computation)
  };

//  'inline' Functions
//  ------------------

inline long PHierarchicalImage::GetNbResolutions () { return nbSubImages; }

inline void PHierarchicalImage::SetCompression (Typ_Compression theCompression) { compression = theCompression; }

inline FPXBaselineColorSpace PHierarchicalImage::GetUsedColorSpace () { return usedSpace; }
inline FPXBaselineColorSpace PHierarchicalImage::GetBaselineSpace()   { return baseSpace; }
inline void PHierarchicalImage::ResetUsedColorSpace () { SetUsedColorSpace (baseSpace); }
inline void PHierarchicalImage::SetUncalibratedFlag(Boolean isUncalibrated) { baseUncalibrated = isUncalibrated; }
inline Boolean PHierarchicalImage::GetUncalibratedFlag() { return baseUncalibrated; }


        

//  'extern' Functions
//  ------------------

//  'extern' Variables
//  ------------------

//  ----------------------------------------------------------------------------
  #endif // PHierarchicalImage_h
//  ----------------------------------------------------------------------------
