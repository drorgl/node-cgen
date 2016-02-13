
struct CV_EXPORTS_W HOGDescriptor
{
public:
    enum { L2Hys = 0
         };
    enum { DEFAULT_NLEVELS = 64
         };

    CV_WRAP HOGDescriptor() : winSize(64,128), blockSize(16,16), blockStride(8,8),
        cellSize(8,8), nbins(9), derivAperture(1), winSigma(-1),
        histogramNormType(HOGDescriptor::L2Hys), L2HysThreshold(0.2), gammaCorrection(true),
        free_coef(-1.f), nlevels(HOGDescriptor::DEFAULT_NLEVELS), signedGradient(false)
    {}

    CV_WRAP HOGDescriptor(Size _winSize, Size _blockSize, Size _blockStride,
                  Size _cellSize, int _nbins, int _derivAperture=1, double _winSigma=-1,
                  int _histogramNormType=HOGDescriptor::L2Hys,
                  double _L2HysThreshold=0.2, bool _gammaCorrection=false,
                  int _nlevels=HOGDescriptor::DEFAULT_NLEVELS, bool _signedGradient=false)
    : winSize(_winSize), blockSize(_blockSize), blockStride(_blockStride), cellSize(_cellSize),
    nbins(_nbins), derivAperture(_derivAperture), winSigma(_winSigma),
    histogramNormType(_histogramNormType), L2HysThreshold(_L2HysThreshold),
    gammaCorrection(_gammaCorrection), free_coef(-1.f), nlevels(_nlevels), signedGradient(_signedGradient)
    {}

    CV_WRAP HOGDescriptor(const String& filename)
    {
        load(filename);
    }

    HOGDescriptor(const HOGDescriptor& d)
    {
        d.copyTo(*this);
    }

    virtual ~HOGDescriptor() {}

    CV_WRAP size_t getDescriptorSize() const;
    CV_WRAP bool checkDetectorSize() const;
    CV_WRAP double getWinSigma() const;

    CV_WRAP virtual void setSVMDetector(InputArray _svmdetector);

    virtual bool read(FileNode& fn);
    virtual void write(FileStorage& fs, const String& objname) const;

    CV_WRAP virtual bool load(const String& filename, const String& objname = String());
    CV_WRAP virtual void save(const String& filename, const String& objname = String()) const;
    virtual void copyTo(HOGDescriptor& c) const;

    CV_WRAP virtual void compute(InputArray img,
                         CV_OUT std::vector<float>& descriptors,
                         Size winStride = Size(), Size padding = Size(),
                         const std::vector<Point>& locations = std::vector<Point>()) const;

    //! with found weights output
    CV_WRAP virtual void detect(const Mat& img, CV_OUT std::vector<Point>& foundLocations,
                        CV_OUT std::vector<double>& weights,
                        double hitThreshold = 0, Size winStride = Size(),
                        Size padding = Size(),
                        const std::vector<Point>& searchLocations = std::vector<Point>()) const;
    //! without found weights output
    virtual void detect(const Mat& img, CV_OUT std::vector<Point>& foundLocations,
                        double hitThreshold = 0, Size winStride = Size(),
                        Size padding = Size(),
                        const std::vector<Point>& searchLocations=std::vector<Point>()) const;

    //! with result weights output
    CV_WRAP virtual void detectMultiScale(InputArray img, CV_OUT std::vector<Rect>& foundLocations,
                                  CV_OUT std::vector<double>& foundWeights, double hitThreshold = 0,
                                  Size winStride = Size(), Size padding = Size(), double scale = 1.05,
                                  double finalThreshold = 2.0,bool useMeanshiftGrouping = false) const;
    //! without found weights output
    virtual void detectMultiScale(InputArray img, CV_OUT std::vector<Rect>& foundLocations,
                                  double hitThreshold = 0, Size winStride = Size(),
                                  Size padding = Size(), double scale = 1.05,
                                  double finalThreshold = 2.0, bool useMeanshiftGrouping = false) const;

