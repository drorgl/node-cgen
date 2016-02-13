extern "C" {

/** @addtogroup objdetect_c
  @{
  */

/****************************************************************************************\
*                         Haar-like Object Detection functions                           *
\****************************************************************************************/

#define CV_HAAR_MAGIC_VAL    0x42500000
#define CV_TYPE_NAME_HAAR    "opencv-haar-classifier"

#define CV_IS_HAAR_CLASSIFIER( haar )                                                    \
    ((haar) != NULL &&                                                                   \
    (((const CvHaarClassifierCascade*)(haar))->flags & CV_MAGIC_MASK)==CV_HAAR_MAGIC_VAL)

#define CV_HAAR_FEATURE_MAX  3


}

extern int test_loop_times;


extern "C" typedef int (*ErrorCallback)( int status, const char* func_name,
                                       const char* err_msg, const char* file_name,
                                       int line, void* userdata );

									   
extern "C" typedef int (*ErrorCallback)( int status, const char* func_name,
                                       const char* err_msg, const char* file_name,
                                       int line, void* userdata );
