#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkMutualInformationImageToImageMetric.h"
#include "itkNormalizedCorrelationImageToImageMetric.h"
#include "itkMattesMutualInformationImageToImageMetric.h"
#include "itkIdentityTransform.h"
#include "itkLinearInterpolateImageFunction.h"

#ifdef _OPENMP
#include <omp.h>
#endif

#include <limits>
#include <vector>
#include <map>
#include <string>

using namespace std;

typedef float m_sPixelType;
static const unsigned int m_uiDimensions = 3;
typedef itk::Image<m_sPixelType, m_uiDimensions> ImageType;

int main(int argc, char *argv[])
{
    if( argc < 6 )
    {
        cout << "Usage: " << argv[0] << " InputImage NumberOfImagesWanted AtlasBaseDirectory AtlasImageFilename AtlasID1 [AtlasID2 ... ]" << std::endl;
        cout << "       All images must have same resolution and reside in the same physical space." << std::endl;
        cout << "       Prints out ID's of the {NumberOfImagesWanted} atlas images most similar to the InputImage." << std::endl;
        return EXIT_FAILURE;
    }
    string kInputImage = argv[1];
    const int iNumberOfImagesWanted = atoi(argv[2]);
    string kAtlasBaseDirectory = argv[3];
    string kAtlasImgFilename = argv[4]; // image in nii format

    ImageType::RegionType kRegionToEvaluate;
    ImageType::IndexType kROICornerIndex;
    kROICornerIndex[0] = 49;
    kROICornerIndex[1] = 59;
    kROICornerIndex[2] = 35;
    ImageType::SizeType kROISize;
    kROISize[0] = 100;
    kROISize[1] = 100;
    kROISize[2] = 80;
    kRegionToEvaluate.SetIndex(kROICornerIndex);
    kRegionToEvaluate.SetSize(kROISize);

    typedef itk::ImageFileReader<ImageType> ReaderType;
    ReaderType::Pointer spReferenceImageReader = ReaderType::New();
    spReferenceImageReader->SetFileName( kInputImage );
    try
    {
        spReferenceImageReader->Update();
    }
    catch (itk::ExceptionObject& /*kExcp*/)
    {
        cerr << "File " << kInputImage << " not readable." << std::endl;
        return EXIT_FAILURE;
    }

    std::map<double, string> kSimilarityValueMap;
    try
    {
        //#pragma omp parallel for
        for (int i = 5; i < argc; ++i)
        {
            string kAtlasId = argv[i];
            string kAtlasImageFilename = kAtlasBaseDirectory + "/" + kAtlasId + string("/") + kAtlasImgFilename;

            ReaderType::Pointer spImageReader = ReaderType::New();
            spImageReader->SetFileName( kAtlasImageFilename );

            try
            {
                spImageReader->Update();
            }
            catch (itk::ExceptionObject& /*kExcp*/)
            {
                cerr << "Atlas image file " << kAtlasImageFilename << " not readable." << std::endl;
                continue;
            }

            typedef itk::NormalizedCorrelationImageToImageMetric<ImageType, ImageType> MetricType;
            //typedef itk::MutualInformationImageToImageMetric<ImageType, ImageType> MetricType;
            typedef itk::IdentityTransform< double, m_uiDimensions >  TransformType;
            MetricType::Pointer spMIMetric = MetricType::New();
            spMIMetric->SetFixedImage( spReferenceImageReader->GetOutput() );
            TransformType::Pointer spTransform = TransformType::New();
            TransformType::ParametersType params;
            spMIMetric->SetTransform( spTransform );
            //spMIMetric->SetFixedImageRegion( spReferenceImageReader->GetOutput()->GetLargestPossibleRegion());
            spMIMetric->SetFixedImageRegion(kRegionToEvaluate);

            typedef itk::LinearInterpolateImageFunction< ImageType, double > InterpolatorType;
            InterpolatorType::Pointer interpolator = InterpolatorType::New();
            spMIMetric->SetInterpolator( interpolator.GetPointer() );
            spMIMetric->SetMovingImage( spImageReader->GetOutput() );
            spMIMetric->Initialize();
            MetricType::MeasureType value = spMIMetric->GetValue(params);
            //std::cout << "Index " << i << " has metric value " << value << std::endl;

            // if there is already an image with the exact same similarity favor the first one
            while (kSimilarityValueMap.find(value) != kSimilarityValueMap.end())
            {
                value = value*0.999;
            }

            kSimilarityValueMap[value] = string(argv[i]);
        }
    }
    catch (itk::ExceptionObject& kExcp)
    {
        cerr << kExcp << std::endl;
        return EXIT_FAILURE;
    }

    std::map<double, string>::iterator kit = kSimilarityValueMap.begin();
    int iNumberOfImagesOutputted = 0;
    while(kit!=kSimilarityValueMap.end() && iNumberOfImagesOutputted<iNumberOfImagesWanted)
    {
        cout << kit->second << " " << flush;
        kit++;
        iNumberOfImagesOutputted++;
    }

    return EXIT_SUCCESS;
}