    CV_WRAP virtual void computeGradient(const Mat& img, CV_OUT Mat& grad, CV_OUT Mat& angleOfs,
                                 Size paddingTL = Size(), Size paddingBR = Size()) const;

    CV_WRAP static std::vector<float> getDefaultPeopleDetector();
    CV_WRAP static std::vector<float> getDaimlerPeopleDetector();

    CV_PROP Size winSize;
    CV_PROP Size blockSize;
    CV_PROP Size blockStride;
    CV_PROP Size cellSize;
    CV_PROP int nbins;
    CV_PROP int derivAperture;
    CV_PROP double winSigma;
    CV_PROP int histogramNormType;
    CV_PROP double L2HysThreshold;
    CV_PROP bool gammaCorrection;
    CV_PROP std::vector<float> svmDetector;
    UMat oclSvmDetector;
    float free_coef;
    CV_PROP int nlevels;
    CV_PROP bool signedGradient;


    //! evaluate specified ROI and return confidence value for each location
    virtual void detectROI(const cv::Mat& img, const std::vector<cv::Point> &locations,
                                   CV_OUT std::vector<cv::Point>& foundLocations, CV_OUT std::vector<double>& confidences,
                                   double hitThreshold = 0, cv::Size winStride = Size(),
                                   cv::Size padding = Size()) const;

    //! evaluate specified ROI and return confidence value for each location in multiple scales
    virtual void detectMultiScaleROI(const cv::Mat& img,
                                                       CV_OUT std::vector<cv::Rect>& foundLocations,
                                                       std::vector<DetectionROI>& locations,
                                                       double hitThreshold = 0,
                                                       int groupThreshold = 0) const;

    //! read/parse Dalal's alt model file
    void readALTModel(String modelfile);
    void groupRectangles(std::vector<cv::Rect>& rectList, std::vector<double>& weights, int groupThreshold, double eps) const;
	
	
	  static Ptr<DownhillSolver> create(const Ptr<MinProblemSolver::Function>& f=Ptr<MinProblemSolver::Function>(),
                                      InputArray initStep=Mat_<double>(1,1,0.0),
                                      TermCriteria termcrit=TermCriteria(TermCriteria::MAX_ITER+TermCriteria::EPS,5000,0.000001));
									  
};


class CV_EXPORTS Exception : public std::exception
{
public:
    /*!
     Default constructor
     */
    Exception();
    /*!
     Full constructor. Normally the constuctor is not called explicitly.
     Instead, the macros CV_Error(), CV_Error_() and CV_Assert() are used.
    */
    Exception(int _code, const String& _err, const String& _func, const String& _file, int _line);
    virtual ~Exception() throw();

    /*!
     \return the error description and the context as a text string.
    */
    virtual const char *what() const throw();
    void formatMessage();

    String msg; ///< the formatted error message

    int code; ///< error code @see CVStatus
    String err; ///< error description
    String func; ///< function name. Available only when the compiler supports getting it
    String file; ///< source file name where the error has occured
    int line; ///< line number in the source file where the error has occured
	
	unsigned state[N];
	
	unsigned char code;
	
	friend class VizStorage;
	
	friend struct WidgetAccessor;
	
	    unsigned int bufId() const;
	
	friend class VizStorage;
};


struct CV_EXPORTS PlaneProjector : ProjectorBase
{
    void mapForward(float x, float y, float &u, float &v);
    void mapBackward(float u, float v, float &x, float &y);
};



class CV_EXPORTS DpSeamFinder : public SeamFinder
{
public:
    enum CostFunction { COLOR, COLOR_GRAD };

    DpSeamFinder(CostFunction costFunc = COLOR);

    CostFunction costFunction() const { return costFunc_; }
    void setCostFunction(CostFunction val) { costFunc_ = val; }

