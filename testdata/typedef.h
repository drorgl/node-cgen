#if defined __GNUC__ && __GNUC__ > 2 && __GNUC_MINOR__  > 4
typedef Ncv32f __attribute__((__may_alias__)) Ncv32f_a;
#else
typedef Ncv32f Ncv32f_a;
#endif


typedef enum CvStatus
{
    CV_BADMEMBLOCK_ERR          = -113,
    CV_INPLACE_NOT_SUPPORTED_ERR= -112,
    CV_UNMATCHED_ROI_ERR        = -111,
    CV_NOTFOUND_ERR             = -110,
    CV_BADCONVERGENCE_ERR       = -109,

    CV_BADDEPTH_ERR             = -107,
    CV_BADROI_ERR               = -106,
    CV_BADHEADER_ERR            = -105,
    CV_UNMATCHED_FORMATS_ERR    = -104,
    CV_UNSUPPORTED_COI_ERR      = -103,
    CV_UNSUPPORTED_CHANNELS_ERR = -102,
    CV_UNSUPPORTED_DEPTH_ERR    = -101,
    CV_UNSUPPORTED_FORMAT_ERR   = -100,

    CV_BADARG_ERR               = -49,  //ipp comp
    CV_NOTDEFINED_ERR           = -48,  //ipp comp

    CV_BADCHANNELS_ERR          = -47,  //ipp comp
    CV_BADRANGE_ERR             = -44,  //ipp comp
    CV_BADSTEP_ERR              = -29,  //ipp comp

    CV_BADFLAG_ERR              =  -12,
    CV_DIV_BY_ZERO_ERR          =  -11, //ipp comp
    CV_BADCOEF_ERR              =  -10,

    CV_BADFACTOR_ERR            =  -7,
    CV_BADPOINT_ERR             =  -6,
    CV_BADSCALE_ERR             =  -4,
    CV_OUTOFMEM_ERR             =  -3,
    CV_NULLPTR_ERR              =  -2,
    CV_BADSIZE_ERR              =  -1,
    CV_NO_ERR                   =   0,
    CV_OK                       =   CV_NO_ERR
}
CvStatus;


typedef          long long Ncv64s;



typedef struct CvHaarFeature
{
    int tilted;
    struct
    {
        CvRect r;
        float weight;
    } rect[CV_HAAR_FEATURE_MAX];
} CvHaarFeature;



typedef struct
#ifdef __cplusplus
  CV_EXPORTS
#endif
_IplImage
{
    int  nSize;             /**< sizeof(IplImage) */
    int  ID;                /**< version (=0)*/
    int  nChannels;         /**< Most of OpenCV functions support 1,2,3 or 4 channels */
    int  alphaChannel;      /**< Ignored by OpenCV */
    int  depth;             /**< Pixel depth in bits: IPL_DEPTH_8U, IPL_DEPTH_8S, IPL_DEPTH_16S,
                               IPL_DEPTH_32S, IPL_DEPTH_32F and IPL_DEPTH_64F are supported.  */
    char colorModel[4];     /**< Ignored by OpenCV */
    char channelSeq[4];     /**< ditto */
    int  dataOrder;         /**< 0 - interleaved color channels, 1 - separate color channels.
                               cvCreateImage can only create interleaved images */
    int  origin;            /**< 0 - top-left origin,
                               1 - bottom-left origin (Windows bitmaps style).  */
    int  align;             /**< Alignment of image rows (4 or 8).
                               OpenCV ignores it and uses widthStep instead.    */
    int  width;             /**< Image width in pixels.                           */
    int  height;            /**< Image height in pixels.                          */
    struct _IplROI *roi;    /**< Image ROI. If NULL, the whole image is selected. */
    struct _IplImage *maskROI;      /**< Must be NULL. */
    void  *imageId;                 /**< "           " */
    struct _IplTileInfo *tileInfo;  /**< "           " */
    int  imageSize;         /**< Image data size in bytes
                               (==image->height*image->widthStep
                               in case of interleaved data)*/
    char *imageData;        /**< Pointer to aligned image data.         */
    int  widthStep;         /**< Size of aligned image row in bytes.    */
    int  BorderMode[4];     /**< Ignored by OpenCV.                     */
    int  BorderConst[4];    /**< Ditto.                                 */
    char *imageDataOrigin;  /**< Pointer to very origin of image data
                               (not necessarily aligned) -
                               needed for correct deallocation */

#ifdef __cplusplus
    _IplImage() {}
    _IplImage(const cv::Mat& m);
#endif
}
IplImage;




typedef struct CV_EXPORTS performance_metrics
{
    size_t bytesIn;
    size_t bytesOut;
    unsigned int samples;
    unsigned int outliers;
    double gmean;
    double gstddev;//stddev for log(time)
    double mean;
    double stddev;
    double median;
    double min;
    double frequency;
    int terminationReason;

    enum
    {
        TERM_ITERATIONS = 0,
        TERM_TIME = 1,
        TERM_INTERRUPT = 2,
        TERM_EXCEPTION = 3,
        TERM_SKIP_TEST = 4, // there are some limitations and test should be skipped
        TERM_UNKNOWN = -1
    };

    performance_metrics();
    void clear();
} performance_metrics;



/** matrix iterator: used for n-ary operations on dense arrays */
typedef struct CvNArrayIterator
{
    int count; /**< number of arrays */
    int dims; /**< number of dimensions to iterate */
    CvSize size; /**< maximal common linear size: { width = size, height = 1 } */
    uchar* ptr[CV_MAX_ARR]; /**< pointers to the array slices */
    int stack[CV_MAX_DIM]; /**< for internal use */
    CvMatND* hdr[CV_MAX_ARR]; /**< pointers to the headers of the
                                 matrices that are processed */
}
CvNArrayIterator;