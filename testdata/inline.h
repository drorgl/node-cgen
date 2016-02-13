CV_INLINE CvRNG cvRNG( int64 seed CV_DEFAULT(-1))
{
    CvRNG rng = seed ? (uint64)seed : (uint64)(int64)-1;
    return rng;
}


inline FileNode::operator int() const    { int value;    read(*this, value, 0);     return value; }
