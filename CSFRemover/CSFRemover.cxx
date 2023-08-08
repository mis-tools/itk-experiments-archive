#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkLabelStatisticsImageFilter.h"
#include "itkMultiplyImageFilter.h"
#include "itkLabelImageToLabelMapFilter.h"
#include "itkImageRegionIteratorWithIndex.h"

#include <limits>

using namespace std;

typedef unsigned short					  m_sPixelType;
static const unsigned int				  m_uiDimensions = 3; 
static const int						  m_iBrainMaskLabel = 1;
static const float						  m_fPercentile = 0.25f;
typedef itk::Image<m_sPixelType, m_uiDimensions> ImageType;

int main(int argc, char *argv[])
{
	if( argc != 5 )
	{
		cout << "Usage: CSFRemover MRImage LabelMaskImage BrainMaskImage OutputMaskImage" << std::endl;
		return EXIT_FAILURE;
	}

	typedef itk::ImageFileReader<ImageType> ReaderType;
	ReaderType::Pointer mrImageReader = ReaderType::New();
	mrImageReader->SetFileName( argv[1] );

	ReaderType::Pointer maskReader = ReaderType::New();
	maskReader->SetFileName( argv[2] );
	ReaderType::Pointer brainMaskReader = ReaderType::New();
	brainMaskReader->SetFileName( argv[3] );

	try
	{
		mrImageReader->Update();
		maskReader->Update();
		brainMaskReader->Update();
	}
	catch (itk::ExceptionObject& kExcp)
	{
		cerr << kExcp << std::endl;
		return EXIT_FAILURE;
	}


	// Filter image with brainmask and compute histograms
	typedef itk::LabelStatisticsImageFilter< ImageType, ImageType > LabelStatisticsImageFilterType;
	LabelStatisticsImageFilterType::Pointer labelStatisticsImageFilter = LabelStatisticsImageFilterType::New();
	labelStatisticsImageFilter->UseHistogramsOn();
	labelStatisticsImageFilter->SetLabelInput( brainMaskReader->GetOutput() );
	labelStatisticsImageFilter->SetInput( mrImageReader->GetOutput() );
	labelStatisticsImageFilter->Update();

	// Get the smallest 25 percentile value in the brainmasked area of the mrimage
	std::cout << "Number of labels: " << labelStatisticsImageFilter->GetNumberOfLabels() << std::endl;
	std::cout << std::endl;

	typedef LabelStatisticsImageFilterType::ValidLabelValuesContainerType ValidLabelValuesType;
	typedef LabelStatisticsImageFilterType::LabelPixelType                LabelPixelType;

	double quantile = 0;
	if ( labelStatisticsImageFilter->HasLabel( m_iBrainMaskLabel ) )
	{
		LabelStatisticsImageFilterType::HistogramPointer histogram = labelStatisticsImageFilter->GetHistogram( m_iBrainMaskLabel );
		quantile = histogram->Quantile(0, m_fPercentile);
	}
	else
	{
		cout << "The brainmasked image does not contain label " << m_iBrainMaskLabel << " exiting program." << endl; 
		return EXIT_FAILURE;
	}

	// Binary thresshold MR image by 25 % percentile value
	typedef itk::BinaryThresholdImageFilter <ImageType, ImageType>
		BinaryThresholdImageFilterType;
	BinaryThresholdImageFilterType::Pointer thresholdFilter
		= BinaryThresholdImageFilterType::New();
	thresholdFilter->SetInput( mrImageReader->GetOutput() );
	thresholdFilter->SetLowerThreshold( quantile );
	thresholdFilter->SetUpperThreshold( std::numeric_limits<unsigned short>::max() );
	thresholdFilter->SetInsideValue( 1 );
	thresholdFilter->SetOutsideValue( 0 );
	thresholdFilter->Update();
	/*
	// Mask out the ventricles (4 and 43)
	typedef itk::LabelImageToLabelMapFilter <ImageType>
	LabelImageToLabelMapFilterType;
	LabelImageToLabelMapFilterType::Pointer labelImageToLabelMapFilter
	= LabelImageToLabelMapFilterType::New ();
	labelImageToLabelMapFilter->SetInput(maskReader->GetOutput());
	labelImageToLabelMapFilter->Update();

	labelImageToLabelMapFilter->GetOutput() 
	*/
	//Make sure the ventricles are not erased by masking them in
	ImageType::Pointer spCSFEstimateImage = thresholdFilter->GetOutput();

	ImageType::Pointer spLabelImage = maskReader->GetOutput();
	itk::ImageRegionIteratorWithIndex<ImageType> imageIterator(spCSFEstimateImage, spCSFEstimateImage->GetLargestPossibleRegion());
	while(!imageIterator.IsAtEnd())
	{
		unsigned short usLabelValue = spLabelImage->GetPixel(imageIterator.GetIndex());

		// here label values for the ventricles have been hardcoded
		if (usLabelValue == 4 || usLabelValue == 43)
		{
			if (imageIterator.Get() == 0)
			{
				imageIterator.Set(1);
			}
			else
			{
				 spLabelImage->SetPixel(imageIterator.GetIndex(), 255);
			}

			imageIterator.Set(1);
		} 

		++imageIterator;
	}

	spLabelImage->Update();
	spCSFEstimateImage->Update();

	// Multiply thressholded MR and segmentation masks
	typedef itk::MultiplyImageFilter <ImageType, ImageType >
		MultiplyImageFilterType;
	MultiplyImageFilterType::Pointer multiplyFilter
		= MultiplyImageFilterType::New ();
	multiplyFilter->SetInput1(spLabelImage);
	multiplyFilter->SetInput2(spCSFEstimateImage);
	multiplyFilter->Update();

	// Output masked segmentation masks :-)
	typedef  itk::ImageFileWriter< ImageType  > WriterType;
	WriterType::Pointer writer = WriterType::New();
	writer->SetFileName(argv[4]);
	writer->SetInput(multiplyFilter->GetOutput());
	writer->Update();

	return EXIT_SUCCESS;
}