    virtual void find(const std::vector<UMat> &src, const std::vector<Point> &corners,
                      std::vector<UMat> &masks);

private:
    enum ComponentState
    {
        FIRST = 1, SECOND = 2, INTERS = 4,
        INTERS_FIRST = INTERS | FIRST,
        INTERS_SECOND = INTERS | SECOND
    };

    class ImagePairLess
    {
    public:
        ImagePairLess(const std::vector<Mat> &images, const std::vector<Point> &corners)
            : src_(&images[0]), corners_(&corners[0]) {}

        bool operator() (const std::pair<size_t, size_t> &l, const std::pair<size_t, size_t> &r) const
        {
            Point c1 = corners_[l.first] + Point(src_[l.first].cols / 2, src_[l.first].rows / 2);
            Point c2 = corners_[l.second] + Point(src_[l.second].cols / 2, src_[l.second].rows / 2);
            int d1 = (c1 - c2).dot(c1 - c2);

            c1 = corners_[r.first] + Point(src_[r.first].cols / 2, src_[r.first].rows / 2);
            c2 = corners_[r.second] + Point(src_[r.second].cols / 2, src_[r.second].rows / 2);
            int d2 = (c1 - c2).dot(c1 - c2);

            return d1 < d2;
        }

    private:
        const Mat *src_;
        const Point *corners_;
    };

    class ClosePoints
    {
    public:
        ClosePoints(int minDist) : minDist_(minDist) {}

        bool operator() (const Point &p1, const Point &p2) const
        {
            int dist2 = (p1.x-p2.x) * (p1.x-p2.x) + (p1.y-p2.y) * (p1.y-p2.y);
            return dist2 < minDist_ * minDist_;
        }

    private:
        int minDist_;
    };

    void process(
            const Mat &image1, const Mat &image2, Point tl1, Point tl2,  Mat &mask1, Mat &mask2);

    void findComponents();

    void findEdges();

    void resolveConflicts(
            const Mat &image1, const Mat &image2, Point tl1, Point tl2, Mat &mask1, Mat &mask2);

    void computeGradients(const Mat &image1, const Mat &image2);

    bool hasOnlyOneNeighbor(int comp);

    bool closeToContour(int y, int x, const Mat_<uchar> &contourMask);

    bool getSeamTips(int comp1, int comp2, Point &p1, Point &p2);

    void computeCosts(
            const Mat &image1, const Mat &image2, Point tl1, Point tl2,
            int comp, Mat_<float> &costV, Mat_<float> &costH);

    bool estimateSeam(
            const Mat &image1, const Mat &image2, Point tl1, Point tl2, int comp,
            Point p1, Point p2, std::vector<Point> &seam, bool &isHorizontal);

    void updateLabelsUsingSeam(
            int comp1, int comp2, const std::vector<Point> &seam, bool isHorizontalSeam);

    CostFunction costFunc_;

    // processing images pair data
    Point unionTl_, unionBr_;
    Size unionSize_;
    Mat_<uchar> mask1_, mask2_;
    Mat_<uchar> contour1mask_, contour2mask_;
    Mat_<float> gradx1_, grady1_;
    Mat_<float> gradx2_, grady2_;

    // components data
    int ncomps_;
    Mat_<int> labels_;
    std::vector<ComponentState> states_;
    std::vector<Point> tls_, brs_;
    std::vector<std::vector<Point> > contours_;
    std::set<std::pair<int, int> > edges_;
};


   class UseRoi
    {
    public:
        inline UseRoi(bool val = false) : val_(val) {}

        inline operator bool() const { return val_; }

    private:
        bool val_;
    };
	
	
	
class CV_EXPORTS Context
{
public:
    Context();
    explicit Context(int dtype);
    ~Context();
    Context(const Context& c);
    Context& operator = (const Context& c);

