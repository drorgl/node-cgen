int hello();

void world(int i);

int (*pt2Func)(int argc, char *argv[]);

typedef int (*pt2Func)(int argc, char *argv[]);

int (*pt2FuncDef)(int argc = 0, char *argv[]);

CV_EXPORTS  int startLoop(int (*pt2Func)(int argc, char *argv[]), int argc, char* argv[]);

CV_EXPORTS void swapChannels(InputOutputArray image, const int dstOrder[4], Stream& stream = Stream::Null());

CV_EXPORTS void rectangle(CV_IN_OUT Mat& img, Rect rec,
                          const Scalar& color, int thickness = 1,
                          int lineType = LINE_8, int shift = 0);

						  
    template<typename _Tp, int m, int n, int nm> static
    void compute( const Matx<_Tp, m, n>& a, Matx<_Tp, nm, 1>& w, Matx<_Tp, m, nm>& u, Matx<_Tp, n, nm>& vt );


CV_EXPORTS void polylines(Mat& img, const Point* const* pts, const int* npts,
					  int ncontours, bool isClosed, const Scalar& color,
					  int thickness = 1, int lineType = LINE_8, int shift = 0 );
					  
void CV_EXPORTS focalsFromHomography(const Mat &H, double &f0, double &f1, bool &f0_ok, bool &f1_ok);

void CV_EXPORTS waveCorrect(std::vector<Mat> &rmats, WaveCorrectKind kind);

void CV_EXPORTS normalizeUsingWeightMap(InputArray weight, InputOutputArray src);


template<typename _Tp, int m, int n> template<int l> inline
Matx<_Tp, n, l> Matx<_Tp, m, n>::solve(const Matx<_Tp, m, l>& rhs, int method) const
{
    Matx<_Tp, n, l> x;
    bool ok;
    if( method == DECOMP_LU || method == DECOMP_CHOLESKY )
        ok = cv::internal::Matx_FastSolveOp<_Tp, m, l>()(*this, rhs, x, method);
    else
    {
        Mat A(*this, false), B(rhs, false), X(x, false);
        ok = cv::solve(A, B, X, method);
    }

    return ok ? x : Matx<_Tp, n, l>::zeros();
}



template <bool x> struct CV_StaticAssert_failed;
     template <> struct CV_StaticAssert_failed<true> { enum { val = 1 }; };
     template<int x> struct CV_StaticAssert_test {};
	 
	 
	 
	 
	 
inline FileNode FileStorage::getFirstTopLevelNode() const { FileNode r = root(); FileNodeIterator it = r.begin(); return it != r.end() ? *it : FileNode(); }
inline FileNode::FileNode() : fs(0), node(0) {}
inline FileNode::FileNode(const CvFileStorage* _fs, const CvFileNode* _node) : fs(_fs), node(_node) {}
inline FileNode::FileNode(const FileNode& _node) : fs(_node.fs), node(_node.node) {}
inline bool FileNode::empty() const    { return node   == 0;    }
inline bool FileNode::isNone() const   { return type() == NONE; }
inline bool FileNode::isSeq() const    { return type() == SEQ;  }
inline bool FileNode::isMap() const    { return type() == MAP;  }
inline bool FileNode::isInt() const    { return type() == INT;  }
inline bool FileNode::isReal() const   { return type() == REAL; }
inline bool FileNode::isString() const { return type() == STR;  }
inline CvFileNode* FileNode::operator *() { return (CvFileNode*)node; }
inline const CvFileNode* FileNode::operator* () const { return node; }
inline FileNode::operator int() const    { int value;    read(*this, value, 0);     return value; }
inline FileNode::operator float() const  { float value;  read(*this, value, 0.f);   return value; }
inline FileNode::operator double() const { double value; read(*this, value, 0.);    return value; }
inline FileNode::operator String() const { String value; read(*this, value, value); return value; }
inline FileNodeIterator FileNode::begin() const { return FileNodeIterator(fs, node); }
inline FileNodeIterator FileNode::end() const   { return FileNodeIterator(fs, node, size()); }
inline void FileNode::readRaw( const String& fmt, uchar* vec, size_t len ) const { begin().readRaw( fmt, vec, len ); }
inline FileNode FileNodeIterator::operator *() const  { return FileNode(fs, (const CvFileNode*)(const void*)reader.ptr); }
inline FileNode FileNodeIterator::operator ->() const { return FileNode(fs, (const CvFileNode*)(const void*)reader.ptr); }
inline String::String(const FileNode& fn): cstr_(0), len_(0) { read(fn, *this, *this); }



CV_INLINE CV_NORETURN void errorNoReturn(int _code, const String& _err, const char* _func, const char* _file, int _line)
{
    error(_code, _err, _func, _file, _line);
#ifdef __GNUC__
# if !defined __clang__ && !defined __APPLE__
    // this suppresses this warning: "noreturn" function does return [enabled by default]
    __builtin_trap();
    // or use infinite loop: for (;;) {}
# endif
#endif
}



template <typename ...Args>
CV_EXPORTS void winrt_startMessageLoop(std::function<void(Args...)>&& callback, Args... args);

template <typename ...Args>
CV_EXPORTS void winrt_startMessageLoop(void callback(Args...), Args... args);



#define CV_MAT_AUG_OPERATOR1(op, cvop, A, B) \
    static inline A& operator op (A& a, const B& b) { cvop; return a; }

#define CV_MAT_AUG_OPERATOR(op, cvop, A, B)   \
    CV_MAT_AUG_OPERATOR1(op, cvop, A, B)      \
    CV_MAT_AUG_OPERATOR1(op, cvop, const A, B)

#define CV_MAT_AUG_OPERATOR_T(op, cvop, A, B)                   \
    template<typename _Tp> CV_MAT_AUG_OPERATOR1(op, cvop, A, B) \
    template<typename _Tp> CV_MAT_AUG_OPERATOR1(op, cvop, const A, B)

CV_MAT_AUG_OPERATOR  (+=, cv::add(a,b,a), Mat, Mat)
CV_MAT_AUG_OPERATOR  (+=, cv::add(a,b,a), Mat, Scalar)
CV_MAT_AUG_OPERATOR_T(+=, cv::add(a,b,a), Mat_<_Tp>, Mat)
CV_MAT_AUG_OPERATOR_T(+=, cv::add(a,b,a), Mat_<_Tp>, Scalar)
CV_MAT_AUG_OPERATOR_T(+=, cv::add(a,b,a), Mat_<_Tp>, Mat_<_Tp>)


