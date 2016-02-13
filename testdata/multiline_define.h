#define hello () \
{ \
	printf("hello \r\n"); \
}



#define FLANN_DISTANCE_CHECK \
    if ( ::cvflann::flann_distance_type() != cvflann::FLANN_DIST_L2) { \
        printf("[WARNING] You are using cv::flann::Index (or cv::flann::GenericIndex) and have also changed "\
        "the distance using cvflann::set_distance_type. This is no longer working as expected "\
        "(cv::flann::Index always uses L2). You should create the index templated on the distance, "\
        "for example for L1 distance use: GenericIndex< L1<float> > \n"); \
    }


#ifndef __CV_TEST_EXEC_ARGS
#if defined(_MSC_VER) && (_MSC_VER <= 1400)
#define __CV_TEST_EXEC_ARGS(...)    \
    while (++argc >= (--argc,-1)) {__VA_ARGS__; break;} /*this ugly construction is needed for VS 2005*/
#else
#define __CV_TEST_EXEC_ARGS(...)    \
    __VA_ARGS__;
#endif
#endif