    bool create();
    bool create(int dtype);
    size_t ndevices() const;
    const Device& device(size_t idx) const;
    Program getProg(const ProgramSource& prog,
                    const String& buildopt, String& errmsg);

    static Context& getDefault(bool initialize = true);
    void* ptr() const;

    friend void initializeContextFromHandle(Context& ctx, void* platform, void* context, void* device);

	friend void* workcycleObjectDetectorFunction(void* p);
	
    bool useSVM() const;
    void setUseSVM(bool enabled);

    struct Impl;
    Impl* p;
};


class CV_EXPORTS_W_MAP Moments
{
public:
    //! the default constructor
    Moments();
    //! the full constructor
    Moments(double m00, double m10, double m01, double m20, double m11,
            double m02, double m30, double m21, double m12, double m03 );
    ////! the conversion from CvMoments
    //Moments( const CvMoments& moments );
    ////! the conversion to CvMoments
    //operator CvMoments() const;

    //! @name spatial moments
    //! @{
    CV_PROP_RW double  m00, m10, m01, m20, m11, m02, m30, m21, m12, m03;
    //! @}

    //! @name central moments
    //! @{
    CV_PROP_RW double  mu20, mu11, mu02, mu30, mu21, mu12, mu03;
    //! @}

    //! @name central normalized moments
    //! @{
    CV_PROP_RW double  nu20, nu11, nu02, nu30, nu21, nu12, nu03;
    //! @}
};

struct HaarFeature64
{
    uint2 _ui2;

#define HaarFeature64_CreateCheck_MaxRectField                  0xFF

    __host__ NCVStatus setRect(Ncv32u rectX, Ncv32u rectY, Ncv32u rectWidth, Ncv32u rectHeight, Ncv32u /*clsWidth*/, Ncv32u /*clsHeight*/)
    {
        ncvAssertReturn(rectWidth <= HaarFeature64_CreateCheck_MaxRectField && rectHeight <= HaarFeature64_CreateCheck_MaxRectField, NCV_HAAR_TOO_LARGE_FEATURES);
        ((NcvRect8u*)&(this->_ui2.x))->x = (Ncv8u)rectX;
        ((NcvRect8u*)&(this->_ui2.x))->y = (Ncv8u)rectY;
        ((NcvRect8u*)&(this->_ui2.x))->width = (Ncv8u)rectWidth;
        ((NcvRect8u*)&(this->_ui2.x))->height = (Ncv8u)rectHeight;
        return NCV_SUCCESS;
    }

    __host__ NCVStatus setWeight(Ncv32f weight)
    {
        ((Ncv32f_a*)&(this->_ui2.y))[0] = weight;
        return NCV_SUCCESS;
    }

    __device__ __host__ void getRect(Ncv32u *rectX, Ncv32u *rectY, Ncv32u *rectWidth, Ncv32u *rectHeight)
    {
        NcvRect8u tmpRect = *(NcvRect8u*)(&this->_ui2.x);
        *rectX = tmpRect.x;
        *rectY = tmpRect.y;
        *rectWidth = tmpRect.width;
        *rectHeight = tmpRect.height;
    }

    __device__ __host__ Ncv32f getWeight(void)
    {
        return *(Ncv32f_a*)(&this->_ui2.y);
    }
};



template<>
struct RefOrVoid<volatile void>{ typedef volatile void type; };


struct TrackedObject
        {
            typedef std::vector<cv::Rect> PositionsVector;

            PositionsVector lastPositions;

            int numDetectedFrames;
            int numFramesNotDetected;
            int id;

            TrackedObject(const cv::Rect& rect):numDetectedFrames(1), numFramesNotDetected(0)
            {
                lastPositions.push_back(rect);
                id=getNextId();
            };

            static int getNextId()
            {
                static int _id=0;
                return _id++;
            }
        };
		
		
		
template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 0, GTEST_10_TUPLE_(T)> {
  typedef T0 type;
};
