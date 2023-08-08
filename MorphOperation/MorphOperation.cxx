#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkErodeObjectMorphologyImageFilter.h"
#include "itkDilateObjectMorphologyImageFilter.h"
#include "itkLabelImageToLabelMapFilter.h"
#include "itkLabelMapToLabelImageFilter.h"
#include "itkBinaryBallStructuringElement.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkMaximumImageFilter.h"
#include "itkBinaryMorphologicalClosingImageFilter.h"
#include "itkBinaryMorphologicalOpeningImageFilter.h"

#include <limits>
#ifdef _WIN32
	#include "../util/XGetopt.h"
#else
	#include <ctype.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
#endif

using namespace std;

typedef unsigned short					  m_sPixelType;
static const unsigned int				  m_uiDimensions = 3; 
static const unsigned int				  m_uiBrainID = 255;
typedef itk::Image<m_sPixelType, m_uiDimensions> ImageType;

int main(int argc, char *argv[])
{
	if( argc < 3 )
	{
		cout << "Usage: MorphOperation [-r radius] [-o morph_opening_segmentID] [-c morph_close_segmentID] LabelMaskImage OutputImage" << std::endl;
		return EXIT_FAILURE;
	}

	unsigned int radius = 2;
	unsigned int segment = 0;
	char *cvalue = NULL;
	set<unsigned int> closingSegments;
	set<unsigned int> openingSegments;
	int index;
	int c;
	int opterr = 0;
	while ((c = getopt (argc, argv, "r:c:o:")) != -1)
	{
		std::stringstream ss(optarg);
		switch (c)
		{
			case 'r':
				ss >> radius;
				break;
			case 'o':
				ss >> segment;
				openingSegments.insert(segment);
				break;
			case 'c':
				ss >> segment;
				closingSegments.insert(segment);
				break;				
			default:
				abort ();
		}
	}

	typedef itk::ImageFileReader<ImageType> ReaderType;
	ReaderType::Pointer maskReader = ReaderType::New();
	maskReader->SetFileName( argv[optind] );

	try
	{
		maskReader->Update();
	}
	catch (itk::ExceptionObject& kExcp)
	{
		cerr << kExcp << std::endl;
		return EXIT_FAILURE;
	}

	typedef itk::BinaryThresholdImageFilter<ImageType, ImageType> BinaryThresholdImageFilter;
	BinaryThresholdImageFilter::Pointer thresholdFilter = BinaryThresholdImageFilter::New();
	thresholdFilter->SetInput( maskReader->GetOutput() );
	thresholdFilter->SetUpperThreshold(m_uiBrainID);
	thresholdFilter->SetLowerThreshold(1);
	thresholdFilter->SetInsideValue(m_uiBrainID);
	thresholdFilter->SetOutsideValue(0);
	thresholdFilter->Update();
	ImageType::Pointer image = thresholdFilter->GetOutput();

    typedef itk::LabelImageToLabelMapFilter<ImageType> LabelImageToLabelMapFilterType;
    LabelImageToLabelMapFilterType::Pointer labelImageToLabelMapFilter = LabelImageToLabelMapFilterType::New();
    labelImageToLabelMapFilter->SetInput( maskReader->GetOutput() );
    labelImageToLabelMapFilter->Update();
	
	std::cout << "Radius: " << radius << std::endl;
    typedef itk::BinaryBallStructuringElement<ImageType::PixelType, ImageType::ImageDimension> StructuringElementType;
    StructuringElementType structuringElement;
    structuringElement.SetRadius(radius);
    structuringElement.CreateStructuringElement();
	
	typedef itk::BinaryMorphologicalClosingImageFilter<ImageType, ImageType, StructuringElementType> BinaryMorphologicalClosingImageFilter;
	BinaryMorphologicalClosingImageFilter::Pointer closingFilter = BinaryMorphologicalClosingImageFilter::New();
	
	typedef itk::BinaryMorphologicalOpeningImageFilter<ImageType, ImageType, StructuringElementType> BinaryMorphologicalOpeningImageFilter;
	BinaryMorphologicalOpeningImageFilter::Pointer openingFilter = BinaryMorphologicalOpeningImageFilter::New();
	
	typedef  itk::ImageFileWriter< ImageType  > WriterType;
	WriterType::Pointer writer = WriterType::New();
	
	for(unsigned int i = 0; i < labelImageToLabelMapFilter->GetOutput()->GetNumberOfLabelObjects(); ++i)
	{
		LabelImageToLabelMapFilterType::OutputImageType::LabelObjectType* labelObject = 
			labelImageToLabelMapFilter->GetOutput()->GetNthLabelObject(i);
		
		const unsigned int label = labelObject->GetLabel();
		
		if (label == m_uiBrainID)
			continue;

		ImageType::Pointer img = maskReader->GetOutput();
		
		// Morph opening
		if (openingSegments.find(label) != openingSegments.end())
		{
			std::cout << "Morphological opening " << label << std::endl;
			openingFilter->SetInput( img );
			openingFilter->SetKernel(structuringElement);
			openingFilter->SetForegroundValue(label);
			openingFilter->Update();
			img = openingFilter->GetOutput();
		}
		
		// Morph closing
		if (closingSegments.find(label) != closingSegments.end())
		{
			std::cout << "Morphological closing " << label << std::endl;
			closingFilter->SetInput( img );
			closingFilter->SetKernel(structuringElement);
			closingFilter->SetForegroundValue(label);
			closingFilter->Update();
			img = closingFilter->GetOutput();
		}

		// Copy Label over
		std::cout << "Copying " << label << std::endl;
		itk::ImageRegionConstIterator<ImageType>  it( img, img->GetRequestedRegion() );
		itk::ImageRegionIterator<ImageType>  it2( image, image->GetRequestedRegion() );
		while (!it.IsAtEnd())
		{
			if (it.Get() == label)
			{
				it2.Set( label );			
			}
			++it2;
			++it;
		}
	}
 	  
	// Output morphed masks
	writer->SetFileName(argv[optind + 1]);
	writer->SetInput(image);
	writer->Update();

	return EXIT_SUCCESS;
}