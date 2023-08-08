#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkLabelStatisticsImageFilter.h"
#include "itkMultiplyImageFilter.h"
#include "itkLabelImageToLabelMapFilter.h"
#include "itkImageRegionIteratorWithIndex.h"

#include <limits>

#include <vector>

using namespace std;

typedef unsigned short					  m_sPixelType;
static const unsigned int				  m_uiDimensions = 3; 
typedef itk::Image<m_sPixelType, m_uiDimensions> ImageType;

const unsigned short cusCSF = 1;
const unsigned short cusGM = 2;
const unsigned short cusWM = 3;

int main(int argc, char *argv[])
{
	if( argc != 4 )
	{
		cout << "Usage: ClassificationCleaner LabelMaskImage TissueClassificationImage OutputMaskImage" << std::endl;
		return EXIT_FAILURE;
	}

	//XXXXXXXXXX TODO Check that sizes of images agree!!!!!!

	typedef itk::ImageFileReader<ImageType> ReaderType;

	ReaderType::Pointer spLabelMapReader = ReaderType::New();
	spLabelMapReader->SetFileName( argv[1] );
	ReaderType::Pointer spClassificationImageReader = ReaderType::New();
	spClassificationImageReader->SetFileName( argv[2] );

	try
	{
		spLabelMapReader->Update();
		spClassificationImageReader->Update();
	}
	catch (itk::ExceptionObject& kExcp)
	{
		cerr << kExcp << std::endl;
		return EXIT_FAILURE;
	}

	//XXXXX TODO these should be read from command line or a configuration file!
	std::vector<int> kLabelsOnlyInCSFSegment;
	kLabelsOnlyInCSFSegment.push_back(4);
	kLabelsOnlyInCSFSegment.push_back(43);

	std::vector<int> kLabelsOnlyInGMSegment;
	kLabelsOnlyInGMSegment.push_back(17);
	kLabelsOnlyInGMSegment.push_back(53);


	ImageType::Pointer spLabelImage = spLabelMapReader->GetOutput();
	itk::ImageRegionIteratorWithIndex<ImageType> imageIterator(spLabelImage, spLabelImage->GetLargestPossibleRegion());
	while(!imageIterator.IsAtEnd())
	{
		unsigned short usLabelValue = imageIterator.Get();
		unsigned short usClassificationValue = spClassificationImageReader->GetOutput()->GetPixel(imageIterator.GetIndex());

		for ( unsigned int iIndex = 0; iIndex < kLabelsOnlyInGMSegment.size(); ++iIndex )
		{
			if (usLabelValue == kLabelsOnlyInGMSegment[iIndex])
			{
				if (usClassificationValue != cusGM)				
				{
					imageIterator.Set(255);
				}
			}
		}

		bool bCurrentLabelCanBeCSFRemoved = true;

		for ( unsigned int iIndex = 0; iIndex < kLabelsOnlyInCSFSegment.size(); ++iIndex )
		{
			if (usLabelValue == kLabelsOnlyInCSFSegment[iIndex])
			{
				if (usClassificationValue != cusCSF)		
				{
					imageIterator.Set(255);
				}

				bCurrentLabelCanBeCSFRemoved = false;
			}
		}

		if ( bCurrentLabelCanBeCSFRemoved && (usClassificationValue == cusCSF || usClassificationValue == 0))
		{
			// remove CSF and background pixels from all segments that are not supposed to be in CSF
			imageIterator.Set(0);
		}

		++imageIterator;
	}

	spLabelImage->Update();

	// Output masked segmentation masks :-)
	typedef  itk::ImageFileWriter< ImageType  > WriterType;
	WriterType::Pointer writer = WriterType::New();
	writer->SetFileName(argv[3]);
	writer->SetInput(spLabelImage);
	writer->Update();

	return EXIT_SUCCESS;
}