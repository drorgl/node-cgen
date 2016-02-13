
enum InterpolationMasks {
       INTER_BITS      = 5,
       INTER_BITS2     = INTER_BITS * 2,
       INTER_TAB_SIZE  = 1 << INTER_BITS,
       INTER_TAB_SIZE2 = INTER_TAB_SIZE * INTER_TAB_SIZE,
	   DIST_USER    = -1,  //!< User defined distance
	   PREV_AROUND_DST   = 0x33,
	   DEPTH_MASK_ALL = (DEPTH_MASK_64F<<1)-1,
        DEPTH_MASK_ALL_BUT_8S = DEPTH_MASK_ALL & ~DEPTH_MASK_8S,
        DEPTH_MASK_FLT = DEPTH_MASK_32F + DEPTH_MASK_64F
     };
	 
	 
enum { generic_type = 0,
           depth        = DataType<channel_type>::depth,
           channels     = (int)sizeof(value_type)/sizeof(channel_type), // 5
           fmt          = DataType<channel_type>::fmt + ((channels - 1) << 8),
           type         = CV_MAKETYPE(depth, channels)
         